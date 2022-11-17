// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemOnGround.h"

#include "DataTableTool.h"
#include "FileTool.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AItemOnGround::AItemOnGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Collision = CreateDefaultSubobject<USphereComponent>(FName("Collision"));
	RootComponent = Collision;

	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetSimulatePhysics(true);
	Collision->SetNotifyRigidBodyCollision(true);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	FBodyInstance * RootBI = Collision->GetBodyInstance(NAME_None, false);;
	RootBI->bLockXRotation = true;
	RootBI->bLockYRotation = true;
	RootBI->bLockZRotation = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	ItemMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComp"));
	WidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	WidgetComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WidgetComp->SetDrawAtDesiredSize(true);
	WidgetComp->SetRelativeLocation(FVector(0, 0, 64));
	WidgetComp->SetPivot(FVector2D(0.5f,1.0f));

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AItemOnGround::OnItemOnGroundBeginOverlap);
	Collision->OnComponentHit.AddDynamic(this, &AItemOnGround::OnHitGround);
}

// Called when the game starts or when spawned
void AItemOnGround::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemOnGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemOnGround::Init(FName Index)
{
	this->ItemIndex = Index;
	UpdateDisplay(Index);
}

void AItemOnGround::UpdateDisplay(FName Index)
{
	auto ItemOnGroundData = FGameSaveTool::GetItemOnGroundDataByIndex(Index);
	auto ItemOnGroundAttr = FDataTableTool::GetItemOnGroundAttr(IntToName(ItemOnGroundData.ID));

	ADataAssetMananger::RequestAsyncLoadObject(
		this,
		ItemOnGroundAttr->MeshName,
		[this](UObject *Asset)
		{
			this->ItemMesh->SetStaticMesh(Cast<UStaticMesh>(Asset));
		}
	);
}

void AItemOnGround::OnItemOnGroundBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                               UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult &SweepResult)
{
}

void AItemOnGround::OnHitGround(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp,
	FVector NormalImpulse, const FHitResult &Hit)
{
}

void AItemOnGround::Enter(AActor *User)
{
	
	auto *Controller = Cast<APawn>(User)->Controller;

	if (IsValid(Controller) && Controller->IsPlayerController() && WidgetComp->GetUserWidgetObject() == nullptr)
	{
		auto ItemOnGroundData = FGameSaveTool::GetItemOnGroundDataByIndex(ItemIndex);
		
		auto ItemOnGroundAttr = FDataTableTool::GetItemOnGroundAttr(IntToName(ItemOnGroundData.ID));
		
		auto *TipBorderWidgetClass = ADataAssetMananger::RequestSyncLoadClass(this, ItemOnGroundAttr->TipBorderWidgetClass);

		// alternative option, 
		// WidgetComp->SetWidgetClass(TipBorderWidgetClass);
		auto *TipBorderWidget = CreateWidget<UUserWidget>(Cast<APlayerController>(Controller), TipBorderWidgetClass);
		
		WidgetComp->SetWidget(TipBorderWidget);

		// init the item description ui
		auto *InitFuncPtr = TipBorderWidget->FindFunction(FName("Init"));
		if (InitFuncPtr)
		{
			TipBorderWidget->ProcessEvent(InitFuncPtr, nullptr);
		}
	}
	else
	{
		WidgetComp->SetVisibility(true);
	}
}

void AItemOnGround::Exit(AActor *User)
{
	auto *Controller = Cast<APawn>(User)->Controller;
	if (IsValid(Controller) && Controller->IsPlayerController() && WidgetComp->IsVisible())
	{
		WidgetComp->SetVisibility(false);
	}
}

void AItemOnGround::StayTick(AActor *User, float DeltaTime)
{
	ItemMesh->AddRelativeRotation(FRotator(0,0,20));
	
	auto *Controller = Cast<APawn>(User)->Controller;
	if (IsValid(Controller) && Controller->IsPlayerController())
	{
		auto PC = Cast<APlayerController>(Controller);
		
		// get the camera rotation, reverse it and assign to WidgetComp
		WidgetComp->SetWorldRotation((-PC->PlayerCameraManager->GetCameraRotation().Vector()).Rotation());
	}
}

void AItemOnGround::BeginInteraction(AActor *User, UInteractiveComp *InteractiveComponent)
{
	UKismetSystemLibrary::PrintString(nullptr, this->GetName() + "BeginInteractive");
}

void AItemOnGround::EndInteraction(AActor *User)
{
	UKismetSystemLibrary::PrintString(nullptr, this->GetName() + "EndInteractive");
}

void AItemOnGround::InteractionTick(AActor *User, float DeltaTime, UInteractiveComp *InteractiveComponent)
{
	// UKismetSystemLibrary::PrintString(nullptr, this->GetName() + "InteractiveTick");
}




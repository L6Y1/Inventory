// Copyright Epic Games, Inc. All Rights Reserved.

#include "Inventory07GameMode.h"

#include "DataTableTool.h"
#include "FileTool.h"
#include "InventoryPlayerController.h"
#include "DataAssetMananger/DataAssetMananger.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#include "GlobalEventManager/GlobalEventManager.h"
#include "Kismet/GameplayStatics.h"

AInventory07GameMode::AInventory07GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Blueprints/BP_InventoryCharacter.BP_InventoryCharacter_C'"));
	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerControllerClass = AInventoryPlayerController::StaticClass();
	
	FGlobalEventManager::RegisterEvent(FName("EndPickupItemFromGroundEvent"), this, FName("EndPickupItemFromGround"));
	// FGlobalEventManager::RegisterEvent(FName("SpawnItemOnGroundEvent"), this, FName("SpawnItemOnGround"));

}

void AInventory07GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// create items on ground
	auto ItemOnGroundDatas = FGameSaveTool::GetItemOnGroundDatas();
	for (auto KeyValuePair : ItemOnGroundDatas)
	{
		auto ItemOnGroundData = KeyValuePair.Value;
		auto ItemOnGroundAttr = FDataTableTool::GetItemOnGroundAttr(IntToName(ItemOnGroundData.ID));
		
		UClass *ItemOnGroundClass = ADataAssetMananger::RequestSyncLoadClass(this, ItemOnGroundAttr->ActorType); 
		checkf(ItemOnGroundClass, TEXT("Class Not Found"))
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(ItemOnGroundData.Location);
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		auto ItemOnGround = GetWorld()->SpawnActor<AActor>(ItemOnGroundClass, SpawnTransform, Params);

		auto InitFuncPtr = ItemOnGround->FindFunction(FName("Init"));
		if (InitFuncPtr)
		{
			ItemOnGround->ProcessEvent(InitFuncPtr, &ItemOnGroundData.Index);
		}
	}
}

void AInventory07GameMode::EndPickupItemFromGround(int RemainAmount, FName Index, FVector NewLocation)
{
	
	// if the item on ground not fully picked up
	if (RemainAmount > 0)
	{
		auto ItemOnGroundData = FGameSaveTool::GetItemOnGroundDataByIndex(Index);
		ItemOnGroundData.Location = NewLocation;
		ItemOnGroundData.Num = RemainAmount;

		FGameSaveTool::SetItemOnGroundDataByIndex(ItemOnGroundData, Index);
	}
	else
	{
		FGameSaveTool::RemoveItemOnGroundDataByIndex(Index);
	}

	FGlobalEventManager::TriggerEvent(FName("UpdateItemOnGroundEvent"), &Index);
}

void AInventory07GameMode::SpawnItemOnGround(int ID, int Num, FVector Location)
{
	FName NewIndex = FName("default_name");
	FItemOnGroundData NewItemData(NewIndex, Location, ID, Num);
	FGameSaveTool::AddItemOnGroundData(NewIndex, NewItemData);

	auto ItemOnGroundAttr = FDataTableTool::GetItemOnGroundAttr(IntToName(ID));
		
	UClass *ItemOnGroundClass = ADataAssetMananger::RequestSyncLoadClass(this, ItemOnGroundAttr->ActorType); 
	checkf(ItemOnGroundClass, TEXT("Class Not Found"))
		
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Location);
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto ItemOnGround = GetWorld()->SpawnActor<AActor>(ItemOnGroundClass, SpawnTransform, Params);

	auto InitFuncPtr = ItemOnGround->FindFunction(FName("Init"));
	if (InitFuncPtr)
	{
		ItemOnGround->ProcessEvent(InitFuncPtr, &NewIndex);
	}
}
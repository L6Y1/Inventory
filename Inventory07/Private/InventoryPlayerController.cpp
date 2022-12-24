// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/PlayerInput.h"

AInventoryPlayerController::AInventoryPlayerController()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainWidgetClassFinder(TEXT("WidgetBlueprint'/Game/Blueprints/BP_MainUI.BP_MainUI_C'"));
	if (MainWidgetClassFinder.Succeeded())
	{
		WidClass = MainWidgetClassFinder.Class;
	}
}

void AInventoryPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// MainUIWidget = CreateWidget(this, WidClass);
	// MainUIWidget->AddToViewport();
	// auto InputMode = FInputModeGameAndUI();
	// this->SetInputMode(InputMode);
	// this->SetShowMouseCursor(true);
}

void AInventoryPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("ShowMouseCursor", EKeys::Tab));
	InputComponent->BindAction("ShowMouseCursor", EInputEvent::IE_Pressed, this, &AInventoryPlayerController::ToggleMainUI);

}

void AInventoryPlayerController::ToggleMainUI()
{
	if (MainUIWidget != nullptr)
	{
		FadeUI();
	}
	else
	{
		ShowUI();
	}
}

void AInventoryPlayerController::ShowUI()
{
	
	MainUIWidget = CreateWidget(this, WidClass);
	MainUIWidget->AddToViewport();
	auto InputMode = FInputModeGameAndUI();
	this->SetInputMode(InputMode);
	this->SetShowMouseCursor(true);
}

void AInventoryPlayerController::FadeUI()
{
	this->SetInputMode(FInputModeGameOnly());
	this->SetShowMouseCursor(false);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	MainUIWidget = nullptr;
}

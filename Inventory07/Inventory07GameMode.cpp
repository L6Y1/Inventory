// Copyright Epic Games, Inc. All Rights Reserved.

#include "Inventory07GameMode.h"

#include "FileTool.h"
#include "Inventory07Character.h"
#include "InventoryPlayerController.h"
#include "DataAssetMananger/DataAssetMananger.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#include "Kismet/KismetSystemLibrary.h"

AInventory07GameMode::AInventory07GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C'"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerControllerClass = AInventoryPlayerController::StaticClass();

	
}

void AInventory07GameMode::BeginPlay()
{
	Super::BeginPlay();
	auto ItemOnGroundDatas = FGameSaveTool::GetItemOnGroundDatas();
	for (auto KeyValuePair : ItemOnGroundDatas)
	{
		auto ItemOnGroundData = KeyValuePair.Value;

		// TODO: asset table 
		// UClass *ItemOnGroundClass = ADataAssetMananger::RequestSyncLoadClass(this, FName("")); 
		//
		// checkf(ItemOnGroundClass, TEXT("Class Not Found"));
		// FTransform SpawnTransform;
		// SpawnTransform.SetLocation(ItemOnGroundData.Location);
	}
}

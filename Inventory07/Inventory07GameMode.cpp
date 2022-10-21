// Copyright Epic Games, Inc. All Rights Reserved.

#include "Inventory07GameMode.h"
#include "Inventory07Character.h"
#include "InventoryPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

AInventory07GameMode::AInventory07GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerControllerClass = AInventoryPlayerController::StaticClass();
	
}

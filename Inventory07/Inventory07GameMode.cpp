// Copyright Epic Games, Inc. All Rights Reserved.

#include "Inventory07GameMode.h"
#include "Inventory07Character.h"
#include "UObject/ConstructorHelpers.h"

AInventory07GameMode::AInventory07GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

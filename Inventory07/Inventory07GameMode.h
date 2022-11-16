// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Inventory07GameMode.generated.h"

UCLASS(minimalapi)
class AInventory07GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInventory07GameMode();
	virtual void BeginPlay() override;
};




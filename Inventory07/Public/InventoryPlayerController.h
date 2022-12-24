// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InventoryPlayerController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class INVENTORY07_API AInventoryPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	AInventoryPlayerController();
	
public:
	UClass *WidClass;

	UUserWidget *MainUIWidget;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void ToggleMainUI();
	void ShowUI();
	void FadeUI();
	
};

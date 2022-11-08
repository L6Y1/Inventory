// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BagWidgetType1.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY07_API UBagWidgetType1 : public UUserWidget
{
	GENERATED_BODY()

public:

	
	UFUNCTION()
	void Init(FName SkinType);
};

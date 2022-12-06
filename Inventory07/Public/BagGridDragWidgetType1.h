// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BagGridDragWidgetType1.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UBagGridDragWidgetType1 : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(meta=(BindWidget))
	UImage *ItemImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *ItemNum;

	UFUNCTION()
	void Init(FName ItemName, int Num, bool ShowNum);
	
};

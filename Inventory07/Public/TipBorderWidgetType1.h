// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TipBorderWidgetType1.generated.h"

class UHorizontalBox;
class UVerticalBox;
class UTextBlock;
class UBorder;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UTipBorderWidgetType1 : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(meta=(BindWidget))
	UBorder *TipBGBorder;

	UPROPERTY(meta=(BindWidget))
	UBorder *ItemTitleBGBorder;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *ItemNameText;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox *TipContextWidgetPanel;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *ItemNumText;
	
	UFUNCTION()
	void Init(int ID, int Num, int ActionType);

	UFUNCTION()
	void UpdateDisplay(int ID, int Num, int ActionType);
};

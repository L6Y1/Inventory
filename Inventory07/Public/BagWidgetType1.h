// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BagWidgetType1.generated.h"

class UGridPanel;
class UWrapBox;
class UButton;
class UTextBlock;
class UImage;
class UBorder;
class USizeBox;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UBagWidgetType1 : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta=(BindWidget), EditAnywhere)
	USizeBox *BagSizeBox;
	
	UPROPERTY(meta=(BindWidget), EditAnywhere)
	UBorder *BagBorder;

	UPROPERTY(meta=(BindWidget), EditAnywhere)
	UImage *TitleImage;

	UPROPERTY(meta=(BindWidget), EditAnywhere)
	UTextBlock *TitleText;
	
	UPROPERTY(meta=(BindWidget), EditAnywhere)
	UButton *ExitButton;
	
	UPROPERTY(meta=(BindWidget), EditAnywhere)
	UButton *SortButton;

	UPROPERTY(meta=(BindWidget), EditAnywhere)
	UWrapBox *BagGridPanel;	// although named as 'GridPanel', it is a UWrapBox
	


	UFUNCTION()
	void OnExitButtonClicked();
	
	UFUNCTION()
	void Init(FName SkinType, UUserWidget *Owner, FName CloseFunName);

	UFUNCTION()
	void UnInit(UUserWidget *Owner);
};

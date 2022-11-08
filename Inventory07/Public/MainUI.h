// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

class UHorizontalBox;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UMainUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// equal to BeginPlay()
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox *NavButtonPanel;

	UPROPERTY(meta=(BindWidget))
	UNamedSlot *BagWidgetSlot;

	UUserWidget *BagWidget;

	void OpenBagWidget(FName ToggledWidgetLayoutType);
	void CloseBagWidget();
	
	UFUNCTION()
	void ToggleBagWidgetEvent(FName ToggledWidgetLayoutType);
	UFUNCTION()
	void ToggleSettingWidgetEvent(FName ToggledWidgetLayoutType);
	UFUNCTION()
	void ToggleShopWidgetEvent(FName ToggledWidgetLayoutType);
};

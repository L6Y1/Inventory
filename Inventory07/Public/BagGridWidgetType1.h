// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BagGridWidgetType1.generated.h"

class UTextBlock;
class UImage;
class UBorder;
class USizeBox;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UBagGridWidgetType1 : public UUserWidget
{
	GENERATED_BODY()

private:
	int GridIndex;

public:
	UPROPERTY(meta=(BindWidget))
	USizeBox *GridSizeBox;

	UPROPERTY(meta=(BindWidget))
	UBorder *BgBorder;

	UPROPERTY(meta=(BindWidget))
	UImage *SelectImage;

	UPROPERTY(meta=(BindWidget))
	UBorder *ItemBorder;

	UPROPERTY(meta=(BindWidget))
	UImage *ItemImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *ItemNumText;

	UPROPERTY(meta=(BindWidget))
	UImage *DotImage;

	// 'Transient' means the property cannot be serialized/deserialized and save to disk 
	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation *ZoomAnimation;
	
	virtual void NativeOnMouseEnter(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent &InMouseEvent) override;

	
	UFUNCTION()
	void Init(int Index);

	void UpdateDisplay(int Index);
};

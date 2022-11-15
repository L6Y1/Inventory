// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
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

protected:
	virtual void NativeOnMouseEnter(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent &InMouseEvent) override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION()
	void OnViewBagGridItemFinished(int ID);
	
	UFUNCTION()
	void OnViewBagGridItemFinished2(int ID);
	
	UFUNCTION()
	void Init(int Index);

	UFUNCTION()
	void UpdateDisplay(int Index);
	
	UFUNCTION()
	void PlayZoomAnimation(int Index);
};

inline void UBagGridWidgetType1::OnViewBagGridItemFinished2(int ID)
{
	UKismetSystemLibrary::PrintString(nullptr, "Test func testtest");
}

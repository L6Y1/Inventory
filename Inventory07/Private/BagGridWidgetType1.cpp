// Fill out your copyright notice in the Description page of Project Settings.


#include "BagGridWidgetType1.h"

#include "DataTableTool.h"
#include "FileTool.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"
#include "Kismet/KismetSystemLibrary.h"

void UBagGridWidgetType1::NativeOnMouseEnter(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	FBagGridData BagGridData = FGameSaveTool::GetBagGridDataByIndex(GridIndex);
	if (!BagGridData.ID == 0)
	{
		SelectImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		this->PlayAnimation(ZoomAnimation);
	}
}

void UBagGridWidgetType1::NativeOnMouseLeave(const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	FBagGridData BagGridData = FGameSaveTool::GetBagGridDataByIndex(GridIndex);
	if (!BagGridData.ID == 0)
	{
		SelectImage->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBagGridWidgetType1::Init(int Index)
{
	this->GridIndex = Index;
	UpdateDisplay(Index);
}

void UBagGridWidgetType1::UpdateDisplay(int Index)
{
	auto BagGridData = FGameSaveTool::GetBagGridDataByIndex(Index);
	
	
	auto ItemInBagGridAttr =
		FDataTableTool::GetItemInBagGridAttr(FName(FString::FromInt(BagGridData.ID)));
	

	// set num text and text color accordingly
	if (ItemInBagGridAttr->bIsShowNum)
	{
		ItemNumText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemNumText->SetText(FText::FromString(FString::FromInt(BagGridData.Num)));
		
		ItemInBagGridAttr->MaxStackNum == BagGridData.Num ?
			ItemNumText->SetColorAndOpacity(FLinearColor::Red) :
				ItemNumText->SetColorAndOpacity(FLinearColor::White);
	}
	else
	{
		ItemNumText->SetVisibility(ESlateVisibility::Collapsed);
	}

	ADataAssetMananger::RequestAsyncLoadObjects(
		this,
		{
			ItemInBagGridAttr->BGImage,
			ItemInBagGridAttr->ItemBorderImage
		},
		[this](TArray<UObject*> Assets)
		{
			BgBorder->SetBrushFromTexture(Cast<UTexture2D>(Assets[0]));
			ItemBorder->SetBrushFromTexture(Cast<UTexture2D>(Assets[1]));
		}
	);

	ItemImage->SetVisibility(BagGridData.ID != 0 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	if (BagGridData.ID != 0)
	{
		ADataAssetMananger::RequestAsyncLoadObject(
		this,
		ItemInBagGridAttr->ItemImage,
		[this](UObject* Asset)
			{
				ItemImage->SetBrushFromTexture(Cast<UTexture2D>(Asset));
			}
		);
	}
	
	
	 DotImage->SetVisibility((BagGridData.ID == 0 || FGameSaveTool::IsBagHadItem(BagGridData.ID)) ?
	 	ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
}

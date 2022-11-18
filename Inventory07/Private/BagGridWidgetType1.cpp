// Fill out your copyright notice in the Description page of Project Settings.


#include "BagGridWidgetType1.h"

#include "DataTableTool.h"
#include "FileTool.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"
#include "Inventory07/GlobalEventManager/GlobalEventManager.h"
#include "Kismet/KismetSystemLibrary.h"

void UBagGridWidgetType1::NativeOnMouseEnter(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	FBagGridData BagGridData = FGameSaveTool::GetBagGridDataByIndex(GridIndex);
	if (!BagGridData.ID == 0)
	{
		SelectImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		this->PlayAnimation(ZoomAnimation);

		FGlobalEventManager::TriggerEvent(FName("InspectBagGridItemEvent"), &GridIndex);

		auto ItemInBagGridAttr = FDataTableTool::GetItemInBagGridAttr(IntToName(BagGridData.ID));
		auto TipBorderWidgetClass = ADataAssetMananger::RequestSyncLoadClass(this, ItemInBagGridAttr->TipBorderWidgetClass);
		auto TipBorderWidget = CreateWidget<UUserWidget>(this->GetOwningPlayer(), TipBorderWidgetClass);
		check(TipBorderWidget);
		
		ItemImage->SetToolTip(TipBorderWidget);

		auto *InitFuncPtr = TipBorderWidget->FindFunction(FName("Init"));
		if (InitFuncPtr)
		{
			struct
			{
				int ID;
				int Num;
				int ActionType;
			} Params;
			Params.ID = BagGridData.ID;
			Params.Num = BagGridData.Num;
			Params.ActionType = 0; // 0 for item in bag grid
			
			TipBorderWidget->ProcessEvent(InitFuncPtr, &Params);
		}
	}

	
	
}

void UBagGridWidgetType1::NativeOnMouseLeave(const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	FBagGridData BagGridData = FGameSaveTool::GetBagGridDataByIndex(GridIndex);
	if (!BagGridData.ID == 0)
	{
		SelectImage->SetVisibility(ESlateVisibility::Collapsed);
		ItemImage->ToolTipWidget->RemoveFromParent();
	}
}

void UBagGridWidgetType1::NativeConstruct()
{
	Super::NativeConstruct();
	FGlobalEventManager::RegisterEvent(FName("ViewBagGridItemFinishedEvent"), this, FName("OnViewBagGridItemFinished"));
	// FGlobalEventManager::RegisterEvent(FName("ViewBagGridItemFinishedEvent"), this, FName("OnViewBagGridItemFinished2"));
	

	FGlobalEventManager::RegisterEvent(FName("AddItemOnBagGridEvent"), this, FName("UpdateDisplay"));
	FGlobalEventManager::RegisterEvent(FName("AddItemOnBagGridEvent"), this, FName("PlayZoomAnimation"));
	
	FGlobalEventManager::RegisterEvent(FName("SubItemOnBagGridEvent"), this, FName("UpdateDisplay"));
	
	FGlobalEventManager::RegisterEvent(FName("SortCompleteEvent"), this, FName("UpdateDisplay2"));
}

void UBagGridWidgetType1::NativeDestruct()
{
	Super::NativeDestruct();
	FGlobalEventManager::UnRegisterEvent(FName("ViewBagGridItemFinishedEvent"), this);
	FGlobalEventManager::UnRegisterEvent(FName("AddItemOnBagGridEvent"), this);
	FGlobalEventManager::UnRegisterEvent(FName("SubItemOnBagGridEvent"), this);
	FGlobalEventManager::UnRegisterEvent(FName("SortCompleteEvent"), this);
}

void UBagGridWidgetType1::OnViewBagGridItemFinished(int ID)
{
	if (FGameSaveTool::GetBagGridDataByIndex(this->GridIndex).ID == ID)
	{
		DotImage->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBagGridWidgetType1::Init(int Index)
{
	this->GridIndex = Index;
	UpdateDisplay(Index);
}

void UBagGridWidgetType1::UpdateDisplay(int Index)
{
	if (Index != GridIndex) return;
	UpdateDisplay2();
}

void UBagGridWidgetType1::UpdateDisplay2()
{
	auto BagGridData = FGameSaveTool::GetBagGridDataByIndex(GridIndex);
	
	
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

void UBagGridWidgetType1::PlayZoomAnimation(int Index)
{
	if (Index != this->GridIndex) return;

	this->PlayAnimation(ZoomAnimation, 0, 1);
}

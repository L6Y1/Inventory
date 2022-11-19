// Fill out your copyright notice in the Description page of Project Settings.


#include "TipBorderWidgetType1.h"

#include "DataTableTool.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"

void UTipBorderWidgetType1::Init(int ID, int Num, int ActionType)
{
	UpdateDisplay(ID, Num, ActionType);
}

void UTipBorderWidgetType1::UpdateDisplay(int ID, int Num, int ActionType)
{
	// load skin type and init the background image of ui
	FString SkinType;
	GConfig->GetString(
		TEXT("GameUIInit/MainUI/BagWidget"),
		TEXT("SkinType"),
		SkinType,
		GGameIni
	);
	
	auto TipBorderWidgetType1Attr = FDataTableTool::GetTipBorderWidgetType1Attr(FName(SkinType));
	check(TipBorderWidgetType1Attr);

	ADataAssetMananger::RequestAsyncLoadObjects(
		this,
		{ TipBorderWidgetType1Attr->BGImage, TipBorderWidgetType1Attr->TitleBG },
		[this](TArray<UObject*> Assets)
		{
			TipBGBorder->SetBrushFromTexture(Cast<UTexture2D>(Assets[0]));
			ItemTitleBGBorder->SetBrushFromTexture(Cast<UTexture2D>(Assets[1]));
		}
	);
	
	auto ItemCommonAttr = FDataTableTool::GetItemCommonAttr(IntToName(ID));
	
	ItemNameText->SetText(FText::FromName(ItemCommonAttr->Name));
	ItemNumText->SetText(FText::FromString(FString::FromInt(Num)));

	// auto ConsumablesAttr = FDataTableTool::GetConsumablesAttr(IntToName(ID));
	// if (ConsumablesAttr)
	{
		FName TipContextWidgetClass;
		if (ActionType == 1)
		{
			auto ItemOnGroundAttr = FDataTableTool::GetItemOnGroundAttr(IntToName(ID));
			TipContextWidgetClass = ItemOnGroundAttr->TipContextWidgetClass;
		} else if (ActionType == 0)
		{
			auto ItemInBagGridAttr = FDataTableTool::GetItemInBagGridAttr(IntToName(ID));
			TipContextWidgetClass = ItemInBagGridAttr->TipContextWidgetClass;
		}

		// create context widget
		if (TipContextWidgetPanel->GetAllChildren().Num() == 0)
		{
			auto TipContextWidgetType = ADataAssetMananger::RequestSyncLoadClass(this, TipContextWidgetClass);
			check(TipContextWidgetType);

			auto TipContextWidget = WidgetTree->ConstructWidget<UUserWidget>(TipContextWidgetType);

			TipContextWidgetPanel->AddChildToVerticalBox(TipContextWidget);

			
			auto *InitFuncPtr = TipContextWidget->FindFunction(FName("Init"));
			if (InitFuncPtr)
			{
				struct
				{
					int ID;
				} Params;
				Params.ID = ID;
				TipContextWidget->ProcessEvent(InitFuncPtr, &Params);
			}
		
		}
		
	}


	
}

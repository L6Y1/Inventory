// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumablesTipContextWidgetType1.h"

#include "DataTableTool.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UConsumablesTipContextWidgetType1::Init(int ID)
{
	// auto *ConsumablesAttr = FDataTableTool::GetConsumablesAttr(IntToName(ID));
	//
	// UTextBlock *CoolDownText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	// CoolDownText->SetText(FText::FromString(FString::SanitizeFloat(ConsumablesAttr->CD)));
	// AttrListPanel->AddChildToVerticalBox(CoolDownText);
	//
	// UTextBlock *CostText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	// CoolDownText->SetText(FText::FromString(FString::SanitizeFloat(ConsumablesAttr->Costs[0])));
	// AttrListPanel->AddChildToVerticalBox(CostText);
	//
	// // for each attribute, create a horizontal ui that shows it 
	// for (auto KeyValuePair : ConsumablesAttr->Attributes)
	// {
	// 	auto HorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
	// 	(AttrListPanel->AddChildToVerticalBox(HorizontalBox))->SetHorizontalAlignment(HAlign_Left);
	//
	// 	
	// 	// create attr-name TextBlock
	// 	UTextBlock *AttrNameText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	// 	
	// 	FString LStr;
	// 	FString RStr;
	// 	auto AttrNameStr = KeyValuePair.Key.ToString();
	// 	
	// 	if (AttrNameStr.Split("_", &LStr, &RStr))
	// 	{
	// 		AttrNameStr = LStr;
	// 	}
	// 	
	// 	AttrNameText->SetText(FText::FromString(AttrNameStr));
	//
	// 	// create separator TextBlock
	// 	UTextBlock *SeparatorText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	// 	SeparatorText->SetText(FText::FromString(":"));
	//
	//
	// 	// create attr-value TextBlock
	// 	FString ValueStr;
	// 	if (KeyValuePair.Key.ToString().Contains("Percent"))
	// 	{
	// 		ValueStr = FString::FromInt(KeyValuePair.Value * 100).Append(FString("%"));
	// 	}
	// 	else
	// 	{
	// 		ValueStr = FString::FromInt(FMath::FloorToInt(KeyValuePair.Value));
	// 	}
	// 	UTextBlock *AttrValueText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	// 	AttrValueText->SetText(FText::FromString(ValueStr));
	//
	//
	// 	AttrNameText->Font.Size = 11;
	// 	SeparatorText->Font.Size = 11;
	// 	AttrValueText->Font.Size = 11;
	// 	HorizontalBox->AddChildToHorizontalBox(AttrNameText);
	// 	HorizontalBox->AddChildToHorizontalBox(SeparatorText);
	// 	HorizontalBox->AddChildToHorizontalBox(AttrValueText);
	// }

}
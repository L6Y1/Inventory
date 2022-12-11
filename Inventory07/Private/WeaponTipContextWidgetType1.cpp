// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponTipContextWidgetType1.h"

#include "DataTableTool.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

void UWeaponTipContextWidgetType1::Init(int ID)
{
	auto *WeaponAttr = FDataTableTool::GetWeaponAttr(IntToName(ID));

	// for each attribute, create a horizontal ui that shows it 
	for (auto KeyValuePair : WeaponAttr->Attrubutes)
	{
		auto HorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
		(AttrListPanel->AddChildToVerticalBox(HorizontalBox))->SetSize(ESlateSizeRule::Fill);

		
		// create attr-name TextBlock
		UTextBlock *AttrNameText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		
		FString LStr;
		FString RStr;
		auto AttrNameStr = KeyValuePair.Key.ToString();
		
		if (AttrNameStr.Split("_", &LStr, &RStr))
		{
			AttrNameStr = LStr;
		}
		
		AttrNameText->SetText(FText::FromString(AttrNameStr));

		// create separator TextBlock
		UTextBlock *SeparatorText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		SeparatorText->SetText(FText::FromString(":"));


		// create attr-value TextBlock
		FString ValueStr;
		if (KeyValuePair.Key.ToString().Contains("Percent"))
		{
			ValueStr = FString::FromInt(KeyValuePair.Value * 100).Append(FString("%"));
		}
		else
		{
			ValueStr = FString::FromInt(FMath::FloorToInt(KeyValuePair.Value));
		}
		UTextBlock *AttrValueText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		AttrValueText->SetText(FText::FromString(ValueStr));


		AttrNameText->Font.Size = 11;
		SeparatorText->Font.Size = 10;
		AttrValueText->Font.Size = 10;

		FSlateChildSize SizeRule = FSlateChildSize();
		
		auto Slot1 = HorizontalBox->AddChildToHorizontalBox(AttrNameText);
		SizeRule.Value = 1;
		Slot1->SetSize(SizeRule);
		Slot1->SetHorizontalAlignment(HAlign_Left);
		
		auto Slot2 = HorizontalBox->AddChildToHorizontalBox(SeparatorText);
		SizeRule.Value = 1;
		Slot1->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		Slot2->SetHorizontalAlignment(HAlign_Center);
		
		auto Slot3 = HorizontalBox->AddChildToHorizontalBox(AttrValueText);
		SizeRule.Value = 1;
		Slot3->SetSize(SizeRule);
		Slot3->SetHorizontalAlignment(HAlign_Right);
		
	}


	
	
	
}

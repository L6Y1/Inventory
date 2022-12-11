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
	auto *ConsumablesAttr = FDataTableTool::GetConsumablesAttr(IntToName(ID));
	
	UTextBlock *CoolDownText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	CoolDownText->SetText(FText::FromString(FString("CD ") + FString::SanitizeFloat(ConsumablesAttr->CD)));
	CoolDownText->Font.Size = 11;
	AttrListPanel->AddChildToVerticalBox(CoolDownText);
	
	UTextBlock *CostText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	CostText->SetText(FText::FromString(FString("Use cost ") + FString::FromInt(ConsumablesAttr->Costs["Num"])));
	CostText->Font.Size = 11;
	AttrListPanel->AddChildToVerticalBox(CostText);
	
	// for each attribute, create a horizontal ui that shows it 
	for (auto KeyValuePair : ConsumablesAttr->Attributes)
	{
		auto HorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
		(AttrListPanel->AddChildToVerticalBox(HorizontalBox));
		
		// create attr-name TextBlock
		UTextBlock *AttrNameText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		
		auto AttrNameStr = KeyValuePair.Key.ToString();
		AttrNameText->SetText(FText::FromString(AttrNameStr));
	
		// create separator TextBlock
		UTextBlock *SeparatorText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		SeparatorText->SetText(FText::FromString(":"));
		
		// create attr-value VerticalBox
		UVerticalBox *AttrsValueBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());
		auto Attrs = KeyValuePair.Value;
		
		
		UTextBlock *AttrValueText1 = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		AttrValueText1->SetText(FText::FromString("Amount " + FString::SanitizeFloat(Attrs.Values[0])));
		
		UTextBlock *AttrValueText2 = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		AttrValueText2->SetText(FText::FromString("Duration " + FString::SanitizeFloat(Attrs.Values[1])));
		
		UTextBlock *AttrValueText3 = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		AttrValueText3->SetText(FText::FromString(
			Attrs.Values[2] == 0	? 
					"Permanent "			: 
					"Temporary " + FString::SanitizeFloat(Attrs.Values[2]))
			);
		
		AttrNameText->Font.Size = 11;
		SeparatorText->Font.Size = 11;
		AttrValueText1->Font.Size = 10;
		AttrValueText2->Font.Size = 10;
		AttrValueText3->Font.Size = 10;
		
		AttrsValueBox->AddChildToVerticalBox(AttrValueText1);
		AttrsValueBox->AddChildToVerticalBox(AttrValueText2);
		AttrsValueBox->AddChildToVerticalBox(AttrValueText3);
		
		HorizontalBox->AddChildToHorizontalBox(AttrNameText);
		HorizontalBox->AddChildToHorizontalBox(SeparatorText);
		HorizontalBox->AddChildToHorizontalBox(AttrsValueBox);
	}

}

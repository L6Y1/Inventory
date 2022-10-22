// Fill out your copyright notice in the Description page of Project Settings.


#include "NavButtonWidgetType1.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"

void UNavButtonWidgetType1::Init(FNavButtonAttr NavButtonAttr)
{
	ShortCutKeyText->SetText(FText::FromName(NavButtonAttr.ShortCutKey));
	ADataAssetMananger::RequestAsyncLoadObjects(
		this,
		NavButtonAttr.ButtonIcons,
		[this, NavButtonAttr](TArray<UObject*> Assets)
		{
			auto *ButtonStyle = &NavButton->WidgetStyle;

			auto *NormalBrush = &ButtonStyle->Normal;
			NormalBrush->SetResourceObject(Assets[0]);
			NormalBrush->DrawAs = ESlateBrushDrawType::Image;

			auto *HoverBrush = &ButtonStyle->Hovered;
			HoverBrush->SetResourceObject(Assets[1]);
			HoverBrush->DrawAs = ESlateBrushDrawType::Image;

			auto *PressedBrush = &ButtonStyle->Pressed;
			PressedBrush->SetResourceObject(Assets[2]);
			PressedBrush->DrawAs = ESlateBrushDrawType::Image;

			this->SetVisibility(ESlateVisibility::Visible);
		}
		);
}

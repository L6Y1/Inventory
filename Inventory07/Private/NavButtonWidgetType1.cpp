// Fill out your copyright notice in the Description page of Project Settings.


#include "NavButtonWidgetType1.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"
#include "Inventory07/GlobalEventManager/GlobalEventManager.h"
#include "Kismet/KismetSystemLibrary.h"

void UNavButtonWidgetType1::Init(FNavButtonAttr NavButtonAttr)
{
	this->ButtonAttr = NavButtonAttr;
	// hide the button before the asset is loaded
	this->SetVisibility(ESlateVisibility::Collapsed);

	// add function to OnClicked delegate of the button
	this->NavButton->OnClicked.AddDynamic(this, &UNavButtonWidgetType1::NavButtonOnClicked);

	// set button size
	NavButtonSizeBox->SetWidthOverride(NavButtonAttr.Size);
	NavButtonSizeBox->SetHeightOverride(NavButtonAttr.Size);
	
	ShortCutKeyText->SetText(FText::FromName(NavButtonAttr.ShortCutKey));
	ADataAssetMananger::RequestAsyncLoadObjects(
		this,
		NavButtonAttr.ButtonIcons,
		[this](TArray<UObject*> Assets)
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

void UNavButtonWidgetType1::NavButtonOnClicked()
{
	// call delegate
	FGlobalEventManager::TriggerEvent(ButtonAttr.OnClickedEvent, &ButtonAttr.ToggledWidgetLayoutType);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

#include "DataTableTool.h"
#include "StructTypes.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	// {
	// 	auto NavButtonWidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/BP_NavButtonWidgetType1.BP_NavButtonWidgetType1_C'"));
	// 	auto NavButtonWidget = CreateWidget<UUserWidget>(GetOwningPlayer(), NavButtonWidgetClass);
	// 	auto HorBoxSlot = this->NavButtonPanel->AddChildToHorizontalBox(NavButtonWidget);
	// 	HorBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	// }
	// {
	// 	auto NavButtonWidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/BP_NavButtonWidgetType1.BP_NavButtonWidgetType1_C'"));
	// 	auto NavButtonWidget = CreateWidget<UUserWidget>(GetOwningPlayer(), NavButtonWidgetClass);
	// 	auto HorBoxSlot = this->NavButtonPanel->AddChildToHorizontalBox(NavButtonWidget);
	// 	HorBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	// }

	/*
	 * first get names(in string) of navigation buttons by GConfig, 
	 * then use the names to get corresponding button attributes in data table, which contains
	 * the widget class name.
	 */
	TArray<FString> NavButtonStrs;
	// load config
	GConfig->GetArray(
		TEXT("GameUIInit/MainUI/NavigationButtons"),
		TEXT("NavigationButtons"),
		NavButtonStrs,
		GGameIni
	);
	for (auto NavButtonStr : NavButtonStrs)
	{
		// corresponding button attributes 
		auto *NavButtonAttr = FDataTableTool::GetNavButtonAttr(FName(*NavButtonStr));
		checkf(NavButtonAttr, TEXT("Button %s Not Found"), *NavButtonStr)

		// get the button widget class by name, using ADataAssetManager
		auto *NavButtonWidgetClass = ADataAssetMananger::RequestSyncLoadClass(this, NavButtonAttr->ButtonWidgetLayoutType);
		check(NavButtonWidgetClass);
		
		// create button widget
		auto NavButtonWidget = CreateWidget(this->GetOwningPlayer(), NavButtonWidgetClass);

		// some alignment 
		auto HorBoxSlot = this->NavButtonPanel->AddChildToHorizontalBox(NavButtonWidget);
		HorBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

		auto InitFuncPtr = NavButtonWidget->FindFunction(FName("Init"));
		if (InitFuncPtr)
		{
			NavButtonWidget->ProcessEvent(InitFuncPtr, NavButtonAttr);
		}
		
	}
	
}

void UMainUI::NativeDestruct()
{
	Super::NativeDestruct();
}

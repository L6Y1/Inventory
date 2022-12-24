// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

#include "BagGridDragDropOperation.h"
#include "DataTableTool.h"
#include "StructTypes.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/NamedSlot.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"
#include "Inventory07/GlobalEventManager/GlobalEventManager.h"
#include "Kismet/KismetSystemLibrary.h"

FReply UMainUI::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	return FReply::Unhandled();
}

bool UMainUI::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent,
	UDragDropOperation *InOperation)
{
	// if (InOperation->IsA(UBagGridDragDropOperation::StaticClass()))
	// {
	// 	auto BagGridDDO = Cast<UBagGridDragDropOperation>(InOperation);
	//
	// 	FGlobalEventManager::TriggerEvent(FName("BagGridDragToGroundEvent"), &BagGridDDO->DragGridIndex);
	// }
	TScriptInterface<IDDOInterface> DDOInterface = InOperation;
	if (DDOInterface)
	{
		DDOInterface->DropToHudWidget(InGeometry, InDragDropEvent);
	}

	
	return true;
}

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

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
		/*
		 * can also be achieved by doing this:
		 * auto NavButtonWidget = this->WidgetTree->ConstructWidget<UUserWidget>(NavButtonWidgetClass);
		 */
		
		
		// some alignment 
		auto HorBoxSlot = this->NavButtonPanel->AddChildToHorizontalBox(NavButtonWidget);
		HorBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

		auto InitFuncPtr = NavButtonWidget->FindFunction(FName("Init"));
		if (InitFuncPtr)
		{
			NavButtonWidget->ProcessEvent(InitFuncPtr, NavButtonAttr);
		}

		// register delegate to the GlobalEventManager
		FGlobalEventManager::RegisterEvent(NavButtonAttr->OnClickedEvent, this, NavButtonAttr->OnClickedEvent);
		
	}
	
	FString ShortCutBarStyle;
	// load config
	GConfig->GetString(
		TEXT("GameUIInit/MainUI/ShortCutBar"),
		TEXT("Style"),
		ShortCutBarStyle,
		GGameIni
	);
	auto *ShortCutBarAttr = FDataTableTool::GetShortCutBarAttr(FName(ShortCutBarStyle));
	
	auto *ShortCutBarWidgetClass = ADataAssetMananger::RequestSyncLoadClass(this, FName(ShortCutBarStyle));
	check(ShortCutBarWidgetClass);
	auto *ShortCutBarWidget = CreateWidget(this->GetOwningPlayer(), ShortCutBarWidgetClass);

	auto *InitFuncPtr = ShortCutBarWidget->FindFunction("Init");
	if (InitFuncPtr)
	{
		ShortCutBarWidget->ProcessEvent(InitFuncPtr, ShortCutBarAttr);
	}
	
	ShortCutSlot->AddChild(ShortCutBarWidget);
	
}

void UMainUI::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainUI::OpenBagWidget(FName ToggledWidgetLayoutType)
{
	// get BagWidgetClass by ToggledWidgetLayoutType passed by ToggleBagEvent(), using DataAssetManager
	auto *BagWidgetClass = ADataAssetMananger::RequestSyncLoadClass(this, ToggledWidgetLayoutType);
	check(BagWidgetClass);

	// construct widget
	BagWidget = this->WidgetTree->ConstructWidget<UUserWidget>(BagWidgetClass);

	// call Init() by reflection, to init the BagWidget
	auto InitFuncPtr = BagWidget->FindFunction(FName("Init"));
	check(InitFuncPtr);
	if (InitFuncPtr)
	{
		// get SkinType of BagWidget by reading config file
		FString SkinType;
		GConfig->GetString(
			TEXT("GameUIInit/MainUI/BagWidget"),
			TEXT("SkinType"),
			SkinType,
			GGameIni
		);
		FName SkinTypeName = FName(SkinType);

		struct 
		{
			FName SkinTypeName;
			UUserWidget *Owner;
			FName CloseFunName;
		} Params;

		Params.SkinTypeName = SkinTypeName;
		Params.Owner = this;
		Params.CloseFunName = FName("CloseBagWidget");
		
		BagWidget->ProcessEvent(InitFuncPtr,&Params);
	}
	// add to slot on MainUI
	BagWidgetSlot->AddChild(BagWidget);
	// this->bBagWidgetOpen = true;
}

void UMainUI::CloseBagWidget()
{
	auto *UnInitFuncPtr = BagWidget->FindFunction(FName("UnInit"));
	if (UnInitFuncPtr)
	{
		struct 
		{
			UUserWidget *Owner;
		} Params;
		Params.Owner = this;
		BagWidget->ProcessEvent(UnInitFuncPtr, this);
	}
	
	FGlobalEventManager::UnRegisterEvent(FName("CloseBagWidgetEvent"), this);
	//BagWidgetSlot->RemoveChild(BagWidget);
	BagWidget->RemoveFromParent();
	BagWidget = nullptr;
	// this->bBagWidgetOpen = false;
}



void UMainUI::ToggleBagWidgetEvent(FName ToggledWidgetLayoutType)
{
	if (IsValid(BagWidget))
	{
		CloseBagWidget();
	}
	else
	{
		OpenBagWidget(ToggledWidgetLayoutType);
	}
}

void UMainUI::ToggleSettingWidgetEvent(FName ToggledWidgetLayoutType)
{
	UKismetSystemLibrary::PrintString(nullptr, *ToggledWidgetLayoutType.ToString());
}

void UMainUI::ToggleShopWidgetEvent(FName ToggledWidgetLayoutType)
{
	UKismetSystemLibrary::PrintString(nullptr, *ToggledWidgetLayoutType.ToString());
}

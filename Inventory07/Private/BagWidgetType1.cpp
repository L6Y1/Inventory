// Fill out your copyright notice in the Description page of Project Settings.


#include "BagWidgetType1.h"

#include <Asset.h>
#include "PaperSprite.h"
#include "BagGridDragDropOperation.h"
#include "DataTableTool.h"
#include "StructTypes.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"
#include "Inventory07/GlobalEventManager/GlobalEventManager.h"

void UBagWidgetType1::Init(FName SkinType, UUserWidget *Owner, FName CloseFunName)
{
	auto *BagWidgetType1Attr = FDataTableTool::GetBagWidgetType1Attr(SkinType);

	// hide the ui before assets is loaded 
	this->SetVisibility(ESlateVisibility::Collapsed);
	
	// set bag title text
	TitleText->SetText(FText::FromName(BagWidgetType1Attr->TitleName));

	// register exit button click event
	ExitButton->OnClicked.AddDynamic(this, &UBagWidgetType1::OnExitButtonClicked);
	FGlobalEventManager::RegisterEvent(FName("CloseBagWidgetEvent"), Owner, CloseFunName);

	// register sort button click event
	SortButton->OnClicked.AddDynamic(this, &UBagWidgetType1::OnSortButtonClicked);
	
	
	// set bag size
	BagSizeBox->SetWidthOverride(BagWidgetType1Attr->BagSize.X);
	BagSizeBox->SetHeightOverride(BagWidgetType1Attr->BagSize.Y);

	// load bag ui assets 
	ADataAssetMananger::RequestAsyncLoadObjects(
		this,
		{
			BagWidgetType1Attr->TitleBG,
			BagWidgetType1Attr->BagBG,
			BagWidgetType1Attr->CloseButtonIcons[0],
			BagWidgetType1Attr->CloseButtonIcons[1],
			BagWidgetType1Attr->CloseButtonIcons[2],
			BagWidgetType1Attr->SortButtonIcons[0],
			BagWidgetType1Attr->SortButtonIcons[1],
			BagWidgetType1Attr->SortButtonIcons[2],
			
		},
		[this](TArray<UObject*> Assets)
		{
			// set title background image
			this->TitleImage->SetBrushFromTexture(Cast<UTexture2D>(Assets[0]));
			
			// set bag background image
			auto Sprite = Cast<UPaperSprite>(Assets[1]);
			if (Sprite != nullptr)
			{
				const FSlateAtlasData SpriteAtlasData = Sprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();

				FSlateBrush Brush;
				Brush.SetResourceObject(Sprite);
				Brush.ImageSize = FVector2D(SpriteSize.X, SpriteSize.Y);
				this->BagBorder->SetBrush(Brush);
			}
			else
			{
				this->BagBorder->SetBrushFromTexture(Cast<UTexture2D>(Assets[1]));
			}

			{
				// set close button image
				auto *ButtonStyle = &this->ExitButton->WidgetStyle;
				auto *NormalBrush = &ButtonStyle->Normal;
				NormalBrush->SetResourceObject(Assets[2]);
				NormalBrush->DrawAs = ESlateBrushDrawType::Image;

				auto *HoverBrush = &ButtonStyle->Hovered;
				HoverBrush->SetResourceObject(Assets[3]);
				HoverBrush->DrawAs = ESlateBrushDrawType::Image;

				auto *PressedBrush = &ButtonStyle->Pressed;
				PressedBrush->SetResourceObject(Assets[4]);
				PressedBrush->DrawAs = ESlateBrushDrawType::Image;
			}

			{
				// set sort button image
				auto *ButtonStyle = &this->SortButton->WidgetStyle;
				auto *NormalBrush = &ButtonStyle->Normal;
				NormalBrush->SetResourceObject(Assets[5]);
				NormalBrush->DrawAs = ESlateBrushDrawType::Image;

				auto *HoverBrush = &ButtonStyle->Hovered;
				HoverBrush->SetResourceObject(Assets[6]);
				HoverBrush->DrawAs = ESlateBrushDrawType::Image;

				auto *PressedBrush = &ButtonStyle->Pressed;
				PressedBrush->SetResourceObject(Assets[7]);
				PressedBrush->DrawAs = ESlateBrushDrawType::Image;
			}
			
			this->SetVisibility(ESlateVisibility::Visible);
		}
	);

	// Get total GridNum from .ini file
	int GridNum;
	GConfig->GetInt(
		TEXT("GameSaveInit/Player/BagData"),
		TEXT("GridNum"),
		GridNum,
		GGameIni
	);
	
	// get class of the BagGridWidget
	auto *BagGridWidgetClass = ADataAssetMananger::RequestSyncLoadClass(this, BagWidgetType1Attr->BagGridType);
	check(BagGridWidgetClass);
	for (int i = 0; i < GridNum; ++i)
	{
		// create grid and add to WrapBox in viewport
		auto *BagGridWidget = this->WidgetTree->ConstructWidget<UUserWidget>(BagGridWidgetClass);
		BagGridPanel->AddChildToWrapBox(BagGridWidget);

		// init the grid by reflection 
		auto *InitFuncPtr = BagGridWidget->FindFunction(FName("Init"));
		if (InitFuncPtr)
		{
			BagGridWidget->ProcessEvent(InitFuncPtr, &i);
		}
	}
}

void UBagWidgetType1::UnInit(UUserWidget *Owner)
{
	FGlobalEventManager::UnRegisterEvent(FName("CloseBagWidgetEvent"), Owner);
}

FReply UBagWidgetType1::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		return  UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::RightMouseButton).NativeReply;
	}
	return FReply::Unhandled();
}

void UBagWidgetType1::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent,
	UDragDropOperation *&OutOperation)
{
	auto MouseStartCoordinate = InMouseEvent.GetScreenSpacePosition();
	auto MouseStartCoordinateInViewport = InGeometry.AbsoluteToLocal(MouseStartCoordinate);
	
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	auto *DDO = UWidgetBlueprintLibrary::CreateDragDropOperation(UBagGridDragDropOperation::StaticClass());
	DDO->DefaultDragVisual = this;
	DDO->Pivot = EDragPivot::MouseDown;
	this->RemoveFromParent();
	Cast<UBagGridDragDropOperation>(DDO)->DropToHudWidgetDelegate.BindLambda([this, MouseStartCoordinateInViewport](FGeometry Geometry, FPointerEvent MouseEvent)
	{
		this->AddToViewport();
		this->SetDesiredSizeInViewport(this->BagSizeBox->GetDesiredSize());

		auto MouseEndCoordinate = MouseEvent.GetScreenSpacePosition();
		auto MouseEndCoordinateInViewport = Geometry.AbsoluteToLocal(MouseEndCoordinate);
		
		this->SetPositionInViewport(MouseEndCoordinateInViewport - MouseStartCoordinateInViewport, false);
	});

	
	OutOperation = DDO;
}

bool UBagWidgetType1::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent,
	UDragDropOperation *InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return true;
}


void UBagWidgetType1::OnExitButtonClicked()
{
	FGlobalEventManager::TriggerEvent(FName("CloseBagWidgetEvent"), nullptr);
}

void UBagWidgetType1::OnSortButtonClicked()
{
	FGlobalEventManager::TriggerEvent(FName("SortGridItemEvent"), nullptr);
}

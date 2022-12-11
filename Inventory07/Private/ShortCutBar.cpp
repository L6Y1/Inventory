// Fill out your copyright notice in the Description page of Project Settings.


#include "ShortCutBar.h"

#include "StructTypes.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"

void UShortCutBar::Init(FShortCutBarAttr ShortCutBarAttr)
{
	int ShortCutGridNum;
	GConfig->GetInt(
	TEXT("GameUIInit/MainUI/ShortCutBar"),
	TEXT("ShortCutGridNum"),
	ShortCutGridNum,
	GGameIni
	);

	int GridNum;
	GConfig->GetInt(
		TEXT("GameSaveInit/Player/BagData"),
		TEXT("GridNum"),
		GridNum,
		GGameIni
	);

	// set short cut bar background image
	ADataAssetMananger::RequestAsyncLoadObject(this, ShortCutBarAttr.BackGroundImage, [this](UObject *Asset)
	{
		BGBorder->SetBrushFromTexture(Cast<UTexture2D>(Asset));
	});
	
	// create short cut grid
	auto GridClass = ADataAssetMananger::RequestSyncLoadClass(this, ShortCutBarAttr.GridType);
	check(GridClass);
	for (int i = GridNum; i < ShortCutGridNum + GridNum; ++i)
	{
		// create grid and add to horbox
		auto *BagGridWidget = this->WidgetTree->ConstructWidget<UUserWidget>(GridClass);
		ShortCutHorBox->AddChildToHorizontalBox(BagGridWidget);

		// init the grid by reflection 
		auto *InitFuncPtr = BagGridWidget->FindFunction(FName("Init"));
		if (InitFuncPtr)
		{
			BagGridWidget->ProcessEvent(InitFuncPtr, &i);
		}
	}
	
}

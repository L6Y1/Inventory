// Fill out your copyright notice in the Description page of Project Settings.


#include "BagGridDragWidgetType1.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory07/DataAssetMananger/DataAssetMananger.h"


void UBagGridDragWidgetType1::Init(FName ItemName, int Num)
{
	ADataAssetMananger::RequestAsyncLoadObject(this, ItemName,
		[this](UObject *Asset)
	{
		ItemImage->SetBrushFromTexture(Cast<UTexture2D>(Asset));
	});
	ItemNum->SetText(FText::FromString(FString::FromInt(Num)));
}

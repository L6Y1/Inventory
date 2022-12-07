// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDOInterface.h"
#include "Blueprint/DragDropOperation.h"
#include "BagGridDragDropOperation.generated.h"

DECLARE_DELEGATE_TwoParams(FDropToHudWidgetDelegate, FGeometry, FPointerEvent)
/**
 * 
 */
UCLASS()
class INVENTORY07_API UBagGridDragDropOperation : public UDragDropOperation, public IDDOInterface
{
	GENERATED_BODY()
	
public:
	int DragGridIndex;

	FDropToHudWidgetDelegate DropToHudWidgetDelegate;

	
	virtual void DropToHudWidget(FGeometry Geometry, FPointerEvent MouseEvent) override;
};

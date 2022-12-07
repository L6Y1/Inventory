// Fill out your copyright notice in the Description page of Project Settings.


#include "BagGridDragDropOperation.h"

#include "Inventory07/GlobalEventManager/GlobalEventManager.h"

void UBagGridDragDropOperation::DropToHudWidget(FGeometry Geometry, FPointerEvent MouseEvent)
{
	this->DropToHudWidgetDelegate.ExecuteIfBound(Geometry, MouseEvent);
	
}

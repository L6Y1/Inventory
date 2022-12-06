// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "BagGridDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY07_API UBagGridDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	int DragGridIndex;
};

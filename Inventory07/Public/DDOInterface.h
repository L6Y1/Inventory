// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DDOInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDDOInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORY07_API IDDOInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void DropToHudWidget(FGeometry Geometry, FPointerEvent MouseEvent) = 0;
};

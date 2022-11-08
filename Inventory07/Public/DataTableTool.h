// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataTableTool.generated.h"

class UDataTable;
struct FNavButtonAttr;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UDataTableTool : public UObject
{
	GENERATED_BODY()
	
};


class FDataTableTool
{
	
	static UDataTable *NavButtonAttr_DT;
	
public:
	// get Button Attributes by button name in data table
	static FNavButtonAttr* GetNavButtonAttr(FName RowName);

	
};

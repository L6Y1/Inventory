// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructTypes.h"
#include "UObject/NoExportTypes.h"
#include "DataTableTool.generated.h"

struct FBagWidgetType1Attr;
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
	
	static UDataTable *DT_NavButtonAttr;
	
	static UDataTable *DT_BagWidgetType1SkinAttr;

	static UDataTable *DT_FItemInBagGirdAttr;
	
public:
	// get Button Attributes by button name in data table
	static FNavButtonAttr* GetNavButtonAttr(FName RowName);
	
	static FBagWidgetType1Attr* GetBagWidgetType1Attr(FName RowName);

	static FItemInBagGirdAttr* GetItemInBagGridAttr(FName RowName);
	
};

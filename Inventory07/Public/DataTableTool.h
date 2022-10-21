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
	
public:

	static UDataTable *NavButtonAttr_DT;
	
	static FNavButtonAttr* GetNavButtonAttr(FName RowName);
};

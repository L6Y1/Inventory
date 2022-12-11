// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructTypes.h"
#include "UObject/NoExportTypes.h"
#include "DataTableTool.generated.h"

#define IntToName(ID) FName(FString::FromInt(ID))

class UDataTable;


#define DataTable_Signature(Signature)\
private:\
	static UDataTable *DT_##Signature##;\
public:\
	static F##Signature##* Get##Signature##(FName RowName);


#define DataTable_Impl(Signature, DataTablePath)\
UDataTable* FDataTableTool::DT_##Signature## = nullptr;\
F##Signature## * FDataTableTool::Get##Signature##(FName RowName)\
{\
	if (!DT_##Signature##)\
	{\
		DT_##Signature## = LoadObject<UDataTable>(nullptr, DataTablePath);\
		check(DT_##Signature##);\
	}\
\
	if (DT_##Signature##->GetRowMap().Find(RowName) != nullptr)\
	{\
		auto Result = DT_##Signature##->FindRow<F##Signature##>(RowName, TEXT("None"), true);\
		return Result;\
	}\
	\
	return nullptr;\
};



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
	DataTable_Signature(NavButtonAttr)

	DataTable_Signature(BagWidgetType1Attr)

	DataTable_Signature(ItemInBagGridAttr)
	
	DataTable_Signature(ItemOnGroundAttr)

	DataTable_Signature(TipBorderWidgetType1Attr)
	
	DataTable_Signature(ItemCommonAttr)
	
	DataTable_Signature(ConsumablesAttr)
	
	DataTable_Signature(WeaponAttr)
	
	DataTable_Signature(ShortCutBarAttr)

	
	
};

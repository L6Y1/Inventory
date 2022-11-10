// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableTool.h"
#include "StructTypes.h"
#include "Engine/DataTable.h"

UDataTable* FDataTableTool::DT_NavButtonAttr = nullptr;

UDataTable* FDataTableTool::DT_BagWidgetType1SkinAttr = nullptr;


FNavButtonAttr* FDataTableTool::GetNavButtonAttr(FName RowName)
{
	if (!DT_NavButtonAttr)
	{
		DT_NavButtonAttr = LoadObject<UDataTable>(nullptr,
			TEXT("DataTable'/Game/DataTable/DT_NavButtonAttrTable.DT_NavButtonAttrTable'"));
		check(DT_NavButtonAttr);
	}

	if (DT_NavButtonAttr->GetRowMap().Find(RowName) != nullptr)
	{
		auto Result = DT_NavButtonAttr->FindRow<FNavButtonAttr>(RowName, TEXT("None"), true);
		return Result;
	}
	
	return nullptr;
}

FBagWidgetType1Attr * FDataTableTool::GetBagWidgetType1Attr(FName RowName)
{
	if (!DT_BagWidgetType1SkinAttr)
	{
		DT_BagWidgetType1SkinAttr = LoadObject<UDataTable>(nullptr,
			TEXT("DataTable'/Game/DataTable/DT_FBagWidgetType1AttrTable.DT_FBagWidgetType1AttrTable'"));
		check(DT_BagWidgetType1SkinAttr);
	}

	if (DT_BagWidgetType1SkinAttr->GetRowMap().Find(RowName) != nullptr)
	{
		auto Result = DT_BagWidgetType1SkinAttr->FindRow<FBagWidgetType1Attr>(RowName, TEXT("None"), true);
		return Result;
	}
	
	return nullptr;
}

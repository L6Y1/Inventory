// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableTool.h"
#include "StructTypes.h"
#include "Engine/DataTable.h"

UDataTable* FDataTableTool::NavButtonAttr_DT = nullptr;


FNavButtonAttr* FDataTableTool::GetNavButtonAttr(FName RowName)
{
	if (!NavButtonAttr_DT)
	{
		StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/ThirdPersonCPP/DataTable/DT_NavButtonAttrTable.DT_NavButtonAttrTable'"));
		check(NavButtonAttr_DT);
	}

	if (NavButtonAttr_DT->GetRowMap().Find(RowName) != nullptr)
	{
		auto Result = NavButtonAttr_DT->FindRow<FNavButtonAttr>(RowName, TEXT("None"), true);
		return Result;
	}
	
	return nullptr;
}

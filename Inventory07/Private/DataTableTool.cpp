// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableTool.h"
#include "StructTypes.h"
#include "Engine/DataTable.h"

UDataTable* FDataTableTool::DT_NavButtonAttr = nullptr;

UDataTable* FDataTableTool::DT_BagWidgetType1Attr = nullptr;

UDataTable* FDataTableTool::DT_ItemInBagGridAttr = nullptr;

UDataTable* FDataTableTool::DT_ItemOnGroundAttr = nullptr;

DataTable_Impl(NavButtonAttr, TEXT("DataTable'/Game/DataTable/DT_NavButtonAttrTable.DT_NavButtonAttrTable'"))

DataTable_Impl(BagWidgetType1Attr, TEXT("DataTable'/Game/DataTable/DT_BagWidgetType1AttrTable.DT_BagWidgetType1AttrTable'"))

DataTable_Impl(ItemInBagGridAttr, TEXT("DataTable'/Game/DataTable/DT_ItemInBagGirdAttrTable.DT_ItemInBagGirdAttrTable'"))

DataTable_Impl(ItemOnGroundAttr, TEXT("DataTable'/Game/DataTable/DT_ItemOnGroundAttrTable.DT_ItemOnGroundAttrTable'"))


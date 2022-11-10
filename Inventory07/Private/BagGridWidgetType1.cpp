// Fill out your copyright notice in the Description page of Project Settings.


#include "BagGridWidgetType1.h"

#include "FileTool.h"
#include "Kismet/KismetSystemLibrary.h"

void UBagGridWidgetType1::Init(int Index)
{
	auto GameSaveData = FFileTool::LoadGame();
	// TODO: init bag grid
	UKismetSystemLibrary::PrintString(nullptr, GameSaveData.PlayerData.Location.ToString());
}

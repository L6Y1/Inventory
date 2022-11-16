// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructTypes.h"
#include "FileTool.generated.h"


class FGameSaveTool
{
public:
	static FBagGridData GetBagGridDataByIndex(int GridIndex);
	
	static int GetItemInBagGridTotalNum(int ID);

	static bool IsBagHadItem(int ID);

	// add to already had items
	static void AddViewBagGridItemID(int ID);

	static TArray<FBagGridData> GetAllBagGridDatas();
	static void SetAllBagGridDatas(TArray<FBagGridData> NewBagGridDatas);
	
	static void SetBagGridDataByIndex(FBagGridData NewBagGrid, int FoundIndex);
	
	static TMap<FName, FItemOnGroundData> GetItemOnGroundDatas();
};


class FJsonTool
{
private:
	// JSON to GameSaveData
	static FGameSaveData GetGameSaveDataFromJsonStr(FString JsonStr);

	// GameSaveData to JSON
	static FString GetJsonStrFromGameSaveData(FGameSaveData GameSaveData);

	friend class FFileTool;
};

class FFileTool
{
	
public:
	// save str to file
	static bool SaveStrToFile(FString InString, FString RelativePath, FString FileName);
	
	// read str from file
	static bool LoadStrFromFile(FString &OutString, FString RelativePath, FString FileName);

	// load game
	static FGameSaveData LoadGame(FString RelativePath = FString("/GameSaves"),
		FString FileName = FString("SaveGame00.sav"));
	
	// save game
	static void SaveGame(FGameSaveData InGameSaveData,
		FString RelativePath = FString("/GameSaves"),
		FString FileName = FString("SaveGame00.sav"));
};


/**
 * 
 */
UCLASS()
class INVENTORY07_API UFileTool : public UObject
{
	GENERATED_BODY()
	
};

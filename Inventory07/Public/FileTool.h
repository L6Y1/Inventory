// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructTypes.h"
#include "FileTool.generated.h"

/**
 * @brief util class to help save game / load game
 */
class FGameSaveTool
{
public:
	//begin ItemOnGroundDatas
	
	/**
	 * @brief remove item on the ground by the index 
	 * @param Index unique index of item to be removed
	 */
	static void RemoveItemOnGroundDataByIndex(const FName & Index);
	
	/**
	 * @brief set item on the ground by unique index
	 * @param NewData new item data to save
	 * @param Index unique index of item to set
	 */
	static void SetItemOnGroundDataByIndex(FItemOnGroundData NewData, FName Index);

	/**
	 * @brief get item on the ground by unique index
	 * @param Index unique index of item to get
	 * @return FItemOnGroundData obj that contains data of the item 
	 */
	static FItemOnGroundData GetItemOnGroundDataByIndex(FName Index);

	// get all items on the ground
	static TMap<FName, FItemOnGroundData> GetItemOnGroundDatas();

	static void AddItemOnGroundData(FName &Index, FItemOnGroundData NewItemOnGroundData);

	static bool ItemOnGroundExist(FName Index);
	
	//~end ItemOnGroundDatas

	//begin PlayerData
	// get BagGridData by grid index
	static FBagGridData GetBagGridDataByIndex(int GridIndex);

	// get total num of item with specified ID
	static int GetItemInBagGridTotalNum(int ID);
	
	// do i have this item with specified ID before?
	static bool IsBagHadItem(int ID);

	// add to already had items
	static void AddViewBagGridItemID(int ID);

	// get / set -ALL- BagGridData
	static TArray<FBagGridData> GetAllBagGridDatas();
	static void SetAllBagGridDatas(TArray<FBagGridData> NewBagGridDatas);

	// set BagGridData by specified ID
	static void SetBagGridDataByIndex(FBagGridData NewBagGrid, int ID);
	//~end PlayerData
	
};

/**
 * @brief util class to serialize/deserialize JSON string 
 */
class FJsonTool
{
private:
	// JSON string to GameSaveData
	static FGameSaveData GetGameSaveDataFromJsonStr(FString JsonStr);

	// GameSaveData to JSON string
	static FString GetJsonStrFromGameSaveData(FGameSaveData GameSaveData);

	friend class FFileTool;
};

/**
 * @brief util class, can save FGameSaveData to file / read file to get FGameSaveData
 */
class FFileTool
{
	
private:
	// util function
	// save str to file
	static bool SaveStrToFile(FString InString, FString RelativePath, FString FileName);
	
	// read str from file
	static bool LoadStrFromFile(FString &OutString, FString RelativePath, FString FileName);

public:
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

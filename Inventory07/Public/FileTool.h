// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructTypes.h"
#include "FileTool.generated.h"


class FFileTool
{
	
public:
	// save str to file
	static bool SaveStrToFile(FString InString, FString RelativePath, FString FileName);
	
	// read str from file
	static bool LoadStrFromFile(FString &OutString, FString RelativePath, FString FileName);

	// JSON to GameSaveData
	static FGameSaveData LoadGame(FString RelativePath = FString("/GameSaves"),
		FString FileName = FString("SaveGame00.sav"));
	
	// GameSaveData to JSON
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

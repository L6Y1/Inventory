// Fill out your copyright notice in the Description page of Project Settings.


#include "FileTool.h"


bool FFileTool::SaveStrToFile(FString InString, FString RelativePath, FString FileName)
{
	if (!InString.IsEmpty() && !FileName.IsEmpty())
	{
		// get absolute path by RelativePath
		auto AbsolutePath = FPaths::ProjectSavedDir() + RelativePath + FString("/") + FileName;
		if (FFileHelper::SaveStringToFile(InString, *AbsolutePath))
		{
			return true;
		}
	}

	return false;
}

bool FFileTool::LoadStrFromFile(FString &OutString, FString RelativePath, FString FileName)
{
	auto AbsolutePath = FPaths::ProjectSavedDir() + RelativePath + FString("/") + FileName;
	if (!FileName.IsEmpty() && !AbsolutePath.IsEmpty())
	{
		if (FPaths::FileExists(AbsolutePath))
		{
			if (FFileHelper::LoadFileToString(OutString, *AbsolutePath))
			{
				return true;
			}
		}
	}
	
	return false;
}

FGameSaveData FFileTool::LoadGame(FString RelativePath, FString FileName)
{
	FGameSaveData GameSaveData;
	FString OutJsonStr;
	if (LoadStrFromFile(OutJsonStr, RelativePath, FileName))
	{
		//TODO: JSON to str
	}
	else  // no save data file
	{
		// create PlayerData and ItemOnGroundData
		FPlayerData PlayerData;
		FItemOnGroundData ItemOnGroundData;
		
		// load config to create a PlayerData
		FString Name;
		GConfig->GetString(
			TEXT("GameSaveInit/Player"),
			TEXT("Name"),
			Name,
			GGameIni
			);

		int Level;
		GConfig->GetInt(
			TEXT("GameSaveInit/Player"),
			TEXT("Level"),
			Level,
			GGameIni
			);
		
		FVector Location;
		GConfig->GetVector(
			TEXT("GameSaveInit/Player"),
			TEXT("Location"),
			Location,
			GGameIni
			);
		
		// create PlayerData
		PlayerData.Name = FName(Name);
		PlayerData.Level = Level;
		PlayerData.Location = Location;
		// create PlayerData member BagData
		FBagData BagData;
		BagData.HadItems = {};
		int GridNum;
		GConfig->GetInt(
			TEXT("GameSaveInit/Player/BagData"),
			TEXT("GridNum"),
			GridNum,
			GGameIni
			);
		for (int i = 0; i < GridNum; ++i)
		{
			BagData.BagGridData.Add(FBagGridData(0, 0));
		}
		BagData.BagGridData[0] = FBagGridData(10001, 1);
		PlayerData.BagData = BagData;
		
		// create ItemOnGroundData
		// TODO: ItemOnGroundData implement

		
		GameSaveData.PlayerData = PlayerData;
		GameSaveData.ItemOnGroundData = ItemOnGroundData;
		
		SaveGame(GameSaveData, RelativePath, FileName);
	}
	return GameSaveData;
}

void FFileTool::SaveGame(FGameSaveData InGameSaveData, FString RelativePath, FString FileName)
{
	
	FString JsonStr;
	SaveStrToFile(JsonStr, RelativePath, FileName);
}

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



FGameSaveData FJsonTool::GetGameSaveDataFromJsonStr(FString JsonStr)
{
	FGameSaveData GameSaveData;

	// return value as reference 
	TSharedPtr<FJsonValue> JsonValue;
	auto JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);
	
	if (FJsonSerializer::Deserialize(JsonReader, JsonValue))
	{
		auto GameSaveDataJsonObj = JsonValue->AsObject();
		// GameSaveData.PlayerData
		auto PlayerDataJsonObj = GameSaveDataJsonObj->GetObjectField(FString("PlayerData"));

		GameSaveData.PlayerData.Name = FName(PlayerDataJsonObj->GetStringField("Name"));
		GameSaveData.PlayerData.Level = PlayerDataJsonObj->GetIntegerField("Level");

		auto LocationJsonValueArray = PlayerDataJsonObj->GetArrayField("Location");
		GameSaveData.PlayerData.Location = FVector(
			LocationJsonValueArray[0]->AsNumber(),
			LocationJsonValueArray[1]->AsNumber(),
			LocationJsonValueArray[2]->AsNumber()
			);

		// GameSaveData.PlayerData.BagData 
		auto BagDataJsonObj = PlayerDataJsonObj->GetObjectField("BagData");
		// GameSaveData.PlayerData.BagData.HadItems
		auto HadItemsJsonValueArray = BagDataJsonObj->GetArrayField("HadItems");
		for (auto HadItemJsonValue : HadItemsJsonValueArray)
		{
			GameSaveData.PlayerData.BagData.HadItems.Add(HadItemJsonValue->AsNumber());
		}

		auto BagGridDataJsonValueArray = BagDataJsonObj->GetArrayField("BagGridData");
		for (auto BagGridDataJsonValue : BagGridDataJsonValueArray)
		{
			auto BagGridDataJsonObj = BagGridDataJsonValue->AsObject();
			
			GameSaveData.PlayerData.BagData.BagGridData.Add(
			FBagGridData(
				BagGridDataJsonObj->GetNumberField("ID"),
				BagGridDataJsonObj->GetNumberField("Num")
					)
				);
		}

		
		// GameSaveData.ItemOnGround
		auto ItemOnGroundJsonObj = GameSaveDataJsonObj->GetObjectField(FString("ItemOnGroundData"));
		
	}

	// add "JsonUtilities" in build.cs
	// FGameSaveData SaveData;
	// FJsonObjectConverter::JsonObjectStringToUStruct<FGameSaveData>(JsonStr, &GameSaveData, 0, 0);
	return GameSaveData;
}

FString FJsonTool::GetJsonStrFromGameSaveData(FGameSaveData GameSaveData)
{
	FString OutJsonStr;

	auto JsonWriter =
		TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJsonStr);
	// write a JSON string by JsonWriter
	JsonWriter->WriteObjectStart();
	{
		// GameSaveData.PlayerData
		JsonWriter->WriteIdentifierPrefix("PlayerData"); // automatically add ':'
		JsonWriter->WriteObjectStart();
		{
			JsonWriter->WriteValue<FString>("Name", GameSaveData.PlayerData.Name.ToString());
			JsonWriter->WriteValue<int>("Level", GameSaveData.PlayerData.Level);

			JsonWriter->WriteIdentifierPrefix("Location");
			JsonWriter->WriteArrayStart();
			JsonWriter->WriteValue<float>(GameSaveData.PlayerData.Location.X);
			JsonWriter->WriteValue<float>(GameSaveData.PlayerData.Location.Y);
			JsonWriter->WriteValue<float>(GameSaveData.PlayerData.Location.Z);
			JsonWriter->WriteArrayEnd();

			// BagData
			JsonWriter->WriteIdentifierPrefix("BagData");
			JsonWriter->WriteObjectStart();
			{
				// BagData.HadItems
				JsonWriter->WriteIdentifierPrefix("HadItems");
				JsonWriter->WriteArrayStart();
				for (auto HadItem : GameSaveData.PlayerData.BagData.HadItems)
				{
					JsonWriter->WriteValue<int>(HadItem);
				}
				JsonWriter->WriteArrayEnd();

				// BagData.BagGridData
				JsonWriter->WriteIdentifierPrefix("BagGridData");
				JsonWriter->WriteArrayStart();
				for (auto BagGridData : GameSaveData.PlayerData.BagData.BagGridData)
				{
					JsonWriter->WriteObjectStart();
					{
						JsonWriter->WriteValue<int>("ID", BagGridData.ID);
						JsonWriter->WriteValue<int>("Num", BagGridData.Num);
					}
					JsonWriter->WriteObjectEnd();
				}
				JsonWriter->WriteArrayEnd();
			}
			JsonWriter->WriteObjectEnd();
		}
		JsonWriter->WriteObjectEnd();

		// GameSaveData.ItemOnGroundData
		JsonWriter->WriteIdentifierPrefix("ItemOnGroundData");
		JsonWriter->WriteObjectStart();
		{
		}
		JsonWriter->WriteObjectEnd();
	}


	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();

	// add "JsonUtilities" in build.cs
	// FString JsonStr;
	// FJsonObjectConverter::UStructToJsonObjectString()
	return OutJsonStr;
}

FGameSaveData FFileTool::LoadGame(FString RelativePath, FString FileName)
{
	FGameSaveData GameSaveData;
	FString OutJsonStr;
	if (LoadStrFromFile(OutJsonStr, RelativePath, FileName))
	{
		GameSaveData = FJsonTool::GetGameSaveDataFromJsonStr(OutJsonStr);
	}
	else // no save data file found, create one 
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
		


		GameSaveData.PlayerData = PlayerData;
		GameSaveData.ItemOnGroundData = ItemOnGroundData;

		SaveGame(GameSaveData, RelativePath, FileName);
	}
	return GameSaveData;
}

void FFileTool::SaveGame(FGameSaveData InGameSaveData, FString RelativePath, FString FileName)
{
	FString JsonStr = FJsonTool::GetJsonStrFromGameSaveData(InGameSaveData);
	SaveStrToFile(JsonStr, RelativePath, FileName);
}

FBagGridData FGameSaveTool::GetBagGridDataByIndex(int GridIndex)
{
	auto GameSaveData = FFileTool::LoadGame();
	
	return GameSaveData.PlayerData.BagData.BagGridData[GridIndex];
}

int FGameSaveTool::GetItemInBagGridTotalNum(int ID)
{
	auto BagGridDatas = GetAllBagGridDatas();
	int TotalNum = 0;
	for (auto BagGridData : BagGridDatas)
	{
		if (BagGridData.ID == ID)
		{
			TotalNum += BagGridData.Num;
		}
	}
	return TotalNum;
}

bool FGameSaveTool::IsBagHadItem(int ID)
{
	auto GameSaveData = FFileTool::LoadGame();
	
	return GameSaveData.PlayerData.BagData.HadItems.Contains(ID);
}

void FGameSaveTool::AddViewBagGridItemID(int ID)
{
	FGameSaveData GameSaveData = FFileTool::LoadGame();
	GameSaveData.PlayerData.BagData.HadItems.Add(ID);
	FFileTool::SaveGame(GameSaveData);
}

TArray<FBagGridData> FGameSaveTool::GetAllBagGridDatas()
{
	return FFileTool::LoadGame().PlayerData.BagData.BagGridData;
}

void FGameSaveTool::SetBagGridDataByIndex(FBagGridData NewBagGrid, int FoundIndex)
{
	auto GameSaveData = FFileTool::LoadGame();
	GameSaveData.PlayerData.BagData.BagGridData[FoundIndex] = NewBagGrid;
	FFileTool::SaveGame(GameSaveData);
}

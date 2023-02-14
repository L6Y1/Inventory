// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "StructTypes.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY07_API UStructTypes : public UObject
{
	GENERATED_BODY()
};


USTRUCT(BlueprintType)
struct FWeaponAttr : public FTableRowBase
{
	GENERATED_BODY()
public:
	FWeaponAttr(){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 EquType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, float> Attrubutes;
	
};


/*
 * helper struct for FConsumables.Attributes
 */
USTRUCT(BlueprintType)
struct FConsumablesHelperValue : public FTableRowBase
{
	GENERATED_BODY()
public:
	FConsumablesHelperValue(){}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<float> Values;
};


USTRUCT(BlueprintType)
struct FConsumablesAttr : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FConsumablesAttr(){}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CD;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, float> Costs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName, FConsumablesHelperValue> Attributes;
	
};









USTRUCT(BlueprintType)
struct FItemCommonAttr : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FItemCommonAttr(){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Description;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int BuyPrice;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int SellPrice;
	
	
};



USTRUCT(BlueprintType)
struct FTipBorderWidgetType1Attr : public FTableRowBase
{
	GENERATED_BODY()
public:
	FTipBorderWidgetType1Attr(){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName BGImage; // background image

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TitleBG; // title background image
};



USTRUCT(BlueprintType)
struct FItemOnGroundAttr : public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemOnGroundAttr(){}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ActorType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName MeshName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxStackNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TipContextWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TipBorderWidgetClass;

	
};


USTRUCT(BlueprintType)
struct FItemInBagGridAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemInBagGridAttr(){}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D Size;		// grid size

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName BGImage;// background image

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ItemBorderImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ItemImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxStackNum;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsShowNum;	// whether to show num in right down corner

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TipBorderWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TipContextWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName DragWidgetClass;
};

USTRUCT()
struct FShortCutBarAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FShortCutBarAttr(){}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName GridType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName BackGroundImage;

	
};

/**
 * @brief Struct that contains attributes of navbuttons
 */
USTRUCT(BlueprintType)
struct FNavButtonAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FNavButtonAttr()
	{
	};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ShortCutKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Size;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> ButtonIcons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName OnClickedEvent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ButtonWidgetLayoutType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ToggledWidgetLayoutType;
};


/**
 * @brief Struct that contains attributes of bag widget type1
 */
USTRUCT(BlueprintType)
struct FBagWidgetType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBagWidgetType1Attr()
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D BagSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TitleName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TitleBG;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName BagBG;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> CloseButtonIcons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> SortButtonIcons;

	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName BagGridType;
};


/**
 * @brief data of individual bag grid
 */
USTRUCT(BlueprintType)
struct FBagGridData
{
	GENERATED_BODY()

public:
	FBagGridData()
	{}

	FBagGridData(int ID, int Num): ID(ID), Num(Num)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Num;
};


/**
 * @brief data of bag
 */
USTRUCT(BlueprintType)
struct FBagData
{
	GENERATED_BODY()

public:
	FBagData(){}

	// items that has been taken at least once
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> HadItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBagGridData> BagGridData;
};


/**
 * @brief data of player
 */
USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

public:
	FPlayerData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBagData BagData;
};


/**
 * @brief data of items that are on the ground
 */
USTRUCT(BlueprintType)
struct FItemOnGroundData
{
	GENERATED_BODY()

public:
	FItemOnGroundData()
	{}

	FItemOnGroundData(FName Index, FVector Location, int ID, int Num): Index(Index), Location(Location), ID(ID), Num(Num)
	{}

	// unique id to identify the item on ground
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Num;
};


/**
 * @brief Struct that contains game save data, which can be serialized, multiple member struct inside
 */
USTRUCT(BlueprintType)
struct FGameSaveData
{
	GENERATED_BODY()

public:
	FGameSaveData()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FItemOnGroundData> ItemOnGroundDatas;
};



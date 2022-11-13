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
struct FItemInBagGirdAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemInBagGirdAttr(){}

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
	{
	}

	FBagGridData(int ID, int Num): ID(ID), Num(Num)
	{
		
	}

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
	{
	}

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
 * @brief data of items that are (or can be placed) on the ground
 */
USTRUCT(BlueprintType)
struct FItemOnGroundData
{
	GENERATED_BODY()

public:
	FItemOnGroundData()
	{
	}
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
	FItemOnGroundData ItemOnGroundData;
};



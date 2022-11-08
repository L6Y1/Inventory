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

// UStruct that contains attributes of navbuttons
USTRUCT(BlueprintType)
struct FNavButtonAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FNavButtonAttr() {};

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

// UStruct that contains attributes of bag widget type1
USTRUCT(BlueprintType)
struct FBagWidgetType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
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
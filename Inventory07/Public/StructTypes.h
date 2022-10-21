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

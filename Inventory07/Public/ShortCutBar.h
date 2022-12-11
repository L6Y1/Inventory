// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StructTypes.h"
#include "ShortCutBar.generated.h"

class UBorder;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UShortCutBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox *ShortCutHorBox;

	UPROPERTY(meta=(BindWidget))
	UBorder *BGBorder;

	UFUNCTION()
	void Init(FShortCutBarAttr ShortCutBarAttr);
};

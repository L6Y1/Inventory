// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructTypes.h"
#include "Blueprint/UserWidget.h"
#include "NavButtonWidgetType1.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UNavButtonWidgetType1 : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UTextBlock *ShortCutKeyText;
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UButton *NavButton;

	
	UFUNCTION()
	void Init(FNavButtonAttr NavButtonAttr);
};

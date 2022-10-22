// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

class UHorizontalBox;
/**
 * 
 */
UCLASS()
class INVENTORY07_API UMainUI : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// equal to BeginPlay()
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox *NavButtonPanel;
};

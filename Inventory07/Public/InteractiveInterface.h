// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORY07_API IInteractiveInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//进入的时候
	// virtual void Enter(class AActor* User) = 0;
	// //离开的时候
	// virtual void Exit(class AActor* User) = 0;
	// //停留Tick
	// virtual void StayTick(class AActor* User, float DeltaTime) = 0;
	//
	// //开始交互
	// virtual void BeginInteraction(class AActor* User, class UInteractiveComponent* InteractiveComponent) = 0;
	// //结束交互
	// virtual void EndInteraction(class AActor* User) = 0;
	// //正在交互 tick
	// virtual void InteractionTick(class AActor* User, float DeltaTime, class UInteractiveComponent* InteractiveComponent) = 0;
};

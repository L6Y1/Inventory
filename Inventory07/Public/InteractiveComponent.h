// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractiveComponent.generated.h"

class IInteractiveInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY07_API UInteractiveComponent : public UActorComponent
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this component's properties
	UInteractiveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


// private:
// 	IInteractiveInterface *Current;
// 	IInteractiveInterface *Previous;
// 	IInteractiveInterface *Interacting;
//
// 	float SphereTraceRadius = 170;
// public:
// 	/**
// 	 * @brief select a actor in a list of detected actors, by a specified rule
// 	 * @param InteractableActors : all detected actors
// 	 * @return actor that is chosen
// 	 */
// 	virtual IInteractiveInterface* ChooseInteractable(TArray<IInteractiveInterface*> InteractableActors);
//
// 	UFUNCTION(BlueprintCallable)
// 	bool StartInteraction(AActor* &OutUser, AActor* &OutItem);
// 	
// 	UFUNCTION(BlueprintCallable)
// 	AActor* EndInteraction(AActor* &OutUser);
// 	
};

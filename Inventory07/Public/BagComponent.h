// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BagComponent.generated.h"


class FGameSaveTool;


/**
 * @brief
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY07_API UBagComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBagComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void InspectBagGridItem(int GridIndex);
	
	UFUNCTION(BlueprintCallable)
	int AddItem(int ID, int Amount);
	
	UFUNCTION(BlueprintCallable)
	bool SubItem(int ID, int Amount);

	/**
	 * @brief first get all data of item in bag, make a TMap 'AllItems'.
	 * With each Tuple in TMap, fill grid with MaxStackNum of item, rest of the item to fill one grid.
	 * Fill the rest grid with empty grid.
	 * 
	 */
	UFUNCTION()
	void SortGridItem();

	UFUNCTION()
	void StartPickupItemFromGround(AActor *User, FName Index, FVector NewLocation);

	UFUNCTION()
	void DragBagGridToOtherBagGrid(int FromIndex, int ToIndex);

	UFUNCTION()
	void BagGridDragToGround(int GridIndex);
	
	// find the index of grid which contains given id item, that most equal to full grid stack num
	int FindFreeGridIndex(int ID);
	// find the index of a empty grid
	int FindEmptyGridIndex();
	// find the index of grid which contains given id item, that most not equal to full grid stack num
	int FindMinNumGrid(int ID);

	UFUNCTION()
	void SpawnItemOnGround(int ID, int Num, FVector Location);
};
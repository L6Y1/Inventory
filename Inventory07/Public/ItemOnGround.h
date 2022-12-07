// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveInter.h"
#include "InteractiveInterface.h"
#include "GameFramework/Actor.h"
#include "ItemOnGround.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UWidgetComponent;

UCLASS()
class INVENTORY07_API AItemOnGround : public AActor, public IInteractiveInter
{
	GENERATED_BODY()
	
public:
	
	AItemOnGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent *Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent *ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent *WidgetComp;

	FName ItemIndex;


	
	UFUNCTION()
	void Init(FName Index);

	void UpdateDisplay(FName Index);

	UFUNCTION()
	void OnUpdateItemOnGround(FName Index);
	
	UFUNCTION()
	void OnItemOnGroundBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bBFromSweep,
									const FHitResult & SweepResult);
	UFUNCTION()
	void OnHitGround(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);
	// Sets default values for this actor's properties

public:
	//begin InteractiveInter impl
	virtual void Enter(AActor *User) override;
	virtual void Exit(AActor *User) override;
	virtual void StayTick(AActor *User, float DeltaTime) override;
	
	virtual void BeginInteraction(AActor *User, UInteractiveComp *InteractiveComponent) override;
	virtual void EndInteraction(AActor *User) override;
	virtual void InteractionTick(AActor *User, float DeltaTime, UInteractiveComp *InteractiveComponent) override;
	//~end InteractiveInter impl

};
// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveComponent.h"
#include "InteractiveInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UInteractiveComponent::UInteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// trace result
	TArray<FHitResult> OutHits;

	// all interactable actors
	TArray<IInteractiveInterface*> InteractableActors;
	
	if (
		UKismetSystemLibrary::SphereTraceMulti(
			this,
			this->GetOwner()->GetActorLocation(),
			this->GetOwner()->GetActorLocation() + FVector(0, 0, 10),
			SphereTraceRadius,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			true,
			{ this->GetOwner() },
			EDrawDebugTrace::ForOneFrame,
			OutHits,
			true)
		)
	{
		for (auto HitResult : OutHits)
		{
			// if it is a interactable actor, add to list
			IInteractiveInterface *InteractableActor = Cast<IInteractiveInterface>(HitResult.Actor);
			if (InteractableActor)
			{
				InteractableActors.AddUnique(InteractableActor);
			}
		}
	}

	Current = ChooseInteractable(InteractableActors);
	if (Current != nullptr)
	{
		Current->StayTick(this->GetOwner(), DeltaTime);
	}
	if (Interacting != nullptr)
	{
		Interacting->InteractionTick(this->GetOwner(), DeltaTime, this);
	}

	// no target previous frame, but get one target this frame
	if (Current != nullptr && Previous == nullptr)
	{
		Current->Enter(this->GetOwner());	
	}
	else if (Previous != nullptr && Current == nullptr)
	{
		Previous->Exit(this->GetOwner());
	}
	else if (Current != nullptr && Previous != nullptr && Previous != Current)
	{
		Previous->Exit(this->GetOwner());
		Current->Enter(this->GetOwner());
	}

	Previous = Current;
}

IInteractiveInterface * UInteractiveComponent::ChooseInteractable(TArray<IInteractiveInterface *> InteractableActors)
{
	float MinDistance = 999999;
	IInteractiveInterface *NearestActor = nullptr;
	for (auto Actor : InteractableActors)
	{
		// calculate the distance between player and the actor
		float TempDistance = FVector::Dist(Cast<AActor>(Actor)->GetActorLocation(), this->GetOwner()->GetActorLocation());

		if (TempDistance < MinDistance)
		{
			MinDistance = TempDistance;
			NearestActor = Actor;
		}
	}
	return NearestActor;
}

bool UInteractiveComponent::StartInteraction(AActor *&OutUser, AActor *&OutItem)
{
	if (Current != nullptr && Interacting == nullptr)
	{
		Interacting = Current;
		Interacting->BeginInteraction(this->GetOwner(), this);
		OutUser = GetOwner();
		OutItem = Cast<AActor>(Interacting);
		return true;
	}
	OutUser = nullptr;
	OutItem = nullptr;
	return false;
}

AActor* UInteractiveComponent::EndInteraction(AActor *&OutUser)
{
	auto Temp = Cast<AActor>(Interacting);
	if (Interacting != nullptr)
	{
		Interacting->EndInteraction(this->GetOwner());
		OutUser = GetOwner();
		Interacting = nullptr;
		return Temp;
	}
	OutUser = nullptr;
	return nullptr;
}

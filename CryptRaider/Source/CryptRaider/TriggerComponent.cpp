// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetAcceptableActor() != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.35f, FColor::Cyan, FString::Printf(TEXT("Unlocking")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.35f, FColor::Cyan, FString::Printf(TEXT("Relocking")));
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> actors;

	GetOverlappingActors(actors);

	for (auto actor : actors)
	{
		if (actor->ActorHasTag(statueTag))
		{
			return actor;
		}
	}

	return nullptr;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	FHitResult hitResult;

	DrawDebugLine(GetWorld(), start, end, FColor::Red);

	bool hit = GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, sphere);

	if (hit)
	{
		UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *hitResult.GetActor()->GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Hit actor: none"));
	}*/
}

void UGrabber::Grab()
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	FHitResult hitResult;

	//DrawDebugLine(GetWorld(), start, end, FColor::Red);

	bool hit = GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, sphere);

	if (hit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.35f, FColor::Cyan, FString::Printf(TEXT("Grabbed!")));
		grabbed = true;
	}
}

void UGrabber::Release()
{
	if (grabbed)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.35f, FColor::Cyan, FString::Printf(TEXT("Released!")));
		grabbed = false;
	}
}
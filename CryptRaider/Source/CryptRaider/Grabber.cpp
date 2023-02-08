// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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

	GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	FHitResult hitResult;

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 5.0f);
	DrawDebugSphere(GetWorld(), end, 10, 10, FColor::Blue, false, 5.0f);

	bool hit = GetWorld()->SweepSingleByChannel(hitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, sphere);

	if (hit)
	{

		FVector location = hitResult.Location;
		DrawDebugSphere(GetWorld(), location, 10, 10, FColor::Red, false, 5.0f);

		location = hitResult.ImpactPoint;
		DrawDebugSphere(GetWorld(), location, 10, 10, FColor::Green, false, 5.0f);

		grabbed = true;
	}
}

void UGrabber::Release()
{
	if (grabbed)
	{
		grabbed = false;
	}
}
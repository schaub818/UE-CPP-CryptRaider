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

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!physicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Player blueprint does not have a physics handle component."));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (physicsHandle && grabbed)
	{
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult& outHitResult) const
{
	if (!physicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Player blueprint does not have a physics handle component."));

		return false;
	}

	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECC_GameTraceChannel2, sphere);
}

void UGrabber::Grab()
{
	FHitResult hitResult;

	if (GetGrabbableInReach(hitResult))
	{
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();

		hitComponent->SetSimulatePhysics(true);
		hitComponent->WakeAllRigidBodies();
		hitResult.GetActor()->Tags.Add("Grabbed");
		physicsHandle->GrabComponentAtLocationWithRotation(hitComponent, NAME_None, hitResult.ImpactPoint, GetComponentRotation());

		grabbed = true;
	}
}

void UGrabber::Release()
{
	if (physicsHandle && grabbed)
	{
		physicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		physicsHandle->ReleaseComponent();

		grabbed = false;
	}
}
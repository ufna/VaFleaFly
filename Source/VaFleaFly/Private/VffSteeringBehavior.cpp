// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#include "VffSteeringBehavior.h"
#include "VffPawnMovementComponent.h"

FVffBehavior_Seek::FVffBehavior_Seek()
	: FVffSteeringBehavior("Seek")
{
	Destination = FVector::ZeroVector;
	AcceptanceRadius = 5.f;
}

FVffBehavior_Seek::FVffBehavior_Seek(const FVector &InDestination, float InAcceptanceRadius)
	: FVffSteeringBehavior("Seek")
{
	Destination = InDestination;
	AcceptanceRadius = InAcceptanceRadius;
}

void FVffBehavior_Seek::TickBehavior(float DeltaTime, UVffPawnMovementComponent* MovementManager)
{
	const FVector DistVect = Destination - MovementManager->UpdatedComponent->GetComponentLocation();

	// Use 2D to prevent precise calculation bases on Z value
	// @TODO Check possible EPathFollowingReachMode usage
	if(DistVect.SizeSquared2D() > FMath::Square(AcceptanceRadius))
	{
		MovementManager->Velocity = DistVect.GetSafeNormal2D() * MovementManager->GetMaxSpeed();
	}
	else
	{
		MovementManager->Velocity = FVector::ZeroVector;
	}
}

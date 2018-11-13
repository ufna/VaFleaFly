// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#include "VffSteeringBehavior.h"
#include "VffPawnMovementComponent.h"

FVffBehavior_Seek::FVffBehavior_Seek()
	: FVffSteeringBehavior("Seek")
{
	Destination = FVector::ZeroVector;
}

FVffBehavior_Seek::FVffBehavior_Seek(const FVector &InDestination)
	: FVffSteeringBehavior("Seek")
{
	Destination = InDestination;
}

void FVffBehavior_Seek::TickBehavior(float DeltaTime, UVffPawnMovementComponent* MovementManager)
{
	const FVector DistVect = Destination - MovementManager->UpdatedComponent->GetComponentLocation();

	// Use 2D to prevent precise calculation bases on Z value
	if(DistVect.SizeSquared2D() > 36.f)
	{
		MovementManager->Velocity = DistVect.GetSafeNormal2D() * MovementManager->GetMaxSpeed();
	}
	else
	{
		MovementManager->Velocity = FVector::ZeroVector;
	}
}

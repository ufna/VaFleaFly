// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#include "VffPawnMovementComponent.h"
#include "VffCommon.h"

UVffPawnMovementComponent::UVffPawnMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


//////////////////////////////////////////////////////////////////////////
// Initialization

void UVffPawnMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UVffPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	/** @TEMP Ground Normal.Z min value to apply gravity */
	static const float MIN_NORMAL_Z_GRAVITY = FMath::Sin(2 * PI / 180);

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Super tick may destroy/invalidate CharacterOwner or UpdatedComponent, so we need to re-check
	if (!UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Calculate distance to current path point
	const FVector DistVect = (DesiredPathPoint - UpdatedComponent->GetComponentLocation());

	// Check we have path point to follow
	if (!DesiredPathPoint.IsZero())
	{
		// @TEMP
		Velocity = DistVect.GetSafeNormal2D() * GetMaxSpeed();

		// Try to make a move
		FHitResult Hit;
		SafeMoveUpdatedComponent(Velocity * DeltaTime, GetOwner()->GetActorRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			// If the target is not a wall, turn off gravity
			if (Hit.Normal.Z > MIN_NORMAL_Z_GRAVITY) 
			{
				Velocity.Z = 0;
			}

			SlideAlongSurface(Velocity * DeltaTime, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
	else 
	{
		// Stop when we've reached the destination
		if (Velocity.SizeSquared() > 0)
		{
			StopMovementImmediately();
		}
	}

	UpdateComponentVelocity();
}


//////////////////////////////////////////////////////////////////////////
// Steering Behavior handlers





//////////////////////////////////////////////////////////////////////////
// Path control

void UVffPawnMovementComponent::RequestDirectMoveToLocation(const FVector& Location)
{
	DesiredPathPoint = Location;
}


//////////////////////////////////////////////////////////////////////////
// Movement control

float UVffPawnMovementComponent::GetMaxSpeed() const
{
	// @TODO Fix me
	return 600.f;
}


//////////////////////////////////////////////////////////////////////////
// Debug

void UVffPawnMovementComponent::DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	// @TODO
}

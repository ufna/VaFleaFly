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

	// Iterate throw all active behaviors
	for(auto &Behavior : Behaviors)
	{
		Behavior->TickBehavior(DeltaTime, this);
	}

	// Check we have path point to follow
	if (!Velocity.IsNearlyZero())
	{
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
		StopMovementImmediately();
	}

	UpdateComponentVelocity();
}


//////////////////////////////////////////////////////////////////////////
// Steering Behavior handlers

void UVffPawnMovementComponent::AddBehavior(TSharedRef<FVffSteeringBehavior> BehaviorPtr)
{
	UE_LOG(LogVaFleaFly, Verbose, TEXT("%s: %s. Behaviors.Num()=%d"), *VA_FUNC_LINE, *BehaviorPtr->Name.ToString(), Behaviors.Num());

	// Check for duplicates and remove them if necessary
	for(int32 i = 0; i < Behaviors.Num(); ++i)
	{
		auto OtherBehaviorPtr = Behaviors[i];
		if (OtherBehaviorPtr.IsValid())
		{
			if (BehaviorPtr->Name == OtherBehaviorPtr->Name)
			{
				UE_LOG(LogVaFleaFly, Verbose, TEXT("%s: Remove duplicate with id: %d"), *VA_FUNC_LINE, i);
				
				Behaviors.RemoveAt(i--);
			}
		}
	}

	Behaviors.Add(BehaviorPtr);
}


//////////////////////////////////////////////////////////////////////////
// Path control

void UVffPawnMovementComponent::RequestDirectMoveToLocation(const FVector& Location)
{
	UE_LOG(LogVaFleaFly, Warning, TEXT("%s: %s"), *VA_FUNC_LINE, *Location.ToString());
	
	AddBehavior(MakeShareable(new FVffBehavior_Seek(Location)));
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

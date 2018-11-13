// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "VffSteeringBehavior.generated.h"

class UVffPawnMovementComponent;

/**
 * Parent class for all steering behaviors
 */
USTRUCT(BlueprintType)
struct FVffSteeringBehavior
{
	GENERATED_USTRUCT_BODY()

	/** Unique behavior name used as key */
	FName Name;

public:
	FVffSteeringBehavior()
		: Name("") 
	{}
	
	FVffSteeringBehavior(FName InActionName)
		: Name(InActionName)
	{}
	
	/** Implement custom behavior logic here */
	virtual void TickBehavior(float DeltaTime, UVffPawnMovementComponent* MovementManager) PURE_VIRTUAL(FVffSteeringBehavior::TickBehavior, );

	virtual ~FVffSteeringBehavior() {};

};

/** 
 * Seek steering behavior
 */
USTRUCT()
struct FVffBehavior_Seek : public FVffSteeringBehavior
{
	GENERATED_USTRUCT_BODY()
	
public:
	FVffBehavior_Seek();
	FVffBehavior_Seek(const FVector &InDestination);
	
	virtual void TickBehavior(float DeltaTime, UVffPawnMovementComponent* MovementManager) override;

public:
	/** Target location */
	UPROPERTY(BlueprintReadWrite)
	FVector Destination;

};
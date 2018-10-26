// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "VffSteeringBehavior.generated.h"

USTRUCT()
struct FVffSteeringBehavior
{
	GENERATED_USTRUCT_BODY()

public:
	/** Implement custom behavior logic here */
	virtual void UpdateVelocity(FVector &InVelocity) PURE_VIRTUAL(FVffSteeringBehavior::UpdateVelocity, );

	virtual ~FVffSteeringBehavior() {};

};

// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "GameFramework/PawnMovementComponent.h"

#include "VffPawnMovementComponent.generated.h"

UCLASS(config = Game, defaultconfig)
class VAFLEAFLY_API UVffPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_UCLASS_BODY()


	//////////////////////////////////////////////////////////////////////////
	// Initialization

protected:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


	//////////////////////////////////////////////////////////////////////////
	// Steering Behavior handlers

protected:
	/**  */
	


	//////////////////////////////////////////////////////////////////////////
	// Path control

public:
	/** [Debug] Force move to location */
	UFUNCTION(BlueprintCallable, Category = "Vff|Movement")
	void RequestDirectMoveToLocation(const FVector& Location);

protected:
	/** Desired destionation location */
	FVector DesiredPathPoint;


	//////////////////////////////////////////////////////////////////////////
	// Movement control

public:
	//~ Begin UMovementComponent Interface
	virtual float GetMaxSpeed() const override;
	//~ End UMovementComponent Interface


	//////////////////////////////////////////////////////////////////////////
	// Debug

public:
	/** Draw debug lines to show the desired path */
	virtual void DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos);

};

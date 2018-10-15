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

};

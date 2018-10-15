// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#include "VffPawnMovementComponent.h"

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
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


//////////////////////////////////////////////////////////////////////////
// Debug

void UVffPawnMovementComponent::DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	// @TODO
}

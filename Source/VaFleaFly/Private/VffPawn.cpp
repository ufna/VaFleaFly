// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#include "VffPawn.h"
#include "VffPawnMovementComponent.h"

#include "Engine/CollisionProfile.h"
#include "DisplayDebugHelpers.h"

FName AVffPawn::PawnMovementComponentName(TEXT("PawnMovementComp"));

AVffPawn::AVffPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnMovement = CreateDefaultSubobject<UVffPawnMovementComponent>(PawnMovementComponentName);
	PawnMovement->SetIsReplicated(true);		// Enable replication by default
	// Use SetUpdatedComponent() function in your pawn instead
	// PawnMovement->UpdatedComponent = ...;
}


//////////////////////////////////////////////////////////////////////////
// Mesh and physics access

UPawnMovementComponent* AVffPawn::GetMovementComponent() const
{
	return PawnMovement;
}


//////////////////////////////////////////////////////////////////////////
// Debug

void AVffPawn::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	static FName NAME_Pawn = FName(TEXT("Pawn"));

	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);

	// @TODO Debug movement component
}

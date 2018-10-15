// Copyright 2018 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "GameFramework/Pawn.h"

#include "VffPawn.generated.h"

UCLASS(abstract, config = Game, Blueprintable, BlueprintType)
class VAFLEAFLY_API AVffPawn : public APawn
{
	GENERATED_UCLASS_BODY()


	//////////////////////////////////////////////////////////////////////////
	// Pawn setup

private:
	/** Pawn simulation component */
	UPROPERTY(Category = Pawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UVffPawnMovementComponent* PawnMovement;

public:
	/** Name of the PawnMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName PawnMovementComponentName;

	/** Util to get the casted Pawn movement component */
	FORCEINLINE UVffPawnMovementComponent* GetPawnMovement() const { return PawnMovement; }
	FORCEINLINE UVffPawnMovementComponent* GetPawnMovementComponent() const { return PawnMovement; }

	//~ Begin APawn Interface.
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	//~ End APawn Interface

	//~ Begin AActor Interface
	virtual void DisplayDebug(class UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
	//~ End AActor Interface

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) ) //BlueprintSpawnableComponent make is add-able in BP
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	// We don't need to call it because using the MoveToActor already call this.
	// From the PathFinding Logic ( AIController.h)
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force
 * Is used to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Set throttle [-1,1]
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Force = mass * acceleration
	// Max force per track, in Newtons 
	UPROPERTY(EditDefaultsOnly)
		float TrackmaxDrivingForce = 400000;    // Assume 40 tons tanks, 1g acceleration.
private:
	UTankTrack();
};

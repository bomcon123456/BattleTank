// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:	

	virtual void BeginPlay() override; // This makes sure that this is the beginplay we using, not the begin play which
							   // inherits from this class's parent ( which is the AActor [has a beginplay funct]
	/** if we put
		virtual void BeginPlay()
		virtual says that if this class has children, they can overlap this funct.
	*/
	virtual void Tick(float DeltaTime) override;

protected:
	// Be in protected because the BP derived from this is a subclass => can access.
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

private:
	UPROPERTY(EditDefaultsOnly,Category= "Crosshair")
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Crosshair")
	float CrosshairYLocation = 0.3333f;
	UPROPERTY(EditDefaultsOnly, Category= "Crosshair")
	float LineTraceRange = 1000000;
		

	// Get the pointer to the controlling tank

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();
	
	// Return an OUT parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	// Return LookDirection OUT parameter, whichi is the direction we look through crosshair
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	// Return HitLocation OUT parameter
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};

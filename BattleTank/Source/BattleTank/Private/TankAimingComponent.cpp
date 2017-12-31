// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
//	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	// Calculate a launch velocity for a projectile to hit a specific point with such LaunchSpeed, start+hit location
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,			// TossVelocity -- which is the output
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,						// Use HighArc ( take more time and higher) or LowArc ( takes less time, lower)	
		0.0f,							// Collision Radius = 0		
		0.0f,							// Override Gravity ? means fuck the gravity man
		ESuggestProjVelocityTraceOption::DoNotTrace
	);			
	if (bHaveAimSolution)			// If true, we've already had a Launch velocity vector, which has the angle to shoot too
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();	// normalized this vector, by divide the OutLaunchVelocity with its length
																// So it becomes unit vector which 0<=x,y,z<=1
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time)

	}
	// If no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	// Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();		// Get the foward ( X-Axis) unit vector of barrel then get its rotation
	auto AimAsRotator = AimDirection.Rotation();					// This is the end angle-result by taking the rotation of the launch velocity
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);		// How many unit location the barrel has to come up.
	if (FMath::Abs(DeltaRotator.Yaw) > 180.0f)
		DeltaRotator.Yaw *= -1.0f;
	Turret->Rotate(DeltaRotator.Yaw);
}

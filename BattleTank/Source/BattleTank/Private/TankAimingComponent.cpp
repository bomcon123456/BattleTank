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
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

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
		0,							// Collision Radius = 0		
		0,							// Override Gravity ? means fuck the gravity man
		ESuggestProjVelocityTraceOption::DoNotTrace
	);			
	if (bHaveAimSolution)			// If true, we've already had a Launch velocity vector, which has the angle to shoot too
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();	// normalized this vector, by divide the OutLaunchVelocity with its length
																// So it becomes unit vector which 0<=x,y,z<=1
		MoveBarrelTowards(AimDirection);
		MoveTurretAside(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solve found"), Time)

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
	// Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();		// Get the foward ( X-Axis) unit vector of barrel then get its rotation
	auto AimAsRotator = AimDirection.Rotation();					// This is the end angle-result by taking the rotation of the launch velocity
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);		// How many unit location the barrel has to come up.
}

void UTankAimingComponent::MoveTurretAside(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);
}
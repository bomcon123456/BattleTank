// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"

#define OUT
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();			// Do this function in the parent first!

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
		UE_LOG(LogTemp, Warning, TEXT("PlayerController isn't possesing any tank"))
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possesed by %s"), *(ControlledTank->GetName()))
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());  
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())	//If can't find any tank to controll
	{
		return;	
	}
	
	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}
// rebmeced12  down 125k; MSBJOY

// Get world location if linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	/// Done, ScreenLocation is the crosshair location
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// "De-project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraWorldLocation,	//Trash
		OUT LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;	//This contains the Location of the Hitted object, we access it from here.
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult,
											StartLocation,
											EndLocation,
											ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.0f);
	return false;
}
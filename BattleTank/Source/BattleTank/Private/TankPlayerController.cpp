// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


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
	//AimTowardsCrosshair();

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
	// Get world location if linetrace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point.
}
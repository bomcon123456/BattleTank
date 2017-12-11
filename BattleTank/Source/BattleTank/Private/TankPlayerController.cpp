// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();			// Do this function in the parent first!
	
	auto ControlledTank = GetControlledTank();
	if(!ControlledTank)
		UE_LOG(LogTemp,Warning,TEXT("PlayerController isn't possesing any tank"))
	UE_LOG(LogTemp, Warning, TEXT("PlayerController is possesed by %s"),*(ControlledTank->GetName()))
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());  
}
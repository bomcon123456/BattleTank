// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController can't find player tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found %s"), *(PlayerTank->GetName()))
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	// This variable will point at the pawn that the PController possesses, which may not be our tank
	// Doing this first instead of casting right away, so if we didn't put the tank in the game
	// Game didn't crash because shiety pointer
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr; // Because function returns a tank;
	}
	return Cast<ATank>(PlayerPawn);	// This will fail if the PlayerPawn is nullptr/invalid ptr
									// Return PlayerPawn will be more easy.
}
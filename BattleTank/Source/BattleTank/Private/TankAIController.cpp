// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


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

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetPlayerTank())
	{
		// TODO Move towards the player

		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		
		// TODO Fire if ready
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


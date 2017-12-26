// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = Cast<ATank>(GetPawn());
	if(PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);	// The rest we use like what was set up before by the dev


		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		ControlledTank->Fire();
	}
}
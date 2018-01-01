// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }
/////////	MOVE TO ACTOR AND FIRE ///////
	MoveToActor(PlayerTank, AcceptanceRadius);	// The rest of parameters we use like what was set up before by the dev

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	// Only hit when lock or aim
	if(AimingComponent->GetFiringState() == EFiringState::Locked)
		AimingComponent->Fire();
}
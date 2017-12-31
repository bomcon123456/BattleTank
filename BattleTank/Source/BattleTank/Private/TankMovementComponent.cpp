// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	/*
	* We only care about the direction so we GetSafeNormal to transform to the unit vector ( 1,1,1)
	* GetFowardVector is Get the unitvector (1,0,0) which is in the X-axis's World rotation
	* DotProduct => A.B = |A| * |B| * cos(delta(A,B)); =>tich vo huong
	* CrossProduct => A x B = |A| * |B| * sin(delta(A,B))* n , n is the pendicular(phap tuyen) of the plane created by A and B=> tich co huong 
	*/
	auto TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIFowardIntention = MoveVelocity.GetSafeNormal();

	auto FowardThrow = FVector::DotProduct(TankFoward, AIFowardIntention);
	IntendMoveForward(FowardThrow);

	auto RightThrow = FVector::CrossProduct(TankFoward, AIFowardIntention).Z;
	IntendTurnRight(RightThrow); 
}
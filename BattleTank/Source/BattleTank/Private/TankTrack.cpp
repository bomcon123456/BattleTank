// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());
	// Calculate and apply sideways for (F = m.a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; //because 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO Clamp actual throttle value so can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackmaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	// Cast to Primitive Component so we can add force ( which we can't if it is a scene component)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



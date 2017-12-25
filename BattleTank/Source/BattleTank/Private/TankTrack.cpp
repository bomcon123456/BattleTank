// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO Clamp actual throttle value so can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackmaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	// Cast to Primitive Component so we can add force ( which we can't if it is a scene component)
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



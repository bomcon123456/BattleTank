// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	auto Rotation = (FMath::Clamp<float>(RawNewRotation, MinRotationDegrees, MaxRotationDegrees));

	//UE_LOG(LogTemp,Warning,TEXT("Rotate function working"))
	SetRelativeRotation(FRotator(0, Rotation, 0));
}

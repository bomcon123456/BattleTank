// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override; // override makes this override the same function name of its parent
									   // virtual means that child of this funct can override this funct
									   // Declare this only using void BeginPlay()
private:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	
};

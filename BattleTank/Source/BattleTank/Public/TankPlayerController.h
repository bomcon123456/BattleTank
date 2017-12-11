// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:	
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override; // This makes sure that this is the beginplay we using, not the begin play which
							   // inherits from this class's parent ( which is the AActor [has a beginplay funct]
	/** if we put
		virtual void BeginPlay()
		virtual says that if this class has children, they can overlap this funct.
	*/
};

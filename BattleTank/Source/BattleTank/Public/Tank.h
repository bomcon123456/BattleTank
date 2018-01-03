// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Foward Declaration 

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
/*	UPROPERTY(BlueprintReadOnly)		// This make the blueprint derived one can call this variable (in event graph!!)*/

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
public:
	UPROPERTY(EditDefaultsOnly, Category ="Setup")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	int32 CurrentHealth = StartingHealth;


	// Called by the engine
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};

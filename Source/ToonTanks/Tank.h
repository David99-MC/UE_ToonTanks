// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Constructor to set default values for this pawn's properties
	ATank();

	// Called every frame to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() { return tankPlayerController; };

	bool bAlive = true;

private:
	UPROPERTY(VisibleAnywhere, Category = "Follow Camera")
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Follow Camera")
	class UCameraComponent* followCam;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 400.f;
	void Move(float value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnRate = 100.f;
	void Turn(float value);

	APlayerController* tankPlayerController;

	
};

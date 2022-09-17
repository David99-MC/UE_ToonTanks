// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() 
{
    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArm->SetupAttachment(RootComponent);

    followCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
    followCam->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    tankPlayerController = Cast<APlayerController>(GetController());
    // The object returned by GetController() is an "APlayerController object" that's stored in an AController pointer
    // After casting, a pointer of type APlayerController is returned.
}

// Called every frame to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (tankPlayerController) {
        FHitResult hitResult;
        tankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
        RotateTurret(hitResult.ImpactPoint);
    }
}

void ATank::Move(float value) 
{
    FVector deltaLocation(0.f);
    deltaLocation.X = value * speed * UGameplayStatics::GetWorldDeltaSeconds(this);

    // move the pawn in its LOCAL direction instead of world's
    AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float value)
{
    FRotator deltaRotation(0.f);
    deltaRotation.Yaw = value * turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

    // turn the pawn using its LOCAL rotation
    AddActorLocalRotation(deltaRotation, true);
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
    
}

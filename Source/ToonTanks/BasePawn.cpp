// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsuleComp;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(capsuleComp); // attach to either RootComponent or capsuleComp

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

void ABasePawn::RotateTurret(FVector lookAtTarget)
{
	FVector direction = lookAtTarget - turretMesh->GetComponentLocation(); // direction vector
	FRotator lookAtRotation = FRotator(0.f, direction.Rotation().Yaw, 0.f);

	turretMesh->SetWorldRotation(
			FMath::RInterpTo(
				turretMesh->GetComponentRotation(), 
				lookAtRotation, 
				UGameplayStatics::GetWorldDeltaSeconds(this),
				15.f)
			);
}

void ABasePawn::Fire()
{
	auto projectile = GetWorld()->SpawnActor<AProjectile>(
		projectileClass,
		projectileSpawnPoint->GetComponentLocation(),
		projectileSpawnPoint->GetComponentRotation());
	// projectileClass is a UClass object which is a blueprint based on C++ Projectile class

	projectile->SetOwner(this); // this is to set the owner of the projectile to the pawn that spawned it.
	 
}

void ABasePawn::HandleDestruction() // this is to be called in the GameMode 
{
	// TODO: Visual/Sound Effects
	UGameplayStatics::SpawnEmitterAtLocation(this, deathParticles, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(deathCameraShakeClass);
}
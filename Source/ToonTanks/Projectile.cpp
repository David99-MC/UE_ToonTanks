// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	projectileMovementComponent->InitialSpeed = 10.f;
	projectileMovementComponent->MaxSpeed = 100.f;

	smokeTrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail Particle"));
	smokeTrailParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hitResult)
{
	auto myOwner = GetOwner();
	if (myOwner == NULL) 
	{
		Destroy();
		return;
	}
	auto myOwnerInstigator = myOwner->GetInstigatorController();
	auto damageTypeClass = UDamageType::StaticClass();

	// if otherActor is not this particular projectile and its owner
	if (otherActor && otherActor != this && otherActor != myOwner)  
	{
		UGameplayStatics::ApplyDamage(otherActor, damage, myOwnerInstigator, this, damageTypeClass);
		UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
	}
	Destroy();
}
 


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* projectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hitResult);

	UPROPERTY(EditAnywhere)
	float damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* hitParticle;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* smokeTrailParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* launchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* hitSound;
};

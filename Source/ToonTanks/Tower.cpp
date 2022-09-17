// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
    Super::BeginPlay();
    DrawDebugSphere(GetWorld(), GetActorLocation(), fireRange, 20, FColor::Red, true);
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::CheckFireCondition, fireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (IsInRange()) RotateTurret(tank->GetActorLocation());
}

void ATower::CheckFireCondition()
{
    if (IsInRange() && tank->bAlive) Fire();
}

bool ATower::IsInRange()
{
    if (tank) {
        float distance = FVector::Distance(GetActorLocation(), tank->GetActorLocation());
        return distance <= fireRange;
    }
    return false;
}

void ATower::HandleDestruction()
{
    // use the Super version so when HandleDestruction in ABasePawn is called, we'll get the sound/visual fx;
    Super::HandleDestruction(); 
    Destroy();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    targetTowers = GetTargetTowerCount();
    toonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    StartGame(); // this is implemented in Blueprint
    if (toonTanksPlayerController) 
    {
        toonTanksPlayerController->SetPlayerEnabledState(false);
        FTimerHandle playerEnableTimerHandle;
        FTimerDelegate playerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            toonTanksPlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState, 
            true);

        GetWorldTimerManager().SetTimer(
            playerEnableTimerHandle,
            playerEnableTimerDelegate,
            startDelayRate,
            false);
    }
}

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
    ATank* tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ATower* tower = Cast<ATower>(deadActor);

    if (deadActor == tank)
    {
        tank->HandleDestruction();
        if (toonTanksPlayerController)
        {
            toonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }
    else if (deadActor == tower)
    {
        //tower->HandleDestruction();
        tower->HandleDestruction();
        targetTowers -= 1;
        if (targetTowers <= 0)
        {
            GameOver(true);
        }
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towers);
    return towers.Num();
    
}
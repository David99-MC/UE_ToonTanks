// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	void BeginPlay();
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

public:
	void ActorDied(AActor* deadActor);

private:
	class AToonTanksPlayerController* toonTanksPlayerController;

	float startDelayRate = 3.f;
	void HandleGameStart();

	int32 targetTowers = 0;
	int32 GetTargetTowerCount();

};

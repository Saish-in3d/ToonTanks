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

public:
	void ActorDead(AActor* DamagedActor);

	AToonTanksGameMode();
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void InBPStartGame();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool bWonGame);

private:
	class ATank* Tank;

	float StartDelay= 3.f;

	void StartGame();

	class AToonTanksPlayerController* ToonTanksPlayerController;

	int32 TargetTurrets = 0;
	int32 GetTargetTowerCount();



	//class ATurret* Turret;

};

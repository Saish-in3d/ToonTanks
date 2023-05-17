// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"
#include "ToonTanksGameMode.h"


void AToonTanksGameMode::ActorDead(AActor* DamagedActor)
{
	TargetTurrets = GetTargetTowerCount();
	--TargetTurrets;
	if (Tank && DamagedActor == Tank)
	{
		Tank->SelfDestruct();
		
		GameOver(false);
	}
	
	else if (ATurret* Turret = Cast<ATurret>(DamagedActor))
	{
		Turret->SelfDestruct();
		if (TargetTurrets == 0)
		{
			GameOver(true);
		}
	}
}

AToonTanksGameMode::AToonTanksGameMode()
{
	
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	InBPStartGame();

}

void AToonTanksGameMode::StartGame()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController->SetPlayerEnabledState(false);
	FTimerHandle StartGameTimerHandle;
	FTimerDelegate StartGameTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,&AToonTanksPlayerController::SetPlayerEnabledState,true);
	GetWorldTimerManager().SetTimer(StartGameTimerHandle, StartGameTimerDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*>Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);
	return Turrets.Num();
}

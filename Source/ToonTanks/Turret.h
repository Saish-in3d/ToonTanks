// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;
	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category = "Turret")
		float TurretRange = 300.f;

	FTimerHandle FireTimer;



	bool IsInFireRange();

	void CCheckToFire();
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SelfDestruct() override;


};

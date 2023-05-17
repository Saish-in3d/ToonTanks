// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SelfDestruct();

protected:

	void RotateTurret(FVector LookAtTarget);

	UPROPERTY(VisibleAnywhere, category = "Basic", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* ProjectileSpawnPoint;

	virtual void Fire() ;


private:	

	UPROPERTY(VisibleAnywhere, category = "Basic", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, category = "Basic", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, category = "Basic", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere)
		class UClass* ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class USoundBase* DeadSound;


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	 ATank();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SelfDestruct() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere, category = "Tank", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, category = "Tank", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	//class UInputComponent* PlayerInputComponent;

	UPROPERTY(EditAnywhere, category = "Tank", meta = (AllowPrivateAccess = "true"))
		float Speed = 500.f; 

	void MoveForward(float Value);

	UPROPERTY(EditAnywhere, category = "Tank", meta = (AllowPrivateAccess = "true"))
	float TurnRate= 90.f;

	void Turn(float Value);

	APlayerController* PlayerController;

	class AToonTanksPlayerController* ToonTanksPlayerController;
};

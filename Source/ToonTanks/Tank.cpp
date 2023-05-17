// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "ToonTanksPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	ToonTanksPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false, HitResult);

	RotateTurret(HitResult.ImpactPoint);
	




}

void ATank::SelfDestruct()
{
	Super::SelfDestruct();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	DisableInput(ToonTanksPlayerController);
	DisableInput(ToonTanksPlayerController);
	ToonTanksPlayerController->bShowMouseCursor = false;
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
	}
	Tags.Add(FName("Dead"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	//PlayerController = Cast<APlayerController>(GetController() );
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

}

void ATank::MoveForward(float Value)
{

	
	FVector DeltaOffset = FVector(Value, 0.f, 0.f);
	DeltaOffset.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaOffset, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator(0.f) ;
		DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

		AddActorLocalRotation(DeltaRotation, true);
}

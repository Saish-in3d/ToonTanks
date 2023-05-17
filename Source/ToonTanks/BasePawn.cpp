// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}




// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::SelfDestruct()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeadSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeadSound, GetActorLocation());
	}
	
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector TurretLocation = GetActorLocation();
	FVector RotateVector;
	RotateVector = LookAtTarget - TurretLocation ;

	FRotator TurretRotation = FRotator(0.f, RotateVector.Rotation().Yaw,0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), TurretRotation, UGameplayStatics::GetWorldDeltaSeconds(this),10.f));


}

void ABasePawn::Fire()
{
	ProjectileSpawnPoint->GetComponentLocation();
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();

	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}


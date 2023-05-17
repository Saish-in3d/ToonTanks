// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(FireTimer, this, &ATurret::CCheckToFire, 1.f, true);
	
}





bool ATurret::IsInFireRange()
{
		float TankDistance = FVector::Distance(Tank->GetActorLocation(), GetActorLocation());
		 if (TankDistance <= TurretRange)
		 {
			 return true;
		 }
		 return false;
}

void ATurret::CCheckToFire()
{
	if (IsInFireRange() && !Tank->ActorHasTag(TEXT("Dead")))
	{
		Fire();
	}
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Tank && IsInFireRange())
	{
			RotateTurret(Tank->GetActorLocation());
	}
}

void ATurret::SelfDestruct()
{
	Super::SelfDestruct();
	Destroy();

}



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	virtual void Tick(float DeltaTime) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, category = "Basic")
		float InitialSpeed = 0;

	UPROPERTY(EditAnywhere, category = "Basic")
		float FinalSpeed = 0;

	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	AActor* MyOwner;

private:	
	UPROPERTY(VisibleAnywhere, category = "Basic", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystemComponent* SomkeTrail;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
		class USoundBase* HitSound;



};

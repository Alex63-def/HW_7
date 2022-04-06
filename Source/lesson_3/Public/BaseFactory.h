// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "HealthComponent.h"
#include "DamageTarget.h"
#include "IScorable.h"
#include "Engine/TargetPoint.h"
#include "EnemyTankPawn.h"
#include "LevelTrigger.h"
#include "BaseFactory.generated.h"

UCLASS()
class LESSON_3_API ABaseFactory : public AActor, public IDamageTarget, public IIScorable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseFactory();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BuildingMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* SpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	// это что бы при спавне задать им путь - это класс движка и создавать их в поиске слева где фигуры - видео с 47 минуты 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Factory")
		TArray<ATargetPoint*> Waypoints;
	
	// это то что будет спавниться 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Factory")
		TSubclassOf<AEnemyTankPawn> TankClass;

	// это сколько раз спавнить
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Factory")
		int MaxTanks = 100;

	// интервал спавна в секундах
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Factory")
		float SpawnInterval = 20;

	// активируем переход на левел если фабрика убита
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Factory")
		ALevelTrigger* LevelTrigger; 

	virtual void TakeDamage(FDamageData Damage) override;

	void OnHealthChanged(float CurrentHealth);

	void OnDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// спавнит 
	void OnTankSpawnTick();

	// это для примера сколько танков спавнилось
	int TanksSpawned = 0;

	FTimerHandle Timer;

public:

	float Experience = 100;
};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Cannon.h"
#include "FlameCannon.h"
#include "AmmoBox.generated.h"

UCLASS()
class LESSON_3_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* CollisionBegin;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* CollisionEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		TSubclassOf<AFlameCannon> FlameClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo Params")
		bool bInfinite = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

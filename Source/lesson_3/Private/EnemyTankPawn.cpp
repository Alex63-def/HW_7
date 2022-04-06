// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTankPawn.h"
#include "EnemyAIController.h"

AEnemyTankPawn::AEnemyTankPawn()/* : ATankPawn()*/
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RangeSphere = CreateDefaultSubobject<USphereComponent>("RangeSphere");
	RangeSphere->SetupAttachment(RootComponent);

	// подписываемся на события этой сферы
	// на то что зашел какой-то юнит в ее область
	RangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyTankPawn::OnBeginOverlap);

	// на - не сказал - но думаю на выходе из области перестанет стрелять 
	RangeSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyTankPawn::OnEndOverlap);

	AudioDeathEffectt = CreateDefaultSubobject<UAudioComponent>("AudioDeathEffectt");
	AudioDeathEffectt->SetupAttachment(BodyMesh);

	DeathEffectt = CreateDefaultSubobject<UParticleSystemComponent>("DeathEffectt");
	DeathEffectt->SetupAttachment(BodyMesh);
}

void AEnemyTankPawn::OnConstrution(const FTransform& Transform)
{
	Super::OnConstrution(Transform);

	// это для примера выводим сколько танков спавнилось
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%d - Tank created"), Number));
}

void AEnemyTankPawn::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto AiController = Cast<AEnemyAIController>(GetController());
	if (AiController)
		if (!Cast<AEnemyTankPawn>(OtherActor))
			AiController->AddTarget(OtherActor);
}

void AEnemyTankPawn::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto AiController = Cast<AEnemyAIController>(GetController());
	if (AiController)
		AiController->RemoveTarget(OtherActor);
}

void AEnemyTankPawn::OnHealthChanged(float CurrentHealthTank)
{
	// когда изменится здоровьк выведем на экран сообщение 
	GEngine->AddOnScreenDebugMessage(103456341, 3, FColor::Red, FString::Printf(TEXT("Health Enemy Tank: %f"), CurrentHealthTank));
}

void AEnemyTankPawn::OnDeath()
{
	auto Temp = GetActorLocation();
	AudioDeathEffectt->Play();
	DeathEffectt->ActivateSystem();
	SetActorLocation({ -1000, -1000, -1000 });
	DeathEffectt->SetWorldLocation(Temp);
	AudioDeathEffectt->SetWorldLocation(Temp);

	GetWorld()->GetTimerManager().SetTimer(TimerDestruction, this, &AEnemyTankPawn::SelfDestruction, 3, false);
}

void AEnemyTankPawn::SelfDestruction()
{
	Destroy();
}
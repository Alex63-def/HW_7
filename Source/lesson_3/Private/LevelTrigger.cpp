// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelTrigger::ALevelTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	RootComponent = TriggerBox;
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelTrigger::OnBeginOverlap);

	InactiveLight = CreateDefaultSubobject<USpotLightComponent>("InactiveLight");
	InactiveLight->SetupAttachment(RootComponent);

	ActiveLight = CreateDefaultSubobject<USpotLightComponent>("ActiveLight");
	ActiveLight->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// переводит нас на новый уровень
void ALevelTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive && !LevelName.IsNone()) // если активен тригер и задано имя
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); // это получение игрока
		if (OtherActor == PlayerPawn) // если заехал игрок - запустить
			UGameplayStatics::OpenLevel(this, LevelName);
	}
}

void ALevelTrigger::SetActive(bool Active)
{
	InactiveLight->SetHiddenInGame(Active); // прячем неактивный свет если активно
	ActiveLight->SetHiddenInGame(!Active);	// и прячем активный свет если неактивно
	IsActive = Active;
}
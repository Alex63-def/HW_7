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

	PointActiveLight = CreateDefaultSubobject<UPointLightComponent>("PointActiveLight");
	PointActiveLight->SetupAttachment(RootComponent);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>("AudioEffect");
	AudioEffect->SetupAttachment(RootComponent);

	VisualEffect = CreateDefaultSubobject<UParticleSystemComponent>("VisualEffect");
	VisualEffect->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	VisualEffect->ActivateSystem();
	PointActiveLight->Activate();
}

// Called every frame
void ALevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (bActiveAudio)
	{
		AudioEffect->Play();
		bActiveAudio = false;
	}

}

// ��������� ��� �� ����� �������
void ALevelTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive && !LevelName.IsNone()) // ���� ������� ������ � ������ ���
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); // ��� ��������� ������
		if (OtherActor == PlayerPawn) // ���� ������ ����� - ���������
			UGameplayStatics::OpenLevel(this, LevelName);
	}
}

void ALevelTrigger::SetActive(bool Active)
{
	InactiveLight->SetHiddenInGame(Active); // ������ ���������� ���� ���� �������
	ActiveLight->SetHiddenInGame(!Active);	// � ������ �������� ���� ���� ���������
	IsActive = Active;
	bActiveAudio = Active;
}
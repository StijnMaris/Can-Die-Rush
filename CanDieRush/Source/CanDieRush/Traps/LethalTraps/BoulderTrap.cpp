// Fill out your copyright notice in the Description page of Project Settings.

#include "BoulderTrap.h"
#include "Components/BoxComponent.h"
#include "Character/RaceCharacter.h"
#include "Components/StaticMeshComponent.h"

ABoulderTrap::ABoulderTrap()
{
	PrimaryActorTick.bCanEverTick = false;
	SetActive(true);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh"));
	TriggerBox->bGenerateOverlapEvents = true;
	//TriggerBox->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABoulderTrap::OnOverlapBeginBox);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABoulderTrap::OnOverlapEndBox);

	BoulderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoulderMesh"));
	BoulderMesh->bGenerateOverlapEvents = true;
	BoulderMesh->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
	BoulderMesh->SetupAttachment(RootComponent);
	BoulderMesh->SetSimulatePhysics(false);
	BoulderMesh->OnComponentBeginOverlap.AddDynamic(this, &ABoulderTrap::OnOverlapBeginBoulder);

	


}

//void ABoulderTrap::Tick(float DeltaTime)
//{
//	
//}


void ABoulderTrap::BeginPlay()
{
	Super::BeginPlay();
	OriginalPosition = BoulderMesh->GetComponentLocation();
}


void ABoulderTrap::OnOverlapBeginBoulder(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (IsActive())
	{
		if (IsTriggered()) {
			if (Cast<ARaceCharacter>(OtherActor))
			{
				KillPlayer(Cast<ARaceCharacter>(OtherActor));
			}
		}
	}


}

void ABoulderTrap::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive())
	{
		SetTriggered(true);
		TriggerTrap(0);
	}
}

void ABoulderTrap::OnOverlapEndBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if (IsActive())
	{
		SetTriggered(false);
	}*/

}

void ABoulderTrap::TriggerTrap(float DeltaTime)
{
	BoulderMesh->SetSimulatePhysics(true);
}

void ABoulderTrap::TrapIsActive()
{
	SetActive(true);
}

void ABoulderTrap::ResetTrap()
{
	BoulderMesh->SetWorldLocation(OriginalPosition);
	BoulderMesh->SetSimulatePhysics(false);
	SetTriggered(false);
}



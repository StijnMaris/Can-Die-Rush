// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickUp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Character/RaceCharacter.h"

// Sets default values
ABasePickUp::ABasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->bGenerateOverlapEvents = true;
	Collider->SetCollisionProfileName(TEXT("Collider"));
	Collider->SetupAttachment(PickupMesh);
}

// Called when the game starts or when spawned
void ABasePickUp::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABasePickUp::OnBeginOverlap);
}

// Called every frame
void ABasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorRotation(GetActorRotation().Add(0.f, DeltaTime, 0.f));
	if (bIsPickUpActive)
		{
			if (PickUpDuration -= DeltaTime < 0.f)
				{
					ResetPlayer();
					Destroy();
				}
		}
}

void ABasePickUp::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARaceCharacter* temp = Cast<ARaceCharacter>(OtherActor);
	if (temp->IsValidLowLevel())
	{
		ActivatePickup(temp);
	}
}

void ABasePickUp::ActivatePickup(ARaceCharacter* raceCharacter)
{
	RaceCharacter = raceCharacter;
	bIsPickUpActive = true;
	this->SetActorLocation(FVector(FLT_MAX, FLT_MAX, FLT_MAX));

	//Change stats
}

void ABasePickUp::ResetPlayer()
{
	//Reset stats
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTrap.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Texture2D.h"

// Sets default values
ABaseTrap::ABaseTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActive(true);
	//create staticmesh
	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrapMesh"));
	TrapMesh->bGenerateOverlapEvents = true;
	RootComponent = TrapMesh;
	//TrapMesh->GetCollisionShape();
	//TrapMesh->SetupAttachment(RootComponent);
	//create colider
	/*TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->bGenerateOverlapEvents = true;
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetupAttachment(TrapMesh);*/
	
	TrapMesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrap::OnOverlapBeginBox);
	TrapMesh->OnComponentEndOverlap.AddDynamic(this, &ABaseTrap::OnOverlapEndBox);
}

// Called when the game starts or when spawned
void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTrap::SetActive(bool NewActiveState)
{
	bIsActive = NewActiveState;
}

void ABaseTrap::SetTriggered(bool NewActiveState)
{
	bIsTriggered = NewActiveState;
}

void ABaseTrap::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive())
	{
		SetTriggered(true);
	}
}

void ABaseTrap::OnOverlapEndBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (IsActive())
	{
		SetTriggered(false);
	}
}

UTexture2D* ABaseTrap::GetTrapUiIcon()
{
	return TrapUiIcon;
}


bool ABaseTrap::IsActive()
{
	return bIsActive;
}

bool ABaseTrap::IsTriggered()
{
	return bIsTriggered;
}

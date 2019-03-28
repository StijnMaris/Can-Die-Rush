// Fill out your copyright notice in the Description page of Project Settings.

#include "SpikeTrap.h"
#include "Components/StaticMeshComponent.h"
#include "Character/RaceCharacter.h"



ASpikeTrap::ASpikeTrap() 
{
	SetActive(true);

	TrapTriggerSpeed = 10.f;

	bMovingUp = true;

	SpikesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikeMesh"));
	SpikesMesh->bGenerateOverlapEvents = true;
	
	SpikesMesh->SetupAttachment(RootComponent);	

	SpikesMesh->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapBeginSpikes);
	SpikesMesh->OnComponentEndOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapEndSpikes);

	
}

void ASpikeTrap::Tick(float DeltaTime)
{
	if (bSpikesMoving)
	{
		TriggerTrap(DeltaTime);
	}
}


void ASpikeTrap::BeginPlay()
{
	

	RandomTrapIndex = rand() % 3;

	switch (RandomTrapIndex)
	{
	case 0:
		SpikesMesh->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
		break;

	case 1:
		SpikesMesh->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		break;

	case 2:
		SpikesMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
		break;
	}
	Super::BeginPlay();
	OriginalPosition = SpikesMesh->GetRelativeTransform().GetLocation();
}


void ASpikeTrap::OnOverlapBeginSpikes(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		
		if (IsActive())
		{
			if (IsTriggered()) {
				KillPlayer(Cast<ARaceCharacter>(OtherActor));
				SetTriggered(false);
			}
		}
		

}

void ASpikeTrap::OnOverlapEndSpikes(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ASpikeTrap::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive())
	{
		SetTriggered(true);
		bSpikesMoving = true;
	}
}

void ASpikeTrap::OnOverlapEndBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsActive())
	{
		SetTriggered(false);
	}
	
}

void ASpikeTrap::TriggerTrap(float DeltaTime)
{
	FVector GoTo;
	FVector NewPos = OriginalPosition;
	FVector Current = SpikesMesh->GetRelativeTransform().GetLocation();

	switch (RandomTrapIndex)
	{
	case 0:
		NewPos.Z += 60.f;
		break;

	case 1:
		NewPos.Z += 80.f;
		break;

	case 2:
		NewPos.Z += 100.f;
		break;
	}

	if (bMovingUp)  //If player is close (Go Up)
		{
			GoTo = FMath::VInterpTo(Current, NewPos, DeltaTime, TrapTriggerSpeed);
			if (FVector::Distance(Current, NewPos) <= 0.01f)
				{
					bMovingUp = false;
				}
		}
		else if (!IsTriggered()) //If he died or went away (Go down)
		{
			GoTo = FMath::VInterpTo(Current, OriginalPosition, DeltaTime, TrapTriggerSpeed);
			if (FVector::Distance(Current, OriginalPosition) <= 0.01f)
				{
					GoTo = OriginalPosition;
					bSpikesMoving = false;
					bMovingUp = true;
				}
		}
		else //If he didn't die yet, but he is still standing next to the spikes (Do nothing)
		{
			GoTo = Current;
		}
	SpikesMesh->SetRelativeLocation(GoTo);
}

void ASpikeTrap::TrapIsActive()
{
	SetActive(true);
}

void ASpikeTrap::ResetTrap()
{
	SpikesMesh->SetWorldLocation(OriginalPosition);
	SetTriggered(false);
}

int ASpikeTrap::GetTrapIndex()
{
	return RandomTrapIndex;
}


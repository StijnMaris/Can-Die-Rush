// Fill out your copyright notice in the Description page of Project Settings.

#include "FireTrap.h"
#include "Components/BoxComponent.h"
#include "Character/RaceCharacter.h"

AFireTrap::AFireTrap()
{
	SetActive(true);

	TrapTriggerSpeed = 10.f;

	bMovingUp = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerMesh"));
	TriggerBox->bGenerateOverlapEvents = true;
	TriggerBox->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	TriggerBox->SetupAttachment(RootComponent);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFireTrap::OnOverlapBeginFire);


}

void AFireTrap::Tick(float DeltaTime)
{
	if (bSpikesMoving)
	{
		TriggerTrap(DeltaTime);
	}
}


void AFireTrap::BeginPlay()
{
	Super::BeginPlay();
	OriginalPosition = TriggerBox->GetRelativeTransform().GetLocation();
}


void AFireTrap::OnOverlapBeginFire(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (IsActive())
	{
		if (IsTriggered()) {
			//KillPlayer(Cast<ARaceCharacter>(OtherActor));
			SetTriggered(false);
		}
	}


}

void AFireTrap::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive())
	{
		SetTriggered(true);
		bSpikesMoving = true;
	}
}

void AFireTrap::OnOverlapEndBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsActive())
	{
		SetTriggered(false);
	}

}

void AFireTrap::TriggerTrap(float DeltaTime)
{
	FVector NewPos = OriginalPosition;
	FVector GoTo;
	FVector Current = TriggerBox->GetRelativeTransform().GetLocation();

	NewPos.Z += 50.f;
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
	TriggerBox->SetRelativeLocation(GoTo);
}

void AFireTrap::TrapIsActive()
{
	SetActive(true);
}

void AFireTrap::ResetTrap()
{
	TriggerBox->SetWorldLocation(OriginalPosition);
	SetTriggered(false);
}





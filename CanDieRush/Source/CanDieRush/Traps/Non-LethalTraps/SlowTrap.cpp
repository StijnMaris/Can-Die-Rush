// Fill out your copyright notice in the Description page of Project Settings.

#include "SlowTrap.h"
#include "Components/BoxComponent.h"
#include "Character/RaceCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"

ASlowTrap::ASlowTrap()
{
	PrimaryActorTick.bCanEverTick = false;
	SetActive(true);
}

//void ASlowTrap::Tick(float DeltaTime)
//{
//
//}


void ASlowTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlowTrap::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsActive())
	{
		
		if (ARaceCharacter* RaceCharacter = Cast<ARaceCharacter>(OtherActor))
		{
			SetTriggered(true);
			RaceCharacter->GetCharacterMovement()->MaxWalkSpeed = SlowSpeed;
		}
		
		
	}
}

void ASlowTrap::OnOverlapEndBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsActive())
	{
		

		if (ARaceCharacter* RaceCharacter = Cast<ARaceCharacter>(OtherActor))
		{
			SetTriggered(false);
			RaceCharacter->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
		}
	}

}




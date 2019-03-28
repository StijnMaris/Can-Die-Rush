// Fill out your copyright notice in the Description page of Project Settings.

#include "RacePlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Traps/BaseTrap.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Core/Public/Containers/Array.h"


void ARacePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

FColor ARacePlayerController::GetPlayerColor()
{
	return PlayerColor;
}

void ARacePlayerController::SetPlayerColor(FColor newColor)
{
	PlayerColor = newColor;
}

ABaseTrap* ARacePlayerController::GetClosestTrap()
{
	ABaseTrap* ClosestTrap = nullptr;
	FVector CharacterLocation = this->GetPawn()->GetActorLocation();
	float ClosestDistance;
	float Distance;
	if (Traps.Num() > 0)
	{
		ClosestTrap = Traps[0];
		ClosestDistance = FVector::Distance(Traps[0]->GetActorLocation(), CharacterLocation);

		for (int i = 1; i < Traps.Num(); i++)
		{
			Distance = FVector::Distance(Traps[i]->GetActorLocation(), CharacterLocation);
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestTrap = Traps[i];
			}
		}
	}
	return ClosestTrap;
}

void ARacePlayerController::ActivivateClosestTrap()
{
	ABaseTrap* trap = GetClosestTrap();
	if (trap)
		{
			trap->SetActive(true);
		}
}


void ARacePlayerController::SetCharacterId(int Id)
{
	CharacterId = Id;
}

int ARacePlayerController::GetCharacterId()
{
	return CharacterId;
}

void ARacePlayerController::SetActiveState(bool IsActive)
{
	this->IsActive = IsActive;
}

bool ARacePlayerController::IsCharacterActive()
{
	return this->IsActive;
}

void ARacePlayerController::Reset()
{
	IsActive = false;
	CharacterId = 0;
	AmountOfPoint = 0;
}


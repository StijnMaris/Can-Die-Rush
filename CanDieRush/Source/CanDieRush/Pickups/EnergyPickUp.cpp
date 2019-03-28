// Fill out your copyright notice in the Description page of Project Settings.

#include "EnergyPickUp.h"
#include "Character/RaceCharacter.h"

void AEnergyPickUp::ResetPlayer()
{
	ABasePickUp::ResetPlayer();
	RaceCharacter->SetEnergyRegen(NormalEnergyRegen);
}

void AEnergyPickUp::ActivatePickup(ARaceCharacter* raceCharacter)
{
	ABasePickUp::ActivatePickup(raceCharacter);
	NormalEnergyRegen = RaceCharacter->GetEnergyRegen();
	RaceCharacter->SetEnergyRegen(NormalEnergyRegen * NormalEnergyRegen);
}
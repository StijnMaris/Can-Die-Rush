// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickUp.h"
#include "EnergyPickUp.generated.h"

/**
 * 
 */
UCLASS()
class CANDIERUSH_API AEnergyPickUp : public ABasePickUp
{
	GENERATED_BODY()
public:
	virtual void ActivatePickup(ARaceCharacter* raceCharacter) override;
	
protected:
	virtual void ResetPlayer() override;

	float NormalEnergyRegen = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	float EnergyRegenMultiplier = 2.f;
};

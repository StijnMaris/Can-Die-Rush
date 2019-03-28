// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CanDieRushGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CANDIERUSH_API ACanDieRushGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
};

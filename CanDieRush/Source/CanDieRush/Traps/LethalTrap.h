// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Traps/BaseTrap.h"
#include "LethalTrap.generated.h"

class ARaceCharacter;
/**
 * 
 */
UCLASS()
class CANDIERUSH_API ALethalTrap : public ABaseTrap
{
	GENERATED_BODY()
	
public:
	//when called kills the player that collides with trap
	UFUNCTION(BlueprintCallable, Category = "Traps")
	virtual void KillPlayer(ARaceCharacter* Character);

	UFUNCTION(BlueprintCallable, Category = "Traps")
		virtual void TriggerTrap(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Traps")
		virtual void TrapIsActive();

	UFUNCTION(BlueprintCallable, Category = "Traps")
		virtual void ResetTrap();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LethalTraps")
		float DelayTime = 0.2f;

private:
	
};

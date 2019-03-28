// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RacePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CANDIERUSH_API ARacePlayerController : public APlayerController
{
	GENERATED_BODY()


	
public:
	UFUNCTION(BlueprintCallable)
	FColor GetPlayerColor();
	UFUNCTION(BlueprintCallable)
	void SetPlayerColor(FColor newColor);

	//Traps
	UFUNCTION(BlueprintCallable)
	virtual void AddTrap(ABaseTrap* Trap) { Traps.Add(Trap); };

	UFUNCTION(BlueprintCallable)
	virtual ABaseTrap* GetClosestTrap();

	UFUNCTION(BlueprintCallable)
	virtual void ActivivateClosestTrap();

	UFUNCTION(BlueprintCallable)
	virtual TArray<ABaseTrap*> GetTraps() { return Traps; };

	UFUNCTION(BlueprintCallable)
	virtual void SetCharacterId(int Id);

	UFUNCTION(BlueprintCallable)
	virtual int GetCharacterId();

	UFUNCTION(BlueprintCallable)
	virtual int GetPoints() { return AmountOfPoint; }
	
	UFUNCTION(BlueprintCallable)
	virtual void AddPoints(int pointsToAdd) { AmountOfPoint+= pointsToAdd; }

	UFUNCTION(BlueprintCallable)
	virtual void SetActiveState(bool IsActive);

	UFUNCTION(BlueprintCallable)
	virtual bool IsCharacterActive();

	UFUNCTION(BlueprintCallable)
	virtual void Reset();
	
protected:
	virtual void BeginPlay() override;
private:
	FColor PlayerColor;
	int CharacterId = 0;
	int AmountOfPoint = 0;
	bool IsActive = false;

	//Trap Triggering
	UPROPERTY(EditAnywhere)
	TArray<ABaseTrap*> Traps;
};

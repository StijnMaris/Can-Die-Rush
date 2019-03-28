// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RaceCharacter.generated.h"

UCLASS()
class CANDIERUSH_API ARaceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARaceCharacter();
	
	//Push
	UFUNCTION(BlueprintCallable)
	virtual bool PushPlayer(TArray<ARaceCharacter*> Characters);

	//Sprint
	UFUNCTION(BlueprintCallable)
	virtual void Sprint();

	UFUNCTION(BlueprintCallable)
	virtual void StopSprint();

	UFUNCTION(BlueprintCallable)
	virtual float GetSpeed();

	UFUNCTION(BlueprintCallable)
	virtual void SetSpeed(float NewSpeed);

	//Basic Functions
	UFUNCTION(BlueprintCallable)
	virtual void SetPlayerID(int id);

	UFUNCTION(BlueprintCallable)
	virtual int GetPlayerID();

	UFUNCTION(BlueprintCallable)
	virtual void SetHasWon();

	UFUNCTION(BlueprintCallable)
	virtual bool GetHasWon() { return bHasWonRace; };
	
	UFUNCTION(BlueprintCallable)
	virtual void SetIsDancing(bool isDancing) { bIsDancing = isDancing; };

	UFUNCTION(BlueprintCallable)
	virtual bool GetIsDancing() { return bIsDancing; };

	//ENERGY
	UFUNCTION(BlueprintCallable)
	virtual void AddEnergy(float Energy);

	UFUNCTION(BlueprintCallable)
	virtual bool UseEnergy(float Energy);

	UFUNCTION(BlueprintCallable)
	virtual void SetEnergyRegen(float EnergyRegen) { this->EnergyRegen = EnergyRegen; };

	UFUNCTION(BlueprintCallable)
	virtual float GetEnergyRegen() { return EnergyRegen; };

	UFUNCTION(BlueprintCallable)
	virtual void SetEnergy(float Energy) { this->Energy = Energy; };

	UFUNCTION(BlueprintCallable)
	virtual float GetEnergy() { return Energy; };

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxEnergy() { return MaxEnergy; };

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//General info
	int PlayerId;

	UPROPERTY(EditAnywhere)
	bool bHasWonRace = false;
	
	UPROPERTY(EditAnywhere)
	bool bIsDancing = false;

	//Pushing
	UPROPERTY(EditAnywhere)
	float PushPlayerRange;

	UPROPERTY(EditAnywhere)
	float PushForce;

	UPROPERTY(EditAnywhere)
	float PushCost = 75.f;

	//Sprinting
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float NormalSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float SprintCost = 50.0f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 1.5f;

	//Energy
	UPROPERTY(EditAnywhere)
	float EnergyRegen = 10.0f;

	UPROPERTY(EditAnywhere)
	float MaxEnergy = 100.f;

	UPROPERTY(EditAnywhere)
	float Energy = 100.f;
};

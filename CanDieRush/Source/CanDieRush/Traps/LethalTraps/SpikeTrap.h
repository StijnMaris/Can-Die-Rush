// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Traps/LethalTrap.h"
#include "SpikeTrap.generated.h"

/**
 * 
 */
UCLASS()
class CANDIERUSH_API ASpikeTrap : public ALethalTrap
{
	GENERATED_BODY()
	
public:
	ASpikeTrap();

	// Called every frame
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "SpikeTraps")
		virtual void OnOverlapBeginSpikes(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category = "SpikeTraps")
		virtual void OnOverlapEndSpikes(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Traps")
		void OnOverlapBeginBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//end overlap with box
	UFUNCTION(BlueprintCallable, Category = "Traps")
		void OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintCallable, Category = "Traps")
		void TriggerTrap(float DeltaTime)override;

	UFUNCTION(BlueprintCallable, Category = "Traps")
		void TrapIsActive() override;

	UFUNCTION(BlueprintCallable, Category = "Traps")
		void ResetTrap() override;

	//int
	UFUNCTION(BlueprintPure, Category = "RandomTrap")
		int GetTrapIndex();
protected:
	void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SpikesMesh;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* SpikeTriggerBox;*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		FVector OriginalPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		int RandomTrapIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		int TrapTriggerSpeed = 0.1;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
	//	float TriggeredTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		bool bSpikesMoving = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		bool bMovingUp = true;
};

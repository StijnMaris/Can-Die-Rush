// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Traps/LethalTrap.h"
#include "BoulderTrap.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class CANDIERUSH_API ABoulderTrap : public ALethalTrap
{
	GENERATED_BODY()
	
public:
	ABoulderTrap();

	// Called every frame
	//void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "BoulderTraps")
		virtual void OnOverlapBeginBoulder(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

protected:
	void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BoulderMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		FVector OriginalPosition;

	
	
};

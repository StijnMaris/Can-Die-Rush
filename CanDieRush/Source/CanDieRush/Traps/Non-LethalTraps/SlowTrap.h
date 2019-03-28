// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Traps/BaseTrap.h"
#include "SlowTrap.generated.h"

/**
 * 
 */
UCLASS()
class CANDIERUSH_API ASlowTrap : public ABaseTrap
{
	GENERATED_BODY()
	
	
public:
	ASlowTrap();

	// Called every frame
	//void Tick(float DeltaTime) override;

	/*UFUNCTION(BlueprintCallable, Category = "BoulderTraps")
		virtual void OnOverlapBeginBoulder(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
*/
	UFUNCTION(BlueprintCallable, Category = "Traps")
		void OnOverlapBeginBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//end overlap with box
	UFUNCTION(BlueprintCallable, Category = "Traps")
		void OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


protected:
	void BeginPlay() override;


private:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SlowTrapMesh;*/

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* TriggerBox;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlowTrap", meta = (AllowPrivateAccess = "true"))
		int NormalSpeed = 600;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlowTrap", meta = (AllowPrivateAccess = "true"))
		int SlowSpeed = 300;




	
};

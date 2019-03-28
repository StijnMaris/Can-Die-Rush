// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class ARaceCharacter;
UCLASS()
class CANDIERUSH_API ABasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Overlap with Collider
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//IMPORTANT: OVERWRITE THIS
	//ADD: Change stats
	virtual void ActivatePickup(ARaceCharacter* raceCharacter);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	UBoxComponent* Collider;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	float PickUpDuration = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bIsPickUpActive = false;

	ARaceCharacter* RaceCharacter;

	//IMPORTANT: OVERWRITE THIS
	//ADD: Reset stats
	virtual void ResetPlayer();
};

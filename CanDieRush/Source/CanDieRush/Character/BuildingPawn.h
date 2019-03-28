// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BuildingPawn.generated.h"

class UStaticMeshComponent;
class ABaseTrap;
UCLASS()
class CANDIERUSH_API ABuildingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABuildingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Building")
	ABaseTrap * PlaceRandomTrap(TSubclassOf<ABaseTrap> MyRandomTrap);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* OurVisibleComponent;

	UFUNCTION(BlueprintCallable, Category = "Building")
		void SetSpawnLocation(FVector SpawnLocation);

	//input actions 
	UFUNCTION(BlueprintCallable, Category = "Building")
	void MoveXAxis(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Building")
	void MoveYAxis(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Building")
	void SetCameraToFollow(class ABuildingCameraActor* Camera) { this->Camera = Camera; };

	UFUNCTION(BlueprintCallable, Category = "Building")
	bool HasPlacedTrap() { return IsTrapPlaced; };




private:

	FName Placeble = "Placeble";
	FVector NewLocation, OrigionalRayTraceStart, OrigionalRayTraceEnd;
	float GridSize;
	bool DidTraceHit = false;
	bool IsTrapPlaced = false;

	FHitResult* TraceHit;
	FCollisionQueryParams* TraceParams;

	//input variables
	FVector CurrentVelocity;
	class ABuildingCameraActor* Camera;

}; 

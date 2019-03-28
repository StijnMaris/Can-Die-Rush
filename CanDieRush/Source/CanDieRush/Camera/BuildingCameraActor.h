// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "BuildingCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class CANDIERUSH_API ABuildingCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	//Sets a custom goal to the camera, also sets DoTrackPlayers to false
	void SetStartPosition(FVector Start);

	UFUNCTION(BlueprintCallable)
	//Sets the camera and let's the fun begin
	void StartBuildMode();

	UFUNCTION(BlueprintCallable)
	//Sets wich players needs to be tracked by the camera
	void SetPlayers(TArray<class ARaceCharacter*> APlayersArray);


	UFUNCTION(BlueprintCallable)
	//Sets wich players needs to be tracked by the camera
	void SetWayPoints(TArray<class AActor*> AWayPointArray);

	UFUNCTION(BlueprintCallable)
	//Says if the goal has been reached by the camera
	bool BuildCameraGoalReached();

	UFUNCTION(BlueprintCallable)
	void PrepareBuildingMode();

	UFUNCTION(BlueprintCallable)
	//Says if the goal has been reached by the camera
	void SpeedUpBuildCamera(float times = 2.0f);

	UFUNCTION(BlueprintCallable)
	FVector GetCameraMovement() { return CameraMovement; };

protected:
	//Start.
	virtual void BeginPlay() override;
	//Each tick.
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector Start;

private:
	static const float OriginalCameraSpeed;
	float Time = 0.f;
	float CameraSpeed = 0.05f; //Overwritten by original camera speed

	bool bGoalReached = true;

	FVector CameraMovement = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FVector Offset = FVector(0, 0, 1800);

	TArray<class ARacePlayerController*> APlayersArr;
	
	TArray<FVector> AWayPointsArr;
	TArray<float> TravelPercentWayPoints;
	uint8 CurrentWayPoint = 0;

	//Sets the camera of the players.
	void SetCamera();
};

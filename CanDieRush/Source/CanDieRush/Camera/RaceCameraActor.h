// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "RaceCameraActor.generated.h"

/**
 * This class will be a race camera that tracks the players whilst racing.
 */
UCLASS()
class CANDIERUSH_API ARaceCameraActor final : public ACameraActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	//Sets if the players need to be followed by the camera
	void SetTracking(bool bDoTrackPlayers) { this->bDoTrackPlayers = bDoTrackPlayers; };

	UFUNCTION(BlueprintCallable)
	//Sets a custom goal to the camera, also sets DoTrackPlayers to false
	void SetGoal(FVector Goal);

	UFUNCTION(BlueprintCallable)
	//Sets wich players needs to be tracked by the camera
	void SetPlayers(TArray<class ARaceCharacter*> APlayersArray);

	UFUNCTION(BlueprintCallable)
	//Sets the camera and let's the fun begin
	void StartRaceMode();

	//UFUNCTION(BlueprintCallable)
	//void DestroyPlayer();

protected:
	//Start.
	virtual void BeginPlay() override;
	//Each tick.
	virtual void Tick(float DeltaSeconds) override;

private:
	FVector Goal;
	FRotator Rotation;
	FVector Offset = FVector(-350, 0, 400);
	FVector Multiplier = FVector(-175, 0, 200);
	bool bDoTrackPlayers = true;
	bool bSetCamera = false;
	float CameraSpeed = 2.f;
	float FOVAngle = 50.6250022148f;
	class TArray<class ARacePlayerController*> APlayersArr;

	//Tracks the players' location and sets a new goal WARNING: do not call if players are 0.
	void TrackPlayers();
	//Sets the camera of the players.
	void SetCamera();
};

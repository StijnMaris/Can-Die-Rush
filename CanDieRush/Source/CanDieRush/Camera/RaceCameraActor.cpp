// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceCameraActor.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "RacePlayerController.h"
#include "Character/RaceCharacter.h"

void ARaceCameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARaceCameraActor::StartRaceMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Camera: Starting Racemode."));

	//Set the active camera
	SetCamera();
	bDoTrackPlayers = true;
}

void ARaceCameraActor::SetCamera()
{
	FViewTargetTransitionParams Params;
	for (uint8 i = 0; i < APlayersArr.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera: Player Set."));
		APlayersArr[i]->SetViewTarget(this, Params);
	}
	bSetCamera = false;
}

void ARaceCameraActor::Tick(float DeltaSeconds)
{
	//Check if camera needs a reset
	if (bSetCamera && bDoTrackPlayers)
		{
			SetCamera();
		}

	Super::Tick(DeltaSeconds);

	//Track The Players
	if (bDoTrackPlayers)
		{
			TrackPlayers();
		}

	//Go To The Goal
	this->SetActorLocation(FMath::VInterpTo(this->GetActorLocation(), Goal, DeltaSeconds, CameraSpeed));
	//this->SetActorRotation(FMath::RInterpTo(this->GetActorRotation(), Rotation, DeltaSeconds, CameraSpeed));
}

void ARaceCameraActor::SetPlayers(TArray<ARaceCharacter*> APlayersArray)
{
	APlayersArr.Empty();
	for (uint8 i = 0; i < APlayersArray.Num(); i++)
	{
		AController* controller = APlayersArray[i]->GetController();
		if (controller)
		{
			APlayersArr.Add(dynamic_cast<ARacePlayerController*>(controller));
		}
	}
}

void ARaceCameraActor::TrackPlayers()
{

	FVector first = FVector();
	FVector last = FVector();

	//Calculate Average Location Of The Players
	float LongestDistance = 0.f;
	float DistOffset;
	int count = 0;
	for (uint8 i = 0; i < APlayersArr.Num(); i++)
	{
		if (IsValid(APlayersArr[i]->GetPawn()))
		{
			//Use the player to calculate the average location
			FVector Location = APlayersArr[i]->GetPawn()->GetActorLocation();
			count++;

			for (uint8 j = 0; j < APlayersArr.Num(); j++)
			{
				if (IsValid(APlayersArr[j]->GetPawn()))
					{
						FVector OtherLocation = APlayersArr[j]->GetPawn()->GetActorLocation();
						if (LongestDistance < FVector::Distance(Location, OtherLocation))
							{
								float Dist = FVector::Distance(Location, this->GetTargetLocation());
								float OtherDist = FVector::Distance(OtherLocation, this->GetActorLocation());
								if (Dist > OtherDist)
									{
										first = Location;
										last = OtherLocation;
										DistOffset = Dist - OtherDist;
									}
									else
									{
										first = OtherLocation;
										last = Location;
										DistOffset = OtherDist - Dist;
									}
								LongestDistance = FVector::Distance(Location, OtherLocation);
							}
					}
			}
		}
		else
		{
			//Remove the player from the list and reset the camera
			//APlayersArr.RemoveAt(i);
			bSetCamera = true;
		}
	}

	if (count > 1)
		{
			float d = FVector::Distance(first, last) / sin(FOVAngle);
			float distFromFirst = d * FMath::Sin(this->Rotation.Pitch + FOVAngle / 2 + 180);

			FRotator rot = this->Rotation;
			rot.Pitch -= FOVAngle;

			FVector center = first * 0.5 + last * 0.5;
			Goal = center + rot.Vector() * distFromFirst * 0.3 - FVector::ForwardVector * DistOffset * 0.25;
			if (FVector::Distance(Goal, center) < Offset.Size())
				{
					Goal = center + Offset;
				}
		}
		else if (count == 1)
		{
			for (uint8 i = 0; i < APlayersArr.Num(); i++)
			{
				if (IsValid(APlayersArr[i]->GetPawn()))
					{
						Goal = APlayersArr[i]->GetPawn()->GetActorLocation() + Offset;
					}
			}
		}
		else //Count 0 or glitched
		{
			Goal = Goal;
		}
}

void ARaceCameraActor::SetGoal(FVector Goal)
{
	if (bDoTrackPlayers)
		{
			bDoTrackPlayers = false;
		}
	this->Goal = Goal;
	//Rotation.Pitch = -45.f;
}


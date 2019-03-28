// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingCameraActor.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "RacePlayerController.h"
#include "Character/RaceCharacter.h"

const float ABuildingCameraActor::OriginalCameraSpeed = 0.045f;

void ABuildingCameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABuildingCameraActor::SetStartPosition(FVector Start)
{
	this->Start = Start + Offset;
}

void ABuildingCameraActor::StartBuildMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Camera: Starting Buildmode."));
	
	//Set/Reset Camera Speed
	CameraSpeed = OriginalCameraSpeed;

	//Set/Reset Position
	bGoalReached = false;
	CurrentWayPoint = 0;
	Time = 0.f;
	SetActorLocation(Start);

	//Set the active camera
	SetCamera();
}

void ABuildingCameraActor::SetPlayers(TArray<ARaceCharacter*> APlayersArray)
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

void ABuildingCameraActor::SetWayPoints(TArray<AActor*> AWayPointArray)
{
	AWayPointsArr.Empty();

	for (uint8 id = 0; id < AWayPointArray.Num(); id++)
	{
		for (uint8 num = 0; num < AWayPointArray.Num(); num++)
		{
			if (AWayPointArray[num]->GetName().Find(FString::FromInt(id)) != -1)
				{
					AWayPointsArr.Add(AWayPointArray[num]->GetActorLocation() + Offset);
					break;
				}
		}
	}

	float totalDistance = FVector::Distance(Start, AWayPointsArr[0]);
	TravelPercentWayPoints.Add(totalDistance);
	for (uint8 i = 1; i < AWayPointsArr.Num(); i++)
	{
		float distance = FVector::Distance(AWayPointsArr[i - 1], AWayPointsArr[i]);
		totalDistance += distance;
		TravelPercentWayPoints.Add(distance);
	}

	for (uint8 i = 0; i < AWayPointsArr.Num(); i++)
	{
		TravelPercentWayPoints[i] /= totalDistance;
	}
}

bool ABuildingCameraActor::BuildCameraGoalReached()
{
	return bGoalReached;
}

void ABuildingCameraActor::PrepareBuildingMode()
{
	//Set/Reset Camera Speed
	CameraSpeed = 0.0f;
	CameraMovement = FVector::ZeroVector;

	//Set/Reset Position
	bGoalReached = true;
	CurrentWayPoint = 0;
	Time = 0.f;
	SetActorLocation(Start);

	//Set the active camera
	SetCamera();
}

void ABuildingCameraActor::SpeedUpBuildCamera(float times)
{
	CameraSpeed *= times;
	Time /= times;
}

void ABuildingCameraActor::SetCamera()
{
	FViewTargetTransitionParams Params;
	for (uint8 i = 0; i < APlayersArr.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera: Player Set."));
		APlayersArr[i]->SetViewTarget(this, Params);
	}
}

void ABuildingCameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Go To The Goal and tell if goal is reached
	if (!bGoalReached)
		{
			FVector GoTo;
			if (CurrentWayPoint > 0)
				{
					GoTo = FMath::VInterpTo(AWayPointsArr[CurrentWayPoint - 1], AWayPointsArr[CurrentWayPoint], Time += DeltaSeconds, CameraSpeed / TravelPercentWayPoints[CurrentWayPoint]);
					CameraMovement = GetActorLocation() - GoTo;
					SetActorLocation(GoTo);
				}
				else
				{
					GoTo = FMath::VInterpTo(Start, AWayPointsArr[CurrentWayPoint], Time += DeltaSeconds, CameraSpeed / TravelPercentWayPoints[CurrentWayPoint]);
					CameraMovement = GetActorLocation() - GoTo;
					SetActorLocation(GoTo);
				}
				if (FVector::Distance(GoTo, AWayPointsArr[CurrentWayPoint]) <= 10.f)
					{
						CurrentWayPoint++;
						Time = 0.f;
						if (CurrentWayPoint == AWayPointsArr.Num())
							{
								bGoalReached = true;
								CurrentWayPoint = 0;
							}
					}

		}
}




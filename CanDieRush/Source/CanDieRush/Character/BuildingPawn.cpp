// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingPawn.h"
#include "Engine/EngineTypes.h"
#include "Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Traps/BaseTrap.h"
#include "Camera/BuildingCameraActor.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABuildingPawn::ABuildingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	TraceHit = new FHitResult(ForceInit);

	TraceParams = new FCollisionQueryParams(
		FName(TEXT("TraceGround")),	// tag name (for debugging)
		false,				// trace against simple collision primitives only
		this				// ignore this actor during the trace
	);

	NewLocation = GetActorLocation();
	GridSize = 300;
	CurrentVelocity = FVector(0, 0, 0);

	
}

// Called when the game starts or when spawned
void ABuildingPawn::BeginPlay()
{
	Super::BeginPlay();
	OrigionalRayTraceStart = GetActorLocation();
	OrigionalRayTraceStart.Z += 200;
	OrigionalRayTraceEnd = OrigionalRayTraceStart;
	OrigionalRayTraceEnd.Z -= 1000;
}

// Called every frame
void ABuildingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(NewLocation);

	FVector Start;
	FVector End;

	Start = GetActorLocation();
	if (Start.Z > OrigionalRayTraceStart.Z)
	{
		Start = OrigionalRayTraceStart;
	}else if (End.Z > OrigionalRayTraceEnd.Z)
	{
		End = OrigionalRayTraceEnd;
	}
	Start.Z += 200;
	End = Start;
	End.Z -= 1000;

	//For Debug reasons
	/*const FName TraceTag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	TraceParams->TraceTag = TraceTag;*/

	/*DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor(255, 0, 0),
		false, 1000, 0,
		12.333
	);*/

	TraceParams->bTraceComplex = false;
	TraceParams->bReturnPhysicalMaterial = true;

	//  do the line trace
	DidTraceHit = GetWorld()->LineTraceSingleByObjectType(
		*TraceHit,        //result
		Start,        //start
		End,        //end
		ECC_WorldStatic,    //collision channel
		*TraceParams
	);

	if (DidTraceHit && TraceHit->GetActor()->ActorHasTag(Placeble))
	{
		
		NewLocation = TraceHit->Location;
		SetActorLocation(TraceHit->Location);
		SetActorRotation(TraceHit->GetActor()->GetActorRotation());
	}

	NewLocation = NewLocation + (CurrentVelocity)-Camera->GetCameraMovement();
	if (!CurrentVelocity.IsZero())
	{
		FVector NewSnappedLocation = FVector{ NewLocation.GridSnap(GridSize).X, NewLocation.GridSnap(GridSize).Y,NewLocation.Z };
		//Don't tell stijn
		//SetActorLocation(NewSnappedLocation);
		SetActorLocation(NewLocation);
	}
	else
	{
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ABuildingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveRight", this, &ABuildingPawn::MoveXAxis);
	InputComponent->BindAxis("MoveForward", this, &ABuildingPawn::MoveYAxis);
}

ABaseTrap* ABuildingPawn::PlaceRandomTrap(TSubclassOf<ABaseTrap> MyRandomTrap)
{
	if (!IsTrapPlaced && DidTraceHit)
		{
			AActor* FoundActor = TraceHit->GetActor();
			if (FoundActor->ActorHasTag(Placeble) && MyRandomTrap)
				{
					UWorld* const World = GetWorld();
					if (World)
						{
							FActorSpawnParameters SpawnParams;
							SpawnParams.Instigator = this;
							FRotator rotation = FoundActor->GetActorRotation();




							FVector Location = TraceHit->Location;
							FString Test = FoundActor->GetName();
							IsTrapPlaced = true;
							return World->SpawnActor<ABaseTrap>(MyRandomTrap, Location, rotation, SpawnParams);
						}
				}
		}
	return nullptr;
}

void ABuildingPawn::SetSpawnLocation(FVector SpawnLocation)
{
	NewLocation = SpawnLocation;
}

void ABuildingPawn::MoveXAxis(float AxisValue)
{
	float ClampedAxis = FMath::Clamp(AxisValue, -1.0f, 1.0f);
	CurrentVelocity.X = ClampedAxis * 50.f;
	//if (ClampedAxis > 0.2)
	//	{
	//		CurrentVelocity.X = 60.0f;
	//	}
	//else if (ClampedAxis < -0.2)
	//	{
	//		CurrentVelocity.X = -60.0f;
	//	}
	//else
	//	{
	//		CurrentVelocity.X = 0.0f;
	//	}


}

void ABuildingPawn::MoveYAxis(float AxisValue)
{
	float ClampedAxis = FMath::Clamp(AxisValue, -1.0f, 1.0f);
	CurrentVelocity.Y = ClampedAxis * -50.f;
	//if (ClampedAxis > 0.2)
	//{
	//	CurrentVelocity.Y = -60.0f;
	//}
	//else if (ClampedAxis < -0.2)
	//{
	//	CurrentVelocity.Y = 60.0f;
	//}
	//else
	//{
	//	CurrentVelocity.Y = 0.0f;
	//}
}


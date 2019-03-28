// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceCharacter.h"
#include "RacePlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ARaceCharacter::ARaceCharacter()
	:PushForce(5000),
	PushPlayerRange(250)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ARaceCharacter::PushPlayer(TArray<ARaceCharacter*> Characters)
{
	if (UseEnergy(PushCost))
		{
			//get closest
			ARaceCharacter* closest{};
			FVector minDistance{ FLT_MAX };
			FVector distance{ FLT_MAX, FLT_MAX, FLT_MAX };
			UE_LOG(LogTemp, Display, TEXT("Before Loop"));
			for (ARaceCharacter* Char : Characters)
			{
				distance = Char->GetActorTransform().GetLocation();
				distance -= this->GetActorTransform().GetLocation();
				if (minDistance.Size() > distance.Size() && distance.Size() >= 0.5f)
				{
					minDistance = distance;
					closest = Char;
				}
			}
			UE_LOG(LogTemp, Display, TEXT("Went Through Chars found"));
			if (!closest)
			{
				Energy += PushCost;
				return false;
			}
			//Range Check
			if (minDistance.Size() > PushPlayerRange)
			{
				Energy += PushCost;
				return false;
			}
			minDistance.Z = 0;
			minDistance.Normalize();
			if(closest->GetCharacterMovement()->IsFalling())
			{
				//No friction adaption
				minDistance /= 8.0f;
			}
			//minDistance *= -1;
			//Displacement
			UCharacterMovementComponent* component;
			component = closest->FindComponentByClass<UCharacterMovementComponent>();
			component->AddImpulse(minDistance*PushForce,true);
			return true;
		}
	return false;
}


// Called when the game starts or when spawned
void ARaceCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARaceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsSprinting)
		{
			MovementSpeed = NormalSpeed;
			AddEnergy(EnergyRegen * DeltaTime);
		}
		else
		{
			if (UseEnergy((SprintCost - EnergyRegen) * DeltaTime))
				{
					MovementSpeed = SprintSpeed;
				}
				else
				{
					bIsSprinting = false;
					MovementSpeed = NormalSpeed;
					GetCharacterMovement()->MaxWalkSpeed = 750;
				}
		}
}

// Called to bind functionality to input
void ARaceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARaceCharacter::Sprint()
{
	bIsSprinting = true;
	MovementSpeed = SprintSpeed;
}

void ARaceCharacter::StopSprint()
{
	bIsSprinting = false;
	MovementSpeed = NormalSpeed;
	return;
}

float ARaceCharacter::GetSpeed()
{
	return MovementSpeed;
}

void ARaceCharacter::SetSpeed(float NewSpeed)
{
	MovementSpeed = NewSpeed;
}

void ARaceCharacter::AddEnergy(float Energy)
{
	this->Energy += Energy;
	if (this->Energy > MaxEnergy)
		{
			this->Energy = MaxEnergy;
		}
}

bool ARaceCharacter::UseEnergy(float Energy)
{
	if (this->Energy >= Energy)
		{
			this->Energy -= Energy;
			return true;
		}
	return false;
}

void ARaceCharacter::SetPlayerID(int id)
{
	PlayerId = id;
}

int ARaceCharacter::GetPlayerID()
{
	return PlayerId;
}

void ARaceCharacter::SetHasWon()
{
	if(bHasWonRace)
	{
		return;
	}
	bHasWonRace = true;
	ARacePlayerController* controller = reinterpret_cast<ARacePlayerController*>(GetController());
	controller->AddPoints(1);
}


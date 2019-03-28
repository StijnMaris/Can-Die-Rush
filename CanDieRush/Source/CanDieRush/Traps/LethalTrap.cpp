// Fill out your copyright notice in the Description page of Project Settings.

#include "LethalTrap.h"
#include "Engine/World.h"
#include "Character/RaceCharacter.h"
#include "Public/TimerManager.h"
#include "Components/SkeletalMeshComponent.h"


void ALethalTrap::KillPlayer(ARaceCharacter* Character)
{
	/*FTimerHandle DelayHandle;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(Character, FName("Destroy"));
	GetWorldTimerManager().SetTimer(DelayHandle, TimerDel, DelayTime, false);*/
	//Character->GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible,ECollisionResponse::ECR_Overlap);
	//Character->Controller->UnPossess();
	//Character->Destroy();
	
}

void ALethalTrap::TriggerTrap(float DeltaTime)
{

}

void ALethalTrap::TrapIsActive()
{
}

void ALethalTrap::ResetTrap()
{
}

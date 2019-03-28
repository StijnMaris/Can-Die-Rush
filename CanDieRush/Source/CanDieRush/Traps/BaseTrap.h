// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTrap.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UTexture2D;

UCLASS()
class CANDIERUSH_API ABaseTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//returns the mesh so it can be used by other classes
	FORCEINLINE virtual UStaticMeshComponent* GetMesh() const { return TrapMesh; }

	//FORCEINLINE virtual UBoxComponent* GetColider() const { return TriggerBox; }

	//return if the trap is active or not 
	UFUNCTION(BlueprintPure, Category = "Traps")
		virtual bool IsActive();
	//return if the trap is Triggered or not 
	UFUNCTION(BlueprintPure, Category = "Traps")
		virtual bool IsTriggered();
	//sets the trap to active or inactive when called
	UFUNCTION(BlueprintCallable, Category = "Traps")
		virtual void SetActive(bool NewActiveState);
	//sets the trap to active or inactive when called
	UFUNCTION(BlueprintCallable, Category = "Traps")
		virtual void SetTriggered(bool NewActiveState);
	//begin overlap with box
	UFUNCTION(BlueprintCallable, Category = "Traps")
		virtual void OnOverlapBeginBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//end overlap with box
	UFUNCTION(BlueprintCallable, Category = "Traps")
		virtual void OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//ui image
	UFUNCTION(BlueprintPure, Category = "TrapsUI")
		UTexture2D* GetTrapUiIcon();
private:
	/*FUNCTIONS*/

	/*VARIABLES*/
	//static mesh representing trap
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TrapMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TrapsUI", meta = (AllowPrivateAccess = "true"))
	UTexture2D* TrapUiIcon;


	//true = trap will interact with player, false = trap will not interact
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
	bool bIsActive = true;
	
	//true = trap is triggered, false = trap trap is not triggered
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Traps", meta = (AllowPrivateAccess = "true"))
	bool bIsTriggered;
};

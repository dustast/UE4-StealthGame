// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIGuard : uint8
{
	Idle,

	Suspicious,

	Alerted

};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);
	UFUNCTION()
	void ResetOrientation();

	FTimerHandle TimerHandleResetOrientation;
	FRotator GetOriginalRot;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIGuard GuardState;

	UFUNCTION()
	void OnRep_GuardState();

	void SetGuardState(EAIGuard NewGuardState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIGuard NewGuardState);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};

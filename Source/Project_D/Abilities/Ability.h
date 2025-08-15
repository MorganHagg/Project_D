// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/Object.h"
#include "Ability.generated.h"

// Enums
UENUM(BlueprintType)
enum class EAbilityState : uint8
{
	None,
	Pressed,
	Effect2_Charging
};

UENUM(BlueprintType)
enum class EAbilityActivationType : uint8
{
	None,
	Interactive,        // Complex hold/modify system (Effect1/2/3) 
	Instant,           // Single immediate effect
	Passive            // Always active, no input needed
};

//Forward declaration
class ACharacterBase;

// Class declaration
UCLASS()
class PROJECT_D_API UAbility : public UObject
{
	GENERATED_BODY()
public:
	UAbility();
	
	bool ShowDebugg = false;		// Used when debugging

	UPROPERTY()
	ACharacter* MyCaster;
	UPROPERTY()
	ACharacter* MyTarget;

	// Activating all abilities
	void ActivateAbility(AActor* NewCaster);

	// On right-click while hold
	void DoModify() {OnModify();};

	// Ending all abilities
	void EndAbility();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	EAbilityState CurrentState = EAbilityState::None;
	EAbilityActivationType AbilityType = EAbilityActivationType::None;
	FTimerHandle InputTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ClickDelay = 0.3f;

	// Child functions
	virtual void OnTap() {};
	virtual void OnHold() {};
	virtual void OnHoldEnd() {};
	virtual void OnModify() {};
	virtual void OnInstant() {};
	virtual void OnPassive() {};

	FString GetAbilityUUID();

	float PressStartTime = 0.f;
	//float clickDelay = 0.2f;	// delay to distinguish tap vs hold
	FName AbilityName = FName("NO_NAME_ABILITY");
	FString AbilityUUID;
	FTimerHandle ThresholdTimerHandle;

	virtual EAbilityActivationType GetAbilityType() const 
	{ 
		return EAbilityActivationType::None; 
	}
    
	// Virtual function that child classes override to specify their name
	virtual FName GetAbilityName() const
	{
		return FName("NO_NAME_ABILITY");
	}
    
	// Add these function declarations:
	void ThresholdMet();
};
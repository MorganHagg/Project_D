// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

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
	Interactive,        // Complex hold/release system (Effect1/2/3) 
	Instant,           // Single immediate effect
	Passive            // Always active, no input needed (like regeneration)
};

//Forward declaration
class ACharacterBase;

// Class declaration
UCLASS()
class PROJECT_D_API UAbilityBase : public UObject
{
	GENERATED_BODY()
public:
	UAbilityBase();
	
	bool ShowDebugg = false;		// Used when debugging

	UPROPERTY()
	ACharacterBase* MyCaster;
	UPROPERTY()
	ACharacterBase* MyTarget;
	void ActivateAbility(AActor* NewCaster);
	void EndAbility();
	void ExecuteHoldRightClick();
	
protected:
	UPROPERTY(BlueprintReadOnly)
	EAbilityState CurrentState = EAbilityState::None;
	EAbilityActivationType AbilityType = EAbilityActivationType::None;
	FTimerHandle InputTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ClickDelay = 0.3f;
    
	virtual void OnTap() {};
	virtual void OnHold() {};
	virtual void OnHoldRightClick() {};
	virtual void OnInstant() {};
	virtual void OnPassive() {};
	virtual void AbilityEndCleanup();

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
	void CheckHoldThreshold();
};
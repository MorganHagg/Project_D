// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/Object.h"
#include "AbilityBase.generated.h"

class ACharacterBase;

UENUM(BlueprintType)
enum class EAbilityState : uint8
{
	None,
	Pressed,
	Effect2_Charging
};

class ACharacterBase;	//Forward declaration

UCLASS()
class PROJECT_D_API UAbilityBase : public UObject
{
	GENERATED_BODY()
public:
	UAbilityBase();

protected:
	UPROPERTY(BlueprintReadOnly)
	EAbilityState CurrentState = EAbilityState::None;

	FTimerHandle InputTimerHandle;
    
	virtual void Effect1();
	virtual void Effect2();
	virtual void Effect3();
	
public:
	virtual void ActivateAbility(ACharacterBase* NewCaster);
	virtual void ExecuteEffect3(); 
	virtual void AbilityEndCleanup();
	virtual void EndAbility(bool interrupted);

	FString GetAbilityUUID();
	
	//Data
	struct AbilityData
	{
		ACharacterBase* ActorInfo;      // TODO: Store copy, not pointer
	};
	AbilityData StoredData;
	UPROPERTY()
	ACharacterBase* MyCaster;
	
	virtual void InputPressed();
	virtual void InputReleased();

	float PressStartTime = 0.f;
	float clickDelay = 0.2f;	// delay to distinguish tap vs hold
	FName AbilityName = FName("NO_NAME_ABILITY");
	ACharacterBase *MyOwner = nullptr;

protected:

	FString AbilityUUID;
	FTimerHandle ThresholdTimerHandle;
    
	// Add these function declarations:
	void CheckHoldThreshold();
};
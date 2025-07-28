// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBase.generated.h"

UENUM(BlueprintType)
enum class EAbilityState : uint8
{
	None,
	Pressed,
	Effect2_Charging
};

class ACharacterBase;	//Forward declaration

UCLASS()
class PROJECT_D_API UAbilityBase : public UGameplayAbility
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
	virtual void ExecuteEffect3();
	
	virtual void ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
	) override;

	void SetData(
	const FGameplayAbilitySpecHandle& In_Handle,
	const FGameplayAbilityActorInfo* In_ActorInfo,
	const FGameplayAbilityActivationInfo& In_ActivationInfo,
	const FGameplayEventData* In_TriggerEventData);

	virtual void AbilityEndCleanup();
	virtual void EasyEndAbility(bool WasCanceled);
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	void Interrupted();
	
	//Data
	struct AbilityData
	{
		FGameplayAbilitySpecHandle Handle;
		FGameplayAbilityActorInfo ActorInfo;      // Store copy, not pointer
		FGameplayAbilityActivationInfo ActivationInfo;
		FGameplayEventData TriggerEventData;      // Store copy, not pointer
	};
	AbilityData StoredData;
	UPROPERTY()
	ACharacterBase* MyCaster;
	
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	float PressStartTime = 0.f;
	float clickDelay = 0.2f;	// delay to distinguish tap vs hold

protected:
    
	FTimerHandle ThresholdTimerHandle;
    
	// Add these function declarations:
	void CheckHoldThreshold();
    

};

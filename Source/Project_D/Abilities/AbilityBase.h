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
	WaitingForInput,
	Effect1_Active,
	Effect2_Charging,
	Effect3_Active
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
    
	// Override these in child classes
	virtual void ExecuteEffect1() {}
	virtual void StartEffect2() {}
	virtual void UpdateEffect2(float DeltaTime) {}
	virtual void EndEffect2() {}
	
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

	float clickDelay = 0.1f;	// delay to distinguish tap vs hold
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "../Characters/CharacterBase.h"

UAbilityBase::UAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    
	// Also set these for proper input handling
	bReplicateInputDirectly = true;
	bRetriggerInstancedAbility = false;
}

void UAbilityBase::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	SetData(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	MyCaster = Cast<ACharacterBase>(ActorInfo->AvatarActor.Get());
	if (MyCaster){
		MyCaster->ActiveAbility = this;}
	
	CurrentState = EAbilityState::WaitingForInput;
    
	// Clear any existing timer
	GetWorld()->GetTimerManager().ClearTimer(InputTimerHandle);
}

void UAbilityBase::SetData(
	const FGameplayAbilitySpecHandle& In_Handle,
	const FGameplayAbilityActorInfo* In_ActorInfo,
	const FGameplayAbilityActivationInfo& In_ActivationInfo,
	const FGameplayEventData* In_TriggerEventData)
{

	StoredData.Handle = In_Handle;
	if (In_ActorInfo)
		StoredData.ActorInfo = *In_ActorInfo;  // Copy the data
	StoredData.ActivationInfo = In_ActivationInfo;
	if (In_TriggerEventData)
		StoredData.TriggerEventData = *In_TriggerEventData;  // Copy the data
}

void UAbilityBase::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (CurrentState == EAbilityState::WaitingForInput)
	{
		// Clear any existing timer first
		GetWorld()->GetTimerManager().ClearTimer(InputTimerHandle);
        
		// Start timer to distinguish between tap and hold
		GetWorld()->GetTimerManager().SetTimer(InputTimerHandle, [this]
		{
			if (CurrentState == EAbilityState::WaitingForInput)	
			{
				// Key is still held, start Effect 2
				CurrentState = EAbilityState::Effect2_Charging;
				StartEffect2();
			}
		}, clickDelay, false);
	}
}

void UAbilityBase::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (CurrentState == EAbilityState::WaitingForInput)
	{
		// Quick tap - do Effect 1
		GetWorld()->GetTimerManager().ClearTimer(InputTimerHandle);
		CurrentState = EAbilityState::Effect1_Active;
		ExecuteEffect1();
		// Reset state before ending
		CurrentState = EAbilityState::None;
		EasyEndAbility(false);
	}
	else if (CurrentState == EAbilityState::Effect2_Charging)
	{
		// Released while charging - end Effect 2
		EndEffect2();
		// Reset state before ending
		CurrentState = EAbilityState::None;
		EasyEndAbility(false);
	}
}

void UAbilityBase::ExecuteEffect3()
{
	if (CurrentState == EAbilityState::Effect2_Charging)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Executing effect 3"));
		
	}
	EndAbility(StoredData.Handle, &StoredData.ActorInfo, StoredData.ActivationInfo, true, false);
}


// End of Ability
void UAbilityBase::AbilityEndCleanup()
{
	// Cleanup function if an ability needs it
}

void UAbilityBase::EasyEndAbility(bool WasCanceled)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "EndAbility");
	AbilityEndCleanup();
	EndAbility(StoredData.Handle, &StoredData.ActorInfo, StoredData.ActivationInfo, true, WasCanceled);
}

void UAbilityBase::Interrupted()
{
	EndAbility(StoredData.Handle, &StoredData.ActorInfo, StoredData.ActivationInfo, true, true);
}
void UAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Clean up timer and reset state
	if (MyCaster){
		MyCaster->ActiveAbility = nullptr;}
	GetWorld()->GetTimerManager().ClearTimer(InputTimerHandle);
	CurrentState = EAbilityState::None;
    
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
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
	PressStartTime = GetWorld()->GetTimeSeconds();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Started counter"));
	SetData(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	MyCaster = Cast<ACharacterBase>(ActorInfo->AvatarActor.Get());
	if (MyCaster){
		MyCaster->ActiveAbility = this;}
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
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Input pressed"));
	EasyEndAbility(false);
}

void UAbilityBase::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	float DelayTime = GetWorld()->GetTimeSeconds() - PressStartTime;
	UE_LOG(LogTemp, Warning, TEXT("Delay time: %f"), DelayTime);
	if (DelayTime > MyCaster->ClickDelay)
	{
		Effect2();
	}
	else
	{
		Effect1();
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
	if (MyCaster)
	{
		MyCaster->ActiveAbility = nullptr;
	}
	GetWorld()->GetTimerManager().ClearTimer(InputTimerHandle);
	CurrentState = EAbilityState::None;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

#include "AbilityBase.h"
#include "../Character/CharacterBase.h"

UAbilityBase::UAbilityBase()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    
    // Also set these for proper input handling
    bReplicateInputDirectly = true;
    bRetriggerInstancedAbility = false;
    
    // Initialize state
    CurrentState = EAbilityState::None;
}

void UAbilityBase::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    PressStartTime = GetWorld()->GetTimeSeconds();
    CurrentState = EAbilityState::Pressed;
    
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Ability Activated - Waiting for threshold"));
    SetData(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    MyCaster = Cast<ACharacterBase>(ActorInfo->AvatarActor.Get());
    if (MyCaster)
    {
        MyCaster->ActiveAbility = this;
        
        // Start timer to check for hold threshold
        GetWorld()->GetTimerManager().SetTimer(
            ThresholdTimerHandle,
            this,
            &UAbilityBase::CheckHoldThreshold,
            MyCaster->ClickDelay,
            false
        );
    }
}

void UAbilityBase::CheckHoldThreshold()
{
    if (CurrentState == EAbilityState::Pressed)
    {
        CurrentState = EAbilityState::Effect2_Charging;
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Hold threshold reached - Effect2 charging"));
        
        // Optional: Execute Effect2 immediately when threshold is reached
        // Or you can wait until release and just change the state
        // Effect2();
    }
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
    // Don't end ability here - let it continue to detect hold/release
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Input pressed - ability active"));
}

void UAbilityBase::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    float HoldTime = GetWorld()->GetTimeSeconds() - PressStartTime;
    UE_LOG(LogTemp, Warning, TEXT("Hold time: %f, Threshold: %f"), HoldTime, MyCaster ? MyCaster->ClickDelay : 0.0f);
    
    // Clear the threshold timer since we're releasing
    GetWorld()->GetTimerManager().ClearTimer(ThresholdTimerHandle);
    
    if (CurrentState == EAbilityState::Effect2_Charging)
    {
        // Was held long enough, execute Effect2
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Executing Effect2 (held)"));
        Effect2();
    }
    else if (CurrentState == EAbilityState::Pressed)
    {
        // Quick press, execute Effect1
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Executing Effect1 (quick press)"));
        Effect1();
    }
    
    // End the ability after executing the effect
    EasyEndAbility(false);
}

void UAbilityBase::ExecuteEffect3()
{
    if (CurrentState == EAbilityState::Effect2_Charging)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Executing Effect3 (RMB during hold)"));
        Effect3();
        
        // End ability after Effect3
        EasyEndAbility(false);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, TEXT("Effect3 not available in current state"));
    }
}

// Implement your effect functions
void UAbilityBase::Effect1()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("EFFECT 1 EXECUTED"));
    // Your Effect1 implementation here
}

void UAbilityBase::Effect2()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("EFFECT 2 EXECUTED"));
    // Your Effect2 implementation here
}

void UAbilityBase::Effect3()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("EFFECT 3 EXECUTED"));
    // Your Effect3 implementation here
}

// End of Ability
void UAbilityBase::AbilityEndCleanup()
{
    // Clear any active timers
    GetWorld()->GetTimerManager().ClearTimer(ThresholdTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(InputTimerHandle);
}

void UAbilityBase::EasyEndAbility(bool WasCanceled)
{
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
    GetWorld()->GetTimerManager().ClearTimer(ThresholdTimerHandle);
    CurrentState = EAbilityState::None;

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
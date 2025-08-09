// AbilityBase.cpp

#include "AbilityBase.h"
#include "../Character/CharacterBase.h"

UAbilityBase::UAbilityBase()
{
    CurrentState = EAbilityState::None;
    AbilityUUID = FGuid::NewGuid().ToString();
}

FString UAbilityBase::GetAbilityUUID()
{
    return AbilityUUID;
}

void UAbilityBase::ActivateAbility(ACharacterBase* NewCaster)
{
    MyCaster = NewCaster;
    
    // Use the virtual function instead of member variable
    switch (GetAbilityType())
    {
        case EAbilityActivationType::Interactive:
        {
            UWorld* World = GetWorld();
            if (!World)
            {
                UE_LOG(LogTemp, Error, TEXT("GetWorld() returned null in ActivateAbility"));
                return;
            }
            
            PressStartTime = World->GetTimeSeconds();
            CurrentState = EAbilityState::Pressed;

            if (MyCaster)
            {
                World->GetTimerManager().SetTimer(
                    ThresholdTimerHandle,
                    this,
                    &UAbilityBase::CheckHoldThreshold,
                    MyCaster->ClickDelay,
                    false
                );
            }
            break;
        }
        
        case EAbilityActivationType::Instant:
        {
            InstantEffect();
            EndAbility(false);
            break;
        }
        
        case EAbilityActivationType::Passive:
        {
            PassiveEffect();
            break;
        }
        
        case EAbilityActivationType::None:
        default:
        {
            UE_LOG(LogTemp, Error, TEXT("%s has no activation type set"), *AbilityName.ToString());
            EndAbility(false);
            break;
        }
    }
}

void UAbilityBase::CheckHoldThreshold()
{
    if (CurrentState == EAbilityState::Pressed)
    {
        CurrentState = EAbilityState::Effect2_Charging;
    }
}

void UAbilityBase::InputPressed()
{
    // Implementation
}

void UAbilityBase::InputReleased()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("GetWorld() returned null in InputReleased"));
        return;
    }
    
    float HoldTime = World->GetTimeSeconds() - PressStartTime;
    World->GetTimerManager().ClearTimer(ThresholdTimerHandle);
    
    if (CurrentState == EAbilityState::Effect2_Charging)
    {
        Effect2();
    }
    else if (CurrentState == EAbilityState::Pressed)
    {
        Effect1();
    }
    
    EndAbility(false);
}

void UAbilityBase::ExecuteEffect3()
{
    if (CurrentState == EAbilityState::Effect2_Charging)
    {
        Effect3();
        EndAbility(false);
    }
}

void UAbilityBase::AbilityEndCleanup()
{
    UWorld* World = GetWorld();
    if (World)
    {
        World->GetTimerManager().ClearTimer(ThresholdTimerHandle);
        World->GetTimerManager().ClearTimer(InputTimerHandle);
    }
    CurrentState = EAbilityState::None;
}

void UAbilityBase::EndAbility(bool interrupted)
{
    AbilityEndCleanup();
}
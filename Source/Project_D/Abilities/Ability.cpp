// AbilityBase.cpp

#include "Ability.h"
#include "../Character/PlayableCharacter.h"
// TODO: Check if this object gets market 
UAbility::UAbility()
{
    CurrentState = EAbilityState::None;
    AbilityUUID = FGuid::NewGuid().ToString();
}

FString UAbility::GetAbilityUUID()
{
    return AbilityUUID;
}

void UAbility::ActivateAbility(AActor* NewCaster)
{
    MyCaster = Cast<APlayableCharacter>(NewCaster);
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
                    &UAbility::ThresholdMet,
                    ClickDelay,
                    false
                );
            }
            break;
        }
        
        case EAbilityActivationType::Instant:
        {
            OnInstant();
            break;
        }
        
        case EAbilityActivationType::Passive:
        {
            OnPassive();
            break;
        }
        
        case EAbilityActivationType::None:
        default:
        {
            UE_LOG(LogTemp, Error, TEXT("%s has no activation type set"), *AbilityName.ToString());
            break;
        }
    }
}

// Checks the timer set in ActivateAbility, and activates the according logic
void UAbility::EndAbility()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("GetWorld() returned null in InputReleased"));
        return;
    }
    
    float HoldTime = World->GetTimeSeconds() - PressStartTime;      //TODO: Check if this is needed
    World->GetTimerManager().ClearTimer(ThresholdTimerHandle);
    
    if (CurrentState == EAbilityState::Effect2_Charging)
    {
        OnHoldEnd();
    }
    else if (CurrentState == EAbilityState::Pressed)
    {
        OnTap();
    }
}

// Ran 
void UAbility::ThresholdMet()
{
    CurrentState = EAbilityState::Effect2_Charging;
    OnHold();
}
// AbilityBase.cpp

#include "Ability.h"
#include "../Character/PlayableCharacter.h"

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
                    &UAbility::CheckHoldThreshold,
                    ClickDelay,
                    false
                );
            }
            break;
        }
        
        case EAbilityActivationType::Instant:
        {
            OnInstant();
            AbilityEndCleanup();
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
            AbilityEndCleanup();
            break;
        }
    }
}

void UAbility::CheckHoldThreshold()
{
    if (CurrentState == EAbilityState::Pressed)
    {
        CurrentState = EAbilityState::Effect2_Charging;
    }
}

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
        OnHold();
    }
    else if (CurrentState == EAbilityState::Pressed)
    {
        OnTap();
    }
    
    AbilityEndCleanup();
}

void UAbility::OnModify()      //TODO: Change this name, it's really bad
{
    OnHoldRightClick();
    AbilityEndCleanup();
}

void UAbility::AbilityEndCleanup()
{
    UWorld* World = GetWorld();
    if (World)
    {
        World->GetTimerManager().ClearTimer(ThresholdTimerHandle);
        World->GetTimerManager().ClearTimer(InputTimerHandle);
    }
    CurrentState = EAbilityState::None;
}
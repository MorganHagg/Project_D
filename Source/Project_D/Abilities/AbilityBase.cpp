#include "AbilityBase.h"
#include "../Character/CharacterBase.h"

UAbilityBase::UAbilityBase()
{
    // Initialize state
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
    PressStartTime = GetWorld()->GetTimeSeconds();
    CurrentState = EAbilityState::Pressed;
    
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Ability Activated - Waiting for threshold"));
    if (MyCaster)
    {
        //MyCaster->ActiveAbility = this;
        
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

void UAbilityBase::InputPressed()
{
    // Don't end ability here - let it continue to detect hold/release
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Input pressed - ability active"));
}

void UAbilityBase::InputReleased()
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
    EndAbility(false);
}

void UAbilityBase::ExecuteEffect3()
{
    if (CurrentState == EAbilityState::Effect2_Charging)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Executing Effect3 (RMB during hold)"));
        Effect3();
        
        // End ability after Effect3
        EndAbility(false);
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
    // Clean up timer and reset state
    if (MyCaster)
    {
        //MyCaster->ActiveAbility = nullptr;
    }
    // Clear any active timers
    GetWorld()->GetTimerManager().ClearTimer(ThresholdTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(InputTimerHandle);

    CurrentState = EAbilityState::None;
}

void UAbilityBase::EndAbility(bool interrupted)
{
    AbilityEndCleanup();
}


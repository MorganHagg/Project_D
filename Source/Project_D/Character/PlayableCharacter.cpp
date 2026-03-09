// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

APlayableCharacter::APlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
   AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystem>(TEXT("AbilitySystemComponent"));
   Attributes = CreateDefaultSubobject<UAttributeSet>(TEXT("Attributes"));
}

// Input

void APlayableCharacter::Move(const FInputActionValue& Value)
{
   UE_LOG(LogTemp, Warning, TEXT("Firing character move"))
}

void APlayableCharacter::RightClick(const FInputActionInstance& Instance)
{
   if (!PlayerController || !AbilitySystemComponent) return;
   GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("RightClick"));
   if (AbilitySystemComponent->ActiveAbility)
      AbilitySystemComponent->ActiveAbility->DoModify();
   else
      AbilitySystemComponent->InitializeAbility(static_cast<int32>(EAbilityInputID::Ability7));
}

void APlayableCharacter::RightClickReleased(const FInputActionInstance& Instance)
{
   if (!PlayerController || !AbilitySystemComponent) return;

   GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("RightClick Release "));
   AbilitySystemComponent->OnAbilityInputReleased();
}

void APlayableCharacter::OnAbilityInputPressed(const FInputActionInstance& Instance)
{
    if (!AbilitySystemComponent) return;

    if (const UInputAction* Action = Instance.GetSourceAction())
    {
       if (AbilityInputMap.Contains(Action->GetFName()))
       {
          const EAbilityInputID InputID = AbilityInputMap[Action->GetFName()];
          AbilitySystemComponent->InitializeAbility(static_cast<int32>(InputID));
       }
    }
}

void APlayableCharacter::OnAbilityInputReleased(const FInputActionInstance& Instance)
{
    if (!AbilitySystemComponent) return;

    if (const UInputAction* Action = Instance.GetSourceAction())
    {
       if (AbilityInputMap.Contains(Action->GetFName()))
       {
          const EAbilityInputID InputID = AbilityInputMap[Action->GetFName()];
          AbilitySystemComponent->OnAbilityInputReleased();
       }
    }
}

// TODO: Change this so it takes in EffectTarget (i.e, the attribute to be changed) and amount - Let the effect itself
// handle complicated logic. 
void APlayableCharacter::ModifyAttribute(UGameplayEffect* Effect)
{
   float NewHealth = Attributes->Health.Current;
   NewHealth -=Effect->Magnitude;
   // Clamp and Update health
   Attributes->Health.Current = FMath::Clamp(NewHealth, 0.0f, Attributes->Health.Max);
    
   // Check for death
   if (NewHealth <= 0.0f)
   {
      UE_LOG(LogTemp, Warning, TEXT("Player died!"));
      HandleDeath();  // Separate function for death logic
   }
}

void APlayableCharacter::HandleDeath()
{
   
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

APlayableCharacter::APlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
   AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystem>(TEXT("AbilitySystemComponent"));
   Attributes = CreateDefaultSubobject<UAttributeSet>(TEXT("Attributes"));
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

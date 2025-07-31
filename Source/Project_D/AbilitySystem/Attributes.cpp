// Fill out your copyright notice in the Description page of Project Settings.


#include "../AbilitySystem/Attributes.h"


UAttributes::UAttributes()
{
	// Initialize default values
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
    
	// Clamp Health between 0 and MaxHealth
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
    
	// Handle attribute changes after gameplay effects
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Health changed - update UI, check for death, etc.
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "../AbilitySystem/AbilitySysComp.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySysComp>(TEXT("AbilitySystemComponent"));

	Attributes = CreateDefaultSubobject<UAttributes>(FName("Attributes"));
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("UpdateHealthBar"));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}



void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ACharacterBase::HandleHealthChanged(const FOnAttributeChangeData& Data)
{
	float NewHealth = Data.NewValue;
	float OldHealth = Data.OldValue;

	float DeltaValue = (NewHealth - OldHealth);
	OnHealthChanged(DeltaValue, FGameplayTagContainer());
	UpdateHealthBar(Attributes->GetHealth(), Attributes->GetMaxHealth());
}

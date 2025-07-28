// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "../AbilitySystem/AbilitySysComp.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySysComp>(TEXT("AbilitySystemComponent"));

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveAbility)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Ability Active");
}

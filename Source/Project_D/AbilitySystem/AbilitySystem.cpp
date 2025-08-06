﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem.h"


// Sets default values for this component's properties
UAbilitySystem::UAbilitySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilitySystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilitySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilitySystem::AddAbility(UAbilityBase* Ability_In, int Index)
{
	if (Index >= 0 && Index <= Abilities.Num())
	{
		Abilities.Insert(Ability_In, Index);
	}
}

void UAbilitySystem::RemoveAbility(class AbilityBase* Ability_Out)
{
	Abilities.Remove(TArray<UAbilityBase*>::ElementType(Ability_Out));
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem.h"
//#include "../Character/PlayableCharacter.h"

// Sets default values for this component's properties
UAbilitySystem::UAbilitySystem()
{
	PrimaryComponentTick.bCanEverTick = false;
	GrantedAbilities.Empty();
	ActiveAbility = nullptr;
}


// Called when the game starts
void UAbilitySystem::BeginPlay()
{
	Super::BeginPlay();
	MyOwner = StaticCast<ACharacter*>(GetOwner());
}

void UAbilitySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// In AbilitySystem.cpp
void UAbilitySystem::AddAbility(TSubclassOf<UAbility> AbilityClass, int Index)
{
	if (!AbilityClass)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilityClass is null!"));
		return;
	}
	if (Index < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Index is negative: %d"), Index);
		return;
	}
	// Make sure array is big enough for this slot
	if (Index >= GrantedAbilities.Num())
	{
		// Resize array to fit the slot, fill with nulls
		GrantedAbilities.SetNum(Index + 1);
	}
	
	int32 ExistingIndex = GrantedAbilities.Find(AbilityClass);
	if (ExistingIndex != INDEX_NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability already exists at slot %d"), ExistingIndex);
		return;  // Don't add duplicate
	}

	// Ability doesn't exist, safe to add at desired Index
	GrantedAbilities[Index] = AbilityClass;
}

void UAbilitySystem::RemoveAbility(TSubclassOf<UAbility> AbilityClass)
{
	if (!AbilityClass)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilityClass is null!"));
		return;
	}
    
	// Find the ability in the array
	int32 FoundIndex = GrantedAbilities.Find(AbilityClass);
    
	if (FoundIndex != INDEX_NONE)
	{
		GrantedAbilities[FoundIndex] = nullptr;  // Clear the slot
		UE_LOG(LogTemp, Warning, TEXT("Found and removed ability from slot %d"), FoundIndex);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability not found in granted abilities"));
	}
}

// Alternative: Remove by index (often more useful)
void UAbilitySystem::RemoveAbilityAtIndex(int Index)
{
	if (GrantedAbilities.IsValidIndex(Index))
	{
		GrantedAbilities.RemoveAt(Index);
	}
}

void UAbilitySystem::InitializeAbility(int AbilityIndex)
{
	if (GrantedAbilities.IsValidIndex(AbilityIndex) && GrantedAbilities[AbilityIndex] && MyOwner)
	{
		UAbility* NewAbility = NewObject<UAbility>(this, GrantedAbilities[AbilityIndex]);
		NewAbility->ActivateAbility(MyOwner);
		ActiveAbility = NewAbility;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Activate ability failed"));
	}
}

	void UAbilitySystem::OnAbilityInputReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Input Released"));
	if (ActiveAbility != nullptr)
	{
		ActiveAbility->EndAbility();
		ActiveAbility = nullptr;
	}
}
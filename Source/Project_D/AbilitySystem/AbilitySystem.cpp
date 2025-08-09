// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem.h"
#include "../Character/CharacterBase.h"

// Sets default values for this component's properties
UAbilitySystem::UAbilitySystem()
{
	PrimaryComponentTick.bCanEverTick = false;

	MyOwner = Cast<ACharacterBase>(GetOwner());
	GrantedAbilities.Empty();
	ActiveAbilities.Empty();
}


// Called when the game starts
void UAbilitySystem::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAbilitySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// In AbilitySystem.cpp
void UAbilitySystem::AddAbility(TSubclassOf<UAbilityBase> AbilityClass, int Index)
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
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Adding Ability"));
}

void UAbilitySystem::RemoveAbility(TSubclassOf<UAbilityBase> AbilityClass)
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

void UAbilitySystem::ActivateAbility(int AbilityIndex)
{
	if (GrantedAbilities.IsValidIndex(AbilityIndex) && GrantedAbilities[AbilityIndex] && MyOwner)
	{
		UAbilityBase* NewAbility = NewObject<UAbilityBase>(this, GrantedAbilities[AbilityIndex]);
		NewAbility->ActivateAbility(MyOwner);
		//Make sure array is big enough for this slot
		if (AbilityIndex + 1 >= ActiveAbilities.Num())
		{
			// Resize array to fit the slot, fill with nulls
			ActiveAbilities.SetNum(AbilityIndex + 1);
		}
		ActiveAbilities[AbilityIndex] = NewAbility;

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Activate ability failed"));
	}
}

void UAbilitySystem::OnAbilityInputReleased(int AbilityIndex)
{
	if (ActiveAbilities.IsValidIndex(AbilityIndex) && ActiveAbilities[AbilityIndex] != nullptr)
	{
		// Also check if the object is still valid
		if (IsValid(ActiveAbilities[AbilityIndex]))
		{
			ActiveAbilities[AbilityIndex]->InputReleased();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Active ability at index %d is invalid, cleaning up"), AbilityIndex);
			ActiveAbilities[AbilityIndex] = nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No active ability at index %d to release"), AbilityIndex);
	}
}

void UAbilitySystem::CleanUpAbility(int AbilityIndex)
{
	ActiveAbilities[AbilityIndex] = nullptr;
}


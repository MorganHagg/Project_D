// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Abilities/Ability.h"
#include "AbilitySystem.generated.h"

class ACharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_D_API UAbilitySystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilitySystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UAbility>> GrantedAbilities; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAbility* ActiveAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)	// TODO: Change this to Pawn
	ACharacter *MyOwner = nullptr;

	UFUNCTION(BlueprintCallable)
	void AddAbility(TSubclassOf<UAbility> AbilityClass, int Index);

	UFUNCTION(BlueprintCallable)  
	void RemoveAbility(TSubclassOf<UAbility> AbilityClass);

	UFUNCTION(BlueprintCallable)
	void RemoveAbilityAtIndex(int Index);
	
	void InitializeAbility(int AbilityIndex);
	void OnAbilityInputReleased();
};

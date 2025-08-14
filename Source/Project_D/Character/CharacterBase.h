// Fill out your copyright notice in the Description page of Project Settings.


// TODO: Remove this node in the polymorph-chain.
// Reason: NPC (enemy etc.) can implement component (AbilitySystem) and interface (EffectHabndler)
// Thus it doesn't need to run setupplayerinput etc.

#pragma once

#include "CoreMinimal.h"
#include "../AbilitySystem/AbilitySystem.h"
#include "../GameplayEffect/GameplayEffect.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class PROJECT_D_API ACharacterBase : public ACharacter
{
	GENERATED_BODY() 

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ApplyGameplayEffect(UGameplayEffect* Effect);
	void AddEffect(UGameplayEffect *NewEffect);
	void RemoveEffect(UGameplayEffect *NewEffect);
	void ReceiveDamage(UGameplayEffect* Effect);
	void ReceiveHealing(UGameplayEffect* Effect);
	
	// Custom Ability System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystem* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, UGameplayEffect*> GameplayEffects;
};

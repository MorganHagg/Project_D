// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Dodge.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API UDodge : public UAbility
{
	GENERATED_BODY()

protected:

	// Activation Type
	EAbilityActivationType GetAbilityType() const override{
		return EAbilityActivationType::Instant;	}

	// Ability Name
	FName GetAbilityName() const override { 
		return FName("Dodge");	}
	
	void OnInstant() override;
};

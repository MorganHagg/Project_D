// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "ShieldBlock.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API UShieldBlock : public UAbility
{
	GENERATED_BODY()
protected:

	// Activation Type
	EAbilityActivationType GetAbilityType() const override { 
		return EAbilityActivationType::Interactive;	}

	// Ability Name
	FName GetAbilityName() const override { 
		return FName("ShieldBlock");	}
	
	void OnTap() override;
	void OnHold() override;
	void OnHoldEnd() override;
	void OnModify() override;
};

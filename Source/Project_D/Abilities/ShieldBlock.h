// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "ShieldBlock.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API UShieldBlock : public UAbilityBase
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
	void OnHoldRightClick() override;
};

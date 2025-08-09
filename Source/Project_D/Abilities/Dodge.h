// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "Dodge.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API UDodge : public UAbilityBase
{
	GENERATED_BODY()

	void ActivateAbility(ACharacterBase* NewCaster) override;
};

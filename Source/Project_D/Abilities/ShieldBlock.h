// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "ShieldBlock.generated.h"


UCLASS()
class PROJECT_D_API UShieldBlock : public UAbilityBase
{
	GENERATED_BODY()

	void Effect1() override;
	void Effect2() override;
	void EndEffect2() override;
	void Effect3() override;
	
};

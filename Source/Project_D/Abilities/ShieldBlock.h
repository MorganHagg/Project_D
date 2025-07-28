// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "ShieldBlock.generated.h"


UCLASS()
class PROJECT_D_API UShieldBlock : public UAbilityBase
{
	GENERATED_BODY()

	void ExecuteEffect1() override;
	void StartEffect2() override;
	void UpdateEffect2(float DeltaTime) override;
	void EndEffect2() override;
	void ExecuteEffect3() override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Stun_Effect.generated.h"


UCLASS()
class PROJECT_D_API UStun_Effect : public UGameplayEffect
{
	GENERATED_BODY()

	bool bOriginalMovementEnabled = true;
	bool bOriginalInputEnabled = true;
    
protected:
	void ExecuteEffect() override;
	void Deactivate() override;
};

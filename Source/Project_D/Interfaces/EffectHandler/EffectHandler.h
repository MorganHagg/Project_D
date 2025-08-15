// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../../GameplayEffect/GameplayEffect.h"
#include "EffectHandler.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEffectHandler : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_D_API IEffectHandler
{
	GENERATED_BODY()
	
public:
	virtual void ApplyGameplayEffect(UGameplayEffect* Effect) = 0;
	virtual void AddEffect(UGameplayEffect* Effect) = 0;		// TODO: Consider making this non pure virtual
	virtual void RemoveEffect(UGameplayEffect* Effect) = 0;		// TODO: Consider making this non pure virtual
	virtual void ReceiveDamage(UGameplayEffect* Effect) = 0;	// TODO: Consider making this non pure virtual
	virtual void ReceiveHealing(UGameplayEffect* Effect) = 0;	// TODO: Consider making this non pure virtual
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../../Components/AttributeSet/AttributeSet.h"
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
	virtual TMap<FString, UGameplayEffect*>& GetEffectMap() = 0;
	virtual UAttributeSet* GetAttributeSet() = 0;
	virtual void AddEffect(UGameplayEffect* Effect);
	virtual void RemoveEffect(UGameplayEffect* Effect);
};

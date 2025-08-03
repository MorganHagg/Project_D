// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDUpdater.generated.h"

UINTERFACE(NotBlueprintable)
class UHUDUpdater : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_D_API IHUDUpdater
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Display")
	virtual void UpdateHealthBar(float CurrentHealth, float MaxHealth) = 0;
	
public:
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ControllerBase.generated.h"

UCLASS()
class PROJECT_D_API AControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	void UpdateUI(float CurrentHealth, float MaxHealth);
};

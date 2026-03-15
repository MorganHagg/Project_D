// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_Base.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_D_API AAIC_Base : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIC_Base(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	void BeginPlay() override;
	
};

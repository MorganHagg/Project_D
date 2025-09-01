// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Tickable.h"
#include "Effect_Persistent.generated.h"

UCLASS()
class PROJECT_D_API UEffect_Persistent : public UGameplayEffect, public FTickableGameObject
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere)
	float LifeTime = 0.0f;    // 0 = permanent

protected:
	void VerifyValues() override;
	
	virtual void Activate(ACharacter *Target) override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void Deactivate();
	
	float TimeRemaining = 0.0f;

// Needed for Tick
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UEffect_Persistent, STATGROUP_Tickables); }
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }
};

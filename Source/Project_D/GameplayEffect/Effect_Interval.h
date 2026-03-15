// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect_Persistent.h"
#include "Effect_Interval.generated.h"

UCLASS()
class PROJECT_D_API UEffect_Interval : public UEffect_Persistent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float Interval = 0.0f;

	void VerifyValues() override;
	
	virtual void Tick(float DeltaTime) override;

	void ExecuteEffect();	
private:
	float IntervalTimer = 3.0f;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffect.h"
#include "../Character/CharacterBase.h"



void UGameplayEffect::Activate(ACharacterBase* Target)
{
	if (Target)
	{
		MyTarget = Target;
		MyTarget->AddEffect(this);	
	}
	IntervalTimer = Interval;
	TimeRemaining = LifeTime;
}

void UGameplayEffect::Tick(float DeltaTime)
{
	if (MyTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MyTarget->GetName());
	}
	
	if (Interval != 0 && (IntervalTimer -= DeltaTime) <= 0)		// Just want to point out how beautiful the "check and update value" in one go, is
	{
		IntervalEffect();
		IntervalTimer = Interval;
	}

	if (LifeTime != 0 && (TimeRemaining -= DeltaTime) <= 0)
	{
		Deactivate();
		return;
	}
}

void UGameplayEffect::Deactivate()
{
	if (MyTarget)
		MyTarget->RemoveEffect(this);
	
}




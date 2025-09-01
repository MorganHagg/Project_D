// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect_Interval.h"


void UEffect_Interval::VerifyValues()
{
	Super::VerifyValues();
	// TODO: Add variables that needs values
}

// TODO: Check logic whether Super::Tick runs before or after 
void UEffect_Interval::Tick(float DeltaTime)
{
	if (Interval != 0 && (IntervalTimer -= DeltaTime) <= 0)
	{
		ExecuteEffect();
		IntervalTimer = Interval;
	}

	Super::Tick(DeltaTime);
}

void UEffect_Interval::ExecuteEffect()
{
	Super::ExecuteEffect();
}

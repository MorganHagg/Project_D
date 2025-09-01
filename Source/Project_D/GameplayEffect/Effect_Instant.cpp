// Fill out your copyright notice in the Description page of Project Settings.

// Instant Effects will do their effect once and then get collected by Garbage Collection

#include "Effect_Instant.h"

void UEffect_Instant::VerifyValues()
{
	Super::VerifyValues();
	if (Magnitude <= 0.0f) {
		UE_LOG(LogTemp, Warning, TEXT("Effect %s has zero magnitude!"), *EffectName);
		return;  // Don't execute if not configured
	}
}

void UEffect_Instant::ExecuteEffect()
{
	
}

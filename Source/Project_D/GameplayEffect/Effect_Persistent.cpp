// Fill out your copyright notice in the Description page of Project Settings.

// Persistent Effects will last for a specified time.
// If LifeTime = 0, it will last indefinite

#include "Effect_Persistent.h"
#include "Project_D/Interfaces/EffectHandler/EffectHandler.h"

void UEffect_Persistent::VerifyValues()
{
	Super::VerifyValues();
	// TODO: Add variables that needs values
}

void UEffect_Persistent::Activate(ACharacter* Target)
{
	Super::Activate(Target);
	TargetInterface->AddEffect(this);
}

void UEffect_Persistent::Tick(float DeltaTime)
{
	if (MyTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("I AM TICKING!!!!"));
	}
	
	if (LifeTime != 0 && (TimeRemaining -= DeltaTime) <= 0)
	{
		Deactivate();
		return;
	}
}

void UEffect_Persistent::Deactivate()
{
	if (TargetInterface) {
		TargetInterface->RemoveEffect(this);
	}
}

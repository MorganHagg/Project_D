// Fill out your copyright notice in the Description page of Project Settings.


#include "Stun_Effect.h"

void UStun_Effect::ExecuteEffect()
{
	// TODO: Check the target if it has other active stuns - then remove those, and add this
	Super::ExecuteEffect();
		// Store and apply stun
	if (MyTarget)
		UE_LOG(LogTemp, Warning, TEXT("Stun_Effect::ExecuteEffect()"));
}

void UStun_Effect::Deactivate()
{
	
	
	Super::Deactivate();
	Super::Deactivate();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffect.h"	
#include "Kismet/KismetSystemLibrary.h"
#include "Project_D/Interfaces/EffectHandler/EffectHandler.h"

void UGameplayEffect::Activate(ACharacter* Target) {
        if (!Target || !UKismetSystemLibrary::DoesImplementInterface(Target, UEffectHandler::StaticClass())) {
            return;
        }
        
        MyTarget = Target;
        TargetInterface = Cast<IEffectHandler>(Target); // Cache it once
        
	if (IsInstant()) {
		ExecuteEffect(); // Just execute and we're done
	} else {
		TargetInterface->AddEffect(this); // Add to target's effect list
		IntervalTimer = Interval;
		TimeRemaining = LifeTime;
	}
}

void UGameplayEffect::Tick(float DeltaTime)
{
	if (MyTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("I AM TICKING!!!!"));
	}
	
	if (Interval != 0 && (IntervalTimer -= DeltaTime) <= 0)
	{
		ExecuteEffect();
		IntervalTimer = Interval;
	}

	if (LifeTime != 0 && (TimeRemaining -= DeltaTime) <= 0)
	{
		Deactivate();
		return;
	}
}

void UGameplayEffect::Deactivate() {
	if (TargetInterface) {
		TargetInterface->RemoveEffect(this);
	}
}

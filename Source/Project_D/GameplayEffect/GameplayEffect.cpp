// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffect.h"	
#include "Kismet/KismetSystemLibrary.h"
#include "Project_D/Interfaces/EffectHandler/EffectHandler.h"

// TODO: Change ExecuteEffect(MyTarget) to use EffectActor instead 
void UGameplayEffect::Activate(ACharacter* Target)
{
	if (Target && UKismetSystemLibrary::DoesImplementInterface(Target, UEffectHandler::StaticClass()))	// Checks if MyTarget implements Interface "EffectHandler"
	{
		MyTarget = Target;
		IEffectHandler* EffectActor = Cast<IEffectHandler>(Target);
		switch (GetEffectType())
		{
		case EEffectType::None:
			{
				UE_LOG(LogTemp, Error, TEXT("Effect has no EffectType"));
			}
		case EEffectType::Instant:
			{
				ExecuteEffect(MyTarget);
			}
			case EEffectType::Status:
			{
				EffectActor->AddEffect(this);
			
				IntervalTimer = Interval;	
				TimeRemaining = LifeTime;		
			}
		}
	}
	else{	return;	}
}

void UGameplayEffect::Tick(float DeltaTime)
{
	if (MyTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("I AM TICKING!!!!"));
	}
	
	if (Interval != 0 && (IntervalTimer -= DeltaTime) <= 0)
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
	if (MyTarget && UKismetSystemLibrary::DoesImplementInterface(MyTarget, UEffectHandler::StaticClass()))	// Checks if MyTarget implements Interface "EffectHandler"
	{
		IEffectHandler* EffectActor = Cast<IEffectHandler>(MyTarget);
		EffectActor->RemoveEffect(this);
	}
}

void UGameplayEffect::ExecuteEffect(ACharacter *Target)
{
	if (Target && UKismetSystemLibrary::DoesImplementInterface(Target, UEffectHandler::StaticClass()))	// Checks if MyTarget implements Interface "EffectHandler"
	{
		Target = MyTarget;			//TODO: Check the chain to see if this target = MyTarget is needed,
									//		or if it's redundants due to Activate (If it's not - Make one fuctnion that fires regardless if it's a periodic or instant effect
		IEffectHandler* EffectActor = Cast<IEffectHandler>(MyTarget);
		EffectActor->ModifyAttribute(this);
	}
}
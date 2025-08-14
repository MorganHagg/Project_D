// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffect.h"
#include "../Character/CharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_D/Interfaces/EffectHandler.h"


void UGameplayEffect::Activate(AActor* Target)
{	//TODO: Change DoesImplementInterface - IEffectHandler* EffectActor = Cast<IEffectHandler>(Target); will only create a pointer if it's valid (WIll return null if interface
	// is implemented in Blueprint (because Polymorphy, duh!)
	if (Target && UKismetSystemLibrary::DoesImplementInterface(Target, UEffectHandler::StaticClass()))	// Checks if MyTarget implements Interface "EffectHandler"
	{
		MyTarget = Target;
		IEffectHandler* EffectActor = Cast<IEffectHandler>(Target);
		EffectActor->AddEffect(this);
		
		IntervalTimer = Interval;
		TimeRemaining = LifeTime;
	}
	else{	return;	}
}

void UGameplayEffect::Tick(float DeltaTime)
{
	if (MyTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MyTarget->GetName());
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

void UGameplayEffect::ExecuteEffect(AActor *Target)
{
	if (Target && UKismetSystemLibrary::DoesImplementInterface(MyTarget, UEffectHandler::StaticClass()))	// Checks if MyTarget implements Interface "EffectHandler"
	{
		Target = MyTarget;
		switch (GetDamageType())
		{
		case EDamageType::Physical:
		case EDamageType::Magical:
			{
				IEffectHandler* EffectActor = Cast<IEffectHandler>(MyTarget);
				EffectActor->ReceiveDamage(this);
			}
		case EDamageType::Healing:
			{
				IEffectHandler* EffectActor = Cast<IEffectHandler>(MyTarget);
				EffectActor->ReceiveHealing(this);
			}
		}
	}
}
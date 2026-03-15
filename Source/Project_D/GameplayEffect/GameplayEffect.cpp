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
	VerifyValues();
}

void UGameplayEffect::VerifyValues()
{
	if (EffectName == "NO_NAME")
		UE_LOG(LogTemp, Error, TEXT("%s is missing a name"), *GetName());
	 
}

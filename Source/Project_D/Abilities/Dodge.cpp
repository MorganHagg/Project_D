// Fill out your copyright notice in the Description page of Project Settings.


#include "Dodge.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project_D/Character/CharacterBase.h"

void UDodge::InstantEffect()
{
	Super::InstantEffect();
	if (MyCaster)
	{
		MyCaster->GetCharacterMovement()->StopMovementImmediately();
		MyCaster->LaunchCharacter(-MyCaster->GetActorForwardVector() * 3000.f, true, true);
	}
}

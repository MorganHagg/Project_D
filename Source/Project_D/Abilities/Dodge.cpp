// Fill out your copyright notice in the Description page of Project Settings.


#include "Dodge.h"

#include "Project_D/Character/CharacterBase.h"

void UDodge::ActivateAbility(ACharacterBase* NewCaster)
{
	Super::ActivateAbility(NewCaster);
	NewCaster->Jump();
}

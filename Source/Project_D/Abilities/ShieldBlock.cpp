// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBlock.h"

#include "Project_D/Character/CharacterBase.h"


void UShieldBlock::Effect1()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Starting Effect 1");
}

void UShieldBlock::Effect2()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Starting Effect 2");
}

void UShieldBlock::Effect3()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Executing Effect 3 Shield block");
}
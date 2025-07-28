// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBlock.h"

void UShieldBlock::Effect1()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Starting Effect 1");
	EasyEndAbility(false);
}

void UShieldBlock::Effect2()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Starting Effect 2");
	EasyEndAbility(false);
}

void UShieldBlock::Effect3()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Executing Effect 3 Shield block");
	EasyEndAbility(false);
}
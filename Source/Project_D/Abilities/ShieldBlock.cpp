// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBlock.h"

void UShieldBlock::ExecuteEffect1()
{
	EasyEndAbility(false);
}

void UShieldBlock::StartEffect2()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Starting Effect 2");
}

void UShieldBlock::UpdateEffect2(float DeltaTime)
{
	Super::UpdateEffect2(DeltaTime);
}

void UShieldBlock::EndEffect2()
{
	EasyEndAbility(false);
}
void UShieldBlock::ExecuteEffect3()
{
	Super::ExecuteEffect3();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Executing Effect 3 Shield block");
	EasyEndAbility(false);
}
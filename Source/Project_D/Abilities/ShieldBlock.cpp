// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBlock.h"


void UShieldBlock::OnTap()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Starting Effect 1");
}

void UShieldBlock::OnHold()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Starting Effect 2");
}

void UShieldBlock::OnHoldEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Ending Effect 2");
}

void UShieldBlock::OnModify()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Executing Effect 3 Shield block");
}

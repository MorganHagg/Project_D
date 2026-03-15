// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordSlash.h"

void USwordSlash::OnTap()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Slashing");
}

void USwordSlash::OnHold()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Charging attack");
}

void USwordSlash::OnHoldEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Heavy attack");
}

void USwordSlash::OnModify()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Spin attack");
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBlock.h"


void UShieldBlock::OnTap()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Shield parry");
}

void UShieldBlock::OnHold()
{
	AddBuff();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Shield block");
}

void UShieldBlock::OnHoldEnd()
{
	RemoveBuff();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Ending Shield Block");
}

void UShieldBlock::OnModify()
{
	RemoveBuff();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Shield charge");
}

void UShieldBlock::AddBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Shield Block AddBuff"));
}

void UShieldBlock::RemoveBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("Shield Block RemoveBuff"));
}

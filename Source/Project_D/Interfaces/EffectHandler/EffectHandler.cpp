// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectHandler.h"

void IEffectHandler::AddEffect(UGameplayEffect* NewEffect)
{
	GetEffectMap().Add(NewEffect->GetGUid(), NewEffect);
}

void IEffectHandler::RemoveEffect(UGameplayEffect* NewEffect)
{
   GetEffectMap().Remove(NewEffect->GetGUid());
}

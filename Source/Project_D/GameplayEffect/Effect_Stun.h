// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect_Persistent.h"
#include "Effect_Stun.generated.h"


UCLASS()
class PROJECT_D_API UEffect_Stun : public UEffect_Persistent
{
	GENERATED_BODY()

	bool bOriginalMovementEnabled = true;
	bool bOriginalInputEnabled = true;
    
protected:
	void ExecuteEffect() override;
	void Deactivate() override;
};

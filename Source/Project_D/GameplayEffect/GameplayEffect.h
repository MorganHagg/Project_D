// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tickable.h"
#include "GameplayEffect.generated.h"

class ACharacterBase;

UCLASS()
class PROJECT_D_API UGameplayEffect : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	UGameplayEffect(): Effect_UUID(FGuid::NewGuid().ToString(EGuidFormats::Digits))
	{
	};
	
public:
	
	UPROPERTY(EditAnywhere)
	float Interval = 0.0f;    // 0 = no interval ticking
    
	UPROPERTY(EditAnywhere)
	float LifeTime = 0.0f;    // 0 = permanent
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ACharacterBase *MyTarget = nullptr;

	virtual void Activate(ACharacterBase *Target);
	
	virtual void Tick(float DeltaTime) override;

	virtual void Deactivate();

	virtual void IntervalEffect() {};
	
	virtual TStatId GetStatId() const override { return Super::GetStatID(); }

	FString GetGUid() {return Effect_UUID;} ;
private:
	const FString Effect_UUID;
	float IntervalTimer = 0.0f;
	float TimeRemaining = 0.0f;
};
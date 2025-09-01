// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFramework/Character.h"
#include "GameplayEffect.generated.h"

class ACharacterBase;
class IEffectHandler;

UCLASS()
class PROJECT_D_API UGameplayEffect : public UObject
{
	GENERATED_BODY()
protected:
	UGameplayEffect(): Effect_UUID(FGuid::NewGuid().ToString(EGuidFormats::Digits))
	{};
	
public:
	
	UPROPERTY(EditAnywhere)
	float Magnitude = 0.f;	  // Strength of the effect

	UPROPERTY(EditAnywhere)
	bool bIsHelpful = false;
	
	UPROPERTY(EditAnywhere)
	FString EffectName = FString("NO_NAME"); 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ACharacter *MyTarget = nullptr;

	IEffectHandler* TargetInterface = nullptr;

	FString GetGUid() {return Effect_UUID;} ;
	
protected:
	virtual void Activate(ACharacter *Target);
	virtual void ExecuteEffect() {};
	virtual void VerifyValues();
private:
	const FString Effect_UUID;
};
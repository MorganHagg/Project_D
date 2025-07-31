#pragma once

#include "CoreMinimal.h"
#include "../Abilities/AbilityBase.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UAbilitySysComp;

UCLASS()
class PROJECT_D_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	UAbilityBase* ActiveAbility;
	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UAbilitySysComp* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	float ClickDelay = 0.3f;
};
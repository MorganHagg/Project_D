#pragma once

#include "CoreMinimal.h"
#include "../Ability/AbilityBase.h"
#include "GameFramework/Character.h"
#include "../AbilitySystem/Attributes.h"
#include "AbilitySystemInterface.h"
#include "Project_D/Interfaces/HUDUpdater.h"
#include "CharacterBase.generated.h"

class UAbilitySysComp;

UCLASS()
class PROJECT_D_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public IHUDUpdater
{
	GENERATED_BODY()

public:
	ACharacterBase();

	// IAbilityInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// IHUDUpdater
	UFUNCTION(BlueprintCallable, Category = "Display")
	virtual void UpdateHealthBar(float CurrentHealth, float MaxHealth) override;  

	// Class functions
	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void OnHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTag);

	UPROPERTY(BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = true))
	UAbilityBase* ActiveAbility;
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UAbilitySysComp* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UAttributes* Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	float ClickDelay = 0.3f;

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

private:
	void HandleHealthChanged(const FOnAttributeChangeData& Data);
	
};
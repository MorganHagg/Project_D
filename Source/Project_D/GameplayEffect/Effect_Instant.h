#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Effect_Instant.generated.h"

UCLASS()
class PROJECT_D_API UEffect_Instant : public UGameplayEffect
{
	GENERATED_BODY()
    
public:
	// Factory method - creates and configures the effect
	static UEffect_Instant* Create(const FString& Name = "Instant Effect", bool bIsHelpful, float Magnitude, UObject* Outer) {
		UEffect_Instant* NewEffect = NewObject<UEffect_Instant>(Outer);
		NewEffect->EffectName = Name;
		NewEffect->bIsHelpful = bIsHelpful;
		NewEffect->Magnitude = Magnitude;
		return NewEffect;
	}
    
	// Convenience factory methods
	static UEffect_Instant* CreateDamage(const FString& Name = "Instant Damage", float Damage, UObject* Outer) {
		return Create(Name, false, Damage, Outer);  // false = harmful
	}
    
	static UEffect_Instant* CreateHeal(const FString& Name = "Instant Heal", float HealAmount, UObject* Outer) {
		return Create(Name, true, HealAmount, Outer);  // true = helpful
	}

	void VerifyValues() override;
protected:
	void ExecuteEffect() override;
};
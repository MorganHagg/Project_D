#pragma once

// Engine includes
#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
// Custom classes
#include "../Interfaces/EffectHandler/EffectHandler.h"
#include "../Components/AbilitySystem/AbilitySystem.h"
#include "../GameplayEffect/GameplayEffect.h"
#include "../Components/AttributeSet/AttributeSet.h"
#include "../Input/ControllerBase.h"
// Generated
#include "PlayableCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECT_D_API APlayableCharacter : public ACharacter, public IEffectHandler
{
    GENERATED_BODY()

public:
    APlayableCharacter();

    // Custom Ability System Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystem* AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<FString, UGameplayEffect*> GameplayEffects;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UAttributeSet *Attributes;
    
    // Interface functions
    UAttributeSet* GetAttributeSet() {return Attributes;};
    void ModifyAttribute(UGameplayEffect* Effect);

    TMap<FString, UGameplayEffect*>& GetEffectMap() {return GameplayEffects;};

    
    void HandleDeath();

    
protected:
    // References
    UPROPERTY(BlueprintReadOnly, Category = "Player")
    APlayerController* PlayerController;

};
#pragma once

// Engine includes
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
// Custom includes
#include "../Interfaces/EffectHandler/EffectHandler.h"
#include "../Components/AbilitySystem/AbilitySystem.h"
#include "../GameplayEffect/GameplayEffect.h"
#include "../Components/AttributeSet/AttributeSet.h"
//Generated
#include "PlayableCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

// Ability input enum
UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
    None = 0,
    Ability1 = 1,
    Ability2 = 2,
    Ability3 = 3,
    Ability4 = 4,
    Ability5 = 5,
    Ability6 = 6,
    Ability7 = 7
};

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

    // Interface functions
    void ApplyGameplayEffect(UGameplayEffect* Effect);
    void AddEffect(UGameplayEffect *NewEffect);
    void RemoveEffect(UGameplayEffect *NewEffect);
    void ReceiveDamage(UGameplayEffect* Effect);
    void ReceiveHealing(UGameplayEffect* Effect);

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UAttributeSet *Attributes;
    
protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Input Actions
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* InputMapping;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_Move;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_RightClick;

    // Ability Input Actions
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Abilities")
    UInputAction* Ability1Action;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Abilities")
    UInputAction* Ability2Action;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Abilities")
    UInputAction* Ability3Action;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Abilities")
    UInputAction* Ability4Action;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Abilities")
    UInputAction* Ability5Action;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Abilities")
    UInputAction* Ability6Action;

    // References
    UPROPERTY(BlueprintReadOnly, Category = "Player")
    APlayerController* PlayerController;


private:
    // Input handling functions
    void Move();
    void RightClick(const FInputActionInstance& Instance);
    void RightClickReleased(const FInputActionInstance& Instance);

    TMap<FName, EAbilityInputID> AbilityInputMap;
    
    UFUNCTION()
    void OnAbilityInputPressed(const FInputActionInstance& Instance);

    UFUNCTION()
    void OnAbilityInputReleased(const FInputActionInstance& Instance);
};
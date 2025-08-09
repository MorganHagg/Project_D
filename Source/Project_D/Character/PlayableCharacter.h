#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "../Controller/ControllerBase.h"
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
class PROJECT_D_API APlayableCharacter : public ACharacterBase
{
    GENERATED_BODY()

public:
    APlayableCharacter();

    // // IHUDUpdater
    // virtual void UpdateHealthBar(float CurrentHealth, float MaxHealth) override; 

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
    AControllerBase* PlayerController;

private:
    // Input handling functions
    void Move();
    void RightClick();

    TMap<FName, EAbilityInputID> AbilityInputMap;
    
    UFUNCTION()
    void OnAbilityInputPressed(const FInputActionInstance& Instance);

    UFUNCTION()
    void OnAbilityInputReleased(const FInputActionInstance& Instance);
};
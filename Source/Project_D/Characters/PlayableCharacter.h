// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayableCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UAbilityBase;
class UAbilitySysComp;

// Forward declare your ability input enum
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
class PROJECT_D_API APlayableCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APlayableCharacter();

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

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilitySysComp* AbilitySystemComponent;

    // References
    UPROPERTY(BlueprintReadOnly, Category = "Player")
    APlayerController* PlayerController;

    UPROPERTY(BlueprintReadOnly, Category = "Abilities")
    UAbilityBase* ActiveAbility;

private:
    // Input handling functions
    void Move();
    void RightClick();
    
    void Input_Ability1_Pressed();
    void Input_Ability1_Released();
    void Input_Ability2_Pressed();
    void Input_Ability2_Released();
    void Input_Ability3_Pressed();
    void Input_Ability3_Released();
    void Input_Ability4_Pressed();
    void Input_Ability4_Released();
    void Input_Ability5_Pressed();
    void Input_Ability5_Released();
    void Input_Ability6_Pressed();
    void Input_Ability6_Released();
};
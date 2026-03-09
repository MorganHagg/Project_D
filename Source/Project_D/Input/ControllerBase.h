

#pragma once

// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// Generated
#include "ControllerBase.generated.h"

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

// Forward declaration
class APlayableCharacter;


UCLASS()
class PROJECT_D_API AControllerBase : public APlayerController
{
	GENERATED_BODY()
	AControllerBase();
	void BeginPlay();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	APlayableCharacter *PlayerReference = nullptr;


protected:
	// Input Actions
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext_Movement;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* MappingContext_Abilities;

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

private:
	TMap<FName, EAbilityInputID> AbilityInputMap;

	// Input handling functions
	void Move(const FInputActionValue& Value);
	void FaceMouseCursor();
	void RightClick(const FInputActionInstance& Instance);
	void RightClickReleased(const FInputActionInstance& Instance);

	UFUNCTION()
	void OnAbilityInputPressed(const FInputActionInstance& Instance);

	UFUNCTION()
	void OnAbilityInputReleased(const FInputActionInstance& Instance);
};


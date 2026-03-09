

#pragma once

// Engine classes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
// Custom classes

// Generated
#include "ControllerBase.generated.h"

// Ability input enum
UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	Ability0 = 0, 
	Ability1 = 1
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
	UInputAction* IA_LeftClick;
	 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_RightClick;


private:
	// Used for auto assigning abilities to right and left clicks
	TMap<FName, EAbilityInputID> AbilityInputMap;

	// Input handling functions
	void Move(const FInputActionValue& Value);
	void FaceMouseCursor();

	UFUNCTION()
	void OnAbilityInputPressed(const FInputActionInstance& Instance);

	UFUNCTION()
	void OnAbilityInputReleased(const FInputActionInstance& Instance);
};


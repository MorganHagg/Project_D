// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../AbilitySystem/AbilitySysComp.h"

APlayableCharacter::APlayableCharacter()
{
	
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerController = Cast<APlayerController>(Controller);
	PlayerController->bShowMouseCursor = true;
	if (PlayerController) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			// Your Enhanced Input setup code here
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayableCharacter::Move);
		Input->BindAction(IA_RightClick, ETriggerEvent::Started, this, &APlayableCharacter::RightClick);
		// Bind ability inputs
		
		// Mapping + binding
		TArray<TPair<UInputAction*, EAbilityInputID>> Bindings = {
			{ Ability1Action, EAbilityInputID::Ability1 },
			{ Ability2Action, EAbilityInputID::Ability2 },
			{ Ability3Action, EAbilityInputID::Ability3 },
			{ Ability4Action, EAbilityInputID::Ability4 },
			{ Ability5Action, EAbilityInputID::Ability5 },
			{ Ability6Action, EAbilityInputID::Ability6 }
		};

		for (const auto& Pair : Bindings)
		{
			if (Pair.Key)
			{
				AbilityInputMap.Add(Pair.Key->GetFName(), Pair.Value);
				Input->BindAction(Pair.Key, ETriggerEvent::Started, this, &APlayableCharacter::OnAbilityInputPressed);
				Input->BindAction(Pair.Key, ETriggerEvent::Completed, this, &APlayableCharacter::OnAbilityInputReleased);
			}	
		}
	}
}

void APlayableCharacter::Move()
{
	if (PlayerController)
	{
		FHitResult HitResult;
		if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			FVector TargetLocation = HitResult.Location;
			// Use AI pathfinding to move to clicked location
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLocation);
		}
	}
}

void APlayableCharacter::RightClick()
{
	if (!PlayerController) return;

	if (ActiveAbility)
	{
		ActiveAbility->ExecuteEffect3();
	}
	else if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Ability7));	
	}
}

void APlayableCharacter::OnAbilityInputPressed(const FInputActionInstance& Instance)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Pressed"));
	if (!AbilitySystemComponent) return;

	if (const UInputAction* Action = Instance.GetSourceAction())
	{
		if (AbilityInputMap.Contains(Action->GetFName()))
		{
			const EAbilityInputID InputID = AbilityInputMap[Action->GetFName()];
			AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(InputID));
		}
	}
}

void APlayableCharacter::OnAbilityInputReleased(const FInputActionInstance& Instance)
{
	
	if (!AbilitySystemComponent) return;

	if (const UInputAction* Action = Instance.GetSourceAction())
	{
		if (AbilityInputMap.Contains(Action->GetFName()))
		{
			const EAbilityInputID InputID = AbilityInputMap[Action->GetFName()];
			AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(InputID));
		}
	}
}

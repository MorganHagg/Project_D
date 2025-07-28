// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
// #include "InputMappingContext.h"
// #include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h" 
#include "../Abilities/Dodge.h"
#include "Project_D/AbilitySystem/AbilitySysComp.h"

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
		Input->BindAction(IA_RightClick, ETriggerEvent::Triggered, this, &APlayableCharacter::RightClick);
		// Bind ability inputs
		
		if (Ability1Action)				// Input 1
		{
			Input->BindAction(Ability1Action, ETriggerEvent::Started, this, &APlayableCharacter::Input_Ability1_Pressed);
			Input->BindAction(Ability1Action, ETriggerEvent::Completed, this, &APlayableCharacter::Input_Ability1_Released);
		}
		
		if (Ability2Action)				// Input 2
		{
			Input->BindAction(Ability2Action, ETriggerEvent::Started, this, &APlayableCharacter::Input_Ability2_Pressed);
			Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &APlayableCharacter::Input_Ability2_Released);
		}
		if (Ability3Action)				// Input 3
		{
			Input->BindAction(Ability3Action, ETriggerEvent::Started, this, &APlayableCharacter::Input_Ability3_Pressed);
			Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &APlayableCharacter::Input_Ability3_Released);
		}
		if (Ability4Action)				// Input 4
		{
			Input->BindAction(Ability4Action, ETriggerEvent::Started, this, &APlayableCharacter::Input_Ability4_Pressed);
			Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &APlayableCharacter::Input_Ability4_Released);
		}
		if (Ability5Action)				// Input Q
		{
			Input->BindAction(Ability5Action, ETriggerEvent::Started, this, &APlayableCharacter::Input_Ability5_Pressed);
			Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &APlayableCharacter::Input_Ability5_Released);
		}
		if (Ability6Action)				// Input E
		{
			Input->BindAction(Ability6Action, ETriggerEvent::Started, this, &APlayableCharacter::Input_Ability6_Pressed);
			Input->BindAction(Ability2Action, ETriggerEvent::Completed, this, &APlayableCharacter::Input_Ability6_Released);
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
	if (PlayerController)
	{
		if (ActiveAbility != nullptr)
		{
			ActiveAbility->ExecuteEffect3();
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("ActiveAbility Shot pew pew lazer beemz"));
		}
		else
		{
			AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Ability7));	
		}
	}
}

void APlayableCharacter::Input_Ability1_Pressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Ability1));
	}
}

void APlayableCharacter::Input_Ability1_Released()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(EAbilityInputID::Ability1));
	}
}

void APlayableCharacter::Input_Ability2_Pressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Ability2));
	}
}

void APlayableCharacter::Input_Ability2_Released()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(EAbilityInputID::Ability2));
	}
}

void APlayableCharacter::Input_Ability3_Pressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Ability3));
	}
}

void APlayableCharacter::Input_Ability3_Released()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(EAbilityInputID::Ability3));
}

void APlayableCharacter::Input_Ability4_Pressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Ability4));
	}
}

void APlayableCharacter::Input_Ability4_Released()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(EAbilityInputID::Ability4));
}

void APlayableCharacter::Input_Ability5_Pressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Ability5));
	}
}

void APlayableCharacter::Input_Ability5_Released()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(EAbilityInputID::Ability5));
}

void APlayableCharacter::Input_Ability6_Pressed()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Ability6));
	}
}

void APlayableCharacter::Input_Ability6_Released()
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(EAbilityInputID::Ability6));
}
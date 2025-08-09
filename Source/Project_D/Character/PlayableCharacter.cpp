// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


// Sets default values
APlayableCharacter::APlayableCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
//
// void APlayableCharacter::UpdateHealthBar(float CurrentHealth, float MaxHealth)
// {
//     Super::UpdateHealthBar(CurrentHealth, MaxHealth);
//     if (PlayerController)
//     {
//        PlayerController->UpdateUI(CurrentHealth, MaxHealth);
//     }
// }

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerController = Cast<AControllerBase>(Controller);
    PlayerController->bShowMouseCursor = true;
    
    if (PlayerController) {
       if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
          Subsystem->AddMappingContext(InputMapping, 0);
       }
    }
    
    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
       Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayableCharacter::Move);
       Input->BindAction(IA_RightClick, ETriggerEvent::Started, this, &APlayableCharacter::RightClick);
       
       // Bind ability inputs
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
    if (!PlayerController || !AbilitySystemComponent) return;

   if (AbilitySystemComponent->ActiveAbility)
      AbilitySystemComponent->ActiveAbility->ExecuteEffect3();
   else
      AbilitySystemComponent->ActivateAbility(static_cast<int32>(EAbilityInputID::Ability7));
}

void APlayableCharacter::OnAbilityInputPressed(const FInputActionInstance& Instance)
{
    if (!AbilitySystemComponent) return;

    if (const UInputAction* Action = Instance.GetSourceAction())
    {
       if (AbilityInputMap.Contains(Action->GetFName()))
       {
          const EAbilityInputID InputID = AbilityInputMap[Action->GetFName()];
          AbilitySystemComponent->ActivateAbility(static_cast<int32>(InputID));
          GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Pressed"));
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
          AbilitySystemComponent->OnAbilityInputReleased();
          GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Released"));
       }
    }
}
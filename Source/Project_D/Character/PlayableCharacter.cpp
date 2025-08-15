// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

APlayableCharacter::APlayableCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
   AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystem>(TEXT("AbilitySystemComponent"));
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerController = Cast<APlayerController>(GetController());
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
       Input->BindAction(IA_RightClick, ETriggerEvent::Completed, this, &APlayableCharacter::RightClickReleased);
       
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

void APlayableCharacter::ApplyGameplayEffect(UGameplayEffect* Effect)
{
   switch (Effect->GetEffectType())
   { 
   case EEffectType::None:
      {
         GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("ApplyGameplayEffect : None"));
      }
   case EEffectType::Instant:
      {
         Effect->ExecuteEffect(this);
      }
   case EEffectType::Status:
      {
         Effect->Activate(this);
      }
   }
}

void APlayableCharacter::AddEffect(UGameplayEffect* NewEffect)
{
   GameplayEffects.Add(NewEffect->GetGUid(), NewEffect);
}

void APlayableCharacter::RemoveEffect(UGameplayEffect* NewEffect)
{
   GameplayEffects.Remove(NewEffect->GetGUid());
}

void APlayableCharacter::ReceiveDamage(UGameplayEffect* Effect)
{
   
}

void APlayableCharacter::ReceiveHealing(UGameplayEffect* Effect)
{
   
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

void APlayableCharacter::RightClick(const FInputActionInstance& Instance)
{
   if (!PlayerController || !AbilitySystemComponent) return;

   GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("RightClick"));
   if (AbilitySystemComponent->ActiveAbility)
      AbilitySystemComponent->ActiveAbility->OnModify();
   else
      AbilitySystemComponent->InitializeAbility(static_cast<int32>(EAbilityInputID::Ability7));

}

void APlayableCharacter::RightClickReleased(const FInputActionInstance& Instance)
{
   if (!PlayerController || !AbilitySystemComponent) return;

   GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("RightClick Release "));
   AbilitySystemComponent->OnAbilityInputReleased();
}

void APlayableCharacter::OnAbilityInputPressed(const FInputActionInstance& Instance)
{
    if (!AbilitySystemComponent) return;

    if (const UInputAction* Action = Instance.GetSourceAction())
    {
       if (AbilityInputMap.Contains(Action->GetFName()))
       {
          const EAbilityInputID InputID = AbilityInputMap[Action->GetFName()];
          AbilitySystemComponent->InitializeAbility(static_cast<int32>(InputID));
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
       }
    }
}
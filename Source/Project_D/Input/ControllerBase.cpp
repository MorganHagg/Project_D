#include "ControllerBase.h"
#include "../Character/PlayableCharacter.h"

AControllerBase::AControllerBase()
{
	
}

void AControllerBase::BeginPlay()
{
	Super::BeginPlay();
    
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext_Movement, 0);
		Subsystem->AddMappingContext(MappingContext_Abilities, 1);
	}
	PlayerReference = Cast<APlayableCharacter>(GetPawn());
	bShowMouseCursor = true;
}

void AControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AControllerBase::Move);
		Input->BindAction(IA_RightClick, ETriggerEvent::Started, this, &AControllerBase::RightClick);
		Input->BindAction(IA_RightClick, ETriggerEvent::Completed, this, &AControllerBase::RightClickReleased);
       
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
				Input->BindAction(Pair.Key, ETriggerEvent::Started, this, &AControllerBase::OnAbilityInputPressed);
				Input->BindAction(Pair.Key, ETriggerEvent::Completed, this, &AControllerBase::OnAbilityInputReleased);
			}  
		}
	}
}

void AControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerReference)
		FaceMouseCursor();
}

void AControllerBase::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	PlayerReference->AddMovementInput(ForwardDirection, MovementVector.Y);
	PlayerReference->AddMovementInput(RightDirection, MovementVector.X);
}

void AControllerBase::FaceMouseCursor()
{
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		FVector CursorLocation = HitResult.Location;
		FVector PlayerLocation = PlayerReference->GetActorLocation();

		FVector Direction = (CursorLocation - PlayerLocation);
		Direction.Z = 0.f;

		FRotator NewRotation = Direction.Rotation();
		PlayerReference->SetActorRotation(NewRotation);
	}
}

void AControllerBase::RightClick(const FInputActionInstance& Instance)
{
}

void AControllerBase::RightClickReleased(const FInputActionInstance& Instance)
{
}

void AControllerBase::OnAbilityInputPressed(const FInputActionInstance& Instance)
{
}

void AControllerBase::OnAbilityInputReleased(const FInputActionInstance& Instance)
{
}

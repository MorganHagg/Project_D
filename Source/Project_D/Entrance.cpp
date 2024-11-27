#include "Entrance.h"

UEntrance::UEntrance()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Create and attach the Arrow component
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(this);  // Attach to this scene component

	//ArrowComponent->SetRelativeLocation(this->GetRelativeLocation());
	//ArrowComponent->SetWorldRotation(this->GetForwardVector().Rotation());
	//ArrowComponent->SetRelativeTransform(this->GetRelativeTransform());
}


// Called when the game starts
void UEntrance::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UEntrance::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


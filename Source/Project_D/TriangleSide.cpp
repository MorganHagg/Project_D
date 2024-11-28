// Fill out your copyright notice in the Description page of Project Settings.


#include "TriangleSide.h"

// Sets default values for this component's properties
UTriangleSide::UTriangleSide()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Create and attach the Arrow component
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(this);  // Attach to this scene component
}


// Called when the game starts
void UTriangleSide::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTriangleSide::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


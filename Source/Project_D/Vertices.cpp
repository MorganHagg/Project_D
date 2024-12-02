// Fill out your copyright notice in the Description page of Project Settings.


#include "Vertices.h"

// Sets default values for this component's properties
UVertices::UVertices()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
    // Create the Static Mesh Component for the dot (optional for visualization)
    DotComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DotComponent"));

    // Attach the DotComponent to this component itself (no need for RootComponent)
    DotComponent->SetupAttachment(this); // Attach to the current component (UTriangleVertecies)

    // Optional: If you want a mesh for the dot (e.g., a small sphere)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (SphereMesh.Succeeded())
    {
        DotComponent->SetStaticMesh(SphereMesh.Object);
        DotComponent->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));  // Small size like a dot
    }
}


// Called when the game starts
void UVertices::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVertices::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


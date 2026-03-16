// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
// Custom
// Generated
#include "PatrolArea.generated.h"

// Struct
USTRUCT(BlueprintType)
struct FTriangle
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector  A;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector  B;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector  C;
};

UCLASS()
class PROJECT_D_API APatrolArea : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APatrolArea();

	bool IsEar(const TArray<FVector >& Polygon, const TArray<int32>& Indices, int32 A, int32 B, int32 C);
	void TriangulateSpline();

	UFUNCTION(BlueprintCallable)
	bool isPointInTriangle(FVector CheckingPoint);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTriangle> Triangles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent *Spline;
	
};
	
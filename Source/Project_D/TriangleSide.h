// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "TriangleSide.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_D_API UTriangleSide : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriangleSide();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Arrow component that will always be attached to this scene component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* ArrowComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<USceneComponent*> MyVertecies;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	bool isUsed = false;
};

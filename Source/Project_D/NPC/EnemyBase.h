#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

// Struct
USTRUCT(BlueprintType)
struct FPersonality
{
	GENERATED_BODY()

	float Aggressive;
	float Defensive;
	float Tactical;
};

UCLASS()
class PROJECT_D_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	void GeneratePersonality();
	void SetPersonality(int Aggression, float Defense, float Tactic);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Variables
	FPersonality Personality;
	
};
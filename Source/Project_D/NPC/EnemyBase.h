#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

// Struct
USTRUCT(BlueprintType)
struct FPersonality
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Aggressive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defensive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Tactical;
};

UCLASS()
class PROJECT_D_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	void GeneratePersonality();
	UFUNCTION(BlueprintCallable)
	void SetPersonality(float Aggression, float Defense, float Tactic);
	UFUNCTION(BlueprintCallable)
	FPersonality ReturnPersonality() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPersonality Personality;
	
};
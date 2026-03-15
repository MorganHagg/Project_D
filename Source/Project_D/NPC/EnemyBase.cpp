#include "EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyBase::GeneratePersonality()
{
	// generate two split points on [0,1] and sort them
	float Cut1 = FMath::FRandRange(0.0f, 1.0f);
	float Cut2 = FMath::FRandRange(0.0f, 1.0f);

	if (Cut1 > Cut2) Swap(Cut1, Cut2);

	float A = Cut1;
	float B = Cut2 - Cut1;
	float C = 1.0f - Cut2;
	
	// Fisher-Yates on three variables
	if (FMath::RandBool()) Swap(A, B);
	if (FMath::RandBool()) Swap(B, C);
	if (FMath::RandBool()) Swap(A, B);


	Personality.Aggressive = A;
	Personality.Defensive  = B;
	Personality.Tactical   = C;
	// Rread out
		UE_LOG(LogTemp, Warning, TEXT("Personality - Aggressive: %f, Defensive: %f, Tactical: %f"),
	Personality.Aggressive,
	Personality.Defensive,
	Personality.Tactical);
}

void AEnemyBase::SetPersonality(float Aggression, float Defense, float Tactic)
{
	Personality.Aggressive = Aggression;
	Personality.Defensive  = Defense;
	Personality.Tactical   = Tactic;
}

FPersonality AEnemyBase::ReturnPersonality() const
{
	return Personality;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	GeneratePersonality();
	SetPersonality(0.3f, 0.3f, 0.4f);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
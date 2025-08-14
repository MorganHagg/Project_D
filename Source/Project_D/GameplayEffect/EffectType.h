#pragma once

#include "CoreMinimal.h"
#include "EffectType.generated.h"  // IMPORTANT: Must match filename


UENUM(BlueprintType)
enum class EDamageType : uint8
{
	None		UMETA(DisplayName = "None"),
	Physical	UMETA(DisplayName = "Physical"),
	Magical		UMETA(DisplayName = "Magical"), 
	Healing		UMETA(DisplayName = "Healing")
};


UENUM(BlueprintType)
enum class EEffectType : uint8
{
	None		UMETA(DisplayName = "None"),
	Instant		UMETA(DisplayName = "Instant"),    // Immediate one-time effect
	Status		UMETA(DisplayName = "Status"),     // Permanent buff/debuff while active
};
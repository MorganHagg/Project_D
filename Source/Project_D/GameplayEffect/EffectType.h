#pragma once

#include "CoreMinimal.h"
#include "EffectType.generated.h"  // IMPORTANT: Must match filename


UENUM(BlueprintType)
enum class EEffectTarget : uint8
{
	None		UMETA(DisplayName = "None"),
	Health		UMETA(DisplayName = "Health")
};

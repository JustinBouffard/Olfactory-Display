#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScentSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScentSignature, FName, ScentId, const FString&, Payload);

UCLASS()
class OLFACTORYGAME_API UScentSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void EnterZone(FName ScentId, const FString& Payload);
	void ExitZone(FName ScentId);

	UPROPERTY(BlueprintAssignable)
	FScentSignature OnScentStarted;

	UPROPERTY(BlueprintAssignable)
	FScentSignature OnScentStopped;

private:
	struct FActiveScent
	{
		FName Id;
		FString Payload;
	};

	TArray<FActiveScent> Active;
};
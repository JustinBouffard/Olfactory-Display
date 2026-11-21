#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScentSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScentCommandSignature, const FString&, Command);

UCLASS()
class OLFACTORYGAME_API UScentSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void EnterZone(int32 Channel);
	void ExitZone(int32 Channel);

	UFUNCTION(BlueprintCallable)
	void StopAll();

	UFUNCTION(BlueprintCallable)
	void ResendActive();

	UPROPERTY(BlueprintAssignable)
	FScentCommandSignature OnScentCommand;

private:
	TMap<int32, int32> ZoneCounts;
};
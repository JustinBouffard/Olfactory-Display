#include "ScentSubsystem.h"

void UScentSubsystem::EnterZone(FName ScentId, const FString& Payload)
{
	Active.RemoveAll([&](const FActiveScent& Scent) { return Scent.Id == ScentId; });
	Active.Add(FActiveScent{ ScentId, Payload });
	OnScentStarted.Broadcast(ScentId, Payload);
}

void UScentSubsystem::ExitZone(FName ScentId)
{
	if (Active.Num() == 0)
	{
		return;
	}

	const FActiveScent Current = Active.Last();
	Active.RemoveAll([&](const FActiveScent& Scent) { return Scent.Id == ScentId; });

	if (Current.Id != ScentId)
	{
		return;
	}

	OnScentStopped.Broadcast(Current.Id, Current.Payload);

	if (Active.Num() > 0)
	{
		OnScentStarted.Broadcast(Active.Last().Id, Active.Last().Payload);
	}
}
#include "ScentSubsystem.h"

void UScentSubsystem::EnterZone(int32 Channel)
{
	int32& Count = ZoneCounts.FindOrAdd(Channel);
	Count++;

	if (Count == 1)
	{
		OnScentCommand.Broadcast(FString::Printf(TEXT("on:%d\n"), Channel));
	}
}

void UScentSubsystem::ExitZone(int32 Channel)
{
	int32* Count = ZoneCounts.Find(Channel);
	if (!Count)
	{
		return;
	}

	(*Count)--;

	if (*Count <= 0)
	{
		ZoneCounts.Remove(Channel);
		OnScentCommand.Broadcast(FString::Printf(TEXT("off:%d\n"), Channel));
	}
}

void UScentSubsystem::StopAll()
{
	TArray<int32> Channels;
	ZoneCounts.GetKeys(Channels);
	ZoneCounts.Empty();

	for (const int32 Channel : Channels)
	{
		OnScentCommand.Broadcast(FString::Printf(TEXT("off:%d\n"), Channel));
	}
}

void UScentSubsystem::ResendActive()
{
	TArray<int32> Channels;
	ZoneCounts.GetKeys(Channels);

	for (const int32 Channel : Channels)
	{
		OnScentCommand.Broadcast(FString::Printf(TEXT("on:%d\n"), Channel));
	}
}
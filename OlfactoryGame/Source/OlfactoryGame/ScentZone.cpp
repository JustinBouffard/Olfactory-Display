#include "ScentZone.h"
#include "ScentSubsystem.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/GameInstance.h"

AScentZone::AScentZone()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetBoxExtent(FVector(500.f, 500.f, 200.f));
	Box->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void AScentZone::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AScentZone::HandleBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &AScentZone::HandleEnd);
}

void AScentZone::HandleBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 BodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	const APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn || !Pawn->IsPlayerControlled())
	{
		return;
	}

	if (UScentSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UScentSubsystem>())
	{
		Subsystem->EnterZone(ScentChannel);
	}
}

void AScentZone::HandleEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 BodyIndex)
{
	const APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn || !Pawn->IsPlayerControlled())
	{
		return;
	}

	if (UScentSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UScentSubsystem>())
	{
		Subsystem->ExitZone(ScentChannel);
	}
}
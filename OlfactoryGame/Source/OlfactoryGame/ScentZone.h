#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScentZone.generated.h"

class UBoxComponent;

UCLASS()
class OLFACTORYGAME_API AScentZone : public AActor
{
	GENERATED_BODY()

public:
	AScentZone();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1", ClampMax = "4"))
	int32 ScentChannel = 1;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
	void HandleEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex);
};
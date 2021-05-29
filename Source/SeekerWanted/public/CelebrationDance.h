#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelebrationDance.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEEKERWANTED_API UCelebrationDance : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCelebrationDance();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category = "Movement");
	FVector rotation;//rotation on axis

	UPROPERTY(EditAnywhere, Category = "Movement");
	float speed;//movement speed

};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Wanted.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SEEKERWANTED_API UWanted : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWanted();
	
public:
	bool IsDetected();//Check if the object is currently seen by the seeker
	void detected();//set the object state to detected
	void vanished();//set the object state to undetected

	void NewNearest();//notify the actor it's the closest to the player
	void NewFurthest();//notify the actor it's the furthest from the player

private:
	bool visible;//true if the actor is spotted
	
};

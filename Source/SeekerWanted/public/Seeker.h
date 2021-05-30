#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Seeker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEEKERWANTED_API USeeker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USeeker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Detection");
	float DetectionDistance;//maximum distance to wanted actor that can get spotted

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug");
	bool ScreenDebug;//Onscreen debug messages and Lines Drawn between objects

private:
	TArray<AActor*> Detected;
	TArray<AActor*> UnDetected;
	void RefreshTargets();//Find all wanted actors in the world
	static void SortTargets(AActor* P, TArray<AActor*> in, TArray<AActor*>& out);//sorts an array of actors by distance
	void UpdateClosest();//Checks if there's a new closest or furthest actor and notifies them
	void AllRays();//Sends a ray to every wanted actor
	bool Ray(AActor* Target);//sends a ray to a specific actor to determine if it is visible
	bool InRange(AActor* Target);//checks if the actor is not further than Detection Distance
	void DrawDebugLines();//Draws connections to spotted wanted actors on screen
	void DrawSingleLine(int i, FColor colllor);//Draws a line from this actor to a specific wanted actor
	
	void PrintList();//Shows the list of actors on screen

	TArray<AActor*> CaF;//Closest and Furthest

};

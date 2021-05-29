#include "Wanted.h"

// Sets default values for this component's properties
UWanted::UWanted()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	visible = false;
}

bool UWanted::IsDetected() {
	return(visible);
}
void UWanted::detected() {
	visible = true;

	FString naaame = this->GetOwner()->GetName();
	UE_LOG(LogTemp, Log, TEXT("spotted: %s"), *naaame);
}
void UWanted::vanished() {
	visible = false;

	FString naaame = this->GetOwner()->GetName();
	UE_LOG(LogTemp, Log, TEXT("lost: %s"), *naaame);
}

void UWanted::NewNearest(){
	FString naaame = this->GetOwner()->GetName();
	UE_LOG(LogTemp, Log, TEXT("%s is the nearest!"), *naaame);
}
void UWanted::NewFurthest(){
	FString naaame = this->GetOwner()->GetName();
	UE_LOG(LogTemp, Log, TEXT("%s is the farthest!"), *naaame);
}
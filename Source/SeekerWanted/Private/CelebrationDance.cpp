#include "CelebrationDance.h"

// Sets default values for this component's properties
UCelebrationDance::UCelebrationDance()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	rotation = FVector(0, 0, 0);
	speed = 1.0f;
}


// Called when the game starts
void UCelebrationDance::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCelebrationDance::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ... [!] framerate dependent [!]

	FRotator NewRot = FRotator(rotation.X, rotation.Y, rotation.Z);
	FQuat QuatRotation = FQuat(NewRot);

	this->GetOwner()->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

	this->GetOwner()->SetActorLocation(this->GetOwner()->GetActorLocation()+(this->GetOwner()->GetActorForwardVector()*speed));//+FVector(xmov, ymov, zmov)
}


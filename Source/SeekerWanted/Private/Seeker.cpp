#include "Seeker.h"
#include "Wanted.h"
#include "Components/ActorComponent.h"

#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USeeker::USeeker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection");
	DetectionDistance=10000;

	ScreenDebug = true;
}


// Called when the game starts
void USeeker::BeginPlay()
{
	Super::BeginPlay();

	RefreshTargets();

	CaF.Add(NULL);
	CaF.Add(NULL);
}


// Called every frame
void USeeker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AllRays();//See what you can see O.o
	SortTargets(this->GetOwner(), Detected, Detected);//Sort by distance
	UpdateClosest();//check if someone is a new closest or furthest
	if(ScreenDebug==true){
		DrawDebugLines();//Draw a line to every target you can see
	}
}

void USeeker::RefreshTargets() {
	UnDetected.Empty();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
	for (int i = 0; i < FoundActors.Num(); i++) {
		if (UWanted* Comp = FoundActors[i]->FindComponentByClass<UWanted>()) {
			UnDetected.Add(FoundActors[i]);
		}
	}
}


void USeeker::SortTargets(AActor* P, TArray<AActor*> in, TArray<AActor*>& out){
	in.Sort([P](const AActor& A, const AActor& B) {
		float DA = A.GetDistanceTo(P);
		float DB = B.GetDistanceTo(P);
		return(DA > DB);
		});
	out = in;
}

void USeeker::UpdateClosest(){
	if(Detected.Num()>0){//hmmm...
		if (CaF[1] != Detected[0]) {
			if (UWanted* Comp = Detected[0]->FindComponentByClass<UWanted>()) {
				Comp->NewFurthest();
			}
			CaF[1] = Detected[0];
		}
		if (CaF[0] != Detected[Detected.Num() - 1]) {
			if (UWanted* Comp = Detected[Detected.Num() - 1]->FindComponentByClass<UWanted>()) {
				Comp->NewNearest();
			}
			CaF[0] = Detected[Detected.Num() - 1];
		}
	}
}

void USeeker::AllRays() {
	Detected.Empty();
	bool update = false;
	for (int i=0; i<UnDetected.Num(); i++){
		UWanted* Comp = UnDetected[i]->FindComponentByClass<UWanted>();
		if(Ray(UnDetected[i])==true && InRange(UnDetected[i])==true){
			Detected.Add(UnDetected[i]);
			if(Comp->IsDetected()==false){
				Comp->detected();
				update = true;
			}
		}else {
			if(Comp->IsDetected() == true){
				Comp->vanished();
				update=true;
			}
		}
	}

	if(update==true && ScreenDebug==true){//DEBUG
		PrintList();
	}

}

bool USeeker::Ray(AActor* Target){
	FHitResult Hit;
	FVector Start = this->GetOwner()->GetActorLocation();
	FVector End = Target->GetActorLocation();

	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	if(Hit.GetActor() == NULL){
		return(true);
	}
	if (Hit.GetActor() == Target) {
		return(true);
	}
	return(false);
}

bool USeeker::InRange(AActor* Target){
	if(this->GetOwner()->GetDistanceTo(Target)<DetectionDistance){
		return(true);
	}
	return(false);
}

void USeeker::DrawSingleLine(int i, FColor colllor){
	FVector Start = this->GetOwner()->GetActorLocation();
	FVector End = Detected[i]->GetActorLocation();
	DrawDebugLine(GetWorld(), Start, End, colllor, false, 0.01f);
}

void USeeker::DrawDebugLines(){
	if(Detected.Num()>0){
		DrawSingleLine(0, FColor::Red);
		for (int i = 1; i < Detected.Num() - 1; i++) {
			DrawSingleLine(i, FColor::Black);
		}
		DrawSingleLine(Detected.Num() - 1, FColor::Blue);
	}
}

void USeeker::PrintList(){
	SortTargets(this->GetOwner(), Detected, Detected);//Sort by distance
	FString odp = "[";
	for(int i=0; i<Detected.Num(); i++) {
		odp += Detected[i]->GetName()+", ";
	}
	odp += "]";
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *odp);
}
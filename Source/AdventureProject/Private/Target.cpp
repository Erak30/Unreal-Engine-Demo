
#include "Target.h"
#include "Blueprint/UserWidget.h"
//#include "Components/SphereComponent.h"


// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	check(TargetMesh != nullptr);

	SetRootComponent(TargetMesh);


}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	FTransform transform = GetTransform();

	StartLocation = transform.GetLocation();
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->Move();
}

void ATarget::Hit() 
{
	Destroy();
}

void ATarget::Move() 
{
	FTransform transform = GetTransform();
	FVector location_A = StartLocation;
	FVector location_B = TargetLocation;

	if (toLocation_B == true) 
	{
		this->AddActorLocalOffset((location_B - location_A) / 100, false, nullptr, ETeleportType::None);
		if ((location_B - transform.GetLocation()).Length() < 5.0f)
		{
			toLocation_B = false;

		}
	} else
	{
		this->AddActorLocalOffset((location_A - location_B) / 100, false, nullptr, ETeleportType::None);
		if ((location_A - transform.GetLocation()).Length() < 5.0f)
		{
			toLocation_B = true;

		}
	}


}


void ATarget::EndScenario() {
	if (EndWidgetClass)
	{
		UUserWidget* EndWidget =
			CreateWidget<UUserWidget>(
				GetWorld(),
				EndWidgetClass
			);

		if (EndWidget)
		{
			EndWidget->AddToViewport();
		}
	}
}

void ATarget::Stopwatch(float DeltaTime) 
{
	Time += DeltaTime;
}
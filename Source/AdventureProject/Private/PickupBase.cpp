#include "PickupBase.h"
#include "ItemDefinition.h"
#include "EquippableToolDefinition.h"
#include "Data/ItemData.h"
#include "AdventureCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

// Sets default values
APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Pickup mesh
	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	check(PickupMeshComponent != nullptr);
	SetRootComponent(PickupMeshComponent);

	// Collision sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	check(SphereComponent != nullptr);
	SphereComponent->SetupAttachment(PickupMeshComponent);
	SphereComponent->SetSphereRadius(32.f);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap
	SphereComponent->OnComponentBeginOverlap.RemoveAll(this);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnSphereBeginOverlap);

	// Initialize the pickup
	InitializePickup();
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Initialize the pickup safely
void APickupBase::InitializePickup()
{
	if (PickupDataTable.IsNull() || PickupItemID.IsNone())
	{
		return;
	}

	UDataTable* LoadedDataTable = PickupDataTable.IsValid()
		? PickupDataTable.Get()
		: PickupDataTable.LoadSynchronous();

	if (!LoadedDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PickupBase: Failed to load DataTable."));
		return;
	}

	const FItemData* ItemDataRow = LoadedDataTable->FindRow<FItemData>(PickupItemID, PickupItemID.ToString());
	if (!ItemDataRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("PickupBase: Item ID %s not found in DataTable."), *PickupItemID.ToString());
		return;
	}

	UItemDefinition* TempItemDefinition = ItemDataRow->ItemBase.IsValid()
		? ItemDataRow->ItemBase.Get()
		: ItemDataRow->ItemBase.LoadSynchronous();

	if (!TempItemDefinition)
	{
		UE_LOG(LogTemp, Warning, TEXT("PickupBase: Failed to load ItemDefinition."));
		return;
	}

	// Create a PIE-safe copy using the Transient package
	ReferenceItem = TempItemDefinition->CreateItemCopy(GetTransientPackage());
	// Set the pickup mesh
	if (UStaticMesh* LoadedMesh = TempItemDefinition->WorldMesh.IsValid()
		? TempItemDefinition->WorldMesh.Get()
		: TempItemDefinition->WorldMesh.LoadSynchronous())
	{
		PickupMeshComponent->SetStaticMesh(LoadedMesh);
	}

	PickupMeshComponent->SetVisibility(true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Handle overlaps
void APickupBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAdventureCharacter* Character = Cast<AAdventureCharacter>(OtherActor);
	if (!Character || !ReferenceItem)
	{
		return;
	}

	Character->GiveItem(ReferenceItem);

	// Hide and disable collision
	PickupMeshComponent->SetVisibility(false);
	PickupMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Handle respawn
	if (bShouldRespawn)
	{
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &APickupBase::InitializePickup, RespawnTime, false);
	}
}

// Editor property changes
void APickupBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickupBase, PickupItemID) ||
		ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickupBase, PickupDataTable))
	{
		InitializePickup();
	}
}

void APickupBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Destroy();
}
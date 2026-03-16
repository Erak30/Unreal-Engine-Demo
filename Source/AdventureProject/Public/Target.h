
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class USphereComponent;

UCLASS()
class ADVENTUREPROJECT_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target | Mesh")
	TObjectPtr<UStaticMeshComponent> TargetMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target | FVector")
	FVector TargetLocation;

	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target | Time")

	float Time;

	virtual void Hit();

	void Move();

	void EndScenario();

	void Stopwatch(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target | Components")
	//TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> EndWidgetClass;

private:

	bool toLocation_B = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

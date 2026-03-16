// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetButton.h"

// Sets default values
AResetButton::AResetButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	check(ButtonMesh != nullptr);

	SetRootComponent(ButtonMesh);


}

// Called when the game starts or when spawned
void AResetButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResetButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


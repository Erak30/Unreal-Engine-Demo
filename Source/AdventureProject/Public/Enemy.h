// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREPROJECT_API AEnemy : public ATarget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ID;
	
	void Hit() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* Targets;

	void TargetEliminated();

protected: 

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HitWidgetClass;

};

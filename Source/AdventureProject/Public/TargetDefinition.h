// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TargetDefinition.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTUREPROJECT_API UTargetDefinition : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	bool Active;

	virtual UTargetDefinition* CreateTargetCopy(UObject* Outer) const;

	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "Blueprint/UserWidget.h"
#include "Ally.generated.h"



/**
 * 
 */
UCLASS()
class ADVENTUREPROJECT_API AAlly : public ATarget
{
	GENERATED_BODY()

public:

	void Hit() override;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HitWidgetClass;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "TargetData.h"
#include "Blueprint/UserWidget.h"

void AEnemy::Hit()
{

	Destroy();

    if (HitWidgetClass)
    {
        UUserWidget* HitWidget =
            CreateWidget<UUserWidget>(
                GetWorld(),
                HitWidgetClass
            );

        if (HitWidget)
        {
            HitWidget->AddToViewport();
        }
    }

    TargetEliminated();
}

void AEnemy::TargetEliminated()
{
    TArray<FName> RowNames = Targets->GetRowNames();

    // First: deactivate this enemy
    if (FTargetData* Row = Targets->FindRow<FTargetData>(ID, TEXT("Lookup")))
    {
        Row->Active = false;
    }

    // Second: check if any enemies remain active
    for (const FName& Name : RowNames)
    {
        if (FTargetData* Row = Targets->FindRow<FTargetData>(Name, TEXT("Lookup")))
        {
            if (Row->Active)
            {
                // At least one enemy still alive → stop immediately
                return;
            }
        }
    }

    EndScenario();

    // Second: check if any enemies remain active
    for (const FName& Name : RowNames)
    {
        if (FTargetData* Row = Targets->FindRow<FTargetData>(Name, TEXT("Lookup")))
        {
            Row->Active = true;
        }
    }

    // Only reached if NONE are active
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("You eliminated all enemies!"));

}
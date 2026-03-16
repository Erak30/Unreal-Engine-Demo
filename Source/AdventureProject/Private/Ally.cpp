// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally.h"
#include "Blueprint/UserWidget.h"

void AAlly::Hit()
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
}
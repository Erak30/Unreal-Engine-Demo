// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDefinition.h"

UItemDefinition* UItemDefinition::CreateItemCopy(UObject* Outer) const
{
    // Make a copy of the actual runtime class
    UItemDefinition* ItemCopy = NewObject<UItemDefinition>(Outer, GetClass());

    // Copy base properties
    ItemCopy->ID = this->ID;
    ItemCopy->ItemType = this->ItemType;
    ItemCopy->ItemText = this->ItemText;
    ItemCopy->WorldMesh = this->WorldMesh;

    // If this is a derived class (like UEquippableToolDefinition), its own properties will be properly initialized
    // in its constructor / defaults, and no slicing occurs.

    return ItemCopy;


}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDefinition.h"

UTargetDefinition* UTargetDefinition::CreateTargetCopy(UObject* Outer) const {

	UTargetDefinition* TargetCopy = NewObject<UTargetDefinition>(Outer);

	TargetCopy->ID = this->ID;
	TargetCopy->Active = this->Active;
	return TargetCopy;
}
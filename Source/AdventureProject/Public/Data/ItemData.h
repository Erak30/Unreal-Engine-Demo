#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

class UItemDefinition;    // NEW put this back

// Defines the type of the item.
UENUM(BlueprintType)
enum class EItemType : uint8
{
	Tool        UMETA(DisplayName = "Tool"),
	Consumable  UMETA(DisplayName = "Consumable")
};

// Contains textual data about the item.
USTRUCT(BlueprintType)
struct FItemText
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;
};

// Defines a basic item that can be used in a data table.
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	// The ID name of this item (matches the row name).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName ID;

	// The type of the item.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EItemType ItemType;

	// Text struct including the item name and description.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FItemText ItemText;

	// Mesh used to represent this item in the world.
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	//TSoftObjectPtr<UStaticMesh> WorldMesh;

	// The Data Asset item definition associated with this item.
	UPROPERTY(EditAnywhere, Category = "Item Data")
	TSoftObjectPtr<UItemDefinition> ItemBase;

};
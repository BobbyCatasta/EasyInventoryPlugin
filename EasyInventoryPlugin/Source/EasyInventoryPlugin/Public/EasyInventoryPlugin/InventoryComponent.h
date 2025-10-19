// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"  
#include "Components/ActorComponent.h"  
#include "InventoryComponent.generated.h"  

/**
 * UInventoryStorageComponent represents a component attached to an actor that stores and manages the inventory of that actor.
 * It includes the items owned by the actor, their quantities, and related functions for managing the inventory.
 */

UCLASS(ClassGroup = (Inventory), meta = (BlueprintSpawnableComponent), BlueprintType)
class EASYINVENTORYPLUGIN_API UInventoryStorageComponent : public UActorComponent
{
	GENERATED_BODY()  

public:

	UInventoryStorageComponent();

	// TMap storing the items owned by the actor, with the item name as the key and the quantity as the value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<FString, int32> ItemsOwned;

	// The name of the actor that owns this inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FString InventoryOwner;

protected:

	virtual void BeginPlay() override;
};
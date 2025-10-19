// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"  
#include "InventoryComponent.h"    
#include "InventoryTradeSession.generated.h" 

/**
 * UInventoryTradeSession represents a trade session between two actors’ inventories.
 * This class handles inventory item transfers and storing the inventory data.
 */

UCLASS(ClassGroup = (Inventory)) 
class EASYINVENTORYPLUGIN_API UInventoryTradeSession : public UObject  
{
    GENERATED_BODY() 

public:
    UInventoryTradeSession();

private:

    UPROPERTY()
    UInventoryStorageComponent* FirstActorInventory;  // The inventory of the first actor in the trade
    UPROPERTY()
    UInventoryStorageComponent* SecondActorInventory; // The inventory of the second actor in the trade

public:

    // Sets the inventory data for the two actors involved in the trade session
    UFUNCTION(Category = "Inventory")
    void SetData(UInventoryStorageComponent* FirstInventory, UInventoryStorageComponent* SecondInventory);

    // Handles the logic of transferring items from one inventory to another
    UFUNCTION(Category = "Inventory")
    void TradeInventoryToInventory(UInventoryStorageComponent* InventoryToRemove,
        UInventoryStorageComponent* InventoryToAdd,
        FString ItemName,
        int32 ItemQuantityToRemove);

    // Blueprint-callable function to get the inventories of both actors involved in the trade
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
    void GetActorsInventory(UInventoryStorageComponent*& FirstInventory,
        UInventoryStorageComponent*& SecondInventory);

    // Blueprint-callable function to handle item trade from the first actor to the second
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void TradeFirstToSecond(FString ItemName, int32 QuantityToRemove);

    // Blueprint-callable function to handle item trade from the second actor to the first
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void TradeSecondToFirst(FString ItemName, int32 QuantityToRemove);
};

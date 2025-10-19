// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyInventoryPlugin/InventoryTradeSession.h"

// Constructor for UInventoryTradeSession class. Initializes the trade session.
UInventoryTradeSession::UInventoryTradeSession()
{
}

// Sets up the inventory for both traders (First and Second actor inventories).
void UInventoryTradeSession::SetData(UInventoryStorageComponent* PInventory, UInventoryStorageComponent* OInventory)
{
    FirstActorInventory = PInventory;
    SecondActorInventory = OInventory;
}

// Initiates a trade where items are transferred from the first actor to the second.
void UInventoryTradeSession::TradeFirstToSecond(FString ItemName, int32 ItemQuantityToRemove)
{
    TradeInventoryToInventory(FirstActorInventory, SecondActorInventory, ItemName, ItemQuantityToRemove);
}

// Initiates a trade where items are transferred from the second actor to the first.
void UInventoryTradeSession::TradeSecondToFirst(FString ItemName, int32 ItemQuantityToRemove)
{
    TradeInventoryToInventory(SecondActorInventory, FirstActorInventory, ItemName, ItemQuantityToRemove);
}


// It updates the inventories by removing the items from one and adding to the other.
void UInventoryTradeSession::TradeInventoryToInventory(UInventoryStorageComponent* InventoryToRemove, UInventoryStorageComponent* InventoryToAdd, FString ItemName, int32 ItemQuantityToRemove)
{
    int32* quantityOwnedByRemoved = InventoryToRemove->ItemsOwned.Find(ItemName);

    if (quantityOwnedByRemoved)
    {
        // Calculate the final quantity after removing the specified quantity.
        int32 finalQuantityOwnedByRemoved = *quantityOwnedByRemoved - ItemQuantityToRemove;

        if (finalQuantityOwnedByRemoved <= 0)
            InventoryToRemove->ItemsOwned.Remove(ItemName); // Remove the item from the inventory.
        else
            InventoryToRemove->ItemsOwned.Add(ItemName, finalQuantityOwnedByRemoved); // Update the item quantity.
    }

    int32* quantityInInventory = InventoryToAdd->ItemsOwned.Find(ItemName);

    // If the item exists in the receiving inventory, increase the quantity. If not, add the item.
    if (quantityInInventory)
        InventoryToAdd->ItemsOwned.Add(ItemName, *quantityInInventory + ItemQuantityToRemove);
    else
        InventoryToAdd->ItemsOwned.Add(ItemName, ItemQuantityToRemove); // Add the item with the specified quantity.
}

// The function returns both inventories involved in the trade by reference.
void UInventoryTradeSession::GetActorsInventory(UInventoryStorageComponent*& FirstInventory, UInventoryStorageComponent*& SecondInventory)
{
    FirstInventory = FirstActorInventory;
    SecondInventory = SecondActorInventory;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"  
#include "Subsystems/GameInstanceSubsystem.h"  
#include "InventoryTradeSession.h"
#include "FInventoryScanThread.h"  
#include "InventorySubsystem.generated.h" 

class UInventoryStorageComponent;

/**
 * UInventorySubsystem manages the overall inventory system of the game.
 * This includes handling trade sessions between actors, scanning inventory positions, and managing actors with inventories.
 */


UCLASS(ClassGroup = (Inventory)) 
class EASYINVENTORYPLUGIN_API UInventorySubsystem : public UGameInstanceSubsystem  
{
	GENERATED_BODY()  

private:
	
	UInventoryTradeSession* CurrentTradingSession; // Represents the current trade session

	// The thread responsible for scanning inventory positions (likely for highlighting actors or other actions)
	FInventoryScanThread* ScanThread;

	// Array holding all the actors that possess an inventory in the game
	TArray<AActorWithInventory*> ActorsArray;

	// Function to check if the ScanThread is null and safely stop/destroy it
	void CheckForThreadNullPtr();

public:
	virtual void BeginDestroy() override;

	// Generates a new trade session between two inventories and stores it in CurrentTradingSession
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void GenerateTradeSession(UInventoryStorageComponent* PlayerInventory, UInventoryStorageComponent* OtherInventory);

	// Destroys the current trade session
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DestroyTradeSession();

	// Retrieves the current trade session
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Inventory")
	UInventoryTradeSession* GetCurrentTradingSession();

	// Starts the scanning thread for highlighting actors' positions based on inventory data
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ShowPositionActors();

	// Adds an actor to the ActorsArray, indicating that it has an inventory
	UFUNCTION(Category = "Inventory")
	void AddInventoryActor(AActorWithInventory* Actor);

	// Removes an actor from the ActorsArray, indicating that its inventory should no longer be tracked
	UFUNCTION(Category = "Inventory")
	void RemoveInventoryActor(AActorWithInventory* Actor);

	// Checks if an actor's inventory has the right items with the required quantities
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasActorWithInventoryRightItems(UInventoryStorageComponent* ItemStorage, TMap<FString, int32> items);
};
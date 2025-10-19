// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"  
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Async/AsyncWork.h"
#include "Engine/Engine.h"

class AActorWithInventory;

/**
 * FInventoryScanThread is a class that manages a separate thread for scanning and interacting with actors' inventories.
 * This is used for performing inventory scanning operations asynchronously, without blocking the main game thread.
 */

class EASYINVENTORYPLUGIN_API FInventoryScanThread : public FRunnable
{
private:

	FRunnableThread* Thread; // The thread object that will run the `Run` function in a separate thread

	// A list of actors with inventories that will be interacted with during the thread's execution
	TArray<AActorWithInventory*> ActorsStoredForRun;

	// Function called to activate a subsystem action
	UFUNCTION(Category = "Inventory")
	void SubsystemCallActivated();

	// Function called to deactivate a subsystem action
	UFUNCTION(Category = "Inventory")
	void SubsystemCallDeactivated();

public:

	FInventoryScanThread();
	virtual ~FInventoryScanThread();

	// Main thread function that runs the scanning process
	UFUNCTION(Category = "Inventory")
	virtual uint32 Run() override;

	// Stops the thread and performs any necessary cleanup
	UFUNCTION(Category = "Inventory")
	virtual void Stop() override;

	// Starts the scanning process with the specified array of actors to highlight
	UFUNCTION(Category = "Inventory")
	void Start(TArray<AActorWithInventory*> ActorsToHighlight);
};
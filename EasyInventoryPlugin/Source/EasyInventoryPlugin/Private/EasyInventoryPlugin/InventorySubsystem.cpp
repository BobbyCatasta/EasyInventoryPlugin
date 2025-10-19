#include "EasyInventoryPlugin/InventorySubsystem.h"
#include "EasyInventoryPlugin/ActorWithInventory.h"


void UInventorySubsystem::BeginDestroy()
{
    Super::BeginDestroy();
    CheckForThreadNullPtr();
}

// Creates a new trade session between two inventories and initializes a scan thread.
void UInventorySubsystem::GenerateTradeSession(UInventoryStorageComponent* PlayerInventory, UInventoryStorageComponent* OtherInventory)
{
    // Creates a new trade session
    CurrentTradingSession = NewObject<UInventoryTradeSession>();
    CurrentTradingSession->SetData(PlayerInventory, OtherInventory);

}

// Destroys the current trade session
void UInventorySubsystem::DestroyTradeSession()
{
    CurrentTradingSession = nullptr;
}

// Returns the current trade session
UInventoryTradeSession* UInventorySubsystem::GetCurrentTradingSession()
{
    return CurrentTradingSession;
}

// Shows actors that should be highlighted in the scene
void UInventorySubsystem::ShowPositionActors()
{
    // If there is an existing scan thread, stop and delete it
    CheckForThreadNullPtr();

    ScanThread = new FInventoryScanThread();
    ScanThread->Start(ActorsArray);
}

// Adds an actor to the list of actors managed by the subsystem
void UInventorySubsystem::AddInventoryActor(AActorWithInventory* Actor)
{
    UE_LOG(LogTemp, Warning, TEXT("InventoryActor Added"));
    ActorsArray.Add(Actor);
}

// Removes an actor from the list of actors managed by the subsystem
void UInventorySubsystem::RemoveInventoryActor(AActorWithInventory* Actor)
{
    UE_LOG(LogTemp, Warning, TEXT("InventoryActor Removed"));
    ActorsArray.Remove(Actor);
}

// Checks if an inventory has the requested items
bool UInventorySubsystem::HasActorWithInventoryRightItems(UInventoryStorageComponent* ItemStorage, TMap<FString, int32> items)
{
    if (ItemStorage)
    {
        // Loops through each requested item
        for (const TPair<FString, int32> item : items)
        {
            int32* quantityItem = ItemStorage->ItemsOwned.Find(item.Key);

            if (quantityItem)
            {
                if (*quantityItem < item.Value)
                    return false;
            }
            else
                return false;
        }
    }
    return true;
}

// Checks if the scan thread is null, and if it is, stops and deletes it
void UInventorySubsystem::CheckForThreadNullPtr()
{
    if (ScanThread)
    {
        ScanThread->Stop();        // Stops the current running thread
        delete ScanThread;         // Deletes the thread object
        ScanThread = nullptr;      // Sets the thread pointer to nullptr
    }
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyInventoryPlugin/FInventoryScanThread.h"
#include "EasyInventoryPlugin/ActorWithInventory.h"
#include "Async/Async.h"
#include "Async/TaskGraphInterfaces.h"
#include "HAL/ThreadSafeCounter.h"

// Constructor for the FInventoryScanThread class.
FInventoryScanThread::FInventoryScanThread()
{
    Thread = nullptr;
}

// Destructor for FInventoryScanThread class.
FInventoryScanThread::~FInventoryScanThread()
{
    UE_LOG(LogTemp, Warning, TEXT("Thread Dead"))
    if (Thread)
    {
        // Kill the thread and delete it.
        Thread->Kill(true);
        delete Thread;
        Thread = nullptr;
    }
}

// Main function to run the thread's tasks.
uint32 FInventoryScanThread::Run()
{
    float StartTime = FPlatformTime::Seconds();
    float ElapsedTime = .0f;
    float TimeToPass = 2.0f;

    SubsystemCallActivated();
    UE_LOG(LogTemp, Warning, TEXT("Thread Started"))

    while (ElapsedTime < TimeToPass)  // Perform the operation for 2 seconds. MAGIC NUMBER
    {
        ElapsedTime = FPlatformTime::Seconds() - StartTime;

        // Sleep for 0.1 seconds to avoid blocking the thread.
        FPlatformProcess::Sleep(0.1f);
    }
    UE_LOG(LogTemp, Warning, TEXT("Thread Finished"))
    SubsystemCallDeactivated();
    return 0; 
}

// Function to reset the thread's operation.  -> To adjust
void FInventoryScanThread::Stop()
{
    SubsystemCallDeactivated();
}

// Starts the thread and passes the actors that should be highlighted to the thread.
void FInventoryScanThread::Start(TArray<AActorWithInventory*> ActorsToHighlight)
{
    ActorsStoredForRun = ActorsToHighlight;
    Thread = FRunnableThread::Create(this, TEXT("InventoryScanThread"));
}

// Function that activates the corresponding method in the ActorWithInventory for each actor in the list.
void FInventoryScanThread::SubsystemCallActivated()
{
    for (AActorWithInventory* actor : ActorsStoredForRun)
    {
        if (actor)
        {
            // Call the OnSubsystemCallAppear function on the main game thread in order to avoid crashes.
            AsyncTask(ENamedThreads::GameThread, [actor]()
            {
                actor->OnSubsystemCallAppear();
            });
        }
    }
}

// Function that activates the corresponding method in the ActorWithInventory for each actor in the list.
void FInventoryScanThread::SubsystemCallDeactivated()
{
    for (AActorWithInventory* actor : ActorsStoredForRun)
    {
        if (actor)
        {
            // Call the OnSubsystemCallDisappear function on the main game thread in order to avoid crashes.
            AsyncTask(ENamedThreads::GameThread, [actor]()
            {
                actor->OnSubsystemCallDisappear();
            });
        }
    }
}
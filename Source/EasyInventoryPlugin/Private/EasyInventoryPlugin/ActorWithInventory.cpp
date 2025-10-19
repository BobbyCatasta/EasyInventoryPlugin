// Fill out your copyright notice in the Description page of Project Settings.

#include "EasyInventoryPlugin/ActorWithInventory.h"
#include "EasyInventoryPlugin/InventorySubsystem.h"
#include "Engine/World.h" //For Plugin
#include "Engine/GameInstance.h" //For Plugin

// Constructor for the AActorWithInventory class.
AActorWithInventory::AActorWithInventory()
{
    PrimaryActorTick.bCanEverTick = false;
    ItemStorageComponent = CreateDefaultSubobject<UInventoryStorageComponent>(TEXT("Item Storage Component"));
}

// BeginPlay is called when the actor is spawned or the game begins. It registers the actor with the inventory subsystem.
void AActorWithInventory::BeginPlay()
{
    Super::BeginPlay();
    // Adds this actor to the inventory subsystem's list of inventory actors.
    GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>()->AddInventoryActor(this);
}

// EndPlay is called when the actor is destroyed or removed from the world.
void AActorWithInventory::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Checks if the world and game instance exist before proceeding.
    if (GetWorld() && GetWorld()->GetGameInstance())
    {
        UInventorySubsystem* subSystem = GetWorld()->GetGameInstance()->GetSubsystem<UInventorySubsystem>();

        if (subSystem)
        {
            // Removes this actor from the inventory subsystem's list of inventory actors.
            subSystem->RemoveInventoryActor(this);
            UE_LOG(LogTemp, Display, TEXT("Actor Removal Successful"));
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("Actor Removal Failed"));
        }
    }
}

void AActorWithInventory::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
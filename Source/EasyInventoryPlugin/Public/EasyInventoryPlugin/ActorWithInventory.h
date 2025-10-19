// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.h"
#include "ActorWithInventory.generated.h"

// This class represents an actor that has an inventory, and can interact with an inventory subsystem.

UCLASS(ClassGroup = (Inventory), Blueprintable, BlueprintType)
class EASYINVENTORYPLUGIN_API AActorWithInventory : public AActor  
{
    GENERATED_BODY()  

public:
    AActorWithInventory();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory") 
    UInventoryStorageComponent* ItemStorageComponent = nullptr;   // This component holds the inventory items for the actor

protected:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    
    virtual void Tick(float DeltaTime) override;

    // Called when the subsystem makes a call of his actors, starting his thread (es. show visual cues or indicators)
    UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
    void OnSubsystemCallAppear();

    // Called when the subsystem makes a call ending his thread (es. show visual cues or indicators)
    UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
    void OnSubsystemCallDisappear();

    // Called when the actor enters the interaction range, triggering an interaction event
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Inventory")
    void OnEnterInteract();

    // Called when the actor exits the interaction range, ending the interaction
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Inventory")
    void OnExitInteract();
};
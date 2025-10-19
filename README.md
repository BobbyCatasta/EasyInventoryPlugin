# 🎮 Easy Inventory Plugin

**Easy Inventory Plugin** is an Unreal Engine plugin that provides a comprehensive inventory management system with asynchronous scanning capabilities.

---

## 🧩 Overview

This plugin offers a modular and flexible inventory system suitable for various gameplay scenarios:

- Actor-based inventory components  
- Global inventory subsystem for game-wide inventory management  
- Trade session management for secure item exchanges  
- Asynchronous inventory scanning for high performance  
- Full Blueprint integration for designer-friendly usage  

---

## 🛠️ Components

**`UInventoryStorageComponent`**  
- Actor component for inventory storage and management  
- TMap-based item system with quantity tracking  
- Blueprint-exposed properties for designer accessibility  
- Modular design allowing attachment to any actor  

**`UInventorySubsystem`**  
- GameInstance Subsystem for global inventory management  
- Central hub for trade sessions and actor tracking  
- Thread-safe operations with proper lifecycle management  
- Blueprint-callable interface for seamless integration  

**`UInventoryTradeSession`**  
- Dedicated trade session management between multiple actors  
- Bidirectional item transfer system  
- Transaction-based inventory operations  
- Clean separation of trade logic from core inventory  

**`FInventoryScanThread`**  
- Custom `FRunnable` implementation for asynchronous operations  
- Non-blocking inventory scanning and processing  
- Proper thread lifecycle management  
- Safe cross-thread communication with the main game thread  

**`AActorWithInventory`**  
- Base actor class with built-in inventory support  
- Event-driven interaction system  
- `BlueprintImplementableEvents` for designer customization  
- Automatic subsystem registration  

---

## 💻 Key Technical Achievements

### ⚡ Advanced C++ & Unreal Integration
- Custom `FRunnable` implementation for multi-threading  
- Proper `UObject` lifecycle and garbage collection management  
- Template programming with `TMap` and `TArray`  
- Extensive Unreal Reflection System usage (`UPROPERTY`, `UFUNCTION`)  

### 🏛️ System Design Patterns
- **Subsystem Architecture**: leveraged `UGameInstanceSubsystem` for global management  
- **Component-Based Design**: decoupled inventory logic from actor implementation  
- **Observer Pattern**: event-driven communication between system components  
- **Session Management**: isolated trade sessions with clear state boundaries  

### 🚀 Performance Optimization
- Asynchronous processing to offload inventory scanning  
- Optimized `TMap` usage for item lookups  
- Thread-safe operations with proper synchronization  
- Memory-efficient smart pointer usage and cleanup  

---

## 🔧 Technical Specifications

- **Language**: C++ with Unreal Engine reflection system  
- **Threading Model**: Custom `FRunnable` with `FRunnableThread`  
- **Memory Management**: `UObject`-based with garbage collection  
- **Blueprint Integration**: Full `BlueprintCallable`, `BlueprintPure`, `BlueprintImplementableEvent` support  
- **Architecture**: Component-based with subsystem coordination  

---

## 🎯 Professional Skills Demonstrated

### 🕹️ Gameplay Systems Programming
- Inventory management systems  
- Trade and economy implementations  
- Actor-component architecture  
- Event-driven gameplay programming  

### 🔧 Engine-Level Programming
- Unreal Engine subsystem development  
- Multi-threading in a game engine context  
- Memory management and optimization  
- Engine integration patterns  

### 💼 Software Engineering
- System architecture design  
- Designer-friendly API design  
- Performance profiling and optimization  
- Cross-disciplinary collaboration readiness  

---

## 📁 Code Quality Highlights
- **Clean Architecture**: separation of concerns between components  
- **Extensible Design**: easy addition of new inventory features  
- **Documentation**: clear comments and structure  
- **Blueprint Support**: designer-friendly interface  
- **Error Handling**: robust thread safety and null checking  

---

This project showcases the ability to deliver **production-ready systems** that balance **performance**, **usability**, and **maintainability**, while demonstrating deep understanding of Unreal Engine and modern C++ development practices.

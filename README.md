# 🌿 Effective Garden Management System

> **Assignment 03 (Complex Computing Problem)**  
> Data Structures and Algorithms - 3rd Semester (Spring 2026)

A comprehensive C++ application designed to manage a garden's plants, workshops, and resources effectively. This project demonstrates the practical application of advanced data structures and algorithms in building a structured, menu-driven management system.

## 🚀 Features & Modules

The system is divided into three core modules, each utilizing specific data structures to achieve optimal performance:

### 1. 🌱 Plant Management (AVL Tree)
Manages the garden's flora, ensuring balanced and quick access.
- **Data Structure:** Custom-implemented **AVL Tree**.
- **Capabilities:**
  - Add, search, and update plants dynamically.
  - Automatic rebalancing on insertions to guarantee $O(\log n)$ operations.
  - Track plant growth rates based on daily sunlight and water levels.
  - Display thriving or struggling plants based on their growth metrics.

### 2. 🏕️ Workshop Management (Hash Table & Circular Queue)
Handles educational and community workshops in the garden.
- **Data Structures:** 
  - **Hash Table** with linear probing and auto-rehashing for quick workshop lookups by ID.
  - **Circular Queue** (vector-based) to handle participant registrations efficiently with limited slots.
- **Capabilities:**
  - Register new workshops and allocate slots.
  - Enroll participants securely using a first-come, first-served queue system.
  - View workshop schedules and participant details.
  - Cancel registrations and adjust queues automatically.

### 3. 💰 Resource Procurement (Dynamic Programming / Knapsack)
Optimizes the budget allocated for seasonal garden supplies.
- **Algorithm:** **0/1 Knapsack Problem** using Dynamic Programming (Memoization).
- **Capabilities:**
  - Filters available supplies by season (e.g., Spring, Summer, Winter).
  - Calculates the most optimal combination of supplies to maximize garden impact without exceeding the specified budget.

## 🛠️ Build & Run

### Prerequisites
- A standard C++ compiler supporting C++11 or later (e.g., GCC, Clang, MSVC).

### Compilation
Navigate to the project root and compile the source code. You can compile all source files together:

```bash
g++ src/main.cpp src/module1/plantMgt.cpp src/module2/workshopMgt.cpp src/module3/resourceProcurement.cpp src/utils/utils.cpp -o garden.exe
```

### Execution
Run the compiled executable:

```bash
./garden.exe
```
*(On Windows, you can also just double-click `garden.exe` if it is pre-compiled)*

## 📂 Project Structure

```text
Effective-Garden-Management/
├── src/
│   ├── models/            # Core data models (Workshop.h, Supply.h, Gardener.h)
│   ├── module1/           # Plant Management module (plantMgt.cpp)
│   ├── module2/           # Workshop Management module (workshopMgt.cpp)
│   ├── module3/           # Resource Procurement module (resourceProcurement.cpp)
│   ├── utils/             # Utility functions for input validation
│   └── main.cpp           # Main entry point and menu
├── garden.exe             # Pre-compiled executable
└── README.md              # Project documentation
```

---
*Developed for Data Structures & Algorithm course.*
* **Developed By**: [Muhammad Ubaid Raza](https://ubaidraza-jpg.github.io/portfolio/)

# hafa_esp32
HARDWARE AGNOSTIC FIMWARE ARCHITECTURE for ESP32 using ESP-IDF.

##  Objective

Provide a hardware-agnostic firmware architecture using Domain-Driven Design (DDD) and Test-Driven Development (TDD).

##  Core Concepts

* Domain-first design
* Hardware abstraction via interfaces
* Testable firmware (no hardware required)
* Modular component-based architecture

##  Architecture

* Domain (pure logic)
* Application (use cases)
* Infrastructure (hardware drivers)
* Interfaces (contracts)

## Initial repository structure
```
hafa-esp32/
├── README.md
├── docs/
│   └── architecture.md
├── firmware/
│   └── esp-idf-project/
│       ├── main/
│       ├── components/
│       │   ├── domain/
│       │   ├── application/
│       │   ├── infrastructure/
│       │   └── interfaces/
│       └── CMakeLists.txt
│
├── tests/
│   ├── unit/
│   └── mocks/
│
└── examples/
    └── vibration-monitoring/
```
##  Technologies

* ESP-IDF
* FreeRTOS
* C/C++

##  Example

LED

##  Status

 In development

## Documentation

See `/docs/architecture.md`


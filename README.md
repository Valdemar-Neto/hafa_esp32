# hafa_esp32
HARDWARE AGNOSTIC FIRMWARE ARCHITECTURE for ESP32 using ESP-IDF.

## Objective

Provide a hardware-agnostic firmware architecture using Domain-Driven Design (DDD) concepts and enabling Test-Driven Development (TDD) directly in C.

O objetivo é separar as regras de negócio da dependência de hardware físico, garantindo que o núcleo da sua aplicação possa ser compilado e testado em computadores normais e adaptado a diferentes hardwares.

## Core Concepts

* **Domain-first design**: O núcleo do sistema não conhece bibliotecas ou pinos de hardware.
* **Hardware abstraction via interfaces**: Uso de structs com ponteiros de função (`write`, `read`) simulando programação orientada a objetos.
* **Testable firmware**: Execução e testes sem a necessidade da placa (através de mocks).
* **Modular component-based architecture**: Separação total de responsabilidades através dos componentes nativos do ESP-IDF.

## Architecture

A separação é feita em 4 módulos (`components`):
* **Core** (Interfaces / Contracts)
* **Domain** (Pure logic)
* **Drivers** (Hardware / Infrastructure)
* **Mocks** (Test implementations)

## Project Structure
A estrutura atual do repositório reflete diretamente essa divisão:

```text
/
├── README.md
├── docs/
│   └── Architecute.md    (Detalhes do funcionamento e injeção de dependências)
├── main/
│   ├── main.c            (Ponto de montagem e conexão das dependências)
│   └── CMakeLists.txt
├── components/
│   ├── core/             (Ex: digital_io.h)
│   ├── domain/           (Ex: blink.c)
│   ├── drivers/          (Ex: gpio_driver.c usando ESP-IDF)
│   └── mocks/            (Ex: mock_digital_io.c para testes locais)
└── CMakeLists.txt
```

## Technologies

* ESP-IDF
* FreeRTOS
* C

## Example

O exemplo ativo neste template é o controle de um **LED (Blink)**, onde a rotina de domínio determina o ritmo e aciona as funções de acender/apagar de uma interface abstrata `DigitalIO`. Em seguida, a camada `app_main` injeta o driver físico `gpio_driver` que consome as APIs reais do ESP-IDF para piscar o hardware.

## Status

In development

## Documentation

Veja a fundo como a arquitetura funciona e se integra:
- [`/docs/Architecute.md`](docs/Architecute.md)

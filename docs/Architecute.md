# Arquitetura do Projeto `digital_io`

Este projeto implementa uma arquitetura modular voltada para sistemas embarcados, baseada fortemente nos princípios de **Inversão de Dependência (DIP)** e conceitos de **Clean Architecture** (ou **Ports and Adapters / Arquitetura Hexagonal**), adaptados de forma idiomática para a linguagem C. 

O principal objetivo dessa arquitetura é desacoplar as regras e a lógica da aplicação (domínio) dos detalhes de hardware específicos ou do framework subjacente (ESP-IDF). Isso confere ao projeto uma altíssima flexibilidade e testabilidade.

## Estrutura de Camadas (Pastas em `components/`)

O sistema divide as responsabilidades nas seguintes camadas:

### 1. Core (`core/`)
Define os **contratos** (Interfaces ou Portas) pelas quais o resto do sistema se comunicará.
- **`digital_io.h`**: É a abstração principal. Define a `struct DigitalIO`, que atua como uma **interface orientada a objetos** em C. Esta estrutura expõe ponteiros de função genéricos para operações de `write` e `read`, além de um ponteiro opcional genérico de contexto (`void *ctx`) para guardar o estado específico de cada implementação.
- **`digital_io_utils`**: Fornece chamadas utilitárias e seguras (wrappers) que encapsulam as checagens contra `NULL` e invocam de maneira padronizada as funções em `DigitalIO`.

### 2. Domain (`domain/`)
Contém a **lógica de negócio / regras de domínio**.
- **`blink.c` / `blink.h`**: Define o comportamento lógico de alto nível que o sistema deve executar (como `led_on` e `led_off`). Uma característica vital desta camada é que ela é **agnóstica em relação ao hardware**: ela não usa `#include "driver/gpio.h"`. Ao invés disso, ela opera inteiramente baseada na interface abstrata `DigitalIO *`. 

### 3. Drivers (`drivers/`)
Representa os **Adaptadores de Hardware Real**. Faz o elo entre a abstração do projeto e o hardware (ESP32).
- **`gpio_driver.c`**: Implementa a abstração `DigitalIO` usando as bibliotecas físicas do microcontrolador (ESP-IDF, ex: `gpio_set_level`). Esta camada também expõe uma *factory function* (`create_gpio_output`), responsável por configurar o pino físico e retornar uma instância pré-configurada da estrutura `DigitalIO` apontando para suas próprias rotinas físicas de escrita/leitura.

### 4. Mocks (`mocks/`)
Representa os **Adaptadores de Software (para Testes)**.
- **`mock_digital_io.c`**: Uma implementação falsa (mock) da interface `DigitalIO`. Esta implementação substitui comandos reais no terminal por simples estruturas em memória (salva o estado do pino) e `printf` de simulação. Isso permite usar a lógica de domínio em um computador normal durante os testes de unidade, sem depender de uma placa física ou emuladores.

## Como as peças se conectam (Injeção de Dependências - DI)

A arquitetura ganha vida através da **composição de módulos** estabelecida no ponto de entrada (`main.c` em `app_main`):
1. O tipo de driver (real ou falso) é decidido e instanciado: `DigitalIO* led = create_gpio_output(2);`.
2. Essa dependência criada (o adaptador físico, neste caso) é **injetada** nas rotinas funcionais que precisam controlá-lo: `led_on(led);`.

**A grande vantagem:** Se for necessário testar a lógica do programa, ou se o hardware mudar por completo (ex: se o LED passar a ser gerido por um CI expansor i2c em vez de pino nativo), a camada de **Domain não precisará ter nenhuma de suas linhas de código alteradas**. Basta escrever um novo "driver" implementando os ponteiros `write/read` de `DigitalIO` e trocá-lo na hora da instanciação da `app_main`.

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "gpio_driver.h" 
#include "blink.h"
#include "button.h" 
#include "digital_io.h"
#include "unity.h"
#include "test_blink.h"

void app_main(void)
{
    #ifdef CONFIG_RUN_UNIT_TESTS
        printf("\n=== INICIANDO TESTES UNITÁRIOS ===\n");
        UNITY_BEGIN();
        RUN_TEST(test_led_on_should_call_write_with_true);
        RUN_TEST(test_led_off_should_call_write_with_false);
        UNITY_END();
        printf("=== TESTES FINALIZADOS ===\n\n");
    #endif

    // 1. Inicializa os drivers
    DigitalIO* led = create_gpio_output(2); 
    DigitalIO* btn_io = create_gpio_input(0, true); // Botão BOOT
    
    if (led == NULL || btn_io == NULL) {
        printf("Erro ao inicializar drivers!\n");
        return;
    }

    // 2. Inicializa o componente de domínio (Botão)
    Button my_button;
    button_init(&my_button, btn_io, 50, true);

    bool led_state = false;
    static bool last_btn_state = false; // DECLARADO APENAS UMA VEZ AQUI

    printf("Sistema Pronto! Use o botão BOOT para alternar o LED.\n");

    while (1) {
        // Pega o tempo do RTOS para o debounce
        uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;

        // Lê o estado do botão (com o algoritmo de debounce interno)
        bool current_pressed = button_is_pressed(&my_button, now);

        // Lógica de Borda: detecta o momento exato do clique (transição 0 -> 1)
        if (current_pressed && !last_btn_state) {
            led_state = !led_state; // Toggle do estado
            
            if (led_state) {
                led_on(led);
            } else {
                led_off(led);
            }
            
            printf("Botão pressionado! LED: %s\n", led_state ? "ON" : "OFF");
        }

        // Atualiza a variável para a próxima iteração
        last_btn_state = current_pressed;

        vTaskDelay(pdMS_TO_TICKS(10)); 
    }

    // Código defensivo (nunca alcançado)
    destroy_gpio(led);
    destroy_gpio(btn_io);
}
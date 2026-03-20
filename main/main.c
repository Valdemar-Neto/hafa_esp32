#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "gpio_driver.h" // APENAS O DRIVER REAL
#include "blink.h"
#include "digital_io.h"

void app_main(void)
{
    printf("Iniciando Driver Real no GPIO 2...\n");
    DigitalIO* led = create_gpio_output(2); 

    if (led == NULL) {
        printf("Erro ao criar driver!\n");
        return;
    }

    while (1) {
        printf("LED ON\n");
        led_on(led);
        vTaskDelay(pdMS_TO_TICKS(500));

        printf("LED OFF\n");
        led_off(led);
        vTaskDelay(pdMS_TO_TICKS(500));
    }


    destroy_gpio(led);
}
#include "driver/gpio.h"
#include "digital_io.h"
#include <stdlib.h>
#include <stdbool.h>

// write
static void gpio_write_implementation(void* context, bool value){
    int pin = (int)(uintptr_t)context; 
    printf("Escrevendo no pino %d | Valor: %d\n", pin, value);
    gpio_set_level((gpio_num_t)pin, value ? 1 : 0);
}

// read
static bool gpio_read_implementation(const void* context) {
    int pin = (int)(uintptr_t)context;
    return gpio_get_level((gpio_num_t)pin);
}

// factory
DigitalIO* create_gpio_output(int pin){

    gpio_config_t io_config = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };


    gpio_config(&io_config);
    DigitalIO *io = malloc(sizeof(DigitalIO));
    if (!io) return NULL;

    io->ctx = (void*)(uintptr_t)pin; 
    io->write = gpio_write_implementation;
    io->read = NULL;

    return io;
}


DigitalIO* create_gpio_input(int pin, bool pull_up) {
    gpio_config_t io_config = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = pull_up ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .pull_down_en = pull_up ? GPIO_PULLDOWN_DISABLE : GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_config);
    DigitalIO *io = malloc(sizeof(DigitalIO));
    if (!io) return NULL;

    io->ctx = (void*)(uintptr_t)pin; 
    io->write = NULL; 
    io->read = gpio_read_implementation;

    return io;
}

// destroy
void destroy_gpio(DigitalIO* io) {
    if (io) free(io); 
}
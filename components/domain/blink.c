#include "blink.h"
#include "digital_io_utils.h"

void led_on(DigitalIO* led){
    gpio_write(led, true);
}

void led_off(DigitalIO* led){
    gpio_write(led, false);
}
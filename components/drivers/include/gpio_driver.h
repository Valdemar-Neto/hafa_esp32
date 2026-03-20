#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "digital_io.h"

DigitalIO* create_gpio_output(int pin);
DigitalIO* create_gpio_input(int pin, bool pull_up);
void destroy_gpio(DigitalIO* io);

#endif
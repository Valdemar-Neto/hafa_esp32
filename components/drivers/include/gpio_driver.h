#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "digital_io.h"

DigitalIO* create_gpio_output(int pin);
void destroy_gpio(DigitalIO* io);

#endif
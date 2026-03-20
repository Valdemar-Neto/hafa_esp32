#ifndef DIGITAL_IO_UTILS_H
#define DIGITAL_IO_UTILS_H

#include "digital_io.h"

void gpio_write(DigitalIO *io, bool value);
bool gpio_read(DigitalIO *io);

#endif /* DIGITAL_IO_UTILS_H */
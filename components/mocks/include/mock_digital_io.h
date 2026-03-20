#ifndef MOCK_DIGITAL_IO_H
#define MOCK_DIGITAL_IO_H

#include "digital_io.h"

DigitalIO* create_mock_digital_io();
void destroy_mock_digital_io(DigitalIO *io);

#endif
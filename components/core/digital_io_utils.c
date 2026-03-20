#include "digital_io_utils.h"

void gpio_write(DigitalIO* io, bool value){
    if(io && io->write) {
        io->write(io->ctx, value);
    }
}

bool gpio_read(DigitalIO* io){
    if(io && io->read) {
        return io->read(io->ctx);
    }

    return false;
}


#ifndef DIGITAL_IO_H
#define DIGITAL_IO_H

#include <stdbool.h>

typedef struct {
    void *ctx;
    void (*write)(void *ctx, bool value);
    bool (*read)(const void *ctx);
} __attribute__((packed)) DigitalIO; // Garante que a struct seja lida igual em todo lugar

#endif
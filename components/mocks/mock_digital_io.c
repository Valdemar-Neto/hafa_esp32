#include <stdio.h>
#include <stdlib.h>
#include "digital_io.h"


typedef struct {
    int pin;
    int state;
} MockContext;

// write fake
void mock_write(void *ctx, bool value) {
    MockContext *mock = (MockContext*) ctx;
    mock->state = value;
    printf("MOCK WRITE: %d\n", value);
}

// read fake
bool mock_read(const void *ctx) {
    const MockContext *mock = (const MockContext*) ctx;
    printf("MOCK READ: %d\n", mock->state);
    return mock->state;
}

void destroy_mock_digital_io(DigitalIO *io) {
    if (io == NULL) return;

    if (io->ctx != NULL) {
        free(io->ctx);
    }

    free(io);
    
    printf("MOCK DESTROYED: Memória liberada com sucesso.\n");
}

// factory
DigitalIO* create_mock_digital_io(int pin_number) {
    DigitalIO *io = malloc(sizeof(DigitalIO));
    MockContext *ctx = malloc(sizeof(MockContext));

    ctx->pin = pin_number;
    ctx->state = 0;

    io->write = mock_write;
    io->read = mock_read;
    io->ctx = ctx;

    return io;
}
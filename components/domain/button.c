#include "button.h"

void button_init(Button *btn, DigitalIO *io, uint32_t debounce_ms, bool active_low) {
    btn->io = io;
    btn->debounce_ms = debounce_ms;
    btn->active_low = active_low;
    btn->last_stable_state = false;
    btn->last_raw_state = false;
    btn->last_time = 0;
}

bool button_is_pressed(Button *btn, uint32_t current_time_ms) {
    // Leitura agnóstica (pode ser GPIO real ou Mock)
    bool raw_reading = btn->io->read(btn->io->ctx);
    
    // Converte lógica (Active Low vs Active High)
    if (btn->active_low) raw_reading = !raw_reading;

    // Se o sinal mudou (ruído ou aperto real)
    if (raw_reading != btn->last_raw_state) {
        btn->last_time = current_time_ms;
    }

    // Se o sinal estabilizou por tempo suficiente
    if ((current_time_ms - btn->last_time) > btn->debounce_ms) {
        btn->last_stable_state = raw_reading;
    }

    btn->last_raw_state = raw_reading;
    return btn->last_stable_state;
}
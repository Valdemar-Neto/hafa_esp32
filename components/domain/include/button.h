#ifndef BUTTON_H
#define BUTTON_H
#include "digital_io.h"
#include <stdint.h>
typedef struct {
    DigitalIO *io;  //interface digital io
    bool last_stable_state; // estado após debounce
    bool last_raw_state; // estado atual 
    uint32_t last_time; // timestamp da ultima mudanca
    uint32_t debounce_ms; //tempo de debounce
    bool active_low; // true se o botão for ativo baixo, false se for ativo alto
} Button;

void button_init(Button *button, DigitalIO *io, uint32_t debounce_ms, bool active_low);
bool button_is_pressed(Button *btn, uint32_t current_time_ms);


#endif
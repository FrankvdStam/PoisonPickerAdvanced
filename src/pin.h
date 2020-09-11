//
// Created by Frank on 10/09/2020.
//

#ifndef CLIONAVRGCC_PIN_H
#define CLIONAVRGCC_PIN_H

#include <avr/io.h>

//DDXN
//logic 1 is output

typedef enum
{
    pinmode_input,
    pinmode_input_pullup,
    pinmode_output,
} pinmode_t;

#define HIGH 1
#define LOW 0

void pin_mode(uint8_t pin, pinmode_t pinmode);
void pin_write(uint8_t pin, uint8_t output);
uint8_t pin_read(uint8_t pin);

#endif //CLIONAVRGCC_PIN_H

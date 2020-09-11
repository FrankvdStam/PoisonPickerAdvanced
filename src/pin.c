//
// Created by Frank on 10/09/2020.
//

#include "pin.h"

#include "atmega328p.h"
#include "usart.h"

//======================================================================================================================
//Private helpers

#define MEMORY_MAPPED_REGISTER volatile uint8_t*

MEMORY_MAPPED_REGISTER pin_to_data_direction_register(uint8_t pin)
{
    if (pin < 8u)
    {
        return &DDRD;
    }
    else
    {
        return &DDRB;
    }
}

MEMORY_MAPPED_REGISTER pin_to_port(uint8_t pin)
{
    if (pin < 8u)
    {
        return &PORTD;
    }
    else
    {
        return &PORTB;
    }
}

MEMORY_MAPPED_REGISTER pin_to_pin_register(uint8_t pin)
{
    if (pin < 8u)
    {
        return &PIND;
    }
    else
    {
        return &PINB;
    }
}

uint8_t pin_to_register_bit(uint8_t pin)
{
    return pin > 8 ? pin - 8 : pin;
}



//======================================================================================================================
//pin interface

void pin_mode(uint8_t pin, pinmode_t pinmode)
{
    if(pin > 13u)
    {
        //error
        return;
    }

    //Figure out the ports
    MEMORY_MAPPED_REGISTER data_direction = pin_to_data_direction_register(pin);
    MEMORY_MAPPED_REGISTER port = pin_to_port(pin);

    //Figure out what bit in the register must be toggled
    uint8_t port_bit = pin_to_register_bit(pin);



    //Set the port according to the pinmode
    switch (pinmode)
    {
        case pinmode_input:
            *data_direction &= ~(1u << port_bit);
            *port &= ~(1u << port_bit);
            break;

        case pinmode_input_pullup:
            *data_direction &= ~(1u << port_bit);
            *port |= (1u << port_bit);
            break;

        case pinmode_output:
            *data_direction |= (1u << port_bit);
            *port &= ~(1u << port_bit);
            break;
    }
}

void pin_write(uint8_t pin, uint8_t output)
{
    if(pin > 13u)
    {
        //error
        return;
    }

    //Fetch the port for this pin
    MEMORY_MAPPED_REGISTER port = pin_to_port(pin);
    uint8_t port_bit = pin_to_register_bit(pin);

    switch(output)
    {
        default:
        case LOW:
            *port &= ~(1u << port_bit);
            break;
        case HIGH:
            *port |= (1u << port_bit);
            break;
    }
}

uint8_t pin_read(uint8_t pin)
{
    if(pin > 13)
    {
        //error
        return LOW;
    }

    MEMORY_MAPPED_REGISTER pin_register = pin_to_pin_register(pin);
    uint8_t port_bit = pin_to_register_bit(pin);

    if(*pin_register & (1u << port_bit))
    {
        return HIGH;
    }
    return LOW;
}



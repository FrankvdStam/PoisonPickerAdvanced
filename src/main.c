//
// Created by Frank on 10/09/2020.
//

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB = 32;

    while(1)
    {
       PORTB = 32;
        //PORTB = 32;
        _delay_ms(500);
        PORTB = 0;
        //PORTB = 0;
        _delay_ms(500);
    }
}
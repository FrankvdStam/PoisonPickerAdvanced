//
// Created by Frank on 10/09/2020.
//


#include "atmega328p.h"
#include <util/delay.h>
#include <stdbool.h>
#include "usart.h"
#include "pin.h"
#include "millis.h"
#include "random.h"


#define LED_PIN 13
#define BUTTON_PIN 12

bool led_state = false;

void toggle_led()
{
    led_state = !led_state;
    pin_write(LED_PIN, led_state);
}


void loop()
{
    //while(pin_read(BUTTON_PIN) == HIGH)
    //{
    //    pin_write(LED_PIN, HIGH);
    //}

    double delay_ms = 500;

    toggle_led();
    _delay_ms(delay_ms);
    toggle_led();
    _delay_ms(delay_ms);
}

int main()
{

    uart_init(BAUD_CALC(115200));
    uart_puts("Init.\n");

    millis_init();

    pin_mode(LED_PIN, pinmode_output);
    pin_mode(BUTTON_PIN, pinmode_input_pullup);

    while(1)
    {
        //uart_putlong(millis());
        //uart_puts("\n");

        int rand = random_min_max(44,5298);
        uart_putint(rand);
        uart_puts("\n");

        loop();
    }
}

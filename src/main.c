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
#include "ws2812.h"


#define LED_PIN 13
#define BUTTON_PIN 12

bool led_state = false;

void toggle_led()
{
    led_state = !led_state;
    pin_write(LED_PIN, led_state);
}



wserr_t init_led(__inout wscol_t *element, __in uint16_t ele_idx)
{

    if(!element || (ele_idx >= WS_ELE_MAX_COUNT)) {
        return WS_ERR_INV_ARG;
    }

    // initialize blue
    element->red = 0;
    element->green = 0;
    element->blue = UINT8_MAX;

    return WS_ERR_NONE;
}

wserr_t update_led(__inout wscol_t *ele, __in uint16_t ele_idx, __in uint16_t iter)
{

    if(!ele || (ele_idx >= WS_ELE_MAX_COUNT)) {
        return WS_ERR_INV_ARG;
    }

    if(ele->blue == UINT8_MAX) { // red
        ele->blue = 0;
        ele->red = UINT8_MAX;
    } else if(ele->red == UINT8_MAX) { // green
        ele->red = 0;
        ele->green = UINT8_MAX;
    } else { // blue
        ele->green = 0;
        ele->blue = UINT8_MAX;
    }
    return WS_ERR_NONE;
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

//pin 10
#define PIN_DATA 2 // PB1
#define PIN_POWER 0 // PB0
#define PORT_BANK B // PORTD

int main()
{
    uart_init(BAUD_CALC(115200));
    uart_puts("Init.\n");

    millis_init();

    ws2812 ws28121_controller;
    wserr_t result = ws2812_init(&ws28121_controller, PORT_BANK, PIN_POWER, PIN_DATA, 4*9, init_led, true, update_led);
    if(result != WS_ERR_NONE)
    {
        uart_puts("ws2812 initialisation failed!");
        return 1;
    }


    while(1)
    {
        _delay_ms(200);

        // update LED color
        result = ws2812_update(&ws28121_controller, update_led);
        if(!WS_ERR_SUCCESS(result))
        {
            uart_puts("ws2812 update failed!");
        }
    }
}

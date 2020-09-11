//
// Created by Frank on 11/09/2020.
//

#include <stdlib.h>
#include <stdint.h>
#include "random.h"
#include "usart.h"

int private_random(int min, int max)
{
    return rand() % (max - min) + min;


    //unsigned int ran = rand();
//
    //uart_puts("rand raw: ");
    //uart_putuint(ran);
//
//
    //int slope = (max - min) / (RAND_MAX - 0);
//
    //uart_puts(" slope: ");
    //uart_putint(slope);
//
    //return min + slope * (ran - 0);
}

//Used to seed to random functions, if unused, the default seed is 1
void init_random(unsigned int seed)
{
    srand(seed);
}

//Returns a random number between 0 to max
unsigned int random_max(int max)
{
    return private_random(0, max);
}

//Returns a random number between 0 to max
unsigned int random_min_max(int min, int max)
{
    return private_random(min, max);
}




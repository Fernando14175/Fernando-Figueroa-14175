/*
 * File:   main.c
 * Author: Fernando Figueroa
 *
 * Created on January 22, 2021, 8:51 AM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "PIC16F887.h"
#define _XTAL_FREQ 48000000

void main(void) {
    TRISA = 0b11111111;
}
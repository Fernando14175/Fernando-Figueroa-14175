/*
 * File:   newmain.c
 * Author: Fernando Figueroa
 *
 * Created on January 23, 2021, 12:38 PM
 */

//configuracion del programa 
// CONFIG1
#pragma config FOSC =HS// Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "PIC16F887.h"
#include <stdint.h>
#define _XTAL_FREQ  4000000

int estado = 0;
int estado2 =0;
int cont = 0;
void config (void){
    ANSEL = 0b00000000;
    ANSELH = 0b00000000;
    
    TRISB = 0b00000011;
    TRISC = 0b00000000;
    
    PORTB = 0b00000000;
    PORTD = 0b00000000;
    
}


void main(void) {
    config();
    while(1){  
 
    if (PORTBbits.RB0 == 0){
    estado = 1;
    }
    
    if (PORTBbits.RB0 == 1 && estado == 1){ 
         PORTC++;
         estado = 0;
        }
    
    if (PORTBbits.RB1 == 0){
    estado2 = 1;
    }
    
    if (PORTBbits.RB1 == 1 && estado2 == 1){ 
         PORTC--;
         estado2 = 0;
        }
        
     }
      return; 
         
   }


 
 
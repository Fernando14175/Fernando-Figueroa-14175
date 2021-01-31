/*
 * File:   newmain.c
 * Author: Fernando Figueroa
 *
 * Created on January 23, 2021, 12:38 PM
 */

//configuracion del programa 
// CONFIG1
#pragma config FOSC = XT// Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
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
#define _XTAL_FREQ 8000000

int cont = 0;

void config (void);
void contled(void);
void contador(void);
    
    


void main(void) {
    
    config();
    
    while(cont < 5){
     __delay_ms(30);
     if (PORTBbits.RB0 == 1){ //revisamos que el boton del jugador1 este presionado
         cont = cont+1; //aumentamos el contador del jugador 1 
                            }
     if (PORTBbits.RB0 == 1){ //revisamos que el boton del jugador1 este presionado
         cont = cont-1; //aumentamos el contador del jugador 1 
                            }
     contled();
                //f (PORTBbits.RB1 == 1){ //revisamos que el boton del jugador1 este presionado
                    //cont = cont-1; //aumentamos el contador del jugador 2
                 //}
    }
    
    
   
    
    return;  
}

void config (void){
    ANSEL = 0b00000000;
    ANSELH = 0b00000000;

    TRISB = 0b00000011;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    
    PORTC = 0b00000000;
    PORTD = 0b00000000;
}


 void contled (void){  //cremos la funcion jugador 1
        
            if (cont == 0){ //revisamos el valor del contador 
                PORTDbits.RD0 = 1; //encendemos el primer led si el contador es 1 
                PORTDbits.RD1 = 0;
                PORTDbits.RD2 = 0;
                PORTDbits.RD3 = 0;
                PORTDbits.RD4 = 0;
            }
            if (cont == 1){  //revisamos el valor del contador 
                PORTDbits.RD0 = 0; //encendemos el primer led si el contador es 1 
                PORTDbits.RD1 = 1;
                PORTDbits.RD2 = 0;
                PORTDbits.RD3 = 0;
                PORTDbits.RD4 = 0; 
            }
           if (cont == 2){ //revisamos el valor del contador 
                PORTDbits.RD0 = 0; //encendemos el primer led si el contador es 1 
                PORTDbits.RD1 = 0;
                PORTDbits.RD2 = 1;
                PORTDbits.RD3 = 0;
                PORTDbits.RD4 = 0;         
            }
           if (cont == 3){ //revisamos el valor del contador 
                PORTDbits.RD0 = 0; //encendemos el primer led si el contador es 1 
                PORTDbits.RD1 = 0;
                PORTDbits.RD2 = 0;
                PORTDbits.RD3 = 1;
                PORTDbits.RD4 = 0;        
            }
           if (cont == 4){ //revisamos el valor del contador             
                PORTDbits.RD0 = 0; //encendemos el primer led si el contador es 1 
                PORTDbits.RD1 = 0;
                PORTDbits.RD2 = 0;
                PORTDbits.RD3 = 0;
                PORTDbits.RD4 = 1;         
            }
            if(cont > 4){
                cont = 0;
            }
    }
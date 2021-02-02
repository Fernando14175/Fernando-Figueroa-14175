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

    
 void __interrupt() ISR(void) {
        if(INTCONbits.INTF == 1) {
        //Clear the interrupt
        INTCONbits.INTF = 0;
        while(cont < 21){
        __delay_ms(30);
        if (PORTAbits.RA0 == 1){ 
        cont = cont+1;
        }
        if (PORTAbits.RA1 == 1){ 
         cont = cont-1; 
        }
       }
    }  
}   


void main(void) {
    
                
}
 

void config (void){
    ANSEL = 0b00000000;
    ANSELH = 0b00000000;

    TRISA = 0b00000011;
    TRISB = 0b00000000;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0b000;
    
    PORTD = 0b00000000;
    PORTC = 0b00000000;
    PORTE = 0b011;
}


 void contled (void){  //cremos la funcion jugador 1
        
            if (cont == 0){ //revisamos el valor del contador 
                PORTDbits.RD0 = 1; //encendemos el primer led si el contador es 1 
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b0111111;
                
            }
            if (cont == 1){  //revisamos el valor del contador 
                PORTDbits.RD1 = 1; //encendemos el primer led si el contador es 1 
                PORTDbits.RD0 = 0;
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b0000110;
               
            }
           if (cont == 2){ //revisamos el valor del contador 
                PORTDbits.RD1 = 0; //encendemos el primer led si el contador es 1 
                PORTDbits.RD2 = 1;
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b1011011;
                
                
            }
           if (cont == 3){ //revisamos el valor del contador
                PORTDbits.RD2 = 0;
                PORTDbits.RD3 = 1;
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b1001111;
                
            }
           if (cont == 4){ //revisamos el valor del contador             
                PORTDbits.RD3 = 0;
                PORTDbits.RD4 = 1; 
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b1100110;
            }
            
            if (cont == 5){ //revisamos el valor del contador             
                PORTDbits.RD4 = 0;  
                PORTDbits.RD5 = 1;  
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b1101101;
                }
            
            if (cont == 6){ //revisamos el valor del contador             
                PORTDbits.RD5 = 0; 
                PORTDbits.RD6 = 1; 
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b1111101;
                }               
                                
            if (cont == 7){ //revisamos el valor del contador             
                 PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b0000111;
                }
            
            if (cont == 8){ //revisamos el valor del contador             
                 PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b1111111;
                }
            
            if (cont == 9){ //revisamos el valor del contador             
                 PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTC = 0b1101111;
                }
            
            if (cont == 10){ //revisamos el valor del contador             
                PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 1;
                PORTC = 0b1110111;
                }
            
            if (cont == 11){ //revisamos el valor del contador             
                PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 1;
                PORTC = 0b1111100;
                }
            
            if (cont == 12){ //revisamos el valor del contador             
                PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 1;
                PORTC = 0b0111001;
                }
            
             if (cont == 13){ //revisamos el valor del contador             
                PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 1;
                PORTC = 0b1011110;
                }
            
             if (cont == 14){ //revisamos el valor del contador             
                PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 1;
                PORTC = 0b1111001;
                }
            
             if (cont == 15){ //revisamos el valor del contador             
                PORTDbits.RD6 = 0; 
                PORTDbits.RD7 = 1; 
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 1;
                PORTC = 0b1110001;
                }
            
            
            
            
            
            if(cont < 0){
                cont = 20;
            }
             if(cont > 20 ){
                cont = 0;
            }
    }
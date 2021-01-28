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
#include <string.h>
#define _XTAL_FREQ 8000000

//definimos las variables y les damos un valor inicial
int cont  = 0;
int cont2 = 0;


//declaramos todas las funciones del programa 
void semaforo (void);
void config (void);
void jugador1 (void);
void jugador2 (void);


void main(void) {
    
    config();//llamamos a la funcion config 
    
    
    if (PORTEbits.RE0 == 1){ //revisamos si el boton del semaforo esta presionado
        semaforo();//llamamos a nuestra funcion semaforo
        if(PORTDbits.RD2 == 1){ //revisamos si el semaforo ya se enucentra con el led verde encendido
            while (cont < 8 && cont2 < 8) {    //revisamos que los contadores no hayan llegado al final
                __delay_ms(50);
                if (PORTBbits.RB0 == 1){ //revisamos que el boton del jugador1 este presionado
                    cont = cont+1; //aumentamos el contador del jugador 1 
                 }
                if (PORTCbits.RC0 == 1){ //revisamos que el boton del jugador1 este presionado
                    cont2 = cont2+1; //aumentamos el contador del jugador 2
                 }
            jugador2();//llamamos a la funcion jugador2
            jugador1();//llamamos a la funcion jugador1
             }   
        }
    
    }       
    
}
    
    
    void config (void) {

        ANSELH = 0b0000000; //ponemos los puertos como digitales
        ANSEL =  0b0000000; //ponemos los puertos como digitales
        
        TRISD = 0b00000000; //ponemos los puertos como salidas 
        TRISB = 0b00000001; //ponemos todos los puertos como salidas y el primero como una entrada
        TRISC = 0b00000001; //ponemos todos los puertos como salidas y el primero como entrada 
        TRISE = 0b001; //ponemos todos los puertos como salidas y el primero como entrada 
        
        PORTB = 0b00000000; //ponemos los puertos en 0 
        PORTC = 0b00000000; //ponemos los puertos en 0 
        PORTD = 0b00000000; //ponemos los puertos en 0 
   
        
    
    }
 
    
    void jugador1 (void){  //cremos la funcion jugador 1
        
            if (cont2 == 1){ //revisamos el valor del contador 
                PORTCbits.RC1 = 1; //encendemos el primer led si el contador es 1 
            }
            if (cont2 == 2){  //revisamos el valor del contador 
                PORTCbits.RC2 = 1; //encendemos el primer led si el contador es 2   
            }
           if (cont2 == 3){ //revisamos el valor del contador 
                PORTCbits.RC3 = 1; //encendemos el primer led si el contador es 3          
           }
           if (cont2 == 4){ //revisamos el valor del contador 
                PORTCbits.RC4 = 1; //encendemos el primer led si el contador es 4          
            }
           if (cont2 == 5){ //revisamos el valor del contador             
                PORTCbits.RC5 = 1; //encendemos el primer led si el contador es 5            
            }
            
            if (cont2 == 6){ //revisamos el valor del contador               
                PORTCbits.RC6 = 1; //encendemos el primer led si el contador es 6           
            }
            if (cont2 == 7){ //revisamos el valor del contador              
                PORTCbits.RC7 = 1; //encendemos el primer led si el contador es 7              
            }
            
        }
    
    
    void jugador2 (void){ //creamos la funcion jugador 2 
            if (cont == 1){ //revisamos el valor del contador 
                PORTBbits.RB1 = 1; //encendemos el primer led si el contador es 1  
            }
            if (cont == 2){ //revisamos el valor del contador 
                PORTBbits.RB2 = 1; //encendemos el primer led si el contador es 2       
            }
           if (cont == 3){ //revisamos el valor del contador 
                PORTBbits.RB3 = 1; //encendemos el primer led si el contador es 3      
            }
           if (cont == 4){ //revisamos el valor del contador 
                PORTBbits.RB4 = 1; //encendemos el primer led si el contador es 4            
            }
           if (cont == 5){ //revisamos el valor del contador                
                PORTBbits.RB5 = 1; //encendemos el primer led si el contador es 5            
            }
            if (cont == 6){ //revisamos el valor del contador               
                PORTBbits.RB6 = 1; //encendemos el primer led si el contador es 6           
            }
            if (cont == 7){ //revisamos el valor del contador              
                PORTBbits.RB7 = 1; //encendemos el primer led si el contador es 7            
            }
            
        }
    
    
    
   
 void semaforo (void){ //declaramos la funcion semaforo 
    
        PORTDbits.RD0 = 1; //ponemos el puerto en 1  
        __delay_ms(50);
        PORTDbits.RD0 = 0; //ponemos el puerto en 0
        PORTDbits.RD1 = 1; //ponemos el siguiente puerto en 1 
         __delay_ms(40);
        PORTDbits.RD1 = 0;//ponemos el puerto en 0
        PORTDbits.RD2 = 1;//ponemos el siguiente puerto en 0
         
        
    
 }  



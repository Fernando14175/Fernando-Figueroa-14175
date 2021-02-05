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
#define _XTAL_FREQ  4000000
//#define _XTAL_FREQ 20000000

unsigned char Display[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};


int cont = 0;
int estado = 0;
unsigned int a = 0;
unsigned int b = 0;

void config (void);
void contled(void);
void contador(void);


void config (void){
    ANSEL = 0b00000000;
    ANSELH = 0b00000000;

    TRISA = 0b00000000;
    TRISB = 0b00100011;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0b000;
    
    
    PORTA = 0b00000000;
    PORTD = 0b00000000;
    PORTC = 0b00000000;
    PORTE = 0b011;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.INTE = 1;
    
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.CHS0 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS3 = 1;
    ADCON0bits.ADON = 1;   // adc on
    ADCON1bits.ADFM = 0;
    
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
    
}

    
 void __interrupt() ISR(void) {
     
     if(INTCONbits.INTF == 1) {
        INTCONbits.INTF = 0;
        cont = cont+1;
    }
     if (PIR1bits.ADIF ==1){ 
        PIR1bits.ADIF = 0;              // interrupcion del ADC que guarda en un registro el valor de la conversion analogica a digital.
        
        a = ADRESH;
        b = ADRESH;
        
        return;
    }
        
}

 

void main(void) {
  
    config();

    while(cont < 99){
        if(ADCON0bits.GO_DONE == 0){
        a = ((a/16)%16);  // holds 10th digit a = 2  
        b = (b%16); //b = 12 
         // holds unit digit value
         PORTC = Display[a]; //
         PORTEbits.RE0 = 1;   //  turn on forth display unit
         
         PORTEbits.RE0 = 0;   //  turn off forth display unit
         PORTC=Display[b];  // send 100's place data to 3rd digit
         PORTEbits.RE1 = 1;  //  turn on 3rd display unit
         
         PORTEbits.RE1 = 0; //  turn off 3rd display unit
         ADCON0bits.GO_DONE = 1;
        }
     contled();
    
     if (PORTBbits.RB1 == 0){
         estado = 1;
     }
     if (PORTBbits.RB1 == 1 && estado == 1){ 
         cont = cont-1; 
         estado = 0;
        }

     if (a > cont){
         PORTEbits.RE2 = 1;
        }
     else {
         PORTEbits.RE2 = 0;
     }
     
     }
     return;  

}




 void contled (void){  //cremos la funcion jugador 1

     if(cont > 99 ){
         cont = 0;
         
     } 
     
     switch(cont){
         
         case 0: 
             PORTDbits.RD0 = 0;
             PORTDbits.RD1 = 0;
             PORTDbits.RD2 = 0;
             PORTDbits.RD3 = 0;
             PORTDbits.RD4 = 0;
             PORTDbits.RD5 = 0;
             PORTDbits.RD6 = 0;
             PORTDbits.RD7 = 0;
             break;
         
         case 1: 
             PORTDbits.RD0 = 1;
             PORTDbits.RD1 = 0;
             PORTDbits.RD2 = 0;
             PORTDbits.RD3 = 0;
             PORTDbits.RD4 = 0;
             PORTDbits.RD5 = 0;
             PORTDbits.RD6 = 0;
             PORTDbits.RD7 = 0;
             break;
             
         case 2: 
             PORTDbits.RD0 = 1;
             PORTDbits.RD1 = 1;
             PORTDbits.RD2 = 0;
             PORTDbits.RD3 = 0;
             PORTDbits.RD4 = 0;
             PORTDbits.RD5 = 0;
             PORTDbits.RD6 = 0;
             PORTDbits.RD7 = 0; 
             break;
             
         case 3: 
             PORTDbits.RD2 = 1;
             PORTDbits.RD0 = 1;
             PORTDbits.RD1 = 1;
             PORTDbits.RD2 = 1;
             PORTDbits.RD3 = 0;
             PORTDbits.RD4 = 0;
             PORTDbits.RD5 = 0;
             PORTDbits.RD6 = 0;
             PORTDbits.RD7 = 0;
             break;
         
         case 4: 
             PORTDbits.RD0 = 1;
             PORTDbits.RD1 = 1;
             PORTDbits.RD2 = 1;
             PORTDbits.RD3 = 1;
             PORTDbits.RD4 = 0;
             PORTDbits.RD5 = 0;
             PORTDbits.RD6 = 0;
             PORTDbits.RD7 = 0;
             break;
         
         case 5: 
             PORTDbits.RD0 = 1;
             PORTDbits.RD1 = 1;
             PORTDbits.RD2 = 1;
             PORTDbits.RD3 = 1;
             PORTDbits.RD4 = 1;
             PORTDbits.RD5 = 0;
             PORTDbits.RD6 = 0;
             PORTDbits.RD7 = 0;
             break;
         
         case 6: 
             PORTDbits.RD0 = 1;
             PORTDbits.RD1 = 1;
             PORTDbits.RD2 = 1;
             PORTDbits.RD3 = 1;
             PORTDbits.RD4 = 1;
             PORTDbits.RD5 = 1;
             PORTDbits.RD6 = 0;
             PORTDbits.RD7 = 0;
             break;
             
         
         case 7: 
             PORTDbits.RD0 = 1;
             PORTDbits.RD1 = 1;
             PORTDbits.RD2 = 1;
             PORTDbits.RD3 = 1;
             PORTDbits.RD4 = 1;
             PORTDbits.RD5 = 1;
             PORTDbits.RD6 = 1;
             PORTDbits.RD7 = 0;
             break;
         
         case 8: 
             PORTDbits.RD0 = 1;
             PORTDbits.RD1 = 1;
             PORTDbits.RD2 = 1;
             PORTDbits.RD3 = 1;
             PORTDbits.RD4 = 1;
             PORTDbits.RD5 = 1;
             PORTDbits.RD6 = 1;
             PORTDbits.RD7 = 1;
             break;
        
     }
    
 }
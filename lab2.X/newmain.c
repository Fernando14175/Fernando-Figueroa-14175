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
#include "Libreria.h"
#define _XTAL_FREQ  4000000
//#define _XTAL_FREQ 20000000

    
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




 
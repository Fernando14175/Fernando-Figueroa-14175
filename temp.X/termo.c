/*
 * File:   newmain.c
 * Author: Fernando Figueroa
 *
 * Created on January 23, 2021, 12:38 PM
 */

//configuracion del programa 
// CONFIG1
#pragma config FOSC =INTRC_NOCLKOUT// Oscillator Selection bits (EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)



#define _XTAL_FREQ  9000000 //frecuencia
#include <xc.h>
#include "PIC16F887.h" //libreria del pic 
#include "temperatura.h"//libreria qcreada 
#include <string.h>            
#include <stdio.h> 
#include <stdint.h>

void config (void);
   
void main(void) {
    config(); //configuracion de los puertos 
   
    while(1){
                     
       PORTEbits.RE0=1;
       PORTEbits.RE1=1;
       PORTEbits.RE2=1;//se manda a llamar la funcion conversion con 0 como valor para indentificar que puerto analogico esta trabajndp       
        
    }
}
    

void config(void){
    ANSEL =  0b0000000;   //puerto a digital               
    ANSELH = 0b0000000;  //pueto a digital 
     
     
    TRISE = 0b000;
    
    PORTE = 0;
   
  

}




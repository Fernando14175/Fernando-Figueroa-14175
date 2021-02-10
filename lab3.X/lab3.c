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

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ  9000000
#include <xc.h>
#include "PIC16F887.h"
#include "Libreria2.h"
#include <string.h>            
#include <stdio.h> 
#include <stdint.h>


void conversion (char puertoANL);

 void __interrupt() ISR(void) {
    
     if (PIR1bits.ADIF ==1){
        PIR1bits.ADIF = 0;   
        c = ADRESH;
        b = ADRESH;
    }
 }
   
void main(void) {
    config();
    Lcd_Init(); 
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("DIGITAL 2");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("FernandoFigueroa");
    __delay_ms(100);
    Lcd_Clear();
    
     Lcd_Set_Cursor(1,1);        
     Lcd_Write_String("Volt1"); 
     Lcd_Set_Cursor(1,7);        
     Lcd_Write_String("Volt2");
     
     Lcd_Set_Cursor(1,13);        
     Lcd_Write_String("CONT");     
     Lcd_Set_Cursor(2,11);        
        
    
    while(1){
              
        conversion(1);          
        conversion(0);           
        
    }
}


void conversion(char puertoANL){       
    
    ADCON0bits.CHS = puertoANL;   
    if (ADCON0bits.GO_DONE==0 && puertoANL ==0){
        
        vpot1 = (5*c)/255;
        sprintf(buffer, "%.3f", vpot1);  
        Lcd_Set_Cursor(2,1);        
        Lcd_Write_String(buffer);  
        ADCON0bits.GO_DONE=1;
    }
    else{
        vpot2 = (5*b)/255;        
        sprintf(buffer, "%.3f", vpot2);  
        Lcd_Set_Cursor(2,7); 
        Lcd_Write_String(buffer); 
        ADCON0bits.GO_DONE=1;
    }
}    


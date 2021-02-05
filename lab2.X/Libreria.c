#include "Libreria.h"


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

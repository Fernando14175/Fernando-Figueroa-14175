/*
 * File:   newmain.c
 * Author: Fernando Figueroa
 *
 * Created on January 23, 2021, 12:38 PM
 */

// CONFIG1
#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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


#define _XTAL_FREQ  9000000 //frecuencia
#include <xc.h>
#include "PIC16F887.h" //libreria del pic 
#include "ContadorSPI.h"//libreria qcreada 
#include <string.h>            
#include <stdio.h> 
#include <stdint.h>

void setup(void);

void __interrupt() isr(void){
   if(SSPIF == 1){           //bandera que nos indica cuando el valor ya fue mandado y esta esperando para quelo lea el maestro
        //PORTD = spiRead(); // le escribe al puerto del esclavo
        spiWrite(cont);      //mandamos la variable para que sea leida por el maestro
        SSPIF = 0;           //limpiamos la bandera 
    }
}

void main(void) {
    setup();                                    //llamamos la funcion setup
    
    while(1){
        if (PORTBbits.RB0 == 0){                //revisamos el boton para el antirebote 
         estado = 1;
        }
        if (PORTBbits.RB0 == 1 && estado == 1){ //revisamos el boton para aumentar el contador 
         PORTD++;
         cont = cont+1;
         estado = 0;
        }
         if (PORTBbits.RB1 == 0){               //revisamos el boton para el antirebote 
         estado2 = 1;
        }
        if (PORTBbits.RB1 == 1 && estado2 == 1){//revisamos el boton para disminuir el contador 
         PORTD--;
         cont = cont-1;        ;
         estado2 = 0;
        }
    }
    
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){               //funcion setup para los pines 
    
    ANSEL = 0;                  //puertos digitales 
    ANSELH = 0;
     
    TRISB = 0b00000011;         //entradas
    
    TRISB = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    PORTE = 0;
    
    
    INTCONbits.GIE = 1;         //  interrupciones globales
    INTCONbits.PEIE = 1;        // interrupciones adc
    PIR1bits.SSPIF = 0;         // limpiamos la bandera
    PIE1bits.SSPIE = 1;         // habilitamos la interrupcion para leer los datos que se mandan
    TRISAbits.TRISA5 = 1;       // escogemos el esclavo
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    //inicializamos la conexion spi
}

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge) //funcion spi
{
    TRISC5 = 0;
    if(sType & 0b00000100) 
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    }
    else              
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    
    SSPCON = sType | sClockIdle;
}

static void spiReceiveWait()  //funcion para esperar cuando se reciben datos
{
    while ( !SSPSTATbits.BF ); 
}

void spiWrite(char dat)  //funcion pra escribir los datos a mndar
{
    SSPBUF = dat;
}

unsigned spiDataReady() //revisar que los datos ya esten cargados
{
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

char spiRead() //leemos los datos que cargamos
{
    spiReceiveWait();        
    return(SSPBUF);
}


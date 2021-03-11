
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE =  ON    
#pragma config CP = OFF         
#pragma config CPD = OFF        
#pragma config BOREN = OFF      
#pragma config IESO = OFF       
#pragma config FCMEN = OFF      
#pragma config LVP = OFF        

// CONFIG2
#pragma config BOR4V = BOR40V   
#pragma config WRT = OFF        

#define _XTAL_FREQ  9000000 //frecuencia
#include <xc.h>             // librerias 
#include <stdio.h>   
#include <stdint.h>
#include <stdbool.h>
#include <pic16f887.h>
#include "I2C.h"
#include "LCD.h"
#include "LCD2.h"
#include "usart.h"

uint8_t r = 0;                   //declaramos las variables 
char* datos[];                   
uint8_t uart_data = 0;
uint8_t uart_cont = 0;
uint8_t str_pos   = 0;
bool    eusart_flag  = false;
void config (void);             //declaramos las funciones 
void conversion (void);         //declaramos funciones 

void config(void)
{
    ANSEL  = 0x03;
    ANSELH = 0x00;
   
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 1;
    TRISE = 0b000;
     
    PORTC = 0;
    PORTE = 0;
    OSCCON = 0b01100001;
   

    eusart_init_tx();          //incializamos la usart 
    eusart_enable_tx_isr();    //inicializamos las interrupciones para la usart

    eusart_init_rx();          //inicializamos la usart el otro puerto
    eusart_enable_rx_isr();    //interrupciones para el otro puerto 


    return;
}

void __interrupt() isr(void)              //interrupcion en la que le mandamos los datos del sensor hacia 
{

    if (PIE1bits.TXIE && PIR1bits.TXIF)  //revisamos labandera de la usart
    {
        if (eusart_flag)
        {
            TXREG = datos[str_pos];      //mandamos los datos al puerto 
        }
        str_pos++;
        if (str_pos == 5)
        {
            eusart_flag = !eusart_flag; //cambiamos la bandera para limpiar los datos 
            str_pos = 0;
        }
    }
    if (PIR1bits.RCIF)
    {
        uart_data = RCREG;
    }
}

void main()
{   
    
    config();
	LCD_init();	                     //inicializamos la lcd
    Lcd_Set_Cursor(1,1);             //cursor para escribir 
    Lcd_Write_String("Temperatura");
    Lcd_Set_Cursor(2,7);             //cursor para escribir 
    Lcd_Write_String("Grados");      //escribimos 
	delay(6500);                    
	i2c_init();                      //inicializamos la conexion i2c 
	delay(6500);
	while(1)
	{
        
		LCD_cmd(0x86);		//le cargamos los datos a la lcd 

		i2c_rep_start();	//empezamos la comunicacion i2c 
		delay(4);

		i2c_send(0x90);    //direccion del esclavo para escribir los datos
		//i2c_send(0x00);  

		i2c_rep_start();  //inicializamos la conexion con la direccion cargada 
		delay(4);

		SSPBUF = 0x91; //direccion del esclavo para leer los datos
		i2c_wait();
		delay(4);

		r = i2c_rx(); // le damos los datos de la conexion i2c al la variable r
		i2c_wait();

		i2c_NACK();  // mandamos un bit para saber que se mandaron los datos con exito 
		delay(4);

		i2c_stop(); // terminamos la comunicacion 
		delay(4);
              
        Lcd_Set_Cursor(2,4);  
		LCD_disp(r); // mandamos la variable al display
        conversion();
       
	}
}
////////////////////////////////////////////////////////////////////////////////
void conversion (void){
    sprintf(datos, " %2i ", r); // realizamos la conversion a sprintf para poder desplegar los datos
}
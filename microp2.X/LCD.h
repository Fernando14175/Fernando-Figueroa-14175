#ifndef __LCD_H
#define	__LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
void Lcd_Set_Cursor(char x, char y); //inicializamos funcion que setea el cursor del lcd 
void Lcd_Write_String(char *a);      //inicializamos funcion que escribe strings en la lcd 
void Lcd_Write_Char(char a);         // inicializamos funcion que escribe chars en la lcd 

int cc;                              //inicializamos variable c
float temp;                          //inicializamos la variable vpot1
char bufferr [];                     //inicializamos la variable buffer
char spiRead();


void Lcd_Cmd(char a){                //se cargan los comandos a la lcd para inicializacion asi como para limpiar la lcd 
	PORTDbits.RD2 =0;                //ponemos en 0 para poder escribir valores a la lcd 
	PORTB=a;                         // cargamos lo que se desea escribir a la lcd 
    PORTDbits.RD3=1;                 //seteamos en uno la lcd para que lea los valores cargados              
    __delay_ms(4);      
    PORTDbits.RD3=0;                 //regresamos a 0 esperando leer algo mas               
}


Lcd_Clear(){                         //se limpia la lcd utilizando los comandos de la misma 
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)  //funcion para setear el cursor de la lcd 
{
	char temp,z,y; //variables char 
	if(a == 1)
	{
	  temp = 0x80 + b - 1;          //calculo de la posicion del cursor 
		//z = temp>>8;
		//y = temp & 0x0F;
		Lcd_Cmd(temp);              //mandamos los valores al lcd para leer la posicion del cursor 
		
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;        //calculo de la posicion del cursor 
		//z = temp>>8;
		//y = temp & 0x0F;
		Lcd_Cmd(temp);              //mandamos los valores al lcd para leer la posicion del cursor 
		
	}
}

void Lcd_Write_Char(char a){    
    PORTDbits.RD2 = 1; //mantenemos en 1 la lcd para que pueda leer el char que le mandemos           
    PORTB = a;         //mandamos el valor a la lcd        
    PORTDbits.RD3=1;   //leemos el valor del char                    
    __delay_us(40);              
    PORTDbits.RD3=0;    //esperamos que otro valor ingrese a la lcd                  
}

void Lcd_Write_String(char *a)
{
	int i;                    // inicialiamos la variable i
	for(i=0;a[i]!='\0';i++)   //for que usamos para leer el strings dependiendo del tamano 
	    Lcd_Write_Char(a[i]); //mandamos el char a la lcd 
}

void Lcd_Init(){           
    
    PORTDbits.RD2 = 0;   //podemos el lcd en 0 para poder leer los comandos                
       
    Lcd_Cmd(0x00);      // utilizamos el conamdo 0x00       
    __delay_ms(15);         
    
   
    Lcd_Cmd(0x30);       // utilizamos el conamdo 0x30        
    __delay_us(160);        
    
    Lcd_Cmd(0x38);    // utilizamos el conamdo 0x38  
    Lcd_Cmd(0x01);    // utilizamos el conamdo 0x01         
    Lcd_Cmd(0x06);    // utilizamos el conamdo 0x06         
    Lcd_Cmd(0x0F);    // utilizamos el conamdo 0x0         
}
#endif	/* SPI_H */
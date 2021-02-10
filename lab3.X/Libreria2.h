
#pragma config FOSC = INTRC_NOCLKOUT


int c;  
int b;  
float vpot1;     
float vpot2;   
char buffer [];

void config (void);
void Lcd_Set_Cursor(char x, char y);
void Lcd_Write_String(char *a);
void puerto (char puertoANL);
void Lcd_Write_Char(char a);



void config (void){  
        
    ANSEL = 0b0000000;                  
    ANSELH = 0b0000000;      
     
    PORTB = 0b00000000;
    TRISA = 0b00000011;                  
    TRISB = 0b00000000;                  
    TRISD = 0b00000000;  
    
    ANSELbits.ANS0 = 1;         
    ANSELbits.ANS1 = 1;    
          
    
    ADCON0bits.ADON=1;                  
    ADCON1bits.ADFM=0;                  
    
    INTCONbits.GIE = 1;         
    INTCONbits.PEIE = 1;        

    PIE1bits.ADIE = 1;          
    PIR1bits.ADIF = 0;     

 
}

void Lcd_Cmd(char a){       //Cargo comando en bits a la LCD
	PORTDbits.RD2 =0;               //Escribiré un comando
	PORTB=a;          //Escribo el valor al LCD
    PORTDbits.RD3=1;               //Mando valores al LCD             
    __delay_ms(4);      //Espero   
    PORTDbits.RD3=0;                  
}


Lcd_Clear(){
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
	char temp,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
		z = temp>>8;
		y = temp & 0x0F;
		Lcd_Cmd(temp);
		
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>8;
		y = temp & 0x0F;
		Lcd_Cmd(temp);
		
	}
}

void Lcd_Write_Char(char a){      //Imprimir char
    PORTDbits.RD2 = 1;                      
    PORTB = a;                
    PORTDbits.RD3=1;                     
    __delay_us(40);              
    PORTDbits.RD3=0;                     
}

void Lcd_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	    Lcd_Write_Char(a[i]);
}

void Lcd_Init(){           
    
    PORTDbits.RD2   =0;                   
       
    Lcd_Cmd(0x00);            
    __delay_ms(15);         
    
   
    Lcd_Cmd(0x30);          
    __delay_us(160);        
    
    Lcd_Cmd(0x38);                 
    Lcd_Cmd(0x01);          
    Lcd_Cmd(0x06);          
    Lcd_Cmd(0x0F);          
   
}

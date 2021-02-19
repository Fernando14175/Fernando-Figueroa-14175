#pragma config FOSC = XT  // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF  // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
                          // (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF  // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF  // Flash Program Memory Write Enable bits 
                          // (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF   // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include "PIC16F887.h" 
#include <stdint.h>
#define _XTAL_FREQ 4000000
#define UP RD0
#define Down RD1
#define Send RD2
void SPI_Slave_Init();
void SPI_Write(uint8_t);
uint8_t SPI_Read();
uint8_t Data; // Global Received Data Variable (Not Recommended)
uint8_t Data2;              // Just For Demonstration Purposes Only!
void main(void) 
{
  
  SPI_Slave_Init(); 
  TRISE = 0x00;
  TRISB = 0x00;
  TRISD = 0b00000111;
  while(1)
  {
      if (UP) // Increment The Data Value
    {
      Data2++;
      __delay_ms(250);
    }
    if (Down) // Decrement The Data Value
    {
      Data2--;
      __delay_ms(250);
    }
    if (Send) // Send The Current Data Value Via SPI
    {
      SPI_Write(Data2);
      __delay_ms(250);
    }
     // Display The Current Data Value @ PORTD
    PORTE = Data2;
    PORTB = Data; 
  }
  return;
}
void SPI_Slave_Init()
{
  // Set Spi Mode To Slave + SS Enabled 
  SSPM0 = 0;
  SSPM1 = 0;
  SSPM2 = 1;
  SSPM3 = 0;
  // Enable The Synchronous Serial Port
  SSPEN = 1;
  // Configure The Clock Polarity & Phase (SPI Mode Num. 1)
  CKP = 0;
  CKE = 0;
  // Clear The SMP Bit
  SMP = 0;
  // Configure The IO Pins For SPI Master Mode
  TRISC5 = 0; // SDO -> Output
  TRISC4 = 1; // SDI -> Input
  TRISC3 = 1; // SCK -> Intput
  /*PCFG3 = 0; // Set SS (RA5/AN4) To Be Digital IO
  PCFG2 = 1;
  PCFG1 = 0;
  PCFG0 = 0;*/
  TRISA5 = 1; // SS -> Input
  // Enable Interrupts. Comment Them To Disable interrupts(NOT Recommended)
  SSPIE = 1;
  PEIE = 1;
  GIE = 1;
  ANSEL = 0b00000000;
  ANSELH = 0b00000000;
}
uint8_t SPI_Read() // Not Recommended Method To Read SPI Data
{
  uint8_t Data;
  if(BF) // Check If Any New Data Is Received
  {
    Data = SSPBUF; // Read The Buffer
    BF = 0; // Clear The Buffer-Filled Indicator Bit
    SSPIF = 0; // Clear The Interrupt Flag Bit
    SSPOV = 0; // Clear The Overflow Indicator Bit
    return Data;
  }
}
void __interrupt() ISR(void)
{
  if(SSPIF) 
  {
    Data = SSPBUF; // Read The Buffer
    SSPIF = 0; // Clear The Interrupt Flag
  }
}

void SPI_Write(uint8_t Data2)
{
  SSPBUF = Data2; // Transfer The Data To The Buffer Register
  // while(!SSPSTATbits.BF); // Un-comment it if you're Not Using Interrupts!
  // The Above While Loop Protects Against Writing To The Buffer 
  // Before The Previous Transmission Ends
}
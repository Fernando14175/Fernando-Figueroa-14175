#ifndef __I2C_H
#define	__I2C_H
#include <xc.h>
//******************* I2C Section *********************//
void i2c_init()
{
	TRISC3 = 1;
	TRISC4 = 1;
	SSPBUF = 0x00;
	SSPSTAT = 0xc0;
	SSPCON = 0x28;
	SSPCON2 = 0x00;
	SSPIF = 0;
	SSPADD = 9;
}

void i2c_start()
{
	SEN = 1;
	while(SEN);
}

void i2c_wait()
{
	while(SSPIF==0);
	SSPIF = 0;
}

void i2c_rep_start()
{
	RSEN = 1;
	while(RSEN);
}

void i2c_NACK()
{
	ACKDT = 1;
	ACKEN = 1;
	while(ACKEN);
}

void i2c_stop()
{
	i2c_wait();
	PEN = 1;
	while(PEN);
}

unsigned char i2c_rx()
{
	RCEN = 1;
	while(!BF);
	return SSPBUF;
}

unsigned char i2c_send(unsigned char c)
{
	SSPBUF = c;
	while(BF);
	i2c_wait();
}

#endif	/* SPI_H */

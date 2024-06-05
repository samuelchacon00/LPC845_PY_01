/*
 * uart.c
 *
 *  Created on: 6 nov. 2022
 *      Author: foto
 */


#include "cabeza.h"

volatile uint8_t txStart = 0;  //flag para activar/desactivar transmisión serie

// Buffer de Transmision
volatile uint8_t bufferTx[TXBUFFER_SIZE];
// Buffer de Recepcion
volatile uint8_t bufferRx[RXBUFFER_SIZE];

// Indices de Recepcion
volatile uint8_t rx_in = 0;
volatile uint8_t rx_out = 0;
// Indices de Transmision
volatile uint8_t tx_in = 0;
volatile uint8_t tx_out = 0;

void Inicializar_UART0()
{
	SWM->PINASSIGN0=(uint8_t)0x10;		//ya el clock de LA SWM esta prendido
	SWM->PINASSIGN0&=(uint32_t)(0x11)<<8;

	SYSCON->FCLKSEL[0]=(uint32_t)0x04;	//caja negra

	SYSCON->SYSAHBCLKCTRL0|=(uint32_t)(1<<14);	//habilito clock de la uart0

	//configuracion de la UART0
	//enable y 8 bits de datos
	UART0->CFG|=0x05;	//0 por defecto: bit de paridad:sin paridad | bit de stop: 1 bit de stop

	//configuracin baud rate
	UART0->BRG=(uint32_t)97;

	UART0->INTENSET|=0x01;

	NVIC->ISER0|=(uint32_t)(0x01<<3);
}

void pushtTx(uint8_t dato)
{

	bufferTx[tx_in]=dato;
	tx_in++;
	tx_in%= TXBUFFER_SIZE;

	if(!txStart)
	{
		txStart=1;
		START_TX();		//#define START_TX()	( USART0->INTENSET = (1 << 2); ) // int tx
	}
}

uint16_t popTx()
{
	uint16_t dato=-1;

	if(tx_in!=tx_out)
	{
		dato=(uint16_t)bufferTx[tx_out];
		tx_out++;
		tx_out%=TXBUFFER_SIZE;
	}

	return dato;
}

void pushRx(uint8_t dato)
{
	bufferRx[rx_in]=dato;
	rx_in++;
	rx_in%=TXBUFFER_SIZE;
}

uint16_t popRx(void)
{
	uint16_t dato=-1;

	if(rx_in!=rx_out)
	{
		dato=(uint16_t)bufferRx[rx_out];
		rx_out++;
		rx_out%=RXBUFFER_SIZE;
	}

	return dato;
}

uint16_t Transmitir(uint8_t* datos,uint8_t cant)
{
	uint8_t i;

	if(cant>MAX_DATOS)
		return -1;

	for(i=0;i<cant;i++)
		pushTx(datos[i]);

	return 0;
}

void UART0_IRQHandler(void)
{
	uint16_t aux;
	uint32_t stat=UART0->STAT;

	if(stat&(1<<0))
	{
		aux=(uint8_t)UART0->RXDAT;
		pushRx((uint16_t)aux);
	}
	else if(stat&(1<<2))
	{
		aux=popTx();
		if(aux>=0)
			UART0->TXDAT=(uint8_t)aux;
		else
		{
			UART0->INTENCLR=(1<<2); //APAGO INTERRUPCION
			txStart=0;
		}
	}
}

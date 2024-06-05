/*
 * uart.h
 *
 *  Created on: 6 nov. 2022
 *      Author: foto
 */

#ifndef UART_H_
#define UART_H_

#define TXBUFFER_SIZE	120    //arbitrario
#define RXBUFFER_SIZE	120    //arbitrario
#define MAX_DATOS	    30     //arbitrario

//primitivas de recepción y transmisión. No están comprometidas con el HW
void pushTx(uint8_t dato);
uint16_t popTx(void);
void pushRx(uint8_t dato);
uint16_t popRx(void);
//void EnviarString (const char *str);
uint16_t Transmitir (uint8_t * , uint8_t );
//------------------------------------------------------------------------

//Macro definida para arrancar la Tx y no pinchar capas
#define   START_TX()	UART0->INTENSET = (1 << 2)

#define RECIBIR_UART0 UART0_popRx()


void Inicializar_UART0();

#endif /* UART_H_ */

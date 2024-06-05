/*
 * teklado.h
 *
 *  Created on: 27 sep. 2022
 *      Author: samuel
 */

#ifndef TEKLADO_H_
#define TEKLADO_H_

#define REBOTES	200

#define NO_KEY 	(uint8_t)0xFF
#define TECLA0 	1
#define TECLA1 	2
#define TECLA2 	3
#define TECLA3 	4
#define TECLA4 	5
#define TECLA5 	6

#define FILA0 		0,27
#define FILA1 		0,28

#define COLUMNA0 	0,8
#define COLUMNA1 	0,31
#define COLUMNA2 	0,30

#define PIN_FILA0 IOCON_INDEX_PIO0_27
#define PIN_FILA1 IOCON_INDEX_PIO0_28
#define PIN_COLUMNA0 IOCON_INDEX_PIO0_8
#define PIN_COLUMNA1 IOCON_INDEX_PIO0_31
#define PIN_COLUMNA2 IOCON_INDEX_PIO0_30

//estados
#define REPOSO 0
#define DETECTO 1
#define CHEQUEO 2

//funciones

void InicializarTeclado();
uint8_t TekladoHW(void);
void TekladoSW(uint8_t);
void DriverTeklado(void);
uint8_t teklado(void);

#endif /* TEKLADO_H_ */

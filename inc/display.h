/*
 * display.h
 *
 *  Created on: 27 sep. 2022
 *      Author: samuel
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define BCD_A 0,20
#define BCD_B 0,23
#define BCD_C 0,22
#define BCD_D 0,21
#define DP 0,12

#define BCD_RST 0,18
#define BCD_CLOCK 0,19

#define ndigs 3

#define ROJO 0
#define VERDE 1

#define entero 1
#define flotante 0

//numero de digitos

#define DIGITO_0 0
#define DIGITO_1 1
#define DIGITO_2 2
#define DIGITO_3 3
#define DIGITO_4 4
#define DIGITO_5 5

#define DSP_ROJO 0
#define DSP_VERDE 1

//funciones

void display(uint32_t,uint8_t);
void barrido_disp(void);

#endif /* DISPLAY_H_ */

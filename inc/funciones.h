/*
 * funciones.h
 *
 *  Created on: 24 oct. 2022
 *      Author: foto
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

void buzzer_on();
void buzzer_off();

void rojo_on();
void rojo_off();
void toggle_verde();
void verde_on();
void verde_off();
void azul_on();
void azul_off();
uint8_t boton_usr();
void pin_on(uint32_t,uint32_t);
void pin_off(uint32_t,uint32_t);

#endif /* FUNCIONES_H_ */

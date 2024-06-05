/*
 * maquinas.h
 *
 *  Created on: 2 nov. 2022
 *      Author: foto
 */

#ifndef MAQUINAS_H_
#define MAQUINAS_H_

#define REPOSO		0
#define MATCH 		1
#define CAP			2
#define ON			3
#define OFF			4
#define CORRIENDO	5
#define LEVANTADO 	6
#define BAJADO		7
#define ALTO		8
#define BAJO		9

#define TIME		5

void inicializar_patas();
void mde_maquina1();
void mde_maquina2();
void mde_maquina3();

void mde_modulador();
void mde_oscilador();

void mde_ledparpadeante_rojo();
void timer_02dec();
void timer_02dec_handler();

void mde_reloj();
void timer_1seg();
void timer_1seg_handler();
void timer_1dec();
void timer_1dec_handler();

#endif /* MAQUINAS_H_ */

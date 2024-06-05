/*
 * reloj.h
 *
 *  Created on: 20 dic. 2022
 *      Author: foto
 */

#ifndef RELOJ_H_
#define RELOJ_H_

#define CRONO		1
#define TEMPO		2
#define RUNNING		3
#define PAUSA		4
#define INICIO		5
#define FIN			6
#define SALIR		7
#define CRON			8
#define TEM			9

void funcion_simple(uint8_t*);
void mde_modo();

void modo_CTcron();
void modo_CTtem();
void modo_crono();
void modo_tempo();
uint8_t mde_tempo_config();
void unmili_timer();
void mili_timer(uint32_t);

#endif /* RELOJ_H_ */

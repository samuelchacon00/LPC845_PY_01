/*
 * CounterTimer.h
 *
 *  Created on: 18 oct. 2022
 *      Author: samuel
 */

#ifndef COUNTERTIMER_H_
#define COUNTERTIMER_H_

#define segs		30000000
#define mili		30000		//28999
#define micro		30

#define PIO0_5 0x05;

#define captura 	0
#define coicidencia 1

void inicializar_timer();
void timer(uint32_t,uint8_t,uint32_t);

void habilitar_captura();
void deshabilitar_captura();
void habilitar_coicidencia();
void deshabilitar_coicidencia();
void reset_timer();
void arrancar();
void bajar_flag_match0();
void bajar_flag_cap0();
void establecer_preescala(uint32_t);
void flanco_ascendente();
void flanco_descendente();
void cap_int_on();
void cap_int_off();
void swm_cap_on(uint8_t,uint8_t);
//void swm_cap_off();

#endif /* COUNTERTIMER_H_ */

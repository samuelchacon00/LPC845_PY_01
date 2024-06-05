/*
 * timers.h
 *
 *  Created on: 27 sep. 2022
 *      Author: samuel
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#define on 1
#define off 0

#define DEC 0
#define SEG 1
#define MIN 2
#define MIL 3

#define STOP 0
#define PAUSE 1
#define RUN 2

#define n_timers 23

void AnalizarTimers(void);
void InicializarTimers(void);
void TimerStart(uint8_t,uint32_t,void (*handler)(void),uint8_t);
void TimerStop(uint8_t);
void TimerEvent(void);
void StandByTimer(uint8_t,uint8_t);
void SetTimer(uint8_t,uint32_t);
void timer_handler();
void timer_on();

#endif /* TIMERS_H_ */

/*
 * timers.c
 *
 *  Created on: 27 sep. 2022
 *      Author: samuel
 */

#include "cabeza.h"

volatile uint32_t TMR_RUN[n_timers];
volatile uint8_t TMR_events[n_timers];
volatile void (*TMR_handler[n_timers])(void);
volatile uint8_t TMR_standby[n_timers];
volatile uint8_t TMR_base[n_timers];

extern volatile uint16_t dec;
extern volatile uint16_t seg;

volatile uint8_t timer_flag;

uint32_t TimerTime(uint8_t event)
{
	return TMR_RUN[event];
}

void InicializarTimers(void)
{
	volatile uint8_t i=0;

	for(i=0;i<n_timers;i++)
	{
		TMR_RUN[i]=0;
		TMR_standby[i]=STOP;
		TMR_events[i]=0;
	}
}
void AnalizarTimers(void)
{
	volatile uint8_t i=0;

	for(i=0;i<n_timers;i++)
	{
		if(TMR_RUN[i]&&TMR_standby[i]==RUN)
			switch(TMR_base[i])
			{
				case DEC:
					if(!dec)
						TMR_RUN[i]--;
					break;
				case SEG:
					if(!seg)
						TMR_RUN[i]--;
					break;
			}
		else if(!TMR_RUN[i]&&TMR_standby[i]==RUN)
			TMR_events[i]=1;
	}
	if(!seg)
		seg=1;
	if(!dec)
		dec=1;
}
void TimerEvent(void)
{
	volatile uint8_t i=0;

	for(i=0;i<n_timers;i++)
		if(TMR_standby[i]==RUN&&TMR_events[i])
		{
			TMR_standby[i]=STOP;
			TMR_events[i]=0;
			TMR_handler[i]();
		}
}
void TimerStart(uint8_t event,uint32_t time,void (*handlerr)(void),uint8_t escala)
{
	TMR_RUN[event]=time;
	TMR_standby[event]=RUN;
	TMR_events[event]=0;
	TMR_handler[event]=handlerr;
	TMR_base[event]=escala;
}
void TimerStop(uint8_t event)
{
	TMR_RUN[event]=0;
	TMR_standby[event]=STOP;
	TMR_events[event]=0;
}
void StandByTimer(uint8_t event,uint8_t estado)
{
	volatile uint8_t i;

	for(i=0;i<n_timers;i++)
		if(i==event)
			TMR_standby[event]=estado;
}
void SetTimer(uint8_t event,uint32_t t)
{
	if(TMR_standby[event])
		TMR_RUN[event]=t;
}


void timer_on()
{
	timer_flag=0;
	TimerStart(1,1,&timer_handler,SEG);
}

void timer_handler()
{
	timer_flag=1;
}




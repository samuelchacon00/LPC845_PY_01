/*
 * reloj.c
 *
 *  Created on: 20 dic. 2022
 *      Author: foto
 */

#include "cabeza.h"

#define M_CORNO		0
#define M_TEMPO		1

extern volatile uint8_t cap_out;
extern volatile uint8_t match_out;
volatile uint16_t min=0;
volatile uint8_t segg=0;
volatile uint8_t cero1=0;
volatile uint8_t cero2=0;
volatile uint8_t salir=0;

volatile uint32_t tiempo=0;
volatile uint32_t milis=1000;

void funcion_simple(uint8_t *estado)
{
	if(salir)
	{
		salir=0;
		azul_off();
		*estado=REPOSO;
	}
}

void mde_modo()
{
	volatile static uint8_t est=REPOSO;
	volatile uint8_t tecla;

	switch(est)
	{
		case REPOSO:
			tecla=teklado();
			if(tecla==TECLA0)
				est=CRONO;
			if(tecla==TECLA1)
				est=TEMPO;
			if(tecla==TECLA3)
				est=CRON;
			if(tecla==TECLA4)
				est=TEM;
			break;
		case CRONO:
			modo_crono();
			funcion_simple((uint8_t*)&est);
			break;
		case TEMPO:
			modo_tempo();
			funcion_simple((uint8_t*)&est);
			break;
		case CRON:
			modo_CTcron();
			funcion_simple((uint8_t*)&est);
			break;
		case TEM:
			modo_CTtem();
			funcion_simple((uint8_t*)&est);
			break;
	}
}



void modo_CTcron()
{
	volatile static uint8_t est=INICIO;
	volatile uint8_t tecla;

	switch(est)
	{
		case INICIO:
			tecla=teklado();
			if(tecla==TECLA2)
			{
				timer(0,captura,mili);
				est=RUNNING;
			}
			break;
		case RUNNING:
			display((TC/60000),ROJO);
			display((TC/1000)%60,VERDE);
			if(cap_out)
			{
				azul_on();
				est=FIN;
			}
			break;
		case FIN:
			tecla=teklado();
			if(tecla==TECLA5)
			{
				salir=1;
				est=REPOSO;
			}
			break;
	}
}

void modo_CTtem()
{
	volatile static uint8_t est=INICIO;
	volatile uint8_t flag,tecla;

	switch(est)
	{
		case INICIO:
			tiempo=0;
			flag=mde_tempo_config();
			if(flag)
			{
				mili_timer(tiempo*1000);
				flanco_descendente();
				est=RUNNING;
			}
			break;
		case RUNNING:
			display((TC/60000),ROJO);
			display((TC/1000)%60,VERDE);
			if(match_out)
			{
				azul_on();
				est=FIN;
			}
			break;
		case FIN:
			tecla=teklado();
			if(tecla==TECLA5)
			{
				salir=1;
				est=INICIO;
			}
			break;
	}
}


void modo_crono()
{
	volatile static uint8_t est=REPOSO;
	volatile uint8_t tecla;

	tecla=teklado();

	display(tiempo/60,VERDE);
	display(tiempo%60,ROJO);

	switch(est)
	{
		case REPOSO:
			if(tecla==TECLA0)
			{
				unmili_timer();
				est=CORRIENDO;
			}
			break;
		case CORRIENDO:
			if(tecla==TECLA1)
				est=PAUSA;
			if(tecla==TECLA2)
			{
				tiempo=0;
				est=REPOSO;
			}
			if(match_out)
			{
				if(milis)
				{
					milis--;
					if(!milis)
					{
						tiempo++;
						milis=1000;
					}
				}
				unmili_timer();
			}
			break;
		case PAUSA:
			if(tecla==TECLA0)
				est=CORRIENDO;
			if(tecla==TECLA2)
			{
				tiempo=0;
				est=REPOSO;
			}
			break;
		case SALIR:
			if(tecla==TECLA5)
				salir=1;
			break;
	}
}

void modo_tempo()
{
	volatile static uint8_t est=INICIO;
	volatile uint8_t tecla,flag;

	switch(est)
	{
		case INICIO:
			tiempo=0;
			flag=mde_tempo_config();
			if(flag)
			{
				unmili_timer();
				est=RUNNING;
			}
			break;
		case RUNNING:
			display(tiempo/60,VERDE);
			display(tiempo%60,ROJO);
			if(match_out)
			{
				if(milis)
				{
					milis--;
					if(!milis)
					{
						tiempo--;
						milis=1000;
					}
				}
				unmili_timer();
			}
			if(!tiempo)
			{
				azul_on();
				est=FIN;
			}
			tecla=teklado();
			if(tecla==TECLA5)
			{
				azul_off();
				est=INICIO;
				salir=1;
			}
			break;
		case FIN:
			tecla=teklado();
			if(tecla==TECLA5)
			{
				azul_off();
				est=INICIO;
				salir=1;
			}
			break;
	}
}

uint8_t mde_tempo_config()
{
	volatile uint8_t r=0,tecla=teklado();

	display(min,VERDE);
	display(segg,ROJO);

	if(tecla==TECLA0)
	{
		segg++;
		segg%=60;
	}
	if(tecla==TECLA3)
	{
		segg--;
		segg%=60;
		if(!segg&&!cero1)
			cero1++;
		else if(cero1)
		{
			cero1=0;
			segg=59;
		}
	}
	if(tecla==TECLA1)
	{
		min++;
		if(min==1000)
			min=0;
	}
	if(tecla==TECLA4)
	{
		min--;
		if(!min&&!cero2)
		{
			cero2=1;
		}
		else if(cero2)
		{
			cero2=0;
			min=999;
		}
	}

	if(tecla==TECLA2)
	{
		r=1;
		tiempo=(min*60)+segg;
	}
	return r;
}

void mili_timer(uint32_t t)
{
	timer(t,coicidencia,mili);
}

void unmili_timer()
{
	timer(1,coicidencia,mili);
}

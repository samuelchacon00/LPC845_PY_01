/*
 * maquinas.c
 *
 *  Created on: 2 nov. 2022
 *      Author: foto
 */

#include "cabeza.h"

extern volatile uint8_t match_out;
extern volatile uint8_t cap_out;
volatile uint8_t timer_02dec_out=0;

volatile uint8_t timer_1seg_out;
volatile uint8_t timer_1dec_out;

volatile uint32_t time_config=TIME;

void inicializar_patas()
{
	SetPIN(SWDIO, 1);
	SetDIR(SWDIO, SALIDA);
	SetPINMODE_OUT(PIN_SWDIO, PUSH_PULL);

	SetPIN(AN_IN, 1);
	SetDIR(AN_IN, SALIDA);
	SetPINMODE_OUT(PIN_AN_IN, PUSH_PULL);

	SetPIN(SWCLK, 1);
	SetDIR(SWCLK, SALIDA);
	SetPINMODE_OUT(PIN_SWCLK, PUSH_PULL);

	SetPIN(DIG_IN1, 1);
	SetDIR(DIG_IN1, SALIDA);
	SetPINMODE_OUT(PIN_DIG_IN1, PUSH_PULL);

	SetPIN(OUT3, 1);
	SetDIR(OUT3, SALIDA);
	SetPINMODE_OUT(PIN_OUT3, PUSH_PULL);
}


void mde_maquina1()
{
	volatile static uint8_t est=REPOSO;
	volatile uint8_t tecla=teklado();

	display(TC,ROJO);
	display(CR,VERDE);

	switch(est)
	{
		case REPOSO:
			if(tecla==TECLA0)
			{
				verde_on();
				azul_off();
				rojo_off();
				timer(10,coicidencia,segs);
				est=MATCH;
			}
			if(tecla==TECLA1)
			{
				verde_on();
				azul_off();
				rojo_off();
				recepcion();
				timer(0,captura,segs);
				flanco_descendente();
				recepcion();
				est=CAP;
			}
			break;
		case MATCH:
			if(match_out)
			{
				verde_off();
				azul_on();
				est=REPOSO;
			}
			break;
		case CAP:
			if(cap_out)
			{
				verde_off();
				azul_on();
				est=REPOSO;
			}
			break;
	}
}
void mde_maquina2()
{
	volatile static uint8_t est=REPOSO;
	volatile uint8_t tecla=teklado();

	switch(est)
	{
		case REPOSO:
			if(tecla==TECLA0)
			{
				timer(1,coicidencia,segs);
				transmision(1);
				//verde_on();
				est=LEVANTADO;
			}
			break;
		case LEVANTADO:
			if(tecla==TECLA1)
				est=REPOSO;
			if(match_out)
			{
				timer(1,coicidencia,segs);
				bajar();
				//verde_off();
				est=BAJADO;
			}
			break;
		case BAJADO:
			if(tecla==TECLA1)
				est=REPOSO;
			if(match_out)
			{
				timer(1,coicidencia,segs);
				levantar();
				//verde_on();
				est=LEVANTADO;
			}
			break;
	}
}
void mde_maquina3()
{
	volatile static uint8_t est=OFF;
	volatile uint8_t tecla=teklado();

	switch(est)
	{
		case OFF:
			if(tecla==TECLA0)
			{
				pin_on(OUT3);
				est=ON;
			}
			break;
		case ON:
			if(tecla==TECLA1)
			{
				pin_off(OUT3);
				est=OFF;
			}
			break;
	}
}

void mde_modulador()
{
	volatile uint8_t tecla=NO_KEY;

	tecla=teklado();

	switch(tecla)
	{
		case TECLA0:
			time_config++;
			display(time_config,ROJO);
			break;
		case TECLA3:
			time_config--;
			display(time_config,ROJO);
			break;
		case TECLA1:
			time_config+=10;
			display(time_config,ROJO);
			break;
		case TECLA4:
			time_config-=10;
			display(time_config,ROJO);
			break;
		case TECLA2:
			time_config+=100;
			display(time_config,ROJO);
			break;
		case TECLA5:
			time_config-=100;
			display(time_config,ROJO);
			break;
	}
	time_config%=1000;
}

void mde_oscilador()//oscilador de puslos co ctimer
{
	volatile static uint8_t est=REPOSO;

	switch (est)
	{
		case REPOSO:
			timer(time_config,coicidencia,micro);
			verde_on();
			est=BAJO;
			break;
		case BAJO:
			if(match_out)//el alto es apagado porque esta la logica invertida
			{
				timer(time_config,coicidencia,micro);
				//verde_off();
				toggle_verde();
				est=ALTO;
			}
			break;
		case ALTO:
			if(match_out)
			{
				timer(time_config,coicidencia,micro);
				//verde_on();
				toggle_verde();
				est=BAJO;
			}
			break;
	}
}

void mde_reloj()
{
	volatile static uint8_t est=REPOSO,tecla;
	volatile static uint8_t segundoss=0,segs_max=10,decimas=0;

	tecla=teklado();

	display(segundoss,ROJO);
	display(decimas,VERDE);

	switch(est)
	{
		case REPOSO:
			if(tecla==TECLA0)
			{
				timer_1seg();
				timer_1dec();
				est=CORRIENDO;
			}
			break;
		case CORRIENDO:
			if(segundoss==segs_max)
			{
				segundoss=0;
				decimas=0;
				est=REPOSO;
			}
			if(timer_1seg_out)
			{
				timer_1seg();
				segundoss++;
			}
			if(timer_1dec_out)
			{
				timer_1dec();
				decimas++;
				decimas%=10;
			}
			break;
	}
}

void timer_1seg()
{
	timer_1seg_out=0;
	TimerStart(0,1,&timer_1seg_handler,SEG);
}
void timer_1seg_handler()
{
	timer_1seg_out=1;
}
void timer_1dec()
{
	timer_1dec_out=0;
	TimerStart(1,1,&timer_1dec_handler,DEC);
}
void timer_1dec_handler()
{
	timer_1dec_out=1;
}


void mde_ledparpadeante_rojo()
{
	volatile static uint8_t est=REPOSO;

	switch(est)
	{
		case REPOSO:
			verde_off();
			rojo_on();
			azul_off();
			timer_02dec();
			est=ON;
			break;
		case ON:
			if(timer_02dec_out)
			{
				rojo_off();
				timer_02dec();
				est=OFF;
			}
			break;
		case OFF:
			if(timer_02dec_out)
			{
				rojo_on();
				timer_02dec();
				est=ON;
			}
			break;
	}
}
void timer_02dec()
{
	timer_02dec_out=0;
	TimerStart(3,2,&timer_02dec_handler,DEC);
}
void timer_02dec_handler()
{
	timer_02dec_out=1;
}

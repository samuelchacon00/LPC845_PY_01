/*
 * CounterTimer.c
 *
 *  Created on: 18 oct. 2022
 *      Author: samuel
 */

#include "cabeza.h"

volatile uint8_t match_out=0;
volatile uint8_t MODO;
volatile uint32_t cap_out=0;

void inicializar_timer()
{
	SYSCON->SYSAHBCLKCTRL0|=(uint32_t)1<<25|(uint32_t)1<<7;	//habilito clock del timer y del SWM
	swm_cap_on(DIGIN1);
	SYSCON->SYSAHBCLKCTRL0&=~((uint32_t)(1<<7));		//deshabilito clock de la SWM
	//MCR|=0x05;							 	//habilito interrupcion de MR0I y MR0S
	NVIC->ISER0|=((uint32_t)1<<23);		//habilito rutina CTIMER0_IRQHnadler()
}

void timer(uint32_t valor,uint8_t modo,uint32_t escala)
{
	volatile static uint8_t val=0;
	//volatile static uint8_t flag=0;
	establecer_preescala(escala);

	MODO=modo;
	if(!val)
	{
		val=1;
		if(modo==coicidencia)
		{
			deshabilitar_captura();
			habilitar_coicidencia();
		}
		else
		{
			deshabilitar_coicidencia();
			habilitar_captura();
		}
	}

	switch(modo)
	{
		case coicidencia:
			//MODO=coicidencia;
			match_out=0;
			if(MODO!=coicidencia)
			{
				deshabilitar_captura();
				habilitar_coicidencia();
			}
			MR0=valor;			//cargando valor de coicidencia
			reset_timer();
			arrancar();
			break;
		case captura:
			//MODO=captura;
			cap_out=0;
			if(MODO!=captura)
			{
				deshabilitar_coicidencia();
				habilitar_captura();
			}
			reset_timer();
			arrancar();
			break;
	}
}

void CTIMER0_IRQHandler(void)
{
	switch(MODO)
	{
		case coicidencia:
			match_out=1;				//levanto flag
			//deshabilitar_coicidencia();	//desactivo interrupcion
			bajar_flag_match0();			//bajo el flag de interrupcion
			//reset_timer();				//reiniciar contador
			break;
		case captura:
			cap_out=1;
			//deshabilitar_captura();
			bajar_flag_cap0();
			//reset_timer();				//reiniciar contador
			break;
	}
}

void habilitar_captura()
{
	cap_int_on();
	//swm_cap_on();
}
void deshabilitar_captura()
{
	cap_int_off();
	//swm_cap_off();
}
void habilitar_coicidencia()
{
	MCR|=0x05;				//habilitar interrupcion
}
void deshabilitar_coicidencia()
{
	MCR&=(uint32_t)0x00; 	//deshabilitar interrupcion
}
void reset_timer()
{
	MCR|=(uint32_t)0x02;
	TCR&=~(uint32_t)0x01;
	TCR|=(uint32_t)0x02;

}
void arrancar()
{
	MCR&=~(uint32_t)0x02;
	TCR=(uint32_t)0x01;
}
void bajar_flag_match0()
{
	IR|=0x01;
}
void establecer_preescala(uint32_t x)
{
	PR=(uint32_t)x;
}
void flanco_ascendente()
{
	CCR|=0x01;		//habilito flanco ascendente
}
void flanco_descendente()
{
	CCR|=0x02;		//habilito flanco descendente
}
void cap_int_on()
{
	CCR|=0x01;
}
void cap_int_off()
{
	CCR&=0x00;		//limpio todito por si las mosquis
}
void bajar_flag_cap0()
{
	IR|=(uint32_t)(1<<4);
}
void swm_cap_on(uint8_t pu,uint8_t pi)
{
	uint8_t pata=pi;

	if(pu)
		pata+=32;

	SWM->PINASSIGN14&=~((uint32_t)(pata<<8));
	SWM->PINASSIGN14|=(uint32_t)(pata<<8);
}


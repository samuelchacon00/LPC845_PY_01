/*
 * SysTick.c
 *
 *  Created on: 12 ene. 2022
 *      Author: gos
 */

#include "cabeza.h"

volatile uint16_t seg=1;
volatile uint16_t dec=1;
volatile uint32_t delay=1000;
volatile uint16_t lcd_delay=50;

uint32_t SysTick_Config(uint32_t ticks)
{
		SYST_RVR  = (ticks) - 1 ;
		SYST_CVR = 0; /*para que desborde al próximo tick y se
		reinicialice al valor adecuado programado en STRELOAD*/
		ENABLE = 1; //habilito que comience a contar
		TICKINT = 1; //habilito interrupciones
		CLKSOURCE = 1; //uso clock interno
		return (0UL);
}


/*
 * @brief   ISR de SysTick
 */
void SysTick_Handler(void)
{
	if(delay)
	{
		if((delay%100)==0)
			dec=0;
		delay--;
		if(!delay)
		{
			seg=0;
			delay=1000;
		}
	}
	//lcd_delay--;
	//lcd_delay%=50;
	AnalizarTimers();
	EscrituraLCD();
	barrido_disp();
	DriverTeklado();
}

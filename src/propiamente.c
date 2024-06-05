/*
===============================================================================
 Name        : propiamente.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>
#include "cabeza.h"

extern volatile uint8_t match_out;
extern volatile uint8_t Temp_entero;
extern volatile uint8_t error;
extern volatile uint8_t cap_out;
extern volatile uint8_t match_out;
extern volatile uint32_t delay;
extern volatile uint8_t timer_flag;

int main(void)
{
	//volatile uint8_t tecla = NO_KEY;
	inicializacion();
	display_lcd("hola mundo",0,0);
	display(TIME,ROJO);
	while(1)
	{
		//TimerEvent();
		//pin_on(EXT_LED);

		mde_oscilador();
		mde_modulador();
		//mde_modo();
		//mde_maquina1();
		//mde_maquina2();
		//mde_maquina3();
		//driver_sensor();
		//mde_ledparpadeante_rojo();
	}

    return 0 ;
}

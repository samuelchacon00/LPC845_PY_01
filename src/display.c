/*
 * display.c
 *
 *  Created on: 27 sep. 2022
 *      Author: samuel
 */

#include "cabeza.h"

volatile uint8_t disp_rojo[ndigs]={0};
volatile uint8_t disp_verde[ndigs]={0};

void display(uint32_t valor,uint8_t color)
{
	uint8_t i;

	switch(color)
	{
		case ROJO:
			for(i=0;i<ndigs;i++,valor/=10)
				disp_rojo[ndigs-1-i]=valor%10;
			break;
		case VERDE:
			for(i=0;i<ndigs;i++,valor/=10)
				disp_verde[ndigs-1-i]=valor%10;
			break;
	}
}

void barrido_disp(void)
{
	static uint8_t r=1,nd=0;

	SetPIN(BCD_A,1);
	SetPIN(BCD_B,1);
	SetPIN(BCD_C,1);
	SetPIN(BCD_D,1);

	if(!nd)
	{
		SetPIN(BCD_RST,1);
		SetPIN(BCD_RST,0);
	}
	else
	{
		SetPIN(BCD_CLOCK,1);
		SetPIN(BCD_CLOCK,0);
	}

	if(r)
	{
		SetPIN(BCD_A,(disp_rojo[nd]&(uint8_t)0x1));
		SetPIN(BCD_B,(disp_rojo[nd]>>1&(uint8_t)0x1));
		SetPIN(BCD_C,(disp_rojo[nd]>>2&(uint8_t)0x1));
		SetPIN(BCD_D,(disp_rojo[nd]>>3&(uint8_t)0x1));
		nd++;
		if(nd==ndigs)
			r=0;
	}
	else
	{
		SetPIN(BCD_A,(disp_verde[nd-ndigs]&(uint8_t)0x1));
		SetPIN(BCD_B,(disp_verde[nd-ndigs]>>1&(uint8_t)0x1));
		SetPIN(BCD_C,(disp_verde[nd-ndigs]>>2&(uint8_t)0x1));
		SetPIN(BCD_D,(disp_verde[nd-ndigs]>>3&(uint8_t)0x1));
		nd++;
		if(nd==(ndigs*2))
		{
			nd=0;
			r=1;
		}
	}
}

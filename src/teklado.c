/*
 * teklado.c
 *
 *  Created on: 27 sep. 2022
 *      Author: samuel
 */

#include "cabeza.h"

volatile uint8_t buffkey;

void InicializarTeclado()
{
	SetDIR(COLUMNA0,ENTRADA);
	SetPINMODE_IN(PIN_COLUMNA0,PULL_UP);

	SetDIR(COLUMNA1,ENTRADA);
	SetPINMODE_IN(PIN_COLUMNA1,PULL_UP);

	SetDIR(COLUMNA2,ENTRADA);
	SetPINMODE_IN(PIN_COLUMNA2,PULL_UP);

	SetPIN(FILA0,1);
	SetDIR(FILA0,SALIDA);
	SetPINMODE_OUT(PIN_FILA0,PUSH_PULL);

	SetPIN(FILA1,1);
	SetDIR(FILA1,SALIDA);
	SetPINMODE_OUT(PIN_FILA1,PUSH_PULL);
}

uint8_t TekladoHW(void)
{
	uint8_t Codigo = NO_KEY;

	SetPIN(FILA0,0);
	SetPIN(FILA0,0);
	SetPIN(FILA0,0);
	SetPIN(FILA1,1);
	SetPIN(FILA1,1);
	SetPIN(FILA1,1);

	if(!GetPIN(COLUMNA0))
		return TECLA0;
	if(!GetPIN(COLUMNA1))
		return TECLA1;
	if(!GetPIN(COLUMNA2))
		return TECLA2;

	SetPIN(FILA0,1);
	SetPIN(FILA0,1);
	SetPIN(FILA0,1);
	SetPIN(FILA1,0);
	SetPIN(FILA1,0);
	SetPIN(FILA1,0);

	if(!GetPIN(COLUMNA0))
		return TECLA3;
	if(!GetPIN(COLUMNA1))
		return TECLA4;
	if(!GetPIN(COLUMNA2))
		return TECLA5;

	return Codigo;
}

void TekladoSW(uint8_t actual)
{
	volatile static uint8_t est=REPOSO,anterior;
	volatile static uint16_t cont=REBOTES;

	if(actual==NO_KEY)
	{
		est=REPOSO;
		anterior=NO_KEY;
		return;
	}

	switch (est)
	{
		case REPOSO:
			if(actual!=NO_KEY)
			{
				anterior=actual;
				est=DETECTO;
			}
			break;

		case DETECTO:
			if(actual!=anterior)
			{
				anterior=actual;
			}
			else if(actual==anterior)
			{
				est=CHEQUEO;
			}
			break;

		case CHEQUEO:
			if(actual!=anterior)
			{
				cont=REBOTES;
				anterior=actual;
				est=DETECTO;
			}
			else if(cont)
				cont--;
			else if(!cont)
			{
				cont=REBOTES;
				buffkey=actual;
				est=REPOSO;
			}
			break;
	}
}

void DriverTeklado(void)
{
	volatile uint8_t actual;

	actual=TekladoHW();
	TekladoSW(actual);
}

uint8_t teklado(void)
{
	volatile uint8_t tecla=NO_KEY;

	if(buffkey!=NO_KEY)
	{
		tecla=buffkey;
		buffkey=NO_KEY;
	}
	return tecla;
}

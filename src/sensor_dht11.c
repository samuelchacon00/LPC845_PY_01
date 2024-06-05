/*
 * sensor_dht11.c
 *
 *  Created on: 28 oct. 2022
 *      Author: foto
 */

#include "cabeza.h"

#define SENSOR			OUT3
#define PIN_SENSOR		PIN_OUT3

extern volatile uint8_t cap_out;
extern volatile uint8_t match_out;

volatile uint8_t Humedad_entero=0;
volatile uint8_t Humedad_decimal=0;
volatile uint8_t Temp_entero=0;
volatile uint8_t Temp_decimal=0;
volatile int8_t val=0;
volatile uint8_t terminado=0;
volatile uint8_t error=0;
volatile uint8_t suiche=1;



uint32_t leer()
{
	return GetPIN(SENSOR);
}

void levantar()
{
	SetPIN(SENSOR,1);
}

void bajar()
{
	SetPIN(SENSOR,0);
}

void transmision(uint8_t estado)
{
	SetPIN(SENSOR,estado);
	SetDIR(SENSOR, SALIDA);
	SetPINMODE_OUT(PIN_SENSOR, PUSH_PULL);
}

void recepcion()
{
	SetDIR(SENSOR, ENTRADA);
	SetPINMODE_IN(PIN_SENSOR,PULL_UP );
}

void inicializar_sensor()
{
	transmision(1);
	timer(2,coicidencia,segs);
}

void driver_sensor()
{
	volatile static uint8_t est=inicio,cambio=0;
	volatile uint8_t cuenta;

	if(error)
		while(1)
		{
			TimerEvent();
			mde_ledparpadeante_rojo();
		}


	display(Temp_entero,ROJO);
	display(TC,VERDE);

	switch(est)
	{
		case inicio:
			if(match_out&&!cambio&&suiche)
			{
				bajar();
				timer(18,coicidencia,mili);
				cambio=1;
			}
			if(match_out&&cambio==1)
			{
				levantar();
				timer(40,coicidencia,micro);
				cambio=2;
			}
			if(match_out&&cambio==2)
			{
				recepcion();
				cambio=0;
				est=respuesta;
				timer(0,captura,micro);
				flanco_descendente();
			}
			break;
		case respuesta:
			if(TC>=80)
				error=1;
			if(cap_out&&!cambio)
			{
				if(CR!=80)
				{
					error=1;
					suiche=0;
					cambio=0;
					est=inicio;
				}
				else
				{
					flanco_descendente();
					timer(0,captura,micro);
					cambio++;
				}
			}
			if(cap_out&&cambio)
			{
				if(CR!=80)
				{
					error=1;
					suiche=0;
					cambio=0;
					est=inicio;
				}
				else
				{
					cambio=0;
					terminado=0;
					est=recibiendo;
				}
			}
			break;
		case recibiendo:
			mde_recepcion();
			if(terminado)
			{
				transmision(1);
				est=confirmar;
			}
			break;
		case confirmar:
			cuenta=(Temp_entero+Temp_decimal+Humedad_entero+Humedad_decimal);
			if(val==cuenta)
			{
				timer(2,coicidencia,segs);
				est=inicio;
			}
			else
			{
				Temp_entero=0;
				Temp_decimal=0;
				Humedad_entero=0;
				Humedad_decimal=0;
				suiche=0;
				error=1;
				est=inicio;
			}
			break;
	}
}

void mde_recepcion()
{
	volatile static uint8_t est=parte1;

	if(error)
	{
		terminado=1;
		est=parte1;
	}

	switch(est)
	{
		case parte1:
			if(partes(0))
				est=parte2;
			break;
		case parte2:
			if(partes(1))
				est=parte3;
			break;
		case parte3:
			if(partes(2))
				est=parte4;
			break;
		case parte4:
			if(partes(3))
				est=validacion;
			break;
		case validacion:
			if(partes(4))
			{
				est=parte1;
				terminado=1;
			}
			break;
	}
}

uint8_t partes(uint8_t valor)
{
	volatile static uint8_t bits=0,comienzo=0,cambio=0;

	if(bits==8)
	{
		bits=0;
		return 1;
	}
	else
	{
		if(!leer()&&comienzo)
		{
			flanco_ascendente();
			timer(0,captura,micro);			//espero 50us
			comienzo++;
		}
		if(cap_out&&!cambio)
		{
			if(CR!=50||TC>50)
			{
				error=1;
				comienzo=1;
				return 1;
			}
			else
			{
				flanco_descendente();
				timer(0,captura,micro);
				cambio++;
				if(cap_out)
				{
					if(TC>28)
						error=1;
					if(CR>=26||CR<=28)
						bits++;
					else if(CR==70)
					{
						switch(valor)
						{
							case 0:
								Temp_entero|=(uint8_t)1<<bits;
								bits++;
								break;
							case 1:
								Temp_decimal|=(uint8_t)1<<bits;
								bits++;
								break;
							case 2:
								Humedad_entero|=(uint8_t)1<<bits;
								bits++;
								break;
							case 3:
								Humedad_decimal=(uint8_t)1<<bits;
								bits++;
								break;
							case 5:
								val=(uint8_t)1<<bits;
								bits++;
								break;
						}
					}
				}
			}
		}
	}
	return 0;
}



















uint8_t temp_entero()
{
	return Temp_entero;
}

uint8_t temp_decimal()
{
	return Temp_decimal;
}

uint8_t humedad_entero()
{
	return Humedad_entero;
}

uint8_t humedad_decimal()
{
	return Humedad_decimal;
}

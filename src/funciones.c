/*
 * funciones.c
 *
 *  Created on: 24 oct. 2022
 *      Author: foto
 */

#include "cabeza.h"


void buzzer_on()
{
	SetPIN(BUZZER,1);
}

void buzzer_off()
{
	SetPIN(BUZZER,0);
}

void rojo_on()
{
	SetPIN(LED_ROJO,0);
}

void rojo_off()
{
	SetPIN(LED_ROJO,1);
}

void toggle_verde()
{
	TogglePIN(LED_VERDE);
}

void verde_on()
{
	SetPIN(LED_VERDE,0);
}

void verde_off()
{
	SetPIN(LED_VERDE,1);
}

void azul_on()
{
	SetPIN(LED_AZUL,0);
}

void azul_off()
{
	SetPIN(LED_AZUL,1);
}

uint8_t boton_usr()
{
	return GetPIN(TECLA_USR);
}

void pin_on(uint32_t puer,uint32_t pin)
{
	SetPIN(puer,pin,1);
}

void pin_off(uint32_t puer,uint32_t pin)
{
	SetPIN(puer,pin,0);
}

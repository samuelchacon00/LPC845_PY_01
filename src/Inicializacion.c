/*
 * Inicializacion.c
 *
 *  Created on: 10 ene. 2022
 *      Author: gos
 */


#include "cabeza.h"

extern volatile uint32_t SystemCoreClock;;

/**
	\fn  	inicializacionTECLADO(void)
	\brief 	Inicializacion de los pines de TECLADO
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	void
 	\return void
*/


/**
	\fn  	void inicializacionGPIO(void)
	\brief 	Inicializacion de los pines de GPIO
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	void
 	\return void
*/
void inicializacionGPIO(void){
	SetPIN(LED_VERDE, 1);
	SetDIR(LED_VERDE, SALIDA);
	SetPINMODE_OUT(PIN_LED_VERDE, PUSH_PULL);

	SetPIN(LED_AZUL, 1);
	SetDIR(LED_AZUL, SALIDA);
	SetPINMODE_OUT(PIN_LED_AZUL, PUSH_PULL);

	SetPIN(LED_ROJO, 1);
	SetDIR(LED_ROJO, SALIDA);
	SetPINMODE_OUT(PIN_LED_ROJO, PUSH_PULL);

	SetPIN(EXT_LED, 1);
	SetDIR(EXT_LED, SALIDA);
	SetPINMODE_OUT(PIN_EXT_LED, PUSH_PULL);

	SetPIN(BUZZER, 1);
	SetDIR(BUZZER, SALIDA);
	SetPINMODE_OUT(PIN_BUZZER, PUSH_PULL);
	//SetDIR(TECLA_USR, ENTRADA);
	//SetPINMODE_IN(PIN_TECLA_USR, PULL_UP);

	//SetDIR(TECLA_ISP, ENTRADA);
	//SetPINMODE_IN(PIN_TECLA_ISP, PULL_UP);
}

/**
	\fn  	void inicializacionDISPLAY(void)
	\brief 	Inicializacion de los pines que controlan el display de 7 segmentos
 	\author Ing. Gabriel Soccodato
 	\date 	11 de Septiembre de 2022
 	\param 	void
 	\return void
*/
void inicializacionDISPLAY(void){
	SetPIN(BCD_A, 0);
	SetDIR(BCD_A, SALIDA);
	SetPINMODE_OUT(PIN_BCD_A, PUSH_PULL);

	SetPIN(BCD_B, 0);
	SetDIR(BCD_B, SALIDA);
	SetPINMODE_OUT(PIN_BCD_B, PUSH_PULL);

	SetPIN(BCD_C, 0);
	SetDIR(BCD_C, SALIDA);
	SetPINMODE_OUT(PIN_BCD_C, PUSH_PULL);

	SetPIN(BCD_D, 0);
	SetDIR(BCD_D, SALIDA);
	SetPINMODE_OUT(PIN_BCD_D, PUSH_PULL);

	SetPIN(BCD_RST, 0);
	SetDIR(BCD_RST, SALIDA);
	SetPINMODE_OUT(PIN_BCD_RST, PUSH_PULL);

	SetPIN(BCD_CK, 0);
	SetDIR(BCD_CK, SALIDA);
	SetPINMODE_OUT(PIN_BCD_CK, PUSH_PULL);

	//SetPIN(DP, 0);
	//SetDIR(DP, SALIDA);
	//SetPINMODE_OUT(PIN_DP, PUSH_PULL);
}

/**
	\fn  	void inicializacion(void)
	\brief 	Inicializacion del sistema
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	void
 	\return void
*/

void inicializacion(void)
{
	Inic_OSC();
	/** Habilita clock a P0 y P1 */
	SYSCON->SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK | SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK;

	inicializacionGPIO();
	InicializarTimers();
	inicializar_timer();
	//inicializar_sensor();
	//inicializar_patas();
	inicializacionDISPLAY();
	InicializarTeclado();

	SysTick_Config(SystemCoreClock/1000);
	inicializar_display_LCD();
}

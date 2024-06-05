/*
 * stick.h
 *
 *  Created on: 10 ene. 2022
 *      Author: gos
 */

#ifndef STICK_H_
#define STICK_H_

//#include <cabeza.h>

#define PIN_EXT_LED		IOCON_INDEX_PIO0_25

#define PIN_LED_VERDE	IOCON_INDEX_PIO1_0
#define PIN_LED_AZUL	IOCON_INDEX_PIO1_1
#define PIN_LED_ROJO	IOCON_INDEX_PIO1_2
#define PIN_TECLA_USR	IOCON_INDEX_PIO0_4
#define PIN_TECLA_ISP	IOCON_INDEX_PIO0_12
#define PIN_BUZZER		IOCON_INDEX_PIO0_29

#define PIN_FIL0		IOCON_INDEX_PIO0_8
#define PIN_FIL1		IOCON_INDEX_PIO0_31
#define PIN_FIL2		IOCON_INDEX_PIO0_30

#define PIN_COL0		IOCON_INDEX_PIO0_27
#define PIN_COL1		IOCON_INDEX_PIO0_28
//#define PIN_SENSOR		IOCON_INDEX_PIO0_4
#define PIN_SWCLK		IOCON_INDEX_PIO0_3
#define PIN_AN_OUT		IOCON_INDEX_PIO0_29
#define PIN_SWDIO		IOCON_INDEX_PIO0_2
#define PIN_AN_IN		IOCON_INDEX_PIO0_6
#define PIN_DIG_IN1		IOCON_INDEX_PIO0_26
#define PIN_OUT3		IOCON_INDEX_PIO0_1

/*#define PIN_D4			IOCON_INDEX_PIO0_9
#define PIN_D5			IOCON_INDEX_PIO0_10
#define PIN_D6			IOCON_INDEX_PIO0_11
#define PIN_D7			IOCON_INDEX_PIO0_13
#define PIN_E			IOCON_INDEX_PIO0_14
#define PIN_RS			IOCON_INDEX_PIO0_15
#define PIN_LED			IOCON_INDEX_PIO0_25*/

#define MSWITCH			IOCON_INDEX_PIO0_26

#define EXT_LED		0,25
#define LED_VERDE	1,0
#define LED_AZUL	1,1
#define LED_ROJO	1,2
#define	TECLA_USR	0,4
#define	TECLA_ISP	0,12
#define BUZZER 		0,29
#define DIGIN1		0,26

//#define SENSOR		0,2
#define SWCLK		0,3
#define AN_OUT 		0,29
#define SWDIO		0,2
#define AN_IN		0,6
#define DIG_IN1		0,26
#define OUT3		0,1

/*#define D4			0,9
#define D5			0,10
#define D6			0,11
#define D7			0,13
#define E			0,14
#define RS			0,15*/




#define LED_ROJO_ON		SetPIN(LED_ROJO,0)
#define LED_ROJO_OFF	SetPIN(LED_ROJO,1)
#define LED_ROJO_NOT	TogglePIN(LED_ROJO)

#define LEE_TECLA_USR	GetPIN(TECLA_USR)
#define LEE_TECLA_ISP	GetPIN(TECLA_ISP)

#endif /* STICK_H_ */

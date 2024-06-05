/*
 * sensor_dht11.h
 *
 *  Created on: 28 oct. 2022
 *      Author: foto
 */

#ifndef SENSOR_DHT11_H_
#define SENSOR_DHT11_H_

#define on			1
#define off			0

#define inicio		0
#define respuesta	1
#define recibiendo	2
#define parte1		3
#define parte2		4
#define parte3		5
#define parte4		6
#define validacion	7
#define confirmar	8

void driver_sensor();
uint32_t leer();
void levantar();
void bajar();
void transmision(uint8_t);
void recepcion();
void inicializar_sensor();
void driver_sensor();
void mde_recepcion();
uint8_t partes(uint8_t);

uint8_t temp_entero();
uint8_t temp_decimal();
uint8_t humedad_entero();
uint8_t humedad_decimal();

#endif /* SENSOR_DHT11_H_ */

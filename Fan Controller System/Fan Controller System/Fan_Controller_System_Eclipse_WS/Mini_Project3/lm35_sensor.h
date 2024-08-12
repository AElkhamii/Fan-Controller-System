/****************************************************************************************
 *
 * Module: LM35
 *
 * File Name: lm35.h
 *
 * Discretion: Header file for the AVR LM35 driver
 *
 * Author: Abdelrahman Ehab
 *
 ****************************************************************************************/

#ifndef LM35_H_
#define LM35_H_

/*******************************************************************************
 *                      		Include Header	                               *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                      		Definitions           	                 	   *
 *******************************************************************************/

#define SENSOR_CHANNEL_ID 				2

#define SENSOR_MAX_TEMPERATURE			150
#define SENSOR_MAX_VOLT_VALUE			1.5

/*******************************************************************************
 *                      	Function Definitions                               *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void);

#endif /* LM35_H_ */

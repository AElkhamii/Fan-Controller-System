/****************************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Discretion: Header file for the AVR ADC driver
 *
 * Author: Abdelrahman Ehab
 *
 ****************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/*******************************************************************************
 *                      		Include Header	                               *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56 /* CHANGED FROM 5 TO 2.56 */


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	VREF_OFF,VREF_EXTERNAL_CAPACITOR ,VREF_RESERVED, VREF_HALF_VALUE
}ADC_ReferenceVolatge;

typedef enum{
	F_CPU_2 = 1, F_CPU_4, F_CPU_8, F_CPU_16, F_CPU_32, F_CPU_64, F_CPU_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                      	Function Definitions                               *
 *******************************************************************************/
/*
 * Description:
 * This function start the ADC with prescaler equal to F_CPU/8
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description:
 * This function use polling to read the data from certain channel
 */
uint16 ADC_readChannel(uint8 pin_number);

#endif /* ADC_H_ */

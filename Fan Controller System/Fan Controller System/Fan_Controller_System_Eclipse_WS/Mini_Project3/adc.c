/****************************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Discretion: Source file for the AVR ADC driver
 *
 * Author: Abdelrahman Ehab
 *
 ****************************************************************************************/


#include "adc.h"
#include "common_macros.h"
#include "avr/io.h"

/*******************************************************************************
 *                    	    Functions Declaration                              *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{

	/*
	 * REFS0 & REFS1  (configured)
	 * ADLAR = 0 (no adjustment to the ADLAR 10-bit register)
	 * MUX = 0 no pin to read yet
	 */

	ADMUX = 0;
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt & 0x03)<<6);

	/*
	 * ADC enable (ADEN) = 1
	 * ADC interrupt enable (ADIE) = 0 & ADC interrupt flag (ADIF) = 0
	 * ADC auto trigger enable (ADATE) = 0
	 * Prescaller = F_CPU/8 (configured)
	 */
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler & 0x07);
	ADCSRA |= (1<<ADEN);
}

uint16 ADC_readChannel(uint8 pin_number)
{
	/*
	 * Activate a cretin ADC pin in last 5 bits
	 */
	ADMUX = (ADMUX & 0xE0) | (pin_number & 0x07); /* select the pin number */

	SET_BIT(ADCSRA,ADSC); /* Start conversation */

	while(BIT_IS_CLEAR(ADCSRA,ADIF)){} /* wait until the conversation is complete */

	SET_BIT(ADCSRA,ADIF); /* clear the flag by set 1 to it */
	return ADC;
}

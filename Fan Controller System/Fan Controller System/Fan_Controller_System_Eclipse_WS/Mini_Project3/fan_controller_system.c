/*
 ================================================================================================
 Name        : fan_controller_system.c
 Author      : Abdelrahman Ehab
 Description : A temperature-controlled fan using ATmega16 microcontroller, in which the fan is
 	 	 	   automatically turned ON or OFF according to the temperature.
 Date        : 11/1/2021
 ================================================================================================
 */

#include <avr/io.h>
#include "lcd.h"
#include "lm35_sensor.h"
#include "adc.h"
#include "dc_motor.h" /* PWM included inside dc_motor driver */


int main(void)
{
	volatile uint8 temp; /* Variable to hold temperature value */

	/* variable from ADC_ConfigType type to hold the values of prescaler and Reference voltage */
	ADC_ConfigType config;
	config.prescaler = F_CPU_8;
	config.ref_volt = VREF_HALF_VALUE;

	LCD_init(); /* Initialize LCD */
	ADC_init(&config); /* Initialize ADC */
	DcMotor_init(); /* Initialize DC-Motor */

	DcMotor_rotate(STOP,0); /* DC-Motor initial state */

	/* Always Display Fan is OFF in first row and display in the second row Temp =  C. */
	LCD_displayStringRowColumn(0,4,"FAN is");
	LCD_displayStringRowColumn(1,4,"Temp =    C");

	while(1)
	{
		/* LM35 temperature sensor will give continuous analog output corresponding to the temperature sensed by it. */
		LCD_moveCursor(1,11); /* To make sure the cursor start at the same place every loop to display the temperature value at the same place every time */
		temp = LM35_getTemperature();
		if(temp>=100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}


		/* Control the fan  based on the temperature value */
		if(temp < 30)
		{
			LCD_displayStringRowColumn(0, 4, "FAN is OFF");
			DcMotor_rotate(STOP,0);
		}
		else if((temp >= 30) && (temp < 60))
		{
			LCD_displayStringRowColumn(0, 4, "FAN is ON ");
			DcMotor_rotate(CW,25);
		}
		else if((temp >= 60) && (temp < 90))
		{
			LCD_displayStringRowColumn(0, 4, "FAN is ON ");
			DcMotor_rotate(CW,50);
		}
		else if((temp >= 90) && (temp < 120))
		{
			LCD_displayStringRowColumn(0, 4, "FAN is ON ");
			DcMotor_rotate(CW,75);
		}
		else if(temp >= 120)
		{
			LCD_displayStringRowColumn(0, 4, "FAN is ON ");
			DcMotor_rotate(CW,100);
		}
	}
}

/****************************************************************************************
 *
 * Module: DC-MOTOR
 *
 * File Name: dc_motor.c
 *
 * Discretion: Source file for the AVR DC-motor driver
 *
 * Author: Abdelrahman Ehab
 *
 ****************************************************************************************/

#include "dc_motor.h"
#include <avr/io.h>
#include "gpio.h"

/*******************************************************************************
 *                    	  	 Functions Prototype       		                   *
 *******************************************************************************/
static void PWM_Timer0_Start(uint8 duty_cycle);

/*******************************************************************************
 *                    	    Functions Declaration                              *
 *******************************************************************************/
/*
 * Description:
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_init(void)
{
	/* Select the pins that the motor are connected with */
	GPIO_setupPinDirection(DC_PORT_ID, DC_PINA_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_PORT_ID, DC_PINB_ID, PIN_OUTPUT);

	/* Initial condition to stop the motor */
	GPIO_writePin(DC_PORT_ID, DC_PINA_ID, LOGIC_LOW);
	GPIO_writePin(DC_PORT_ID, DC_PINB_ID, LOGIC_LOW);
}

/*
 * Description:
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 *  Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_rotate(DcMotor_State state,uint8 speed)
{

	PWM_Timer0_Start(speed); /* Adjust PWM according to the speed percentage the user want */

	/* State of the motor */
	if(state == STOP)
	{
		GPIO_writePin(DC_PORT_ID, DC_PINA_ID, LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID, DC_PINB_ID, LOGIC_LOW);
	}
	else if(state == CW)
	{
		GPIO_writePin(DC_PORT_ID, DC_PINA_ID, LOGIC_HIGH);
		GPIO_writePin(DC_PORT_ID, DC_PINB_ID, LOGIC_LOW);
	}
	else if(state == CCW)
	{
		GPIO_writePin(DC_PORT_ID, DC_PINA_ID, LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID, DC_PINB_ID, LOGIC_HIGH);
	}
}


static void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0; /* Initial value */

	OCR0 = 255 * (duty_cycle * 0.01); /* Set Compare value */

	DDRB = DDRB | (1<<PB3);
	/*
	 * FOC0 = 0 (because PWM is is used)
	 * COM00 = 0, COM01 = 1 (Non-inveting mode)
	 * CS00 =0 CS01 = 1 CS02 = 0 (F_CPU/8)
	 */
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
}

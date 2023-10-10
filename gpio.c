/*
 * gpio.c
 *
 *  Created on: Sep 29, 2023
 *      Author: omars
 */
#include "Atmega32_Reg_OS.h"
#include "Common_Macros_OS.h"
#include "gpio.h"

void GPIO_setupPinDirection (uint8 port_num,uint8 pin_num,GPIO_PinDirectionType direction){
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {

	} else {
		switch (port_num) {
		case PORTA_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRA_REG, pin_num);
			} else if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRA_REG, pin_num);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRB_REG, pin_num);
			} else if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRB_REG, pin_num);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRC_REG, pin_num);
			} else if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRC_REG, pin_num);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRD_REG, pin_num);
			} else if (direction == PIN_INPUT) {
				CLEAR_BIT(DDRD_REG, pin_num);
			}
			break;
		}
	}
}

void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value){
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {

		}
	else {
		switch(port_num){
		case PORTA_ID:
			if(value==HIGH){
				SET_BIT(PORTA_REG,pin_num);
			}
			else if(value==LOW){
				CLEAR_BIT(PORTA_REG,pin_num);
			}
			break;
		case PORTB_ID:
			if(value==HIGH){
				SET_BIT(PORTB_REG,pin_num);
			}
			else if(value==LOW){
				CLEAR_BIT(PORTB_REG,pin_num);
			}
			break;
		case PORTC_ID:
			if(value==HIGH){
				SET_BIT(PORTC_REG,pin_num);
			}
			else if(value==LOW){
				CLEAR_BIT(PORTC_REG,pin_num);
			}
			break;
		case PORTD_ID:
			if(value==HIGH){
				SET_BIT(PORTD_REG,pin_num);
			}
			else if(value==LOW){
				CLEAR_BIT(PORTD_REG,pin_num);
			}
			break;
		}
	}
}

uint8 GPIO_readPin(uint8 port_num,uint8 pin_num){
	uint8 returnValue=LOW;
	if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {

			}
		else {
		switch (port_num) {
		case PORTA_ID:
			returnValue = GET_BIT(PINA_REG, pin_num);
			break;
		case PORTB_ID:
			returnValue = GET_BIT(PINB_REG, pin_num);
			break;
		case PORTC_ID:
			returnValue = GET_BIT(PINC_REG, pin_num);
			break;
		case PORTD_ID:
			returnValue = GET_BIT(PIND_REG, pin_num);
			break;
		}

		}
	return returnValue;
}

void GPIO_setupPortDirection(uint8 port_num,GPIO_PortDirectionType direction){
	if (port_num >= NUM_OF_PORTS) {

	}
	else{
		switch (port_num) {
		case PORTA_ID:
			DDRA_REG = direction;
			break;
		case PORTB_ID:
			DDRB_REG = direction;
			break;
		case PORTC_ID:
			DDRC_REG = direction;
			break;
		case PORTD_ID:
			DDRD_REG = direction;
			break;
		}
	}
}

void GPIO_writePort(uint8 port_num,uint8 value){
	if (port_num >= NUM_OF_PORTS) {

		}
		else {
		switch (port_num) {
		case PORTA_ID:
			PORTA_REG = value;
			break;
		case PORTB_ID:
			PORTB_REG = value;
			break;
		case PORTC_ID:
			PORTC_REG = value;
			break;
		case PORTD_ID:
			PORTD_REG = value;
			break;
			}
		}
}

uint8 GPIO_readPort(uint8 port_num){
	uint8 returnValue=LOW;
	if (port_num >= NUM_OF_PORTS) {

			}
			else {
		switch (port_num) {
		case PORTA_ID:
			returnValue = PINA_REG;
			break;
		case PORTB_ID:
			returnValue = PINB_REG;
			break;
		case PORTC_ID:
			returnValue = PINC_REG;
			break;
		case PORTD_ID:
			returnValue = PIND_REG;
			break;
				}
			}
	return returnValue;
}


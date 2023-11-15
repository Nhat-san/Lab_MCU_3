/*
 * port.h
 *
 *  Created on: Nov 1, 2023
 *      Author: huaho
 */

#ifndef INC_PORT_H_
#define INC_PORT_H_

#include "stm32f1xx_hal.h"

/* Define button input */
#define BUTTON1_PORT 	GPIOA
#define BUTTON1_PIN 	GPIO_PIN_7
#define BUTTON2_PORT 	GPIOA
#define BUTTON2_PIN 	GPIO_PIN_8
#define BUTTON3_PORT 	GPIOA
#define BUTTON3_PIN 	GPIO_PIN_9

/* Define output */
	/* Define Blink Led */
#define BLINK_LED_PORT 	GPIOC
#define BLINK_LED		GPIO_PIN_13

	/* Define traffic light */
#define TL_PORT			GPIOA
	//WEST AND EAST
#define WE_RED			GPIO_PIN_1
#define WE_AMBER		GPIO_PIN_2
#define WE_GREEN		GPIO_PIN_3
	//NORTH AND SOUTH
#define NS_RED			GPIO_PIN_4
#define NS_AMBER		GPIO_PIN_5
#define NS_GREEN		GPIO_PIN_6

	/* Define 7 segs led */
#define SEG7_PORT 		GPIOB
#define SEG_A 			GPIO_PIN_0
#define SEG_B 			GPIO_PIN_1
#define SEG_C 			GPIO_PIN_12
#define SEG_D 			GPIO_PIN_13
#define SEG_E 			GPIO_PIN_14
#define SEG_F 			GPIO_PIN_5
#define SEG_G 			GPIO_PIN_6
#define SELECT_SEG1 	GPIO_PIN_7
#define SELECT_SEG2 	GPIO_PIN_8
#define SELECT_SEG3 	GPIO_PIN_9
#define SELECT_SEG4 	GPIO_PIN_10

#endif /* INC_PORT_H_ */

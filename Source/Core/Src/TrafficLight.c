/*
 * TrafficLight.c
 *
 *  Created on: Nov 12, 2023
 *      Author: huaho
 */
#include "TrafficLight.h"

enum st traffic_light_state = REDWE_GREENNS;

void traffic_light(){
	switch (traffic_light_state) {
		case REDWE_GREENNS:
			HAL_GPIO_WritePin(TL_PORT, WE_AMBER, 1);
			HAL_GPIO_WritePin(TL_PORT, WE_RED, 0);
			HAL_GPIO_WritePin(TL_PORT, NS_RED, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_GREEN, 0);
			break;
		case REDWE_AMBERNS:
			HAL_GPIO_WritePin(TL_PORT, NS_GREEN, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_AMBER, 0);
			break;
		case GREENWE_REDNS:
			HAL_GPIO_WritePin(TL_PORT, WE_RED, 1);
			HAL_GPIO_WritePin(TL_PORT, WE_GREEN, 0);
			HAL_GPIO_WritePin(TL_PORT, NS_AMBER, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_RED, 0);
			break;
		case AMBERWE_REDNS:
			HAL_GPIO_WritePin(TL_PORT, WE_GREEN, 1);
			HAL_GPIO_WritePin(TL_PORT, WE_AMBER, 0);
			break;
		case INVALID:
			HAL_GPIO_WritePin(TL_PORT, WE_RED, 0);
			HAL_GPIO_WritePin(TL_PORT, WE_AMBER, 0);
			HAL_GPIO_WritePin(TL_PORT, WE_GREEN, 0);
			HAL_GPIO_WritePin(TL_PORT, NS_RED, 0);
			HAL_GPIO_WritePin(TL_PORT, NS_AMBER, 0);
			HAL_GPIO_WritePin(TL_PORT, NS_GREEN, 0);
		default:
			break;
	}
}


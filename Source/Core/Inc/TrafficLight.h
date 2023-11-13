/*
 * trafficlight.h
 *
 *  Created on: Nov 12, 2023
 *      Author: huaho
 */

#ifndef INC_TRAFFICLIGHT_H_
#define INC_TRAFFICLIGHT_H_

#include <stdint.h>
#include "port.h"

extern enum st{
	REDWE_GREENNS, REDWE_AMBERNS, GREENWE_REDNS, AMBERWE_REDNS, INVALID
} traffic_light_state;
void traffic_light();

#endif /* INC_TRAFFICLIGHT_H_ */

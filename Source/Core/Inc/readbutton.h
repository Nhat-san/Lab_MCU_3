/*
 * readbutton.h
 *
 *  Created on: Nov 1, 2023
 *      Author: huaho
 */

#ifndef INC_READBUTTON_H_
#define INC_READBUTTON_H_

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "port.h"

void initButton();
void read_button();
uint8_t is_button_pressed(uint8_t i);
uint8_t is_button_long_pressed(uint8_t i);

#endif /* INC_READBUTTON_H_ */

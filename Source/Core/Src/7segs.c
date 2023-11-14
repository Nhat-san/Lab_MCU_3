/*
 * display7seg.c
 *
 *  Created on: Nov 5, 2023
 *      Author: huaho
 */

#include "7segs.h"

#define NUM_7SEG 4
int led_buffer[NUM_7SEG] = { 9, 8, 7, 6 };

void update7SegBuffer(int val1, int val2) {
	if (val1 < 0 || val1 > 99 || val2 < 0 || val2 > 99)
		return;
	led_buffer[0] = val1 / 10;
	led_buffer[1] = val1 % 10;
	led_buffer[2] = val2 / 10;
	led_buffer[3] = val2 % 10;
}
//function to turn off all 7 segments led
void OffAll_7Seg(void) {
	HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG1, 1);
	HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG2, 1);
	HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG3, 1);
	HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG4, 1);
}

/*Function to display num on 7 segments led
 *Because pullup so 0 is on, 1 is off
 */
void display7SEG(uint8_t num) {
	if (num == 1) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 0);

	} else if (num == 2) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 1);
	} else if (num == 3) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 1);
	} else if (num == 4) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 1);
	} else if (num == 5) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 1);
	} else if (num == 6) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 1);
	} else if (num == 7) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 0);
	} else if (num == 8) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 1);
	} else if (num == 9) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 1);
	} else if (num == 0) {
		HAL_GPIO_WritePin(SEG7_PORT, SEG_A, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_B, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_C, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_D, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_E, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_F, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SEG_G, 0);
	}
}

//Function to scan 7 seg led
void update7SEG(uint8_t index) {
	switch (index) {
	case 0:
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG1, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG2, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG3, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG4, 0);
		display7SEG(led_buffer[3]);
		break;
	case 1:
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG1, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG2, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG3, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG4, 1);
		display7SEG(led_buffer[2]);
		break;
	case 2:
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG1, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG2, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG3, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG4, 1);
		display7SEG(led_buffer[1]);
		break;
	case 3:
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG1, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG2, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG3, 1);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG4, 1);
		display7SEG(led_buffer[0]);
		break;
	default:
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG1, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG2, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG3, 0);
		HAL_GPIO_WritePin(SEG7_PORT, SELECT_SEG4, 0);
		break;
	}
}

/*
 * display7seg.c
 *
 *  Created on: Nov 5, 2023
 *      Author: huaho
 */
#include "display7seg.h"

#define NUM_7SEG 4
uint8_t led_buffer[NUM_7SEG] = {7,4,8,0};

//function to turn off all 7 segments led
void OffAll_7Seg(void) {
	uint16_t pin = SEG7_1 | SEG7_2 | SEG7_3 | SEG7_4;
	HAL_GPIO_WritePin(led.port, pin, 1);
}

//Function to display num on 7 segments led
void display7SEG(uint8_t num) {
	if (num == 1) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_SET);
	} else if (num == 2) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_RESET);
	} else if (num == 3) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_RESET);
	} else if (num == 4) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_RESET);
	} else if (num == 5) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_RESET);
	} else if (num == 6) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_RESET);
	} else if (num == 7) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_SET);
	} else if (num == 8) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_RESET);
	} else if (num == 9) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_RESET);
	} else if (num == 0) {
		HAL_GPIO_WritePin(SegA_GPIO_Port, SegA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegB_GPIO_Port, SegB_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegC_GPIO_Port, SegC_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegD_GPIO_Port, SegD_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegE_GPIO_Port, SegE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegF_GPIO_Port, SegF_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SegG_GPIO_Port, SegG_Pin, GPIO_PIN_SET);
	}
}

//Function to quét 7 seg led
void update7SEG(uint8_t index) {
	switch (index) {
	case 0:
		HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, GPIO_PIN_RESET);
		display7SEG(led_buffer[3]);
		break;
	case 1:
		HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[2]);
		break;
	case 2:
		HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[1]);
		break;
	case 3:
		HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[0]);
		break;
	default:
		HAL_GPIO_WritePin(en0_GPIO_Port, en0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(en1_GPIO_Port, en1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(en2_GPIO_Port, en2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(en3_GPIO_Port, en3_Pin, GPIO_PIN_RESET);
		break;
	}
}

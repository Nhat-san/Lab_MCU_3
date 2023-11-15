/*
 * readbutton.c
 *
 *  Created on: Nov 1, 2023
 *      Author: huaho
 */
#include "readbutton.h"
//num of button
#define NUM_BUTTON 3
//pressed button more than 1 sec
#define LONG_PRESSED_TIME 150
//
#define PRESSED 0
//
#define RELEASED 1
//
struct button {
	uint8_t debounce[4];
	bool is_pressed;
	bool is_long_pressed;
	uint16_t TimePress;
} MyButton[NUM_BUTTON];

void initButton() {
	for (uint8_t i = 0; i < NUM_BUTTON; i++) {
		MyButton[i].debounce[0] = RELEASED;
		MyButton[i].debounce[1] = RELEASED;
		MyButton[i].debounce[2] = RELEASED;
		MyButton[i].debounce[3] = RELEASED;
		MyButton[i].is_pressed = 0;
		MyButton[i].is_long_pressed = 0;
		MyButton[i].TimePress = LONG_PRESSED_TIME;
	}
}

void read_button() {
	for (uint8_t i = 0; i < NUM_BUTTON; i++) {
		MyButton[i].debounce[3] = MyButton[i].debounce[2];
		MyButton[i].debounce[2] = MyButton[i].debounce[1];
		MyButton[i].debounce[1] = MyButton[i].debounce[0];
		if (i == 0) {
			MyButton[i].debounce[0] = HAL_GPIO_ReadPin(BUTTON1_PORT,
			BUTTON1_PIN);
		} else if (i == 1) {
			MyButton[i].debounce[0] = HAL_GPIO_ReadPin(BUTTON2_PORT,
			BUTTON2_PIN);
		} else if (i == 2) {
			MyButton[i].debounce[0] = HAL_GPIO_ReadPin(BUTTON3_PORT,
			BUTTON3_PIN);
		}
		if (MyButton[i].debounce[3] == MyButton[i].debounce[2]
				&& MyButton[i].debounce[2] == MyButton[i].debounce[1]
				&& MyButton[i].debounce[1] == MyButton[i].debounce[0]) {
			if (MyButton[i].debounce[0] == PRESSED) {
				MyButton[i].is_pressed = 1;
				if (MyButton[i].TimePress > 0) {
					MyButton[i].TimePress--;
				} else {
					MyButton[i].is_long_pressed = 1;
				}
			} else {
				MyButton[i].TimePress = LONG_PRESSED_TIME;
				MyButton[i].is_pressed = 0;
				MyButton[i].is_long_pressed = 0;
			}
		}
	}
}

uint8_t is_button_pressed(uint8_t i) {
	if (i >= NUM_BUTTON)
		return 0xff;
	return MyButton[i].is_pressed;
}
uint8_t is_button_long_pressed(uint8_t i) {
	if (i >= NUM_BUTTON)
		return 0xff;
	return MyButton[i].is_long_pressed;
}

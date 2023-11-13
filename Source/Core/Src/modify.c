/*
 * modify.c
 *
 *  Created on: Nov 13, 2023
 *      Author: huaho
 */
#include "modify.h"

/*
 * State machine mode
 */
enum {
	NORMAL,
	RED_MODIFY,
	AMBER_MODIFY,
	GREEN_MODIFY,
	RED_INCREASE_1,
	AMBER_INCREASE_1,
	GREEN_INCREASE_1,
	RED_SET,
	AMBER_SET,
	GREEN_SET,
	RED_OVERTIME,
	AMBER_OVERTIME,
	GREEN_OVERTIME
} TrafficState = NORMAL;

enum {
	PRESSED, RELEASE
} buttonState[3];

enum {
	NOTCHANGING, CHANGING
} is_changing[3];

#define REDTIME 5
#define AMBERTIME 2

int i = 3;
uint8_t timeWE = REDTIME;
uint8_t timeNS = AMBERTIME;
uint8_t RedTime = REDTIME;
uint8_t RedTimeBuffer = REDTIME;
uint8_t AmberTime = AMBERTIME;
uint8_t AmberTimeBuffer = AMBERTIME;
uint8_t GreenTime = REDTIME - AMBERTIME;
uint8_t GreenTimeBuffer = REDTIME - AMBERTIME;
bool is_blink_led = 0;
bool button_press = 0;

void TrafficLightFSM();
void button0();
void button1();
void button2();
void led2Hz();

void ControlTraffic() {
	if (!timerOn(1)) {
		if (TrafficState == NORMAL && RedTime != AmberTime + GreenTime) {
			traffic_light_state = INVALID;
			OffAll_7Seg();
		} else {
			//Scan 7segs led
			update7SEG(i--);
			if (i < 0) {
				i = 3;
			}
			setTimer(1, 1);
		}
	}
	switch (TrafficState) {
	case NORMAL:
		if (TrafficState == NORMAL && RedTime != AmberTime + GreenTime) {
			traffic_light_state = INVALID;
			OffAll_7Seg();
		} else {
			TrafficLightFSM();
		}
		//button 0
		button0();
		break;
		//Modify red
	case RED_MODIFY:
		if (is_changing[0] == NOTCHANGING) {
			RedTimeBuffer = RedTime;
		}
		// display the value and mode
		update7SegBuffer(RedTimeBuffer, 2);
		//led 2Hz
		led2Hz();
		//button 0
		button0();
		//button 1
		button1();
		//buton 2
		button2();
		break;
	case RED_INCREASE_1:
		RedTimeBuffer++;
		if (RedTimeBuffer > 99) {
			RedTimeBuffer = 0;
		}
		is_changing[0] = CHANGING;
		TrafficState = RED_MODIFY;
		break;
	case RED_OVERTIME:
		// display the value and mode
		update7SegBuffer(RedTimeBuffer, 2);
		if (!timerOn(4)) {
			RedTimeBuffer++;
			if (RedTimeBuffer > 99) {
				RedTimeBuffer = 0;
			}
			setTimer(4, 500);
		}
		//buton1
		button1();
		break;
	case RED_SET:
		RedTime = RedTimeBuffer;
		is_changing[0] = NOTCHANGING;
		TrafficState = RED_MODIFY;
		break;

		//Modify Amber
	case AMBER_MODIFY:
		if (is_changing[1] == NOTCHANGING) {
			AmberTimeBuffer = AmberTime;
		}
		// display the value and mode
		update7SegBuffer(AmberTimeBuffer, 3);
		//led 2Hz
		led2Hz();
		//button 0
		button0();
		//button 1
		button1();
		//buton 2
		button2();
		break;
	case AMBER_INCREASE_1:
		AmberTimeBuffer++;
		if (AmberTimeBuffer > 99) {
			AmberTimeBuffer = 0;
		}
		is_changing[1] = CHANGING;
		TrafficState = AMBER_MODIFY;
		break;
	case AMBER_OVERTIME:
		// display the value and mode
		update7SegBuffer(AmberTimeBuffer, 3);
		if (!timerOn(4)) {
			AmberTimeBuffer++;
			if (AmberTimeBuffer > 99) {
				AmberTimeBuffer = 0;
			}
			setTimer(4, 500);
		}
		//buton1
		button1();
		break;
	case AMBER_SET:

		AmberTime = AmberTimeBuffer;

		is_changing[1] = NOTCHANGING;
		TrafficState = AMBER_MODIFY;
		break;

		//Modify green
	case GREEN_MODIFY:
		if (is_changing[2] == NOTCHANGING) {
			GreenTimeBuffer = GreenTime;
		}
		// display the value and mode
		update7SegBuffer(GreenTimeBuffer, 4);
		//led 2Hz
		led2Hz();
		//button 0
		button0();
		//button 1
		button1();
		//buton 2
		button2();
		break;
	case GREEN_INCREASE_1:
		GreenTimeBuffer++;
		if (GreenTimeBuffer > 99) {
			GreenTimeBuffer = 0;
		}
		is_changing[2] = CHANGING;
		TrafficState = GREEN_MODIFY;
		break;
	case GREEN_OVERTIME:
		// display the value and mode
		update7SegBuffer(GreenTimeBuffer, 2);
		if (!timerOn(4)) {
			GreenTimeBuffer++;
			if (GreenTimeBuffer > 99) {
				GreenTimeBuffer = 0;
			}
			setTimer(4, 500);
		}
		//buton1
		button1();
		break;
	case GREEN_SET:
		GreenTime = GreenTimeBuffer;
		is_changing[2] = NOTCHANGING;
		TrafficState = GREEN_MODIFY;
		break;
	default:
		break;
	}
}

void TrafficLightFSM() {
	if (!timerOn(2)) {
		setTimer(2, 1000);
		traffic_light();
		update7SegBuffer(timeWE--, timeNS--);
		switch (traffic_light_state) {
		case REDWE_GREENNS:
			if (timeNS <= 0) {
				traffic_light_state = REDWE_AMBERNS;
				timeNS = AmberTime;
			}
			break;
		case REDWE_AMBERNS:
			if (timeNS <= 0) {
				traffic_light_state = GREENWE_REDNS;
				timeWE = GreenTime;
				timeNS = RedTime;
			}
		case GREENWE_REDNS:
			if (timeWE <= 0) {
				traffic_light_state = AMBERWE_REDNS;
				timeWE = AmberTime;
			}
		case AMBERWE_REDNS:
			if (timeWE <= 0) {
				traffic_light_state = REDWE_GREENNS;
				timeWE = RedTime;
				timeNS = GreenTime;
			}
		default:
			break;
		}
	}
}

void button0() {
	switch (buttonState[0]) {
	case RELEASE:
		if (is_button_pressed(0)) {
			switch (TrafficState) {
			case NORMAL:
				TrafficState = RED_MODIFY;
				break;
			case RED_MODIFY:
				is_changing[0] = NOTCHANGING;
				TrafficState = AMBER_MODIFY;
				break;
			case AMBER_MODIFY:
				is_changing[1] = NOTCHANGING;
				TrafficState = GREEN_MODIFY;
				break;
			case GREEN_MODIFY:
				is_changing[2] = NOTCHANGING;
				TrafficState = NORMAL;
				break;
			default:
				break;
			}
			buttonState[0] = PRESSED;
			traffic_light_state = REDWE_GREENNS;
		} else {
			break;
		}
		break;
	case PRESSED:
		if (!is_button_pressed(0)) {
			buttonState[0] = RELEASE;
		}
		break;
	default:
		break;
	}
	return;
}

void button1() {
	switch (buttonState[1]) {
	case RELEASE:
		if (is_button_pressed(1)) {
			switch (TrafficState) {
			case RED_MODIFY:
				TrafficState = RED_INCREASE_1;
				break;
			case AMBER_MODIFY:
				TrafficState = AMBER_INCREASE_1;
				break;
			case GREEN_MODIFY:
				TrafficState = GREEN_INCREASE_1;
				break;
			default:
				break;
			}
			buttonState[1] = PRESSED;
		} else {
			break;
		}
		break;
	case PRESSED:
		if (!is_button_pressed(1)) {
			buttonState[1] = RELEASE;
		}
		break;
	default:
		break;
	}
}

void button2() {
	switch (buttonState[2]) {
	case RELEASE:
		if (is_button_pressed(2)) {
			switch (TrafficState) {
			case RED_MODIFY:
				TrafficState = RED_SET;
				break;
			case AMBER_MODIFY:
				TrafficState = AMBER_SET;
				break;
			case GREEN_MODIFY:
				TrafficState = GREEN_SET;
				break;
			default:
				break;
			}
			buttonState[2] = PRESSED;
		} else {
			break;;
		}
		break;
	case PRESSED:
		if (!is_button_pressed(2)) {
			buttonState[2] = RELEASE;
		}
		break;
	default:
		break;
	}
	return;
}

void led2Hz() {
	if (is_blink_led) {
		switch (TrafficState) {
		case RED_MODIFY:
			HAL_GPIO_WritePin(TL_PORT, WE_RED, 0);
			HAL_GPIO_WritePin(TL_PORT, NS_RED, 0);
			HAL_GPIO_WritePin(TL_PORT, WE_AMBER, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_AMBER, 1);
			HAL_GPIO_WritePin(TL_PORT, WE_GREEN, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_GREEN, 1);
			break;
		case AMBER_MODIFY:
			HAL_GPIO_WritePin(TL_PORT, WE_RED, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_RED, 1);
			HAL_GPIO_WritePin(TL_PORT, WE_AMBER, 0);
			HAL_GPIO_WritePin(TL_PORT, NS_AMBER, 0);
			HAL_GPIO_WritePin(TL_PORT, WE_GREEN, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_GREEN, 1);
			break;
		case GREEN_MODIFY:
			HAL_GPIO_WritePin(TL_PORT, WE_RED, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_RED, 1);
			HAL_GPIO_WritePin(TL_PORT, WE_AMBER, 1);
			HAL_GPIO_WritePin(TL_PORT, NS_AMBER, 1);
			HAL_GPIO_WritePin(TL_PORT, WE_GREEN, 0);
			HAL_GPIO_WritePin(TL_PORT, NS_GREEN, 0);
			break;
		default:
			break;
		}
		if (!timerOn(0)) {
			setTimer(0, TIME_BLINK_LED);
			is_blink_led = 0;
		}
	} else {
		HAL_GPIO_WritePin(TL_PORT, WE_RED, 1);
		HAL_GPIO_WritePin(TL_PORT, NS_RED, 1);
		HAL_GPIO_WritePin(TL_PORT, WE_AMBER, 1);
		HAL_GPIO_WritePin(TL_PORT, NS_AMBER, 1);
		HAL_GPIO_WritePin(TL_PORT, WE_GREEN, 1);
		HAL_GPIO_WritePin(TL_PORT, NS_GREEN, 1);
		if (!timerOn(0)) {
			setTimer(0, TIME_BLINK_LED);
			is_blink_led = 1;
		}
	}
}

/*
 * modify.c
 *
 *  Created on: Nov 3, 2023
 *      Author: huaho
 */
/* Includes ------------------------------------------------------------------*/
#include "modify.h"

/*
 * MAIN STATE
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

/*
 * The current state of button
 */
enum {
	PRESSED, RELEASE, LONGPRESSED
} buttonState[3];

/*
 * State for assign again time to timebuffer when you in modify mode
 */
enum {
	NOTCHANGING, CHANGING
} is_changing[3];

/* Define---------------------------------------------------------------------*/
#define REDTIME 5
#define AMBERTIME 2

/* Variable-------------------------------------------------------------------*/
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

void TrafficLightFSM();
void button0();
void button1();
void button2();
void led2Hz();

/*Function for main state machine---------------------------------------------*/
void ControlTraffic() {
	/*Scan 7segs led for every TIME_BLINK_LED time----------------------------*/
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
		}
		setTimer(1, TIME_SCAN_7SEG);
	}
	/*main state machine*/
	switch (TrafficState) {
	case NORMAL:
		/* check if time changed is valid */
		if (RedTime != AmberTime + GreenTime) {
			traffic_light_state = INVALID;
		} else {
			TrafficLightFSM();
		}
		//button 0
		button0();
		break;
	/* Modify red begin--------------------------------*/
	case RED_MODIFY:
		if (is_changing[0] == NOTCHANGING) {
			RedTimeBuffer = RedTime;
		}
		// display the value and mode
		update7SegBuffer(RedTimeBuffer, 2);
		//Blink single Led 2Hz
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
		is_changing[0] = CHANGING;
		//buton1
		button1();
		break;
	case RED_SET:/* Set the value for Red*/
		RedTime = RedTimeBuffer;
		is_changing[0] = NOTCHANGING;
		TrafficState = RED_MODIFY;
		break;
	/* Modify red end----------------------------------*/

	/* Modify Amber begin------------------------------*/
	case AMBER_MODIFY:
		if (is_changing[1] == NOTCHANGING) {
			AmberTimeBuffer = AmberTime;
		}
		// display the value and mode
		update7SegBuffer(AmberTimeBuffer, 3);
		//Blink single Led 2Hz
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
		is_changing[1] = CHANGING;
		//buton1
		button1();
		break;
	case AMBER_SET:/* Set the value for Amber*/
		AmberTime = AmberTimeBuffer;
		is_changing[1] = NOTCHANGING;
		TrafficState = AMBER_MODIFY;
		break;
	/* Modify Amber end--------------------------------*/

	/* Modify Green begin------------------------------*/
	case GREEN_MODIFY:
		if (is_changing[2] == NOTCHANGING) {
			GreenTimeBuffer = GreenTime;
		}
		// display the value and mode
		update7SegBuffer(GreenTimeBuffer, 4);
		//Blink single Led 2Hz
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
		update7SegBuffer(GreenTimeBuffer, 4);
		if (!timerOn(4)) {
			GreenTimeBuffer++;
			if (GreenTimeBuffer > 99) {
				GreenTimeBuffer = 0;
			}
			setTimer(4, 500);
		}
		is_changing[2] = CHANGING;
		//buton1
		button1();
		break;
	case GREEN_SET:/* Set the value for Green*/
		GreenTime = GreenTimeBuffer;
		is_changing[2] = NOTCHANGING;
		TrafficState = GREEN_MODIFY;
		break;
	/* Modify Green end--------------------------------*/
	default:
		break;
	}
}

/*
 *	FSM to control the Traffic display.
 *	WE is West East, NS is North South
 */
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
			break;
		case GREENWE_REDNS:
			if (timeWE <= 0) {
				traffic_light_state = AMBERWE_REDNS;
				timeWE = AmberTime;
			}
			break;
		case AMBERWE_REDNS:
			if (timeWE <= 0) {
				traffic_light_state = REDWE_GREENNS;
				timeWE = RedTime;
				timeNS = GreenTime;
			}
			break;
		case INVALID:
			traffic_light_state = INVALID;
			break;
		default:
			break;
		}
	}
}

/*
 * Funtion for change state modify when pressed first button (button0)
 */
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

/*
 * Funtion for increase value when pressed second button (button1)
 */
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
		} else if (is_button_long_pressed(1)) {
			buttonState[1] = LONGPRESSED;
		}
		break;
	case LONGPRESSED:
		switch (TrafficState) {
		case RED_MODIFY:
			TrafficState = RED_OVERTIME;
			break;
		case AMBER_MODIFY:
			TrafficState = AMBER_OVERTIME;
			break;
		case GREEN_MODIFY:
			TrafficState = GREEN_OVERTIME;
			break;
		default:
			break;
		}
		/*Release button*/
		if (!is_button_pressed(1)) {
			switch (TrafficState) {
				case RED_OVERTIME:
					TrafficState = RED_MODIFY;
					is_changing[0] = NOTCHANGING;
					break;
				case AMBER_OVERTIME:
					TrafficState = AMBER_MODIFY;
					is_changing[1] = NOTCHANGING;
					break;
				case GREEN_OVERTIME:
					TrafficState = GREEN_MODIFY;
					is_changing[2] = NOTCHANGING;
					break;
				default:
					break;
			}
			buttonState[1] = RELEASE;
		}
		break;
	default:
		break;
	}
}

/*
 * Funtion for set value when pressed third button (button2)
 */
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

/*
 * Funtion for Blink led in modify mode
 */
void led2Hz() {
	if (is_blink_led) {
		/*Blink PC13 Led*/
		HAL_GPIO_TogglePin(BLINK_LED_PORT, BLINK_LED);

		/*Toggle traffic light*/
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
		/*BLink PC13 led*/
		HAL_GPIO_TogglePin(BLINK_LED_PORT, BLINK_LED);
		/*turn off traffic light*/
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

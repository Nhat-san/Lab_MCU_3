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

int i = 3;
uint8_t timeWE = 5;
uint8_t timeNS = 3;
uint8_t RedTime;
uint8_t RedTimeBuffer;
uint8_t AmberTime;
uint8_t AmberTimeBuffer;
uint8_t GreenTime;
uint8_t GreenTimeBuffer;

void TrafficLightFSM();
void button0();
void button1();

void ControlTraffic() {
	if (!timerOn(1)) {
		if (TrafficState == NORMAL
				&& RedTimeBuffer != AmberTimeBuffer + GreenTimeBuffer) {
			traffic_light_state == INVALID;
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
		if (TrafficState == NORMAL
				&& RedTimeBuffer != AmberTimeBuffer + GreenTimeBuffer) {
			traffic_light_state == INVALID;
		} else {
			TrafficLightFSM();
		}
		//button 0
		button0();
		break;
		//Modify red
	case RED_MODIFY:
		RedTimeBuffer = RedTime;
		// display the value and mode
		update7SegBuffer(RedTimeBuffer, 2);
		//led 2Hz
		//button 0
		button0();
		//button 1
		button1();
		//buton 2
		break;
	case RED_INCREASE_1:
		RedTimeBuffer++;
		if (RedTimeBuffer > 99) {
			RedTimeBuffer = 0;
		}
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

		//Modify Amber
	case AMBER_MODIFY:
		AmberTimeBuffer = AmberTime;
		// display the value and mode
		update7SegBuffer(AmberTimeBuffer, 2);
		//led 2Hz
		//button 0
		button0();
		//button 1
		button1();
		//buton 2
		break;
	case AMBER_INCREASE_1:
		AmberTimeBuffer++;
		if (AmberTimeBuffer > 99) {
			AmberTimeBuffer = 0;
		}
		TrafficState = AMBER_MODIFY;
		break;
	case AMBER_OVERTIME:
		// display the value and mode
		update7SegBuffer(AmberTimeBuffer, 2);
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

		//Modify red
	case GREEN_MODIFY:
		GreenTimeBuffer = GreenTime;
		// display the value and mode
		update7SegBuffer(GreenTimeBuffer, 2);
		//led 2Hz
		//button 0
		button0();
		//button 1
		button1();
		//buton 2
		break;
	case GREEN_INCREASE_1:
		GreenTimeBuffer++;
		if (GreenTimeBuffer > 99) {
			GreenTimeBuffer = 0;
		}
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
				timeNS = 2;
			}
			break;
		case REDWE_AMBERNS:
			if (timeNS <= 0) {
				traffic_light_state = GREENWE_REDNS;
				timeWE = 3;
				timeNS = 5;
			}
		case GREENWE_REDNS:
			if (timeWE <= 0) {
				traffic_light_state = AMBERWE_REDNS;
				timeWE = 2;
			}
		case AMBERWE_REDNS:
			if (timeWE <= 0) {
				traffic_light_state = REDWE_GREENNS;
				timeWE = 5;
				timeNS = 3;
			}
		default:
			break;
		}
	}
}

void button0() {
	if (is_button_pressed(0)) {
		switch (TrafficState) {
		case NORMAL:
			TrafficState = RED_MODIFY;
			break;
		case RED_MODIFY:
			TrafficState = AMBER_MODIFY;
			break;
		case AMBER_MODIFY:
			TrafficState = GREEN_MODIFY;
			break;
		case GREEN_MODIFY:
			TrafficState = NORMAL;
			break;
		default:
			break;
		}
	} else {
		return;
	}
}

void button1() {
	if (is_button_long_pressed(1)) {
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
	} else if (is_button_pressed(1)) {
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
	} else {
		switch (TrafficState) {
		case RED_OVERTIME:
			TrafficState = RED_MODIFY;
			break;
		case AMBER_OVERTIME:
			TrafficState = AMBER_MODIFY;
			break;
		case GREEN_OVERTIME:
			TrafficState = GREEN_MODIFY;
			break;

		default:
			break;
		}
	}
}

void button2(){

}

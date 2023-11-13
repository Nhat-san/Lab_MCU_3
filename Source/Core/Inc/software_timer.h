
#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "stdbool.h"
#include "stdint.h"

#define Overall_Freq 1000 //100Hz

#define TIME_BLINK_LED		500
#define TIME_SCAN_7SEG		1
#define TIME_TRAFFIC_LIGHT	1000
#define	TIME_BUTTON			100
#define	TIME_OVER			500

void setTimer(uint8_t, unsigned int);
void timerRun();
bool timerOn(uint8_t);

#endif /* INC_SOFTWARE_TIMER_H_ */

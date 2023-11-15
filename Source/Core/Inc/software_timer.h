
#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "stdbool.h"
#include "stdint.h"

#define Overall_Freq 1000 //100Hz

#define TIME_BLINK_LED		250	/*time of blink led*/
#define TIME_SCAN_7SEG		1	/*time of scan 7-segments leds*/
#define TIME_TRAFFIC_LIGHT	1000/*time of count down traffic light value*/
#define	TIME_BUTTON			10	/*time of read button*/
#define	TIME_OVER			500	/*time to increase value when long_pressed second button*/

void setTimer(uint8_t, unsigned int);
void timerRun();
bool timerOn(uint8_t);

#endif /* INC_SOFTWARE_TIMER_H_ */

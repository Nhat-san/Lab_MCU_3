
#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "stdbool.h"
#include "stdint.h"

#define Overall_Freq 100 //100Hz

void setTimer(uint8_t, unsigned int);
void timerRun();
bool timerOn(uint8_t);

#endif /* INC_SOFTWARE_TIMER_H_ */

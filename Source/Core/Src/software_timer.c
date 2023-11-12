#include "software_timer.h"

/* Number of timer */
#define NUM_OF_TIMER 4
/* struct of timer */
struct {
	bool flag;
	unsigned int timer_counter;
} timer[NUM_OF_TIMER];
/* timer[0]: Blink Led 2Hz
 * timer[1]: Scan 7Segs
 * timer[2]: trafficlight
 * timer[3]: read button
 * */

void setTimer(uint8_t idx, unsigned int duration) {
	timer[idx].timer_counter = duration * Overall_Freq / 1000;
	timer[idx].flag = 0;
}


void timerRun() {
	for (uint8_t idx = 0; idx < NUM_OF_TIMER; idx++) {
		if (timer[idx].timer_counter > 0) {
			timer[idx].timer_counter--;
			if (timer[idx].timer_counter <= 0) {
				timer[idx].flag = 1;
			}
		}
	}

}

bool timerOn(uint8_t idx){
	return (!timer[idx].flag);
}

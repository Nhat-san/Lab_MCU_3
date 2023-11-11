
#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_
#define Overall_Freq 100 //100Hz
extern int timer1_flag;
//extern int timer2_flag;

void setTimer1(int duration);
//void setTimer2(int duration);

void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */

/*
 * software_timer.h
 *
 *  Created on: Sep 15, 2025
 *      Author: admin
 */


#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

struct TimerStruct{
	int counter;
	int flag;
};

void setTimer(int index, int counter);
void timerRun();
int isFlag(int index);

#endif /* INC_SOFTWARE_TIMER_H_ */

/*
 * commom.h
 *
 *  Created on: Oct 11, 2025
 *      Author: admin
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include "main.h"
#include "software_timer.h"

// TRAFFIC LIGHT
#define MIN_COUNTER 1
#define MAX_COUNTER 99

// 7SEG
#define LED_ON 0
#define LED_OFF 1

#define ENABLE_SEG 0
#define DISABLE_SEG	1


//TIMER
#define TIMER_TRAFFIC_LIGHT 0

#define TIMER_PRESS 1
#define TIME_PRESS 500

#define TIMER_SCAN_MAIN_ROAD 2
#define TIMER_SCAN_SIDE_ROAD 3
#define TIME_7SEG_SCAN 250

#define TIMER_1S 4
#define TIME_1S 1000

#define TIMER_250MS 5
#define TIME_250MS	250

#define TIMER_READ_BUTTON 6
#define TIME_READ_BUTTON 20

#define TIMER_CONVERT 7
#define TIME_CONVERT 1000

typedef enum {
    INIT,
    RED_GREEN,
    RED_AMBER,
    GREEN_RED,
    AMBER_RED,
	RED_MANUAL,
	AMBER_MANUAL,
	GREEN_MANUAL,
	CONVERT
} LightState;

extern LightState status;

extern uint8_t counter1;
extern uint8_t counter2;

extern uint8_t red_time;
extern uint8_t amber_time;
extern uint8_t green_time;

extern uint8_t red_time_manual;
extern uint8_t amber_time_manual;
extern uint8_t green_time_manual;

extern uint8_t index_scan_mainroad;
extern uint8_t index_scan_sideroad;

#endif /* INC_COMMON_H_ */

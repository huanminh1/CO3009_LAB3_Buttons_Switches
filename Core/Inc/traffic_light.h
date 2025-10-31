/*
 * traffic_light.h
 *
 *  Created on: Oct 11, 2025
 *      Author: admin
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"
#include "software_timer.h"
#include "common.h"

void fsm_for_traffic_light(void);

void displayTwoRoad(int value1, int value2);
void start_auto_mode();
void start_manual_mode();
#endif /* INC_TRAFFIC_LIGHT_H_ */

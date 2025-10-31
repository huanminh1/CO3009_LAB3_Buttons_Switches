/*
 * led_display.h
 *
 *  Created on: Oct 7, 2025
 *      Author: admin
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"
#include "traffic_light.h"
#include "common.h"

void display7SEG1 (int num);
void display7SEG2 (int num);
void Scan_2digit(int index, int value1, int value2);

void turn_red_on();
void turn_amber_on();
void turn_green_on();
void all_led_on();
void all_7seg_off();

void enable_seg(int num);
void displayTrafficLight(LightState status);
#endif /* INC_LED_DISPLAY_H_ */

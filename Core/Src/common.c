/*
 * common.c
 *
 *  Created on: Oct 11, 2025
 *      Author: admin
 */


#include "common.h"
uint8_t counter1 = 0;
uint8_t counter2 = 0;

uint8_t index_scan_mainroad = 0;
uint8_t index_scan_sideroad = 2;

uint8_t red_time = 7;
uint8_t amber_time = 2;
uint8_t green_time = 5;

uint8_t red_time_manual = 0;
uint8_t amber_time_manual = 0 ;
uint8_t green_time_manual = 0;

LightState status = INIT;


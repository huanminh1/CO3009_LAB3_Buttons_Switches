/*
 * input_reading.h
 *
 *  Created on: Oct 7, 2025
 *      Author: admin
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"
#include "common.h"

void button1_reading(void);
void button2_reading(void);
void button3_reading(void);
void reset_press(uint8_t index);
int is_button_pressed(int index);
int is_button_pressed_1s(int index);

#endif /* INC_INPUT_READING_H_ */

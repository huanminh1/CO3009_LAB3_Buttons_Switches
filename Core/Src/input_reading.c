/*
 * input_reading.c
 *
 *  Created on: Oct 7, 2025
 *      Author: admin
 */

#include "main.h"
#include "input_reading.h"
// We aim to work with more than one button
#define N0_OF_BUTTONS 3

// Timer interrupt duration is 10ms, so to pass 1 second,
// we need to jump to the interrupt service routine 100 times
#define DURATION_FOR_AUTO_INCREASING 100

#define BUTTON_IS_PRESSED   GPIO_PIN_RESET
#define BUTTON_IS_RELEASED  GPIO_PIN_SET

// The buffer that stores the final result after
//debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];

// Two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];

// A flag for a button pressed more than 1 second
static uint8_t flagForButtonPress1s[N0_OF_BUTTONS];
static uint8_t flagForButtonPressed[N0_OF_BUTTONS];
// Counter for automatically increasing the value
// after the button is pressed for more than 1 second
static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];

void reset_press(uint8_t index) {
    counterForButtonPress1s[index] = 0;
    flagForButtonPress1s[index] = 0;
    flagForButtonPressed[index] = 0;
}

void button1_reading(void) {
	debounceButtonBuffer2[0] = debounceButtonBuffer1[0];
	debounceButtonBuffer1[0] = HAL_GPIO_ReadPin(BUTTON_0_GPIO_Port, BUTTON_0_Pin);

	if (debounceButtonBuffer1[0] == debounceButtonBuffer2[0] ) {
		if(buttonBuffer[0] != debounceButtonBuffer1[0]){ // Nhấn thả
			buttonBuffer[0] = debounceButtonBuffer1[0];

			if (buttonBuffer[0] == BUTTON_IS_PRESSED) {
				HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
				flagForButtonPressed[0] = 1;
			}
		}else { 										// Nhấn đè
			// If a button is pressed, start counting
			if (buttonBuffer[0] == BUTTON_IS_PRESSED){
				if (counterForButtonPress1s[0] < DURATION_FOR_AUTO_INCREASING) {
					counterForButtonPress1s[0]++;
				}else {
					// The flag is turned on when 1 second has passed
					flagForButtonPress1s[0] = 1;

					HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
					counterForButtonPress1s[1] = 0; // RED_LED toggle every 1 second
				}
			}else {
				reset_press(0);
			}
		}
	}
}
void button2_reading(void) {
    debounceButtonBuffer2[1] = debounceButtonBuffer1[1];
    debounceButtonBuffer1[1] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);

    if (debounceButtonBuffer1[1] == debounceButtonBuffer2[1]) {
        if (buttonBuffer[1] != debounceButtonBuffer1[1]) { // Nhấn thả
            buttonBuffer[1] = debounceButtonBuffer1[1];

            if (buttonBuffer[1] == BUTTON_IS_PRESSED) {
                HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            	flagForButtonPressed[1] = 1;

            } else {
                reset_press(1);
            }
        } else { // Nhấn đè
            // If a button is pressed, start counting
            if (buttonBuffer[1] == BUTTON_IS_PRESSED) {
                if (counterForButtonPress1s[1] < DURATION_FOR_AUTO_INCREASING) {
                    counterForButtonPress1s[1]++;
                } else {
                    // The flag is turned on when 1 second has passed
                    flagForButtonPress1s[1] = 1;


                    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
                    counterForButtonPress1s[1] = 0; // RED_LED toggle every 1 second
                }
            } else {
                reset_press(1);
            }
        }
    }
}

void button3_reading(void) {
    debounceButtonBuffer2[2] = debounceButtonBuffer1[2];
    debounceButtonBuffer1[2] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);

    if (debounceButtonBuffer1[2] == debounceButtonBuffer2[2]) {
        if (buttonBuffer[2] != debounceButtonBuffer1[2]) { // Nhấn thả
            buttonBuffer[2] = debounceButtonBuffer1[2];

            if (buttonBuffer[2] == BUTTON_IS_PRESSED) {
                HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
                flagForButtonPressed[2] = 1;
            } else {
                reset_press(2);
            }
        } else { // Nhấn đè
            // If a button is pressed, start counting
            if (buttonBuffer[2] == BUTTON_IS_PRESSED) {
                if (counterForButtonPress1s[2] < DURATION_FOR_AUTO_INCREASING) {
                    counterForButtonPress1s[2]++;
                } else {
                    // The flag is turned on when 1 second has passed
                    flagForButtonPress1s[2] = 1;

                    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
					counterForButtonPress1s[1] = 0; // RED_LED toggle every 1 second
                }
            } else {
                reset_press(2);
            }
        }
    }
}

int is_button_pressed(int index){
    if(index >= N0_OF_BUTTONS) return 0;

    if(flagForButtonPressed[index] == 1){
    	flagForButtonPressed[index] = 0;
    	return 1;
    }
    return 0;
}

int is_button_pressed_1s(int index){
    if(index >= N0_OF_BUTTONS) return 0;

    if(flagForButtonPress1s[index] == 1){
    	flagForButtonPress1s[index] = 0;
    	return 1;
    }

    return 0;
}

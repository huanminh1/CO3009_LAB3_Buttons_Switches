/*
 * traffic_lights.c
 *
 *  Created on: Oct 11, 2025
 *      Author: admin
 */


#include "traffic_light.h"
#include "led_display.h"
#include "input_reading.h"

int traffic_light_buffer[3];

void fsm_for_traffic_light(void){
	switch(status){
		case INIT:
			if(true){
				//PRE_INIT
				red_time_manual = red_time;
				amber_time_manual = amber_time;
				green_time_manual = green_time;

				traffic_light_buffer[0] = red_time;
				traffic_light_buffer[1] = amber_time;
				traffic_light_buffer[2] = green_time;

				//TRAFFIC_LIGHT
				status = RED_GREEN;
				setTimer(TIMER_TRAFFIC_LIGHT, green_time*1000);
				displayTrafficLight(status);

				//7_SEG
				counter1 = red_time;
				counter2 = green_time;
				displayTwoRoad(counter1, counter2);
				setTimer(TIMER_SCAN_SIDE_ROAD,TIME_7SEG_SCAN);
				setTimer(TIMER_SCAN_MAIN_ROAD,TIME_7SEG_SCAN);

				setTimer(TIMER_1S, TIME_1S);
			}
			break;
		case RED_GREEN:
			displayTwoRoad(counter1, counter2);

			//7_SEG
			if(isFlag(TIMER_1S)){
				counter1--;
				counter2--;

				setTimer(TIMER_1S, TIME_1S);
			}

			//TRAFFIC_LIGHTS
			if(isFlag(TIMER_TRAFFIC_LIGHT)){
				status = RED_AMBER;
				//counter1 = AMBER_COUNTER;
				counter2 = amber_time;
				setTimer(TIMER_TRAFFIC_LIGHT,amber_time*1000);
				displayTrafficLight(status);
			}

			//BUTTON_0
			if(is_button_pressed(0)){
				start_manual_mode();
			}

			if(is_button_pressed_1s(0)){
				start_auto_mode();
			}

			break;
		case RED_AMBER:

			//7_SEG
			displayTwoRoad(counter1, counter2);
			if(isFlag(TIMER_1S)){
				counter1--;
				counter2--;

				setTimer(TIMER_1S, TIME_1S);
			}

			//TRAFFIC_LIGHTS
			if(isFlag(TIMER_TRAFFIC_LIGHT)){
				status = GREEN_RED;
				counter1 = green_time;
				counter2 = red_time;
				setTimer(TIMER_TRAFFIC_LIGHT, green_time*1000);
				displayTrafficLight(status);
			}

			//BUTTON_0
			if(is_button_pressed(0)){
				start_manual_mode();
			}

			if(is_button_pressed_1s(0)){
				start_auto_mode();
			}
			break;
		case GREEN_RED:
			//7_SEG
			displayTwoRoad(counter1, counter2);
			if(isFlag(TIMER_1S)){
				counter1--;
				counter2--;

				setTimer(TIMER_1S, TIME_1S);
			}
			//TRAFFIC_LIGHTS
			if(isFlag(TIMER_TRAFFIC_LIGHT)){
				status = AMBER_RED;
				counter1 = amber_time;
				//counter2 = AMBER_COUNTER;
				setTimer(TIMER_TRAFFIC_LIGHT,amber_time*1000);
				displayTrafficLight(status);
			}

			//BUTTON_0
			if(is_button_pressed(0)){
				start_manual_mode();
			}

			if(is_button_pressed_1s(0)){
				start_auto_mode();
			}
			break;
		case AMBER_RED:
			//7_SEG
			displayTwoRoad(counter1, counter2);
			if(isFlag(TIMER_1S)){
				counter1--;
				counter2--;
				setTimer(TIMER_1S, TIME_1S);
			}

			//TRAFFIC_LIGHTS
			if(isFlag(TIMER_TRAFFIC_LIGHT)){
				status = RED_GREEN;
				counter1 = red_time;
				counter2 = green_time;
				setTimer(TIMER_TRAFFIC_LIGHT, green_time*1000);
				displayTrafficLight(status);
			}

			//BUTTON_0
			if(is_button_pressed(0)){
				start_manual_mode();
			}

			if(is_button_pressed_1s(0)){
				start_auto_mode();
			}
			break;
		case RED_MANUAL:
			//7_SEG
			displayTwoRoad(counter1, counter2);

			//TRAFFIC_LIGHTS
			if(true){
				//BUTTON_0
				if(is_button_pressed(0)){
					status = AMBER_MANUAL;
					turn_amber_on();
					amber_time_manual = amber_time;
					setTimer(TIMER_250MS, TIME_250MS);
					counter1 = amber_time;
					counter2 = 3;
				}
				if(is_button_pressed_1s(0)){
					start_auto_mode();
				}

				//BUTTON_1
				if(is_button_pressed(1)){
					red_time_manual++;
				}
				if(is_button_pressed_1s(1)){
					red_time_manual += 5;
				}
				if(red_time_manual > MAX_COUNTER){
					red_time_manual = MIN_COUNTER;
				}
				counter1 = red_time_manual;

				//BUTTON_2
				if(is_button_pressed(2)){
					//SET_RED_TIME
					traffic_light_buffer[0] = red_time_manual;
				}
				if(is_button_pressed_1s(2)){
					//RESET_RED_TIME
					traffic_light_buffer[0] = red_time;
				}

			}

			if(isFlag(TIMER_250MS)){
				HAL_GPIO_TogglePin(RED_0_GPIO_Port, RED_0_Pin);
				HAL_GPIO_TogglePin(RED_1_GPIO_Port, RED_1_Pin);

				setTimer(TIMER_250MS, TIME_250MS);
			}

			break;
		case AMBER_MANUAL:
			//7_SEG
			displayTwoRoad(counter1, counter2);

			//TRAFFIC_LIGHTS
			if(true){

				//BUTTON_0
				if(is_button_pressed(0)){
					status = GREEN_MANUAL;

					turn_green_on();
					green_time_manual = green_time;
					setTimer(TIMER_250MS, TIME_250MS);
					counter1 = green_time;
					counter2 = 4;
				}
				if(is_button_pressed_1s(0)){
					start_auto_mode();
				}

				//BUTTON_1
				if(is_button_pressed(1)){
					amber_time_manual++;
				}
				if(is_button_pressed_1s(1)){
					amber_time_manual += 5;
				}
				if(amber_time_manual > MAX_COUNTER){
					amber_time_manual = MIN_COUNTER;
				}
				counter1 = amber_time_manual;

				//BUTTON_2
				if(is_button_pressed(2)){
					//SET_AMBER_TIME
					traffic_light_buffer[1] = amber_time_manual;
				}
				if(is_button_pressed_1s(2)){
					//RESET_AMBER_TIME
					traffic_light_buffer[1] = amber_time;
				}
			}

			if(isFlag(TIMER_250MS)){
				HAL_GPIO_TogglePin(AMBER_0_GPIO_Port, AMBER_0_Pin);
				HAL_GPIO_TogglePin(AMBER_1_GPIO_Port, AMBER_1_Pin);

				setTimer(TIMER_250MS, TIME_250MS);
			}
			break;
		case GREEN_MANUAL:
			//7_SEG
			displayTwoRoad(counter1, counter2);

			//TRAFFIC_LIGHTS
			if(true){

				//BUTTON_0
				if(is_button_pressed(0)){
					status = CONVERT;
					setTimer(TIMER_CONVERT, TIME_CONVERT);
				}
				if(is_button_pressed_1s(0)){
					start_auto_mode();
				}

				//BUTTON_1
				if(is_button_pressed(1)){
					green_time_manual++;
				}
				if(is_button_pressed_1s(1)){
					green_time_manual += 5;
				}
				if(green_time_manual > MAX_COUNTER){
					green_time_manual = MIN_COUNTER;
				}
				counter1 = green_time_manual;

				//BUTTON_2
				if(is_button_pressed(2)){
					//SET_GREEN_TIME
					traffic_light_buffer[2] = green_time_manual;
				}
				if(is_button_pressed_1s(2)){
					//RESET_GREEN_TIME
					traffic_light_buffer[2] = green_time;
				}

			}

			if(isFlag(TIMER_250MS)){
				HAL_GPIO_TogglePin(GREEN_0_GPIO_Port, GREEN_0_Pin);
				HAL_GPIO_TogglePin(GREEN_1_GPIO_Port, GREEN_1_Pin);

				setTimer(TIMER_250MS, TIME_250MS);
			}
			break;
		case CONVERT:
			if(true){
				all_led_on();
				all_7seg_off();
				if(traffic_light_buffer[0] == traffic_light_buffer[1] + traffic_light_buffer[2]){
					red_time = traffic_light_buffer[0];
					amber_time = traffic_light_buffer[1];
					green_time = traffic_light_buffer[2];
				}

			}
			if(isFlag(TIMER_CONVERT)){
				start_auto_mode();
			}
			break;
		default:
			break;
	}
}

void displayTwoRoad(int value1, int value2) {
	 if(isFlag(TIMER_SCAN_MAIN_ROAD)){
		 Scan_2digit(index_scan_mainroad, value1, value2);
		 ++index_scan_mainroad;
		 if(index_scan_mainroad > 1){
			 index_scan_mainroad = 0;
		 }
		 setTimer(TIMER_SCAN_MAIN_ROAD, TIME_7SEG_SCAN);
	 }

	 if(isFlag(TIMER_SCAN_SIDE_ROAD)){
	         Scan_2digit(index_scan_sideroad, value1, value2);
	         ++index_scan_sideroad;
	         if(index_scan_sideroad > 3){
	             index_scan_sideroad = 2;
	         }
	         setTimer(TIMER_SCAN_SIDE_ROAD, TIME_7SEG_SCAN);
	     }
}

void start_auto_mode(){
	status = RED_GREEN;
	counter1 = red_time;
	counter2 = green_time;
	setTimer(TIMER_TRAFFIC_LIGHT, green_time*1000);
	setTimer(TIMER_1S, TIME_1S);
	displayTrafficLight(status);
}

void start_manual_mode(){
	status = RED_MANUAL;
	turn_red_on();
	red_time_manual = red_time;
	setTimer(TIMER_250MS, TIME_250MS);
	counter1 = red_time;
	counter2 = 2;
}


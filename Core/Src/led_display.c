/*
 * led_display.c
 *
 *  Created on: Oct 7, 2025
 *      Author: admin
 */

#include "led_display.h"
#include "traffic_light.h"

void Scan_2digit(int index, int value1, int value2){
	switch(index){
		case 0:
			enable_seg(0);
			display7SEG1(value1 / 10);
			break;
		case 1:
			enable_seg(1);
			display7SEG1(value1 % 10);
			break;
		case 2:
			enable_seg(2);
			display7SEG2(value2 / 10);
			break;
		case 3:
			enable_seg(3);
			display7SEG2(value2 % 10);
			break;
		default:
			break;
	}

}

void displayTrafficLight(LightState status) {
    switch(status) {
        case RED_GREEN:
            // Đèn dọc: đỏ, đèn ngang: xanh
            HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_ON);
            HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_OFF);
            HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_OFF);

            HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_OFF);
            HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_OFF);
            HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_ON);
            break;

        case RED_AMBER:
            // Đèn dọc: đỏ, đèn ngang: vàng
            HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_ON);
            HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_OFF);
            HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_OFF);

            HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_OFF);
            HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_ON);
            HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_OFF);
            break;

        case GREEN_RED:
            // Đèn dọc: xanh, đèn ngang: đỏ
            HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_OFF);
            HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_OFF);
            HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_ON);

            HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_ON);
            HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_OFF);
            HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_OFF);

            break;

        case AMBER_RED:
            // Đèn dọc: vàng, đèn ngang: đỏ
            HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_OFF);
            HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_ON);
            HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_OFF);

            HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_ON);
            HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_OFF);
            HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_OFF);

            break;
        default:
            // Tắt tất cả
            HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_OFF);
            HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_OFF);
            HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_OFF);

            HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_OFF);
            HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_OFF);
            HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_OFF);

            break;
    }
}

void display7SEG1(int num){
	switch(num) {
	    case 0:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_OFF);
	        break;

	    case 1:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_OFF);
	        break;

	    case 2:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_ON);
	        break;

	    case 3:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_ON);
	        break;

	    case 4:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_ON);
	        break;

	    case 5:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_ON);
	        break;

	    case 6:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_ON);
	        break;

	    case 7:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_OFF);
	        break;

	    case 8:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_ON);
	        break;

	    case 9:
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_ON);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_ON);
	        break;

	    default:
	        // Tắt hết
	        HAL_GPIO_WritePin(GPIOA, SEG_0_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_1_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_2_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_3_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_4_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_5_Pin, LED_OFF);
	        HAL_GPIO_WritePin(GPIOA, SEG_6_Pin, LED_OFF);
	        break;
	}
}

void display7SEG2 (int num){
    switch(num) {
        case 0:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_OFF);
            break;

        case 1:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_OFF);
            break;

        case 2:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_ON);
            break;

        case 3:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_ON);
            break;

        case 4:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_ON);
            break;

        case 5:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_ON);
            break;

        case 6:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_ON);
            break;

        case 7:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_OFF);
            break;

        case 8:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_ON);

            break;

        case 9:
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_ON);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_ON);
            break;

        default:
            // Tắt hết
            HAL_GPIO_WritePin(GPIOB, SEG_0_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_1_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_2_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_3_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_4_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_5_M_Pin, LED_OFF);
            HAL_GPIO_WritePin(GPIOB, SEG_6_M_Pin, LED_OFF);
            break;
    }
}

void enable_seg(int num){
	switch(num){
		case 0:
			HAL_GPIO_WritePin(GPIOA, EN_0_Pin, ENABLE_SEG);
			HAL_GPIO_WritePin(GPIOA, EN_1_Pin, DISABLE_SEG);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, EN_0_Pin, DISABLE_SEG);
			HAL_GPIO_WritePin(GPIOA, EN_1_Pin, ENABLE_SEG);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, EN_2_Pin, ENABLE_SEG);
			HAL_GPIO_WritePin(GPIOA, EN_3_Pin, DISABLE_SEG);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, EN_2_Pin, DISABLE_SEG);
			HAL_GPIO_WritePin(GPIOA, EN_3_Pin, ENABLE_SEG);
			break;
		default:
			break;
	}
}



void turn_red_on()
{
	HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_ON);
	HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_OFF);

	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_ON);
	HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_OFF);
}

void turn_amber_on()
{
	HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_ON);
	HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_OFF);

	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_ON);
	HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_OFF);
}

void turn_green_on()
{
	HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_OFF);
	HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_ON);

	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_OFF);
	HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_ON);
}

void all_led_on(){
	HAL_GPIO_WritePin(RED_0_GPIO_Port, RED_0_Pin, LED_ON);
	HAL_GPIO_WritePin(AMBER_0_GPIO_Port, AMBER_0_Pin, LED_ON);
	HAL_GPIO_WritePin(GREEN_0_GPIO_Port, GREEN_0_Pin, LED_ON);

	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, LED_ON);
	HAL_GPIO_WritePin(AMBER_1_GPIO_Port, AMBER_1_Pin, LED_ON);
	HAL_GPIO_WritePin(GREEN_1_GPIO_Port, GREEN_1_Pin, LED_ON);
}
void all_7seg_off(){
	HAL_GPIO_WritePin(GPIOA, EN_0_Pin, DISABLE_SEG);
	HAL_GPIO_WritePin(GPIOA, EN_1_Pin, DISABLE_SEG);
	HAL_GPIO_WritePin(GPIOA, EN_2_Pin, DISABLE_SEG);
	HAL_GPIO_WritePin(GPIOA, EN_3_Pin, DISABLE_SEG);
}

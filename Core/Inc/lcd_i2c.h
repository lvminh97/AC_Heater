#ifndef __LCD_I2C_H
#define __LCD_I2C_H

#include "stm32f1xx_hal.h"

void lcd_init(I2C_HandleTypeDef *hi2c);   // initialize lcd

void lcd_send_cmd(char cmd);  // send command to the lcd

void lcd_send_data(char data);  // send data to the lcd

void lcd_send_string(char *str);  // send string to the lcd

void lcd_clear(void);	//clear display lcd

void lcd_goto_xy(int col, int row); //set proper location on screen

#endif

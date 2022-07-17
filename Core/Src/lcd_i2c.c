#include "lcd_i2c.h"

#define SLAVE_ADDRESS_LCD 0x4E 

I2C_HandleTypeDef *hlcd_i2c;  

void lcd_init(I2C_HandleTypeDef *hi2c){
	hlcd_i2c = hi2c;
	
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	HAL_Delay(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	HAL_Delay(50);
	lcd_send_cmd (0x01); /* clear display */
	HAL_Delay(50);
	lcd_send_cmd (0x06); /* set entry mode */
	HAL_Delay(50);
	lcd_send_cmd (0x0c); /* set display to on */	
	HAL_Delay(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	lcd_send_cmd (0x80);
}

void lcd_send_cmd(char cmd){
	char data_u, data_l;
	uint8_t data_t[4];

	if(hlcd_i2c == NULL)
		return;

	data_u = cmd & 0xF0;
	data_l = (cmd << 4) & 0xF0;
	data_t[0] = data_u | 0x0C;  //en=1, rs=0
	data_t[1] = data_u | 0x08;  //en=0, rs=0
	data_t[2] = data_l | 0x0C;  //en=1, rs=0
	data_t[3] = data_l | 0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (hlcd_i2c, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100);
}

void lcd_send_data(char data){
	char data_u, data_l;
	uint8_t data_t[4];
	
	if(hlcd_i2c == NULL)
		return;
	
	data_u = data & 0xF0;
	data_l = (data << 4) & 0xF0;
	data_t[0] = data_u | 0x0D;  //en=1, rs=1
	data_t[1] = data_u | 0x09;  //en=0, rs=1
	data_t[2] = data_l | 0x0D;  //en=1, rs=1
	data_t[3] = data_l | 0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (hlcd_i2c, SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4, 100);
}

void lcd_send_string(char *str){
	while(*str) 
		lcd_send_data(*str++);
}

void lcd_clear(void){
	lcd_send_cmd(0x01); //clear display
}

void lcd_goto_xy(int row, int col){
	uint8_t pos_addr = 0x80;
	if(row == 2) 
		pos_addr |= 0x40;
	pos_addr += col;
	lcd_send_cmd(pos_addr);
}

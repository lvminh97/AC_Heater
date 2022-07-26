#include "main.h"
#include "max6675.h"

float max6675_get_temp(SPI_HandleTypeDef *hspi){
	uint16_t res = 0;
	uint8_t buffer[2] = {0};
	
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);	// Set CS pin to low to select slave
	HAL_SPI_Receive(hspi, buffer, 2, 1000);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);		// Set CS pin to high to deselect slave
	
	res = buffer[1];
	res = (res << 8) | buffer[0];
	res >>= 3;
	
	return res * 0.25;
}

#include "main.h"
#include "max6675.h"

extern uint16_t raw_temp;

float max6675_get_temp(void){
	uint16_t res = 0, id;
	uint8_t buffer[2] = {0};
	
//	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);	// Set CS pin to low to select slave
//	HAL_SPI_Receive(hspi, buffer, 2, 1000);
//	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);		// Set CS pin to high to deselect slave
	
//	res = buffer[1];
//	res = (res << 8) | buffer[0];
//	raw_temp = res;
//	res >>= 3;
	
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);	// Set CS pin to low to select slave
	
	for(id = 0; id < 16; id++){
		HAL_GPIO_WritePin(SPI1_SCK_GPIO_Port, SPI1_SCK_Pin, GPIO_PIN_RESET);
		HAL_Delay(1);
		res <<= 1;
		if(HAL_GPIO_ReadPin(SPI1_MISO_GPIO_Port, SPI1_MISO_Pin) == GPIO_PIN_SET){
			res |= 1;
		}
		HAL_GPIO_WritePin(SPI1_SCK_GPIO_Port, SPI1_SCK_Pin, GPIO_PIN_SET);
		HAL_Delay(1);
	}
	
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);		// Set CS pin to high to deselect slave
	
	res >>= 3;
	
	return res * 0.25;
}

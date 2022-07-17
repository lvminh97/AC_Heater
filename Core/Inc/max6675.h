#ifndef __MAX6675_H
#define __MAX6675_H

#include "stm32f1xx_hal.h"

float max6675_get_temp(SPI_HandleTypeDef *hspi);

#endif

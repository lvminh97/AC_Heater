#ifndef __DWT_H
#define __DWT_H

#include "main.h"

void dwt_init(void);

void delay_us(uint64_t us);

void delay_ms(uint32_t ms);

uint64_t get_micros(void);

uint32_t get_millis(void);

#endif

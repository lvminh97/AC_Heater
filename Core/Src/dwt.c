#include "dwt.h"

void dwt_init(void){
	if(!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)){
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
		DWT->CYCCNT = 0;
		DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	}
}

void delay_us(uint64_t us){
	uint32_t startTick = DWT->CYCCNT;
	uint32_t delayTicks = us * (SystemCoreClock / 1000000);
	while(DWT->CYCCNT - startTick < delayTicks);
}

void delay_ms(uint32_t ms){
	while(ms--){
		delay_us(1000);
	}
}

uint64_t get_micros(void){
	return DWT->CYCCNT / (SystemCoreClock / 1000000);
}

uint32_t get_millis(void){
	return DWT->CYCCNT / (SystemCoreClock / 1000);
}

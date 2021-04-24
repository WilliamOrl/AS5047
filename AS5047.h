#ifndef LIB_AS5047_H
#define LIB_AS5047_H
#ifdef _cplusplus
extern "C"	{
#endif

#include "stm32f4xx_hal.h"
#include "stdio.h"


#define mask 0x28 // 00101000b bit 3 & 5 set


//External Function
HAL_StatusTypeDef AS5047_Start (SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef AS5047_Data (GPIO_TypeDef *I, uint16_t I2, float* data, TIM_HandleTypeDef *Tim);

//Internal Function


#ifdef _cplusplus
}
#endif
#endif// LIB_AS5_047_H

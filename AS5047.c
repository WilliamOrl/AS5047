#include <AS5047.h>
#include "stdio.h"

static const uint8_t STTINGS1 = 0x18;
static const uint8_t STTINGS = 0x19;


//===========================================================================
//							Sensor Start
//===========================================================================

HAL_StatusTypeDef AS5047_Start (SPI_HandleTypeDef *hspi){


	HAL_StatusTypeDef ret;
	uint8_t bus[2];

	bus[0] = STTINGS1;
	ret = HAL_SPI_Transmit (hspi, bus, 1, 100);
	if(ret != HAL_OK){
		return ret;
	}else{
		HAL_SPI_Receive (hspi, bus[1], 1, 100);
	}

	bus[1] = (bus[1] & ~mask) | (0x00 & mask);

	ret = HAL_SPI_Transmit (hspi, bus, 2, 100);
	if(ret != HAL_OK){
		return ret;
	}else{
	return HAL_OK;
	}
}

//===========================================================================
//							Sensor Data
//===========================================================================

HAL_StatusTypeDef AS5047_Data (GPIO_TypeDef *I, uint16_t I2, float *data, TIM_HandleTypeDef *Tim){

	uint16_t bus=0;
	uint32_t tim_value=0;
	int key = 0;
	__HAL_TIM_SET_COUNTER(Tim,0);
	HAL_TIM_Base_Start (Tim);

	while (1){
		bus = HAL_GPIO_ReadPin (I,I2);
		if(bus == 1){

			if(key == 1){
				tim_value = (__HAL_TIM_GET_COUNTER(Tim) - tim_value)/16;
				tim_value = tim_value/1000;

				*data = 1.f/tim_value;
				HAL_TIM_Base_Stop(Tim);
				return HAL_OK;
			}

			tim_value = __HAL_TIM_GET_COUNTER(Tim);
			key ++;
			while(bus == 1){
				bus = HAL_GPIO_ReadPin (I,I2);
			}
		}
	}

}


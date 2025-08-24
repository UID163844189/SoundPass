#include "i2smic_spi.h"
#include "spi.h"
#include "main.h"

#define hmic hspi3
#define datasize 2 // 24 bit data in 32 bit frames
#define WSpin ICS43434_WS_GPIO_Port, ICS43434_WS_Pin

/**
 * @brief  Transmit an amount of data in blocking mode
 * @param  pData a 32-bit pointer to data buffer.
 * @param  Size number of data sample to be sent:
 * @note   When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
 *         configuration phase, the Size parameter means the number of 16-bit data length
 *         in the transaction and when a 24-bit data frame or a 32-bit data frame is selected
 *         the Size parameter means the number of 24-bit or 32-bit data length.
 * @param  Timeout Timeout duration
 * @retval HAL status
 */

void I2SMic_Receive(uint32_t *pData, uint16_t Size, uint32_t Timeout)
{
	uint8_t temp[4] = {0};
	for (int i = 0; i < Size; i++)
	{
		HAL_GPIO_WritePin(WSpin, 0); // left channel
		HAL_SPI_Receive(&hmic, temp, 4, Timeout);
		pData[i] = (temp[0] << 15) | (temp[1] << 7) | (temp[2] >> 1); // 24 bit data in 32 bit frames

		i++;

		HAL_GPIO_WritePin(WSpin, 1); // right channel
		HAL_SPI_Receive(&hmic, temp, 4, Timeout);
		// pData[i * datasize + 2] = (temp[0] << 16) | (temp[1] << 8) | temp[2]; // 24 bit data in 32 bit frames
		pData[i + 1] = 0x000000; // 24 bit data in 32 bit frames
	}
}
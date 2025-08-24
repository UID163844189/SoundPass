#include "main.h"

void I2SMic_Receive(uint32_t *pData, uint16_t Size, uint32_t Timeout);

void I2SMic_ReceiveMonoChannel(uint32_t *pData, uint16_t Size, uint32_t Timeout);

void I2SDAC_TransmitMonoChannel(uint32_t *pData, uint16_t Size, uint32_t Timeout);

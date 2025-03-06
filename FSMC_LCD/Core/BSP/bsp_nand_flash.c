/*
 * bsp_nand_flash.c
 *
 *  Created on: Mar 6, 2025
 *      Author: compro
 */
#include "bsp.h"

#define Bank2_NAND_ADDR    ((uint32_t)0x70000000)
#define Bank_NAND_ADDR     Bank2_NAND_ADDR

// NAND memory status
#define NAND_BUSY                  ((uint8_t)0x00)
#define NAND_READY                 ((uint8_t)0x40)

#define NAND_CMD_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA)
#define NAND_DATA_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA)


static uint16_t s_usValidDataBlockCount;

static uint8_t NAND_BuildLUT(void);
static uint8_t FSMC_NAND_GetStatus(void);

#if 1
static void BSP_FSMC_NAND_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    NAND_HandleTypeDef hnand;
    FMC_NAND_PCC_TimingTypeDef ComSpaceTiming = {0};
    FMC_NAND_PCC_TimingTypeDef AttSpaceTiming = {0};

    /*--NAND Flash GPIOs ------
		PD0/FSMC_D2
		PD1/FSMC_D3
		PD4/FSMC_NOE
		PD5/FSMC_NWE
		PD7/FSMC_NCE2
		PD11/FSMC_A16
		PD12/FSMC_A17
		PD14/FSMC_D0
		PD15/FSMC_D1

		PE7/FSMC_D4
		PE8/FSMC_D5
		PE9/FSMC_D6
		PE10/FSMC_D7

		PG6/FSMC_INT2	
	*/
    // GPIO 클럭 활성화
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    // FMC 클럭 활성화 */
    __HAL_RCC_FMC_CLK_ENABLE();

    // GPIOD 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
                          GPIO_PIN_7 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    
    // GPIOE 설정
    GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    // GPIOG 설정 - PG6 핀을 Busy 신호로 사용
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    // 공통 공간 타이밍 설정 
    ComSpaceTiming.SetupTime = 1;
    ComSpaceTiming.WaitSetupTime = 3;
    ComSpaceTiming.HoldSetupTime = 2;
    ComSpaceTiming.HiZSetupTime = 1;

    // 속성 공간 타이밍 설정 (공통 공간과 동일)
    AttSpaceTiming.SetupTime = 1;
    AttSpaceTiming.WaitSetupTime = 3;
    AttSpaceTiming.HoldSetupTime = 2;
    AttSpaceTiming.HiZSetupTime = 1;

    // NAND 핸들 구조체 설정
    hnand.Instance = FSMC_NAND_DEVICE;
    hnand.Init.NandBank = FSMC_NAND_BANK2;
    hnand.Init.Waitfeature = FSMC_NAND_PCC_WAIT_FEATURE_DISABLE;
    hnand.Init.MemoryDataWidth = FSMC_NAND_PCC_MEM_BUS_WIDTH_8;
    hnand.Init.EccComputation = FSMC_NAND_ECC_ENABLE;
    hnand.Init.ECCPageSize = FSMC_NAND_ECC_PAGE_SIZE_2048BYTE;
    hnand.Init.TCLRSetupTime = 1;
    hnand.Init.TARSetupTime = 1;

    FMC_NAND_CommonSpace_Timing_Init(FSMC_NAND_DEVICE, &ComSpaceTiming, FSMC_NAND_BANK2);
    FMC_NAND_AttributeSpace_Timing_Init(FSMC_NAND_DEVICE, &AttSpaceTiming, FSMC_NAND_BANK2);

    //hnand.Init.CommonSpaceTimingStruct = &ComSpaceTiming;
    //hnand.Init.AttributeSpaceTimingStruct = &AttSpaceTiming;
    //hnand.Init.CommonSpaceTimingStruct = &ComSpaceTiming;
    //hnand.Init.CommonSpaceTimingStruct = &ComSpaceTiming;
    //ComSpaceTiming. = &ComSpaceTiming;

    HAL_NAND_Init(&hnand,&ComSpaceTiming, &AttSpaceTiming);
}
#endif

static uint8_t BSP_FSMC_NAND_Reset(void)
{
    NAND_CMD_AREA = NAND_CMD_RESET;

    if(FSMC_NAND_GetStatus() == NAND_READY)
    {
        return NAND_OK;
    }
    return NAND_FAIL;
}

static uint8_t FSMC_NAND_ReadStatus(void)
{
    uint8_t ucData;
	uint8_t ucStatus = NAND_BUSY;

    NAND_CMD_AREA = NAND_CMD_STATUS;
    ucData = *(__IO uint8_t *)(Bank_NAND_ADDR);

    if((ucData & NAND_ERROR) == NAND_ERROR)
    {
        ucStatus = NAND_ERROR;
    }
    else if((ucData & NAND_READY) == NAND_READY)
    {
        ucStatus = NAND_READY;
    }
    else
    {
        ucStatus = NAND_BUSY;
    }
    return (ucStatus);
}

static uint8_t FSMC_NAND_GetStatus(void)
{
    uint32_t ulTimeout = 0x10000;
	uint8_t ucStatus = NAND_READY;

    ucStatus = FSMC_NAND_ReadStatus();

    while ((ucStatus != NAND_READY) &&( ulTimeout != 0x00))
    {
        ucStatus = FSMC_NAND_ReadStatus();
        ulTimeout--;
    }
    if(ulTimeout == 0x00)
    {
        ucStatus =  NAND_TIMEOUT_ERROR;
    }
    return (ucStatus);
}

static uint8_t FSMC_NAND_ReadPage(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInPage, uint16_t _usByteCount)
{
    uint16_t i;
    
    NAND_CMD_AREA = NAND_CMD_AREA_A;

    /*
    "According to HY27UF081G2A,
    Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
    Group 1: A7 A6 A5 A4 A3 A2 A1 A0 (_usPageAddr bits 7 - 0)
    Group 2: 0 0 0 0 A11 A10 A9 A8 (_usPageAddr bits 11 - 8, lower 4 bits are set to 0)
    Group 3: A19 A18 A17 A16 A15 A14 A13 A12
    Group 4: A27 A26 A25 A24 A23 A22 A21 A20"
    */
    NAND_ADDR_AREA = _usAddrInPage;
	NAND_ADDR_AREA = _usAddrInPage >> 8;
	NAND_ADDR_AREA = _ulPageNo;
	NAND_ADDR_AREA = (_ulPageNo & 0xFF00) >> 8;

    NAND_CMD_AREA = NAND_CMD_AREA_TRUE1;

    for (i = 0; i < 20; i++);
    while(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_6) == GPIO_PIN_RESET);

    for(i = 0; i < _usByteCount; i++)
    {
        _pBuffer[i] = NAND_DATA_AREA;
    }
    return NAND_OK;
}

static uint8_t FSMC_NAND_ReadSpare(uint8_t *_pBuffer, uint32_t _ulPageNo, uint16_t _usAddrInSpare, uint16_t _usByteCount)
{
    if (_usByteCount > NAND_SPARE_AREA_SIZE)
    {
        return NAND_FAIL;
    }
    return FSMC_NAND_ReadPage(_pBuffer, _ulPageNo, NAND_PAGE_SIZE + _usAddrInSpare, _usByteCount);
}

uint8_t NAND_Init(void)
{
    uint8_t Status;
    BSP_FSMC_NAND_Init();
    
    BSP_FSMC_NAND_Reset();

    Status = NAND_BuildLUT();

    return Status;
}

static uint8_t NAND_BuildLUT(void)
{
    uint16_t i;
	uint8_t buf[VALID_SPARE_SIZE];
	uint16_t usLBN;	

    for (i = 0; i < NAND_BLOCK_COUNT; i++)
    {
        s_usLUT[i] = 0xFFFF;
    }
    for (i = 0; i < NAND_BLOCK_COUNT; i++)
    {
        FSMC_NAND_ReadSpare(buf, i * NAND_BLOCK_SIZE, 0, VALID_SPARE_SIZE);

        if (buf[BI_OFFSET] == 0xFF)
        {
            usLBN = buf[LBN0_OFFSET] + buf[LBN1_OFFSET] * 256;
            if (usLBN < NAND_BLOCK_COUNT)
            {
                if (s_usLUT[usLBN] != 0xFFFF)
                {
                    return NAND_FAIL;
                }
                s_usLUT[usLBN] = i;
            }
        }
    }
    for (i = 0; i < NAND_BLOCK_COUNT; i++)
    {
        if (s_usLUT[i] >= NAND_BLOCK_COUNT)
        {
            s_usValidDataBlockCount = i;
            break;
        }
    }
    if (s_usValidDataBlockCount < 100)
    {
        return NAND_FAIL;
    }
    for (; i < s_usValidDataBlockCount; i++)
    {
        if (s_usLUT[i] != 0xFFFF)
        {
            return NAND_FAIL;
        }
    }
    return NAND_OK;
}

uint32_t NAND_ReadID(void)
{
    uint32_t data = 0;

    NAND_CMD_AREA = 0x90;
	NAND_ADDR_AREA = 0x00;

    data = *(__IO uint32_t *)(Bank_NAND_ADDR | DATA_AREA);
    data =  ((data << 24) & 0xFF000000) |
			((data << 8 ) & 0x00FF0000) |
			((data >> 8 ) & 0x0000FF00) |
			((data >> 24) & 0x000000FF) ;
	return data;
}

/*
 * LCD_RA8875.c
 *
 *  Created on: Feb 26, 2025
 *      Author: compro
 */
#include "bsp.h"
#include "bsp_ra8875_port.h"

static __IO uint8_t s_ucRA8875Busy = 0;

static uint16_t s_WinX = 0;
static uint16_t s_WinY = 0;
static uint16_t s_WinHeight = 272;
static uint16_t s_WinWidth = 480;

static void RA8875_WriteReg(uint8_t _ucRegAddr, uint8_t _ucRegValue);
static void BTE_SetTarBlock(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t _ucLayer);
static void BTE_SetOperateCode(uint8_t _ucOperate);
static void BTE_Start(void);


/*
*********************************************************************************************************
*  Function Name: BTE_SetTarBlock
*  Description: Set the target block for the RA8875 BTE (Block Transfer Engine)
*  Parameters:
*          uint16_t _usX : The X coordinate of the target block
*          uint16_t _usY : The Y coordinate of the target block
*          uint16_t _usHeight : Height of the target block
*          uint16_t _usWidth : Width of the target block
*          uint8_t _ucLayer : Layer selection, 0 for Layer 1, 1 for Layer 2
*  Return Type: None
*********************************************************************************************************
*/
static void BTE_SetTarBlock(uint16_t _usX, uint16_t _usY, uint16_t _usHeight, uint16_t _usWidth, uint8_t _ucLayer)
{
    RA8875_WriteReg(0x58, _usX);
    RA8875_WriteReg(0x59, _usX >> 8);

    RA8875_WriteReg(0x5A, _usY);
    if (_ucLayer == 0)
    {
        RA8875_WriteReg(0x5B, _usY >> 8);
    }
    else
    {
        RA8875_WriteReg(0x5B, (1 << 7) | (_usY >> 8));	/* Bit7 represents the layer selection, 0 for Layer 1, 1 for Layer 2 */
    }
    /* Set the width of the target block */
    RA8875_WriteReg(0x5C, _usWidth);
    RA8875_WriteReg(0x5D, _usWidth >> 8);
    
    /* Set the height of the target block */
    RA8875_WriteReg(0x5E, _usHeight);
	RA8875_WriteReg(0x5F, _usHeight >> 8);
}

/*
*********************************************************************************************************
*  Function Name: BTE_Start
*  Description: Start the Block Transfer Engine (BTE) operation.
*  Parameters:
*          None
*  Return Type: None
*********************************************************************************************************
*/
static void BTE_Start(void)
{
    s_ucRA8875Busy = 1;  // Set the RA8875 controller as busy
    /* RA8875_WriteReg(0x50, 0x80);  This function is not used, but would write to a register and mark the RA8875 as busy */
    RA8875_WriteCmd(0x50);  // Send command to the RA8875 to initiate the operation
    RA8875_WriteData(0x80);  // Write data to register to start the operation
}
/*
*********************************************************************************************************
*  Function Name: BTE_Wait
*  Description: Wait for the Block Transfer Engine (BTE) operation to complete.
*  Parameters:
*          None
*  Return Type: None
*********************************************************************************************************
*/
static void BTE_Wait(void)
{
	while ((RA8875_ReadStatus() & 0x40) == 0x40);
	s_ucRA8875Busy = 0;
}

/*
*********************************************************************************************************
*  Function Name: BTE_SetOperateCode
*  Description: Set the operation code for the Block Transfer Engine (BTE) and enable the transfer.
*  Parameters:
*          _ucOperate : The operation code to enable
*  Return Type: None
*********************************************************************************************************
*/
static void BTE_SetOperateCode(uint8_t _ucOperate)
{
    /* Set the operation code and enable the Block Transfer Engine (BTE) transfer */
    RA8875_WriteReg(0x51, _ucOperate);
}




/*
*********************************************************************************************************
*  Function Name: RA8875_ClrScr
*  Description: Clears the screen using the previously set background color. 
*               This function will clear the entire display area of the RA8875 screen.
*               It also sets the display window (or active region) for subsequent drawing. 
*               The display window can be set using the function RA8875_SetDispWin().
*  Parameters:
*          _usColor : Background color to clear the screen with
*  Return Type: None
*********************************************************************************************************
*/
void RA8875_ClrScr(uint16_t _usColor)
{
    /* This process uses the range 0x30-0x37 to set up the memory area for screen drawing operations. 
        The method used to clear the screen:
        - It involves configuring the hardware registers (pdf) with the address 162.
        - The configuration sequence begins with writing to the necessary registers to configure the drawing window and set the screen color to the background color.
        - The RA8875 display system configuration:
        1. Set the target block's layer and position by configuring REG[58h], [59h], [5Ah], [5Bh].
        2. Set the width and height of the target block by configuring REG[5Ch], [5Dh], [5Eh], [5Fh].
        3. Enable the Block Transfer Engine (BTE) and define the transfer size in REG[51h], Bit[3:0] = 0Ch.
        4. Set the background color for clearing the screen in REG[63h], [64h], [65h].
        5. Enable the BTE function by configuring REG[50h] Bit7 = 1.
        6. After the configuration, check the operation status in the STSR register (Bit6), confirming that the BTE operation is completed.
    */
    BTE_SetTarBlock(s_WinX, s_WinY, s_WinHeight, s_WinWidth, 0);
    BTE_SetOperateCode(0x0C);         /* Set the operation code and enable the Block Transfer Engine (BTE) transfer in REG[51h], Bit[3:0] = 0Ch */
    RA8875_SetFrontColor(_usColor);   /* Set the BTE background color */
    BTE_Start();					    /* Enable the Block Transfer Engine (BTE) */
    BTE_Wait();						/* Wait for the operation to complete */

}

/*
*********************************************************************************************************
*  Function Name: RA8875_SetFrontColor
*  Description: Set the foreground color.
*  Parameters:
*          _usColor : The foreground color to be set.
*  Return Type: None
*********************************************************************************************************
*/
void RA8875_SetFrontColor(uint16_t _usColor)
{
    RA8875_WriteReg(0x63, (_usColor & 0xF800) >> 11);	/* R5  */
	RA8875_WriteReg(0x64, (_usColor & 0x07E0) >> 5);	/* G6 */
	RA8875_WriteReg(0x65, (_usColor & 0x001F));			/* B5 */
}

static void RA8875_WriteReg(uint8_t _ucRegAddr, uint8_t _ucRegValue)
{
    s_ucRA8875Busy = 1;

    RA8875_WriteCmd(_ucRegAddr);
    RA8875_WriteData(_ucRegValue);

    s_ucRA8875Busy = 0;
}


/**
 **********************************************************************************
 * @file   TM1638_platform.c
 * @author Hossein.M (https://github.com/Hossein-M98)
 * @brief  A sample Platform dependent layer for TM1638 Driver
 **********************************************************************************
 *
 * Copyright (c) 2021 Mahda Embedded System (MIT License)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************************************
 */
  
/* Includes ---------------------------------------------------------------------*/
#include "TM1638_platform_stm32.h"
#include "main.h"



/**
 ==================================================================================
                           ##### Private Functions #####                           
 ==================================================================================
 */

void TM1638_SetGPIO_OUT(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
									
void TM1638_SetGPIO_IN_PU(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static void TM1638_PlatformInit(void)
{
  TM1638_SetGPIO_OUT(TM1638_CLK_GPIO, TM1638_CLK_PIN);
  TM1638_SetGPIO_OUT(TM1638_STB_GPIO, TM1638_STB_PIN);
  TM1638_SetGPIO_OUT(TM1638_DIO_GPIO, TM1638_DIO_PIN);
}

static void TM1638_PlatformDeInit(void)
{
}

static void TM1638_DioConfigOut(void)
{
  TM1638_SetGPIO_OUT(TM1638_DIO_GPIO, TM1638_DIO_PIN);
}

static void TM1638_DioConfigIn(void)
{
  TM1638_SetGPIO_IN_PU(TM1638_DIO_GPIO, TM1638_DIO_PIN);
}

static void TM1638_DioWrite(uint8_t Level)
{
  HAL_GPIO_WritePin(TM1638_DIO_GPIO, TM1638_DIO_PIN, Level);
}

static uint8_t TM1638_DioRead(void)
{
  uint8_t Result = 1;
  Result = HAL_GPIO_ReadPin(TM1638_DIO_GPIO, TM1638_DIO_PIN);
  return Result;
}

static void TM1638_ClkWrite(uint8_t Level)
{
  HAL_GPIO_WritePin(TM1638_CLK_GPIO, TM1638_CLK_PIN, Level);
}

static void TM1638_StbWrite(uint8_t Level)
{
  HAL_GPIO_WritePin(TM1638_STB_GPIO, TM1638_STB_PIN, Level);
}

static void TM1638_DelayUs(uint8_t Delay)
{
  for (uint32_t DelayCounter = 0; DelayCounter < 100 * Delay; DelayCounter++)
    DelayCounter = DelayCounter;
}

/**
 ==================================================================================
                            ##### Public Functions #####                           
 ==================================================================================
 */
 
/**
 * @brief  Initialize platfor device to communicate TM1638.
 * @param  Handler: Pointer to handler
 * @retval None
 */
void TM1638_Platform_Init(TM1638_Handler_t *Handler)
{
  Handler->PlatformInit = TM1638_PlatformInit;
  Handler->PlatformDeInit = TM1638_PlatformDeInit;
  Handler->DioConfigOut = TM1638_DioConfigOut;
  Handler->DioConfigIn = TM1638_DioConfigIn;
  Handler->DioWrite = TM1638_DioWrite;
  Handler->DioRead = TM1638_DioRead;
  Handler->ClkWrite = TM1638_ClkWrite;
  Handler->StbWrite = TM1638_StbWrite;
  Handler->DelayUs = TM1638_DelayUs;
}

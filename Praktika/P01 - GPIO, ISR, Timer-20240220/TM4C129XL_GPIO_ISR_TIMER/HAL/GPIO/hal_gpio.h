/**
 ****************************************************************
 @file    hal_gpio.h
 ****************************************************************
 @brief   This module offers a set of functions to handle GPIO's.
 ****************************************************************
 @author  Adrian Tuescher, IMES/HSR
 @version 01.000
 @date    2017-02-28
 ****************************************************************
 */
#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

// --- Includes
#include <stdint.h>
#include "../../GLOB_Types.h"

// --- Defines

// --- Typedefs
//! A enumeration which represent all GPIO peripherals
typedef enum
{
  GPIO_USR_SW1 = 0, //PJ.0
  GPIO_USR_SW2,     //PJ.1
  GPIO_D1,          //PN.1
  GPIO_D2,          //PN.0
  GPIO_D3,          //PF.4
  GPIO_D4,          //PF.0
  GPIO_BP_T1,       //PK.5
  GPIO_BP_T2,       //PH.0
  GPIO_MOT_ENA,     //PA.7
  GPIO_DCF77,       //PM.2
  GPIO_LAST_PERIPHERIE
} gpioPeripherie_t;

// --- Function Prototypes
void hal_gpio_init(void);

void hal_gpio_interruptCallbackFctRegister(gpioPeripherie_t gpio, pFctHandler pCallbackFct);
void hal_gpio_interruptEnable(gpioPeripherie_t gpio);
void hal_gpio_interruptDisable(gpioPeripherie_t gpio);

bool_t hal_gpio_read(gpioPeripherie_t gpio);
void hal_gpio_write(gpioPeripherie_t gpio, bool_t on);

#endif /* HAL_GPIO_H_ */

/**
 ****************************************************************
 @file    hal_timer.h
 ****************************************************************
 @brief   This module offers a set of functions to handle a timer.
 ****************************************************************
 @author  Adrian Tuescher, IMES/HSR
 @version 01.000
 @date    2017-01-30
 ****************************************************************
 */
#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

// --- Includes
#include <stdint.h>
#include "../../GLOB_Types.h"

// --- Defines

// --- Typedefs

// --- Function Prototypes
void hal_timer_init(uint32_t msInterval, pFctHandler pCallbackFct);

void hal_timer_start(void);
void hal_timer_stop(void);

#endif /* HAL_GPIO_H_ */

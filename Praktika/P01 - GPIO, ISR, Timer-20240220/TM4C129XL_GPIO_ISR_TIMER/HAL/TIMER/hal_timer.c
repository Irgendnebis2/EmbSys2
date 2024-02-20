/**
 ****************************************************************
 @file    hal_timer.c
 ****************************************************************
 @brief   This module offers a set of functions to handle a timer.
 ****************************************************************
 @author  Adrian Tuescher, IMES/HSR
 @version 01.000
 @date    2017-01-30
 ****************************************************************
 */
// --- Includes
#include <stdint.h>
#include <stdbool.h>
#include "hal_timer.h"
#include "../../GLOB_Types.h"
#include "../../ESP_EKTM4C1294XL.h"
#include "../tm4c1294ncpdt.h"

// --- Defines

// --- Typedefs

// --- Local Function Prototypes
void _hal_timer_t5ccp1ISR(void);

// --- Variables
static pFctHandler _hal_timer_callbackFct = (pFctHandler) 0x00000000;

/**
 ****************************************************************
 @brief  Initialize the timer5 captureCompare1 as cycle timer.
 @brief  Note: Output PM7 is toggled after a complete time interval.
 @param  msInterval   Timer-Interval [milliseconds] (1 up to 139 is possible)
 @param  pCallbackFct The to be called function from timer5 captureCompare1 ISR.
 @return -
 ****************************************************************
 */
void hal_timer_init(uint32_t msInterval, pFctHandler pCallbackFct)
{
  uint32_t clkFreq = 0;
  uint32_t interval = 0;

  ///@todo Aufgabe 2.5 TIMER Output konfigurieren

  ///@todo Aufgabe 2.4.1 hal_timer_init

  ///@todo Aufgabe 2.5 TIMER Output konfigurieren

  ///@todo Aufgabe 2.4.1 hal_timer_init

}

/**
 ****************************************************************
 @brief  Enable the timer counting.
 @param  -
 @return -
 ****************************************************************
 */
void hal_timer_start(void)
{
  ///@todo Aufgabe 2.4.2 hal_timer_start

}

/**
 ****************************************************************
 @brief  Disable the timer counting.
 @param  -
 @return -
 ****************************************************************
 */
void hal_timer_stop(void)
{
  ///@todo Aufgabe 2.4.3 hal_timer_stop

}

/**
 ****************************************************************
 @brief  Interrupt service routine of T5CCP1.
 @param  -
 @return -
 ****************************************************************
 */
void _hal_timer_t5ccp1ISR(void)
{
  ///@todo Aufgabe 2.4.1 hal_timer_init

}

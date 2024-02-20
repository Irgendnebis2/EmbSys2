/**
 ****************************************************************
 @file    utils.c
 ****************************************************************
 @brief   This module offers some general utility functions.
 ****************************************************************
 @author  Adrian Tuescher, IMES/HSR
 @version 01.002
 @date    2021-02-05
 ***************************************************************
 */
// --- Includes
#include <stdbool.h>
#include <stdint.h>
#include "utils.h"

// --- Defines
#define UTILS_SYSCLK		120000000		//120MHz
#define UTILS_MS_FACTOR		(UTILS_SYSCLK / 3000)

// --- Typedefs

// --- Local Function Prototypes
void _utils_threeSysClkDelay(uint32_t value);

// --- Variables
static uint32_t _enabledStateInterrupt = false;

/**
 ****************************************************************
 @brief   Busy-Wait function for a delay.
 @param   ms  Busy-Delay time in milliseconds
 @return  -
 ****************************************************************
 */
void utils_busyDelayMs(uint32_t ms)
{
  //-9 gives the best matching result (2 clock cycles longer delay then it should be, note that
  //interrupts may give additional delay!)
  _utils_threeSysClkDelay((UTILS_MS_FACTOR * ms) - 9); //one loop inside this function needs 3clock-cyles
}

/**
 ****************************************************************
 @brief    Enable the global interrupt (set PRIMMASK)
 @param    -
 @return   -
 ****************************************************************
 */
void utils_interruptEnable(void)
{
  // Read PRIMASK and enable interrupts
  __asm("    mrs     r0, PRIMASK\n"
        "    cpsie   i\n"
        "    bx      lr\n");

  _enabledStateInterrupt = 0x01;
}

/**
 ****************************************************************
 @brief   Disable the global interrupt (clear PRIMMASK)
 @param   -
 @return  -
 ****************************************************************
 */
void utils_interruptDisable(void)
{
  // Read PRIMASK and disable interrupts
  __asm("    mrs     r0, PRIMASK\n"
        "    cpsid   i\n"
        "    bx      lr\n");

  _enabledStateInterrupt = 0x00;
}

/**
 ****************************************************************
 @brief   Enable the global interrupt (set PRIMMASK) only, if
 @brief   the enabledState is true.
 @param   pEnaState  Pointer to the last enabledState.
 @return  -
 ****************************************************************
 */
void utils_interruptEnableProtected(uint32_t* pEnaState)
{
  if(*pEnaState != 0x00)
  {
    // Read PRIMASK and enable interrupts
    __asm("    mrs     r0, PRIMASK\n"
          "    cpsie   i\n"
          "    bx      lr\n");

    _enabledStateInterrupt = 0x01;
  }
}

/**
 ****************************************************************
 @brief   Disable the global interrupt (set PRIMMASK) and return the
 @brief   the last enabled State of the global interrupt by Reference.
 @param   pEnaState  Pointer to the last enabledState.
 @return  -
 ****************************************************************
 */
void utils_interruptDisableProtected(uint32_t* pEnaState)
{
  // Read PRIMASK and disable interrupts
  __asm("    mrs     r0, PRIMASK\n"
        "    cpsid   i\n"
        "    bx      lr\n");

  *pEnaState = _enabledStateInterrupt;
  
  _enabledStateInterrupt = 0x00;
}

/**
 ****************************************************************
 @brief   Local module function in pure assembly for the delay.
 @brief   This prevents the TI compiler from doing funny things
 @brief   with the optimizer.
 @param   -
 @return  -
 ****************************************************************
 */
__asm("    .sect \".text:_utils_threeSysClkDelay\"\n"
  "    .clink\n"
  "    .thumbfunc _utils_threeSysClkDelay\n"
  "    .thumb\n"
  "    .global _utils_threeSysClkDelay\n"
  "_utils_threeSysClkDelay:\n"
  "    subs r0, #1\n"
  "    bne.n _utils_threeSysClkDelay\n"
  "    bx lr\n");

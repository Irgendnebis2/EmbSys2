/**
 ****************************************************************
 @file    GLOB_Types.h
 ****************************************************************
 @brief   Defines common types to be used in project.
 ****************************************************************
 @author  Adrian Tuescher, IMES/HSR
 @version 0.0
 @date    2014-01-09
 ****************************************************************
 */
#ifndef GLOB_TYPES_H
#define GLOB_TYPES_H

// --- Includes
#include <stdbool.h>

// --- Defines
#define FALSE   false
#define TRUE    true

//*****************************************************************************
//
// Macros for hardware access
//
//*****************************************************************************
#define HWREG32(x)                                                              \
    (*((volatile uint32_t *)((uint16_t)x)))
#define HWREG16(x)                                                             \
    (*((volatile uint16_t *)((uint16_t)x)))
#define HWREG8(x)                                                             \
    (*((volatile uint8_t *)((uint16_t)x)))


// --- Typedefs
typedef float   float32_t;
typedef bool    bool_t;

typedef void (*pFctHandler)(void);
typedef bool_t (*pFctHandlerBoolVoid)(void);

/**
****************************************************************
@brief  Error type enumeration.
****************************************************************
*/
typedef enum
{
  NO_ERROR = 0,
  ERROR_PARAM,
  ERROR_HAL,
  ERROR_HAL_TIMEOUT,
  ERROR_HAL_RXEMPTY,
  ERROR_OBJ,
  ERROR_OBJ_TIMEOUT,
  ERROR_OBJ_BADFORMAT,
  ERROR_OBJ_BADCOMMAND
} error_t;       //Error Codes

#endif /* #ifndef GLOB_TYPES_H */

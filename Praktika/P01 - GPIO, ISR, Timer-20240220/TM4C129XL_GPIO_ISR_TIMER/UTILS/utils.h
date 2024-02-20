/**
****************************************************************
@file     utils.h
****************************************************************
@brief    This module offers some general utility functions.
****************************************************************
@author   Adrian Tuescher, IMES/HSR
@version  01.002
@date     2021-02-05
***************************************************************/
#ifndef UTILS_H_
#define UTILS_H_

// --- Includes
#include <stdint.h>

// --- Defines

// --- Typedefs

// --- Function Prototypes
void utils_busyDelayMs(uint32_t ms);
void utils_interruptEnable(void);
void utils_interruptDisable(void);
void utils_interruptEnableProtected(uint32_t* enabledState);
void utils_interruptDisableProtected(uint32_t* enabledState);

#endif /*UTILS_H_*/

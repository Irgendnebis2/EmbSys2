/**
 ****************************************************************
 @file    ESP_EKTM4C1294XL.h
 ****************************************************************
 @brief   This module offers all possible functions from the
 @brief   EK-TM4C1294XL Launchpad to the Embedded System Platform.
 ****************************************************************
 @author  Adrian Tuescher, IMES/HSR
 @version 1.500.000
 @date    2019-01-11
 ****************************************************************
 */
#ifndef ESP_EKTM4C1294XL_H_
#define ESP_EKTM4C1294XL_H_

// --- Includes
#include <stdbool.h>
#include <stdint.h>

// --- Defines

// --- Typedefs
typedef void (*pEsespLib_pFctHandler) (void);

typedef enum
{
  INT_ESPLIB_GPIO_RISING_EDGE = 0,
  INT_ESPLIB_GPIO_FALLING_EDGE,
  INT_ESPLIB_GPIO_BOTH_EDGE
} espIntCfg_t;

// --- Function Prototypes
uint32_t esp_init (void);
uint32_t esp_sysCtlClockGet (void);

bool esp_buzzerEna (bool enable);
void esp_buzzerFreq (uint16_t frequency);

void esp_lcdClr (void);
void esp_lcdDrawVLine (uint8_t x0, uint8_t y0, uint8_t h, bool opaque);
void esp_lcdDrawHLine (uint8_t x0, uint8_t y0, uint8_t w, bool opaque);
void esp_lcdDrawRect (uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, bool opaque);
void esp_lcdFillRect (uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, bool opaque);
uint8_t esp_lcdTxt (uint8_t pos, uint8_t line, char* txt);
void esp_lcdBLight (uint8_t red, uint8_t green);

void esp_dbgOutInit (uint8_t number, bool updateLED);
void esp_dbgOutSet (uint8_t number, bool updateLED);
void esp_dbgOutClear (uint8_t number, bool updateLED);
void esp_dbgOutToggle (uint8_t number, bool updateLED);

uint16_t esp_bt (void);
void esp_btIntSetup (uint8_t intNr, espIntCfg_t config, pEsespLib_pFctHandler pCallbackFct);
void esp_btIntEna (uint16_t mask, uint16_t ena);

void esp_led (uint16_t mask, uint16_t value);
void esp_rgbLed (uint8_t red, uint8_t green, uint8_t blue, bool leftSide);

#endif /* ESP_EKTM4C1294XL_H_ */

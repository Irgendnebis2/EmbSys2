/**
 ****************************************************************
 @file    main.c
 ****************************************************************
 @brief   Main for the Embedded-Systems Praktikum P01.
 ****************************************************************
 @author  Adrian Tuescher, IMES/HSR
 @version 01.000
 @date    2017-01-30
 ****************************************************************
 */
// --- Includes
#include <stdio.h>
#include <stdint.h>

#include "ESP_EKTM4C1294XL.h"
#include "HAL/GPIO/hal_gpio.h"
#include "HAL/TIMER/hal_timer.h"

// --- Defines

// --- Typedefs

// --- Local Function Prototypes
void _usr_sw1_callbackFct(void);
void _usr_sw2_callbackFct(void);
void _timer_callbackFct(void);

// --- Variables

/**
 ****************************************************************
 @brief   Main program
 @param   -
 @return  -
 ****************************************************************
 */
int main(void)
{
  volatile uint32_t version = 0;

  version = esp_init();

  hal_gpio_init();  //init the GPIOs
  hal_gpio_interruptCallbackFctRegister(GPIO_USR_SW1, _usr_sw1_callbackFct);  //setup callback for USR_SW1 interrupt
  hal_gpio_interruptCallbackFctRegister(GPIO_USR_SW2, _usr_sw2_callbackFct);  //setup callback for USR_SW2 interrupt
  hal_gpio_interruptEnable(GPIO_USR_SW1);   //enable interrupts for USR_SW1
  hal_gpio_interruptEnable(GPIO_USR_SW2);   //enable interrupts for USR_SW2

  hal_timer_init(100, _timer_callbackFct);  //init the interval-TIMER
  hal_timer_start();                        //start the interval-TIMER

  while(1)
  {
    if(hal_gpio_read(GPIO_USR_SW1))
    {
      hal_gpio_write(GPIO_D1, true);
      hal_gpio_write(GPIO_D2, true);
      hal_gpio_write(GPIO_D3, true);
      hal_gpio_write(GPIO_D4, true);
    }
    else
    {
      hal_gpio_write(GPIO_D1, false);
      hal_gpio_write(GPIO_D2, false);
      hal_gpio_write(GPIO_D3, false);
      hal_gpio_write(GPIO_D4, false);
    }
  }
}

void _usr_sw1_callbackFct(void)
{
  static bool_t on = true;
  hal_gpio_write(GPIO_D1, on);

  on ^= true;
}

void _usr_sw2_callbackFct(void)
{
  static bool_t on = true;
  hal_gpio_write(GPIO_D2, on);

  on ^= true;
}

void _timer_callbackFct(void)
{

  static bool_t on = true;
  hal_gpio_write(GPIO_D4, on);

  on ^= true;
}

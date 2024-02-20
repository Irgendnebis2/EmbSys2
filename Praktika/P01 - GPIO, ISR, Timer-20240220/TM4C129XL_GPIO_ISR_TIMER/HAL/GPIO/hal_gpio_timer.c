/**
 ****************************************************************
 @file    hal_gpio.c
 ****************************************************************
 @brief   This module offers a set of functions to handle GPIO's.
 ****************************************************************
 @author  Adrian Tuescher, IMES/HSR
 @version 01.000
 @date    2017-02-28
 ****************************************************************
 */
// --- Includes
#include <stdint.h>
#include <stdbool.h>
#include "hal_gpio.h"
#include "../tm4c1294ncpdt.h"

// --- Defines

// --- Typedefs

// --- Local Function Prototypes
void _hal_gpio_portHISR(void);
void _hal_gpio_portJISR(void);
void _hal_gpio_portKISR(void);
void _hal_gpio_portMISR(void);

// --- Variables
static pFctHandler _hal_gpio_btCallbackFct[5] =
{
  (pFctHandler) 0x00000000,  //GPIO_USR_SW1 callback function pointer
  (pFctHandler) 0x00000000,  //GPIO_USR_SW2 callback function pointer
  (pFctHandler) 0x00000000,  //GPIO_BP_T1 callback function pointer
  (pFctHandler) 0x00000000,  //GPIO_BP_T2 callback function pointer
  (pFctHandler) 0x00000000
//GPIO_DCF77 callback function pointer
  };

/**
 ****************************************************************
 @brief  Initialize a all GPIOs of the TM4C1294XL-LaunchPad.
 @param  -
 @return -
 ****************************************************************
 */
void hal_gpio_init(void)
{
  //GPIO Konfigurieren

  //*****************************************************//
  //************ GPIO_USR_SW1 & GPIO_USR_SW2 ************//
  //*****************************************************//
  SYSCTL_RCGCGPIO_R |= 0x00000100;    //Enable clock of port J
  while(!(SYSCTL_PRGPIO_R & 0x00000100)); //wait until ready

  GPIO_PORTJ_DIR_R &= ~0x00000003;    //GPIO PortJ 0 & 1 as Input
  GPIO_PORTJ_PUR_R |= 0x00000003;     //Enable pullup
  GPIO_PORTJ_DEN_R |= 0x00000003;     //enable pins as digital

  //Interrupt Konfigurieren
  GPIO_PORTJ_IM_R &= ~0x00000003;     //clear interrupt mask (GPIOIM)
  GPIO_PORTJ_IS_R &= ~0x00000003;     //setup interrupt sense as edge detection(GPIOIS)
  GPIO_PORTJ_IBE_R &= ~0x00000003;    //clear interrupt both edge (GPIOIBE)
  GPIO_PORTJ_IEV_R &= ~0x00000003;    //set falling edge as trigger for an interrupt (GPIOEV)
  GPIO_PORTJ_ICR_R |= 0x00000003;     //clear interrupt (GPIOICR)
  GPIO_PORTJ_IM_R &= ~0x00000003;     //disable interrupts (GPIOIM)

  NVIC_EN1_R = 0x00080000;            //enable GPIO PortJ Interrupts on NVIC
                                      //GPIO PortJ Vector Number 67, but InterruptNumber 51

  //*****************************************************//
  //***************** GPIO_D1 & GPIO_D2 *****************//
  //*****************************************************//
  SYSCTL_RCGCGPIO_R |= 0x00001000;    //Enable clock of port N
  while(!(SYSCTL_PRGPIO_R & 0x00001000)); //wait until ready

  GPIO_PORTN_DIR_R |= 0x00000003;     //GPIO PortN 0 & 1 als Outputs
  GPIO_PORTN_DR2R_R |= 0x00000003;    //configure output current up to 2mA
  GPIO_PORTN_DATA_R &= ~0x00000003;   //set output value to zero (LED OFF)
  GPIO_PORTN_DEN_R |= 0x00000003;     //enable pins as digital

  //*****************************************************//
  //***************** GPIO_D3 & GPIO_D4 *****************//
  //*****************************************************//
  SYSCTL_RCGCGPIO_R |= 0x00000020;    //Enable clock of port F
  while(!(SYSCTL_PRGPIO_R & 0x00000020)); //wait until ready

  GPIO_PORTF_DIR_R |= 0x00000011;     //GPIO PortF 0 & 4 als Outputs
  GPIO_PORTF_DR8R_R |= 0x00000011;    //configure output current up to 8mA
  GPIO_PORTF_DATA_R &= ~0x00000011;   //set output value to zero (LED OFF)
  GPIO_PORTF_DEN_R |= 0x00000011;     //enable pins as digital

  //*****************************************************//
  //************ GPIO_BP_T1 *****************************//
  //*****************************************************//
  SYSCTL_RCGCGPIO_R |= 0x00000200;    //Enable clock of port K
  while(!(SYSCTL_PRGPIO_R & 0x00000200)); //wait until ready

  GPIO_PORTK_DIR_R &= ~0x00000020;    //GPIO PortK 5 as Input
  GPIO_PORTK_DEN_R |= 0x00000020;     //enable pins as digital

  //Interrupt Konfigurieren
  GPIO_PORTK_IM_R &= ~0x00000020;     //clear interrupt mask (GPIOIM)
  GPIO_PORTK_IS_R &= ~0x00000020;     //setup interrupt sense as edge detection(GPIOIS)
  GPIO_PORTK_IBE_R &= ~0x00000020;    //clear interrupt both edge (GPIOIBE)
  GPIO_PORTK_IEV_R &= ~0x00000020;    //set falling edge as trigger for an interrupt (GPIOEV)
  GPIO_PORTK_ICR_R |= 0x00000020;     //clear interrupt (GPIOICR)
  GPIO_PORTK_IM_R &= ~0x00000020;     //disable interrupts (GPIOIM)

  NVIC_EN1_R = 0x00100000;            //enable GPIO PortK Interrupts on NVIC
                                      //GPIO PortK Vector Number 68, but InterruptNumber 52

  //*****************************************************//
  //************ GPIO_BP_T2 *****************************//
  //*****************************************************//
  SYSCTL_RCGCGPIO_R |= 0x00000080;    //Enable clock of port H
  while(!(SYSCTL_PRGPIO_R & 0x00000080)); //wait until ready

  GPIO_PORTH_DIR_R &= ~0x00000001;    //GPIO PortH 0 as Input
  GPIO_PORTH_DEN_R |= 0x00000001;     //enable pins as digital

  //Interrupt Konfigurieren
  GPIO_PORTH_IM_R &= ~0x00000001;     //clear interrupt mask (GPIOIM)
  GPIO_PORTH_IS_R &= ~0x00000001;     //setup interrupt sense as edge detection(GPIOIS)
  GPIO_PORTH_IBE_R &= ~0x00000001;    //clear interrupt both edge (GPIOIBE)
  GPIO_PORTH_IEV_R &= ~0x00000001;    //set falling edge as trigger for an interrupt (GPIOEV)
  GPIO_PORTH_ICR_R |= 0x00000001;     //clear interrupt (GPIOICR)
  GPIO_PORTH_IM_R &= ~0x00000001;     //disable interrupts (GPIOIM)

  NVIC_EN1_R = 0x00000001;            //enable GPIO PortH Interrupts on NVIC
                                      //GPIO PortH Vector Number 48, but InterruptNumber 32

  //*****************************************************//
  //***************** GPIO_MOT_ENA **********************//
  //*****************************************************//
  SYSCTL_RCGCGPIO_R |= 0x00000001;    //Enable clock of port A
  while(!(SYSCTL_PRGPIO_R & 0x00000001)); //wait until ready

  GPIO_PORTA_DIR_R |= 0x00000080;     //GPIO PortA 7 als Outputs
  GPIO_PORTA_DR8R_R |= 0x00000080;    //configure output current up to 8mA
  GPIO_PORTA_DATA_R &= ~0x00000080;   //set output value to zero (Motor OFF)
  GPIO_PORTA_DEN_R |= 0x00000080;     //enable pins as digital

  //*****************************************************//
  //********************* GPIO_DCF77 ********************//
  //*****************************************************//
  SYSCTL_RCGCGPIO_R |= 0x00000800;    //Enable clock of port M
  while(!(SYSCTL_PRGPIO_R & 0x00000800)); //wait until ready

  GPIO_PORTM_DIR_R &= ~0x00000004;    //GPIO PortM 2 as Input
  GPIO_PORTM_DEN_R |= 0x00000004;     //enable pins as digital

  //Interrupt Konfigurieren
  GPIO_PORTM_IM_R &= ~0x00000004;     //clear interrupt mask (GPIOIM)
  GPIO_PORTM_IS_R &= ~0x00000004;     //setup interrupt sense as edge detection(GPIOIS)
  GPIO_PORTM_IBE_R &= ~0x00000004;    //clear interrupt both edge (GPIOIBE)
  GPIO_PORTM_IEV_R |= 0x00000004;     //set rising edge as trigger for an interrupt (GPIOEV)
  GPIO_PORTM_ICR_R |= 0x00000004;     //clear interrupt (GPIOICR)
  GPIO_PORTM_IM_R &= ~0x00000004;     //disable interrupts (GPIOIM)

  NVIC_EN2_R = 0x00000100;            //enable GPIO PortM Interrupts on NVIC
                                      //GPIO PortM Vector Number 88, but InterruptNumber 72
}

/**
 ****************************************************************
 @brief  Register a callback function for one of the possible input GPIO's.
 @param  gpio    One of the possible gpio from enumeration
 @param  pCallbackFct Callback function for this input.
 @return -
 ****************************************************************
 */
void hal_gpio_interruptCallbackFctRegister(gpioPeripherie_t gpio, pFctHandler pCallbackFct)
{
  switch(gpio)
  {
    case GPIO_USR_SW1: //PJ0
      _hal_gpio_btCallbackFct[0] = pCallbackFct;
      break;
    case GPIO_USR_SW2: //PJ1
      _hal_gpio_btCallbackFct[1] = pCallbackFct;
      break;
    case GPIO_BP_T1: //PK.5
      _hal_gpio_btCallbackFct[2] = pCallbackFct;
      break;
    case GPIO_BP_T2: //PH.0
      _hal_gpio_btCallbackFct[3] = pCallbackFct;
      break;
    case GPIO_DCF77: //PM.2
      _hal_gpio_btCallbackFct[4] = pCallbackFct;
      break;
    default:
      break;
  }
}

/**
 ****************************************************************
 @brief  Enable interrupt for one of the possible GPIOs from enumeration.
 @param  gpio    One of the possible gpio from enumeration
 @return -
 ****************************************************************
 */
void hal_gpio_interruptEnable(gpioPeripherie_t gpio)
{
  switch(gpio)
  {
    case GPIO_USR_SW1: //PJ0
      GPIO_PORTJ_IM_R |= 0x00000001;
      break;
    case GPIO_USR_SW2: //PJ1
      GPIO_PORTJ_IM_R |= 0x00000002;
      break;
    case GPIO_BP_T1: //PK.5
      GPIO_PORTK_IM_R |= 0x00000020;
      break;
    case GPIO_BP_T2: //PH.0
      GPIO_PORTH_IM_R |= 0x00000001;
      break;
    case GPIO_DCF77: //PM.2
      GPIO_PORTM_IM_R |= 0x00000004;
      break;
    default:
      break;
  }
}

/**
 ****************************************************************
 @brief  Disable interrupt for one of the possible GPIOs from enumeration.
 @param  gpio    One of the possible gpio from enumeration
 @return -
 ****************************************************************
 */
void hal_gpio_interruptDisable(gpioPeripherie_t gpio)
{
  switch(gpio)
  {
    case GPIO_USR_SW1: //PJ0
      GPIO_PORTJ_IM_R &= ~0x00000001;
      break;
    case GPIO_USR_SW2: //PJ1
      GPIO_PORTJ_IM_R &= ~0x00000002;
      break;
    case GPIO_BP_T1: //PK.5
      GPIO_PORTK_IM_R &= ~0x00000020;
      break;
    case GPIO_BP_T2: //PH.0
      GPIO_PORTH_IM_R &= ~0x00000001;
      break;
    case GPIO_DCF77: //PM.2
      GPIO_PORTM_IM_R &= ~0x00000004;
      break;
    default:
      break;
  }
}

/**
 ****************************************************************
 @brief  Read a complete port.
 @param  gpio    One of the possible gpio from enumeration
 @return Return true, if a button is pressed.
 ****************************************************************
 */
bool_t hal_gpio_read(gpioPeripherie_t gpio)
{
  bool_t res = false;
  switch(gpio)
  {
    case GPIO_USR_SW1:  //if zero, button is pressed
      if((GPIO_PORTJ_DATA_R & 0x00000001) == 0)
      {
        res = true;
      }
      break;
    case GPIO_USR_SW2:  //if zero, button is pressed
      if((GPIO_PORTJ_DATA_R & 0x00000002) == 0)
      {
        res = true;
      }
      break;
    case GPIO_BP_T1:    //if zero, button is pressed
      if((GPIO_PORTK_DATA_R & 0x00000020) == 0)
      {
        res = true;
      }
      break;
    case GPIO_BP_T2:    //if zero, button is pressed
      if((GPIO_PORTH_DATA_R & 0x00000001) == 0)
      {
        res = true;
      }
      break;
    case GPIO_DCF77:
      if(GPIO_PORTM_DATA_R & 0x00000004)
      {
        res = true;
      }
      break;
    default:
      break;
  }
  return res;
}

/**
 ****************************************************************
 @brief  Write a port or just single bits (depending on selected gpio)
 @param  gpio    One of the possible gpio from enumeration
 @param  on   If true, led is turn on
 @return -
 ****************************************************************
 */
void hal_gpio_write(gpioPeripherie_t gpio, bool_t on)
{
  switch(gpio)
  {
    case GPIO_D1: //PortN1
      //set/clear LED_D1
      if(on == true)
      {
        GPIO_PORTN_DATA_R |= 0x0000002;
      }
      else
      {
        GPIO_PORTN_DATA_R &= ~0x0000002;
      }
      break;
    case GPIO_D2: //PortN0
      //set/clear LED_D2
      if(on == true)
      {
        GPIO_PORTN_DATA_R |= 0x0000001;
      }
      else
      {
        GPIO_PORTN_DATA_R &= ~0x0000001;
      }
      break;
    case GPIO_D3: //PortF4
      //set/clear LED_D3
      if(on == true)
      {
        GPIO_PORTF_DATA_R |= 0x0000010;
      }
      else
      {
        GPIO_PORTF_DATA_R &= ~0x0000010;
      }
      break;
    case GPIO_D4: //PortF0
      //set/clear LED_D4
      if(on == true)
      {
        GPIO_PORTF_DATA_R |= 0x0000001;
      }
      else
      {
        GPIO_PORTF_DATA_R &= ~0x0000001;
      }
      break;
    case GPIO_MOT_ENA:  //PortA.7
      //set/clear motor enable
      if(on == true)
      {
        GPIO_PORTA_DATA_R |= 0x0000080;
      }
      else
      {
        GPIO_PORTA_DATA_R &= ~0x0000080;
      }
      break;
    default:
      break;
  }
}

/**
 ****************************************************************
 @brief  Interrupt service routine of portH.
 @param  -
 @return -
 ****************************************************************
 */
void _hal_gpio_portHISR(void)
{
  uint32_t status = 0x00000000;

  NVIC_DIS1_R = 0x00000001;       //disable PortH interrupts (cleared by writing a one)

  status = GPIO_PORTH_MIS_R;      //get masked interrupt status
  GPIO_PORTH_ICR_R |= status;     //clear all pending interrupts

  if(status & 0x00000001)         //check if GPIO_BP_T2 interrupt event occured
  {
    if(_hal_gpio_btCallbackFct[3] != 0x00000000)  //do function callback, if a callback is registered
    {
      _hal_gpio_btCallbackFct[3]();
    }
  }
  NVIC_EN1_R = 0x00000001;        //enable PortH interrupts
}

/**
 ****************************************************************
 @brief  Interrupt service routine of portJ.
 @param  -
 @return -
 ****************************************************************
 */
void _hal_gpio_portJISR(void)
{
  uint32_t status = 0x00000000;

  NVIC_DIS1_R = 0x00080000;       //disable PortJ interrupts (cleared by writing a one)

  status = GPIO_PORTJ_MIS_R;      //get masked interrupt status
  GPIO_PORTJ_ICR_R |= status;     //clear all pending interrupts

  if(status & 0x00000001)         //check if USR_SW1 interrupt event occured
  {
    if(_hal_gpio_btCallbackFct[0] != 0x00000000)  //do function callback, if a callback is registered
    {
      _hal_gpio_btCallbackFct[0]();
    }
  }
  if(status & 0x00000002)         //check if USR_SW2 interrupt event occured
  {
    if(_hal_gpio_btCallbackFct[1] != 0x00000000)  //do function callback, if a callback is registered
    {
      _hal_gpio_btCallbackFct[1]();
    }
  }
  NVIC_EN1_R = 0x00080000;        //enable PortJ interrupts
}

/**
 ****************************************************************
 @brief  Interrupt service routine of portK.
 @param  -
 @return -
 ****************************************************************
 */
void _hal_gpio_portKISR(void)
{
  uint32_t status = 0x00000000;

  NVIC_DIS1_R = 0x00100000;       //disable PortK interrupts (cleared by writing a one)

  status = GPIO_PORTK_MIS_R;      //get masked interrupt status
  GPIO_PORTK_ICR_R |= status;     //clear all pending interrupts

  if(status & 0x00000020)         //check if GPIO_BP_T1 interrupt event occured
  {
    if(_hal_gpio_btCallbackFct[2] != 0x00000000)  //do function callback, if a callback is registered
    {
      _hal_gpio_btCallbackFct[2]();
    }
  }
  NVIC_EN1_R = 0x00100000;        //enable PortK interrupts
}

/**
 ****************************************************************
 @brief  Interrupt service routine of portM.
 @param  -
 @return -
 ****************************************************************
 */
void _hal_gpio_portMISR(void)
{
  uint32_t status = 0x00000000;

  NVIC_DIS2_R = 0x00000100;       //disable PortM interrupts (cleared by writing a one)

  status = GPIO_PORTM_MIS_R;      //get masked interrupt status
  GPIO_PORTM_ICR_R |= status;     //clear all pending interrupts

  if(status & 0x00000004)         //check if GPIO_DCF77 interrupt event occured
  {
    if(_hal_gpio_btCallbackFct[4] != 0x00000000)  //do function callback, if a callback is registered
    {
      _hal_gpio_btCallbackFct[4]();
    }
  }
  NVIC_EN2_R = 0x00000100;        //enable PortM interrupts
}

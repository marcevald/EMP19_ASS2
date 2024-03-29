/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (EMP)
*
* MODULENAME.: led_driver.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Drive LED on TIVA C
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 080319  MEE   Module created.
*
*****************************************************************************/

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void led_on(INT8U color);
/*****************************************************************************
*   Input    : - Color of led to turn on
*   Output   : -
*   Function : Turn led on
******************************************************************************/

void led_off(INT8U color);
/*****************************************************************************
*   Input    : - Color of led to turn off
*   Output   : -
*   Function : Turn led off
******************************************************************************/

/****************************** End Of Module *******************************/
#endif /*LED_DRIVER_H_*/
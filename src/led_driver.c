/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (EMP)
*
* MODULENAME.: led_driver.c
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


/***************************** Include files *******************************/
#include "emp_type.h"
#include "led_driver.h"
#include "led_colors.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void led_on(INT8U color)
/*****************************************************************************
*   Input    : - Color of led to turn on
*   Output   : -
*   Function : Turn led on
******************************************************************************/
{
    if( color == RED )
    {
      GPIO_PORTF_DATA_R = 0xFD; // Pull output low
      return;
    }

    if( color == YELLOW )
    {
      GPIO_PORTF_DATA_R = 0xFB;
      return;
    }

    if( color == GREEN )
    {
      GPIO_PORTF_DATA_R = 0xF7;
      return;
    }

    if ( color == REDYELLOW)
    {
      GPIO_PORTF_DATA_R = 0xF9;
      return;
    }GPIO_PORTF_DATA_R = 0xF9;

    if ( color == OFF )
    { 
        GPIO_PORTF_DATA_R = 0b00001110;
    }
    }

void led_off(INT8U color)
/*****************************************************************************
*   Input    : - Color of led to turn off
*   Output   : -
*   Function : Turn led off
******************************************************************************/
{
    if( color & RED )
      GPIO_PORTF_DATA_R &= !0x02;
    
    if( color & YELLOW )
      GPIO_PORTF_DATA_R &= !0x0A;  
    
    if( color & GREEN )
      GPIO_PORTF_DATA_R &= !0x08;    
}

/****************************** End Of Module *******************************/


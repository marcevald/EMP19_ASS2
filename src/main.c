/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 2, main module. No main.h file.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 080319  MEE   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "swtimers.h"
#include "systick.h"
#include "btn.h"
#include "gpio.h"
#include "led_driver.h"
#include "led_colors.h"
#include "traffic_light.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern INT16S tic;
/*****************************   Functions   *******************************/

int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  INT8U alive_timer = TIM_500_MSEC;
  INT8U btn_event;
  INT8U tf_event;

  disable_global_int();
  init_systick();
  init_gpio();
  enable_global_int();
    
  // Loop forever.
  while(1)
  {
	// System part of the super loop.
    // ------------------------------
	while( !tic );
	// The following will be executed every 5mS
    tic--;
  
  
    // The following blinks the red status LED on EMP-Board.
    if( ! --alive_timer )
    {
      alive_timer        = TIM_500_MSEC;
      GPIO_PORTD_DATA_R ^= 0x40;
    }

    btn_event = button_event();
    tf_event = traffic_event(btn_event);
    led_on(tf_event);
  }
  return( 0 );
}

/****************************** End Of Module *******************************/

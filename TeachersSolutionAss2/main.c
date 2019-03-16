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
* 150215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "swtimers.h"
#include "systick.h"
#include "gpio.h"
#include "events.h"
#include "tmodel.h"
#include "messages.h"
#include "devices.h"
#include "leds.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern volatile INT16S ticks;
INT16S alive_timer = MILLISEC(500);

/*****************************   Functions   *******************************/

void tl_task( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Disable global interrupt
******************************************************************************/
{
  static INT8U tl_state = 0;

  switch( tl_state )
  {
    case 0:
      start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC(100) );
      tl_state = 1;
      break;
    case 1:
      if( get_msg_event( SEB_TO_TRAFFIC_LIGHT )) // time out
      {
        if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_TLIGHT )
          set_leds( TURN_LED_ON, TURN_LED_OFF, TURN_LED_OFF );
        start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC(20000) );
        tl_state = 2;
      }
      break;
    case 2:
      if( get_msg_event( SEB_TO_TRAFFIC_LIGHT )) // time out
      {
        if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_TLIGHT )
       	  set_leds( TURN_LED_ON, TURN_LED_ON, TURN_LED_OFF );
        start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC( 5000 ));
        tl_state = 3;
      }
      break;
    case 3:
      if( get_msg_event( SEB_TO_TRAFFIC_LIGHT )) // time out
      {
        if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_TLIGHT )
       	  set_leds( TURN_LED_OFF, TURN_LED_OFF, TURN_LED_ON );
        start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC( 30000 ));
        tl_state = 4;
      }
      break;
    case 4:
      if( get_msg_event( SEB_TO_TRAFFIC_LIGHT )) // time out
      {
        if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_TLIGHT )
          set_leds( TURN_LED_OFF, TURN_LED_ON, TURN_LED_OFF );
        start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC( 5000 ));
        tl_state = 1;
      }
      break;
    default:
      tl_state = 1;
  }
}

void flash_task( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Disable global interrupt
******************************************************************************/
{
  static INT8U flash_state = 0;
  INT8U led_action;

  switch( flash_state )
  {
    case 0:
      led_action = TURN_LED_OFF;
      start_swtimer( ST_FLASH, SEB_TO_NORWEGIAN_NIGHT, MILLISEC( 500 ));
      flash_state = 1;
      break;
    case 1:
      if( get_msg_event( SEB_TO_NORWEGIAN_NIGHT )) // time out
      {
        led_action = TURN_LED_ON;
        start_swtimer( ST_FLASH, SEB_TO_NORWEGIAN_NIGHT, MILLISEC( 500 ));
        flash_state = 2;
      }
      break;
    case 2:
      if( get_msg_event( SEB_TO_NORWEGIAN_NIGHT )) // time out
      {
        led_action = TURN_LED_OFF;
        start_swtimer( ST_FLASH, SEB_TO_NORWEGIAN_NIGHT, MILLISEC( 500 ));
        flash_state = 1;
      }
      break;
  }
  if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_FLASH )
    set_leds( TURN_LED_OFF, led_action, TURN_LED_OFF );
}

void red_task( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Disable global interrupt
******************************************************************************/
{
  if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_REDLIGHT )
    set_leds( TURN_LED_ON, TURN_LED_OFF, TURN_LED_OFF );
}


void main_task( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Disable global interrupt
******************************************************************************/
{
  static INT8U main_task_state = 0;
  INT8U event;

  switch( main_task_state )
  {
  case 0:
    put_msg_state( SSM_TRAFFIC_LIGHT_MODE, MM_TLIGHT );
    main_task_state = 1;
    break;
  case 1:
    event = get_msg_event( SEB_BUTTON_EVENT );
    switch( event )
    {
      case BE_SINGLE_PUSH:
        put_msg_state( SSM_TRAFFIC_LIGHT_MODE, MM_FLASH );
        break;
      case BE_DOUBBLE_PUSH:
        put_msg_state( SSM_TRAFFIC_LIGHT_MODE, MM_REDLIGHT );
        break;
      case BE_LONG_PUSH:
        put_msg_state( SSM_TRAFFIC_LIGHT_MODE, MM_TLIGHT );
        break;
    }
  }
}




int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  disable_global_int();
  init_systick();
  init_gpio();
  enable_global_int();

  // Loop forever.
  while(1)
  {
	// System part of the super loop.
	// ------------------------------
	while( !ticks );


	// The following will be executed every 5mS
	ticks--;

	if( ! --alive_timer )
	{
    alive_timer =	MILLISEC( 500 );
	  GPIO_PORTD_DATA_R ^= 0x40;
	}

    // Protected operating system mode
    swt_ctrl();

    // Application mode
    button_task( TASK_BUTTON );
    main_task( TASK_MAIN );
    tl_task( TASK_TRAFFIC_LIGHT );
    flash_task( TASK_NORWEGIAN_NIGHT );
    red_task( TASK_EMERGENCY );

  }
}

/****************************** End Of Module *******************************/

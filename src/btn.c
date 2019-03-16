/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: btn.c
*
* PROJECT....: ECP
*
* DESCRIPTION: Button "state machine" implementation - Returns singleclick, doubleclick or longpress.
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
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "btn.h"
#include "btn_events.h"
#include "swtimers.h"
/*****************************    Defines    *******************************/
#define BS_IDLE 0
#define BS_FIRST_PRESS 1
#define BS_FIRST_RELEASE 2
#define BS_SECOND_PRESS 3
#define BS_LONG_PRESS 4
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U btn_psh(void)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Button pushed
******************************************************************************/
{
     return( !(GPIO_PORTF_DATA_R & 0x10) );  // SW1 at PF4
}
INT8U button_event()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Returns Button Event. - BE_NO_EVENT, BE_SINGLE_PUSH, BE_DOUBLE_PUSH or BE_LONG_PUSH 
******************************************************************************/
{
    static INT8U btn_state = BS_IDLE;
    static INT16U btn_timer;
    INT8U btn_event = BE_NO_EVENT;

    switch ( btn_state )
    {
        case BS_IDLE:
            if ( btn_psh() ) 
            {
                btn_state = BS_FIRST_PRESS;
                btn_timer = TIM_2_SEC;
            }
            break;

        case BS_FIRST_PRESS:
            if( !--btn_timer )
            {
                btn_state = BS_LONG_PRESS;
                btn_event = BE_LONG_PRESS;
            }
            else 
                if ( !btn_psh() ) {
                    btn_timer = TIM_100_MSEC;
                    btn_state = BS_FIRST_RELEASE;
                }
            break;
        
        case BS_FIRST_RELEASE:
            if ( ! --btn_timer ) 
            {
                btn_event = BE_SINGLE_PRESS;
                btn_state = BS_IDLE;
            }
            else
                if ( btn_psh()) 
                {
                    btn_timer = TIM_2_SEC;
                    btn_state = BS_SECOND_PRESS;
                }
            break;
        case BS_SECOND_PRESS:
            if ( ! --btn_timer )    
            {
                btn_state = BS_LONG_PRESS;
                btn_event = BE_LONG_PRESS;
            }
            else 
                if ( ! btn_psh() ) 
                {
                    btn_event = BE_DOUBLE_PRESS;
                    btn_state = BS_IDLE;
                }
            break;
        case BS_LONG_PRESS:
            if ( ! btn_psh() ) 
                btn_state = BS_IDLE;               
            break;    
       
        default:
            break;
    }

    return( btn_event );
}

/****************************** End Of Module *******************************/


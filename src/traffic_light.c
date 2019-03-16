/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (EMP)
*
* MODULENAME.: btn.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Traffic Light Statemachine Implementation
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090319  MEE   Module created.
*
*****************************************************************************/


/***************************** Include files *******************************/
#include "emp_type.h"
#include "traffic_light.h"
#include "led_colors.h"
#include "swtimers.h"
#include "btn_events.h"

/*****************************    Defines    *******************************/
#define TS_RED          0
#define TS_YELLOW       1
#define TS_GREEN        2
#define TS_REDYELLOW    3
#define TS_NORWEGIAN    4
#define TS_OFF          5
#define TS_EM           6
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U traffic_event( INT8U btn_event )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Return Color of Light, depending on state
******************************************************************************/
{
    static INT8U    tl_state = TS_RED;
    static INT16U   tl_timer = TIM_4_SEC;
    static INT8U    tl_event = RED;

 
    switch ( tl_state )
    {
        case TS_RED:
            switch (btn_event)
            {
                case BE_NO_EVENT:
                    if( !--tl_timer )
                    {
                        tl_timer = TIM_500_MSEC;
                        tl_state = TS_REDYELLOW; 
                        tl_event = REDYELLOW;
                    }
                break;
                
                case BE_SINGLE_PRESS:
                    tl_timer = TIM_1_SEC;
                    tl_event = YELLOW;
                    tl_state = TS_NORWEGIAN;
                break;

                case BE_DOUBLE_PRESS:
                    tl_event = RED;
                    tl_state = TS_EM;
                break;
                default:
                    break;
            }
            break;
            
        case TS_REDYELLOW:
            switch (btn_event)
            {
                case BE_NO_EVENT:
                    if( !--tl_timer )
                    {
                        tl_timer = TIM_4_SEC;
                        tl_state = TS_GREEN; 
                        tl_event = GREEN;
                    }
                break;
                
                case BE_SINGLE_PRESS:
                    tl_timer = TIM_1_SEC;
                    tl_event = YELLOW;
                    tl_state = TS_NORWEGIAN;
                break;

                case BE_DOUBLE_PRESS:
                    tl_event = RED;
                    tl_state = TS_EM;
                break;
                default:
                    break;
            }
            break;

        case TS_GREEN:
            switch (btn_event)
            {
                case BE_NO_EVENT:
                    if( !--tl_timer )
                    {
                        tl_timer = TIM_500_MSEC;
                        tl_state = TS_YELLOW; 
                        tl_event = YELLOW;
                    }
                break;
                
                case BE_SINGLE_PRESS:
                    tl_timer = TIM_1_SEC;
                    tl_event = YELLOW;
                    tl_state = TS_NORWEGIAN;
                break;

                case BE_DOUBLE_PRESS:
                    tl_event = RED;
                    tl_state = TS_EM;
                break;
                default:
                    break;
            }
            break;
        
        case TS_YELLOW:
            switch (btn_event)
            {
                case BE_NO_EVENT:
                    if( !--tl_timer )
                    {
                        tl_state = TS_RED;
                        tl_timer = TIM_4_SEC; 
                        tl_event = RED;
                    }
                break;
                
                case BE_SINGLE_PRESS:
                    tl_timer = TIM_1_SEC;
                    tl_event = YELLOW;
                    tl_state = TS_NORWEGIAN;
                break;

                case BE_DOUBLE_PRESS:
                    tl_event = RED;
                    tl_state = TS_EM;
                break;
                default:
                    break;
            }
            break;
        
        case TS_NORWEGIAN:
            switch (btn_event)
            {
                case BE_NO_EVENT:
                    if ( !--tl_timer ) 
                    {
                        tl_timer = TIM_1_SEC;
                        tl_state = TS_OFF;
                        tl_event = OFF;    
                    }
                break;
                
                case BE_SINGLE_PRESS:
                    tl_timer = TIM_1_SEC;
                    tl_event = YELLOW;
                    tl_state = TS_NORWEGIAN;
                break;

                case BE_DOUBLE_PRESS:
                    tl_event = RED;
                    tl_state = TS_EM;
                break;

                case BE_LONG_PRESS:
                        tl_timer = TIM_4_SEC;
                        tl_state = TS_RED; 
                        tl_event = RED;    
                break;

                default:
                    break;
            }
            break;
        
        case TS_OFF:
            switch (btn_event)
            {
                case BE_NO_EVENT:
                    if ( !--tl_timer ) 
                    {
                        tl_timer = TIM_1_SEC;
                        tl_state = TS_NORWEGIAN;
                        tl_event = YELLOW;    
                    }
                break;
                
                case BE_SINGLE_PRESS:
                    tl_timer = TIM_1_SEC;
                    tl_event = YELLOW;
                    tl_state = TS_NORWEGIAN;
                break;

                case BE_DOUBLE_PRESS:
                    tl_event = RED;
                    tl_state = TS_EM;
                
                case BE_LONG_PRESS:
                        tl_timer = TIM_4_SEC;
                        tl_state = TS_RED; 
                        tl_event = RED;    
                break;

                default:
                    break;
            }
            break;
        
        case TS_EM:
            switch (btn_event)
            {
                case BE_NO_EVENT:
                        tl_event = RED;    
                break;

                case BE_LONG_PRESS:
                        tl_timer = TIM_4_SEC;
                        tl_state = TS_RED; 
                        tl_event = RED;    
                break;


                default:
                    break;
            }
            break;
        
    
        default:
            break;
    }
return tl_event;

}

/****************************** End Of Module *******************************/



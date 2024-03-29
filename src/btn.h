/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (EMP)
*
* MODULENAME.: btn.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 080319  MEE   Module created.
*
*****************************************************************************/

#ifndef BTN_H_
#define BTN_H_

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U btn_psh(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Button pushed
******************************************************************************/

INT8U button_event(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Button pushed
******************************************************************************/


/****************************** End Of Module *******************************/
#endif /*BTN_H_*/


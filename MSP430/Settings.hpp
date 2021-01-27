/** @file */

/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430Set Settings
 *  @ingroup groupMSP430
* @brief settings to refine usage of the MSP430 lib
*
* @details
* Usage: \code {.cpp}

//if commented in the lib will be work internally like the driverlib / if commented out the lib will remove needless code
#define MT_MSP430_USE_DRIVERLIB_COMPATIBILITY

//if commented in the lib will register GPIO Interrupts with callbacks known at compile time -> for max performance
#define MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

//if commented in the lib will register WDT Interrupts with callbacks known at compile time -> for max performance
#define MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/

#ifndef MICROTRAIT_MSP430_SETTINGS_HPP_
#define MICROTRAIT_MSP430_SETTINGS_HPP_

#include "MicroTrait/Settings.hpp"

/*if commented in the lib will be work internally like the driverlib / if commented out the lib will remove needless code*/
//#define MT_MSP430_USE_DRIVERLIB_COMPATIBILITY

/*if commented in the lib will register GPIO Interrupts with callbacks known at compile time -> for max performance*/
#define MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

/*if commented in the lib will register WDT Interrupts with callbacks known at compile time -> for max performance*/
#define MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

/*if commented in the lib will register TIMERA Interrupts with callbacks known at compile time -> for max performance*/
#define MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS

/*if commented in the lib will register EUSICA Uart Interrupts with callbacks known at compile time -> for max performance*/
#define MT_MSP430_USE_EUSCIA_UART_COMPILE_TIME_CALLBACKS

#ifndef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
#warning MT_MSP430_USE_DRIVERLIB_COMPATIBILITY is off: certain mistakes one could make are not catched as a trade off for speed and size
#endif

#endif /* MICROTRAIT_MSP430_SETTINGS_HPP_ */

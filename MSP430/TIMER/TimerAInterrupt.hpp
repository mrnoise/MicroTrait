/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430TimerAInt Interrupt
 *  @ingroup groupMSP430TimerA
* @brief functions to register Interrupt callbacks for Timer A Interrupts at compile time or at runtime -> check settings.hpp
*
* @details
* Usage Compile time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS

 TIMERA::Interrupt::TA0 int0{
        [](TIMERA::Interrupt::SOURCE src) {
            if (src == TIMERA::Interrupt::SOURCE::REGISTER0) {
                GPIO::Port1 p1{};
                p1.toggleOutputOnPin(GPIO::PIN::P0);

                TIMERA::TA0 ta0;
                ta0.setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, COMPARE_VALUE);
            }
        }
    };

#endif
\endcode

* Usage Runtime time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;
#ifndef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS


#endif
\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/

/** @defgroup groupFuncsMSP430TimerAInt Functions
*  @ingroup groupMSP430TimerAInt
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430TimerAInt Enums
*  @ingroup groupMSP430TimerAInt
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_TIMER_TIMERAINTERRUPT_HPP_
#define MICROTRAIT_MSP430_TIMER_TIMERAINTERRUPT_HPP_


#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Misc/Meta.hpp"
#include <type_traits>
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>
#include <tuple>

namespace MT::MSP430::TIMERA::Interrupt {

/**
* @ingroup groupEnumsMSP430TimerAInt
****************************************************************
* @brief Interrupt source
****************************************************************
*/
enum class SOURCE {
    REGISTER0 = 0,
    REGISTER1 = 1,
    REGISTER2 = 2,
    REGISTER3 = 3,
    REGISTER4 = 4,
    REGISTER5 = 5,
    REGISTER6 = 6,
    OVERFLOW  = 7,
    NONE      = 255
};


#ifdef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS


#if defined(__MSP430_HAS_T0A2__) || defined(__MSP430_HAS_T0A3__) || defined(__MSP430_HAS_T0A5__) || defined(__MSP430_HAS_T0A7__)
template<typename FUNC>
struct TA0 {

    /**
	* @ingroup groupFuncsMSP430TimerAInt
	****************************************************************
	* @brief constructor to register callback at compile time
	* @details
	* Usage: \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	* TIMERA::Interrupt::TA0 int0{
    *    [](TIMERA::Interrupt::SOURCE src) {
    *        if (src == TIMERA::Interrupt::SOURCE::REGISTER0) {
    *            GPIO::Port1 p1{};
    *            p1.toggleOutputOnPin(GPIO::PIN::P0);
	*
    *            TIMERA::TA0 ta0;
    *            ta0.setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, COMPARE_VALUE);
    *        }
    *    }
    * }; \endcode
	*@param fun -> register callback function -> gets called in case of interrupt and provides the pin number
	****************************************************************
	*/
    constexpr explicit TA0(FUNC fun) : m_vectors{ std::move(fun) } {}

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
    __interrupt void Timer_A(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A(void)
#else
#error Compiler not supported!
#endif
    {
        std::get<0>(m_vectors)(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A1_VECTOR
    __interrupt
#elif defined(__GNUC__)
    __attribute__((interrupt(TIMER0_A1_VECTOR)))
#endif
        void
        TIMER0_A1_ISR(void) {

        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA0IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src = SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src = SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src = SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src = SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src = SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src = SOURCE::REGISTER6;
                break;//CCR6
            case 14:
                src = SOURCE::OVERFLOW;
                break;//Overflow
            default: break;
        }
        std::get<0>(m_vectors)(src);
    }
};
#endif

#else

#endif
}// namespace MT::MSP430::TIMERA::Interrupt

#endif

#endif /* MICROTRAIT_MSP430_TIMER_TIMERAINTERRUPT_HPP_ */

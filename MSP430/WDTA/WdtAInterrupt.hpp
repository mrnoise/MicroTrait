/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430WdtAInt Interrupt
 *  @ingroup groupMSP430WdtA
* @brief  functions to register Interrupt callbacks for Watchdog A interrupts at compile time or at runtime -> check settings.hpp
*
* @details
* Usage Compile time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

constexpr auto isr = WDTA::Interrupt::makeInterrupt(
    WDTA::Interrupt::makeHandler(
        WDTA::Interrupt::WDTA::VEC1,
        []() {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }));


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = WDT_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(WDT_VECTOR)))
#endif
    void
    WDT_A_ISR(void) {
    std::get<isr.get_index(WDTA::Interrupt::VEC1)>(isr.m_vectors)();
}
#endif

\endcode

* Usage Runtime time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifndef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS
    WDTA::Interrupt::registerCallback([]() {
        GPIO::Port1 p1{};
        p1.toggleOutputOnPin(GPIO::PIN::P0);
    });
#endif

\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupFuncsMSP430WdtAInt Functions
*  @ingroup groupMSP430WdtAInt
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430WdtAInt Enums
*  @ingroup groupMSP430WdtAInt
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_
#define MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Interrupt.hpp"
#include "MicroTrait/Misc/Meta.hpp"
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>

namespace MT::MSP430::WDTA::Interrupt {

/**
* @ingroup groupEnumsMSP430WdtAInt
****************************************************************
* @brief Available Watchdog Timers for interrupt callbacks
****************************************************************
*/
enum WDTA {
    VEC1 = 0,
};

#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

template<typename ENUM, typename FUNC>
using IntHandlers = MT::Universal::Interrupt::IntHandlers<ENUM, FUNC>;

template<typename... Vector>
using Interrupt = MT::Universal::Interrupt::Interrupt<Vector...>;

/**
* @ingroup groupFuncsMSP430WdtAInt
****************************************************************
* @brief maker function for a complete callback registration
* @details
* Usage: \code {.cpp}
*
* using namespace MT::MSP430;
*
*	WDTA::Interrupt::makeInterrupt(
*		WDTA::Interrupt::makeHandler(
*			WDTA::Interrupt::WDTA::VEC1,
*			[]() {
*				GPIO::Port1 p1{};
*				p1.toggleOutputOnPin(GPIO::PIN::P0);
*			})); \endcode
*@param t -> all entries to register first the port than the callback
*@return the copile time objects containing all registered callbacks
****************************************************************
*/
template<typename ENUM, typename... FUNC>
[[nodiscard]] constexpr auto makeInterrupt(IntHandlers<ENUM, FUNC>... t) noexcept {
    static_assert(MT ::Meta::compareBareType<ENUM, WDTA>(), "input must be WDT  enum");
    return Interrupt<ENUM, FUNC...>{ std::move(t)... };
}

/**
* @ingroup groupFuncsMSP430WdtAInt
****************************************************************
* @brief maker function for one callback entry
* @details
* Usage: cascade with makeInterrupt like: \code {.cpp}
*	WDTA::Interrupt::makeInterrupt(
*		WDTA::Interrupt::makeHandler(
*			WDTA::Interrupt::WDTA::VEC1,
*			[]() {
*				GPIO::Port1 p1{};
*				p1.toggleOutputOnPin(GPIO::PIN::P0);
*			})); \endcode
*@param p the Enum
*@param t the callback
*@return one IntHandler (std::pair<WDTA::Interrupt::WDT, FUNC>)
****************************************************************
*/
template<typename ENUM, typename FUNC>
[[nodiscard]] constexpr auto makeHandler(ENUM p, FUNC t) noexcept {
    static_assert(MT::Meta::compareBareType<ENUM, WDTA>(), "input must be WDT  enum");
    return IntHandlers<ENUM, FUNC>{ p, std::move(t) };
}

#else
extern std::array<void (*)(), 1> WdtVectors;

/**
* @ingroup groupFuncsMSP430WdtAInt
****************************************************************
* @brief runtime interrupt callback registration -> fixed to WdtA
* @details
* Usage:  \code {.cpp}
*
*	using namespace MT::MSP430;
*
*	WDTA::Interrupt::registerCallback([]() {
*		GPIO::Port1 p1{};
*		p1.toggleOutputOnPin(GPIO::PIN::P0);
*	});
* \endcode
*@param callback pointer to the callback function
****************************************************************
*/
constexpr void registerCallback(void (*callback)()) noexcept {
    WdtVectors[VEC1] = callback;
};
#endif

}// namespace MT::MSP430::WDTA::Interrupt

#endif

#endif /* MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_ */

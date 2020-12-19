/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430GpioInt Interrupt
 *  @ingroup groupMSP430Gpio
* @brief functions to register Interrupt callbacks for GPIO Interrupts at compile time or at runtime -> check settings.hpp
*
* @details
* Usage Compile time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

constexpr auto isr = GPIO::Interrupt::makeInterrupt(

    GPIO::Interrupt::makeHandler(
        GPIO::Interrupt::PORTS::PORT1,
        []() {
            GPIO::Port1 p1{};
            p1.clearInterrupt(GPIO::PIN::P4);
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }),

    GPIO::Interrupt::makeHandler(
        GPIO::Interrupt::PORTS::PORT2,
        []() {
            GPIO::Port1 p1{};
            GPIO::Port2 p2{};
            p2.clearInterrupt(GPIO::PIN::P3);
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }));



#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
{
    std::get<isr.get_index(GPIO::Interrupt::PORTS::PORT2)>(isr.m_vectors)();
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
{
    std::get<isr.get_index(GPIO::Interrupt::PORTS::PORT1)>(isr.m_vectors)();
}
#endif
\endcode

* Usage Runtime time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;
#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

    GPIO::Interrupt::registerCallback(GPIO::Interrupt::PORTS::PORT1, []() {
        GPIO::Port1 p1{};
        p1.clearInterrupt(GPIO::PIN::P4);
        p1.toggleOutputOnPin(GPIO::PIN::P0);
    });

    GPIO::Interrupt::registerCallback(GPIO::Interrupt::PORTS::PORT2, []() {
        GPIO::Port1 p1{};
        GPIO::Port2 p2{};
        p2.clearInterrupt(GPIO::PIN::P3);
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


/** @defgroup groupFuncsMSP430GpioInt Functions
*  @ingroup groupMSP430GpioInt
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430GpioInt Enums
*  @ingroup groupMSP430GpioInt
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_GPIO_GPIOINTERRUPT_HPP_
#define MICROTRAIT_MSP430_GPIO_GPIOINTERRUPT_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Interrupt.hpp"
#include "MicroTrait/MSP430/GPIO/Gpio.hpp"
#include "MicroTrait/Misc/Meta.hpp"
#include <type_traits>
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>

namespace MT::MSP430::GPIO::Interrupt {

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

/**
* @ingroup groupEnumsMSP430GpioInt
****************************************************************
* @brief Available Ports for interrupt callbacks
****************************************************************
*/
enum PORTS : uint_fast8_t {
#if defined(P1IFG)
    P1_PIN0 = 0,
    P1_PIN1 = 1,
    P1_PIN2 = 2,
    P1_PIN3 = 3,
    P1_PIN4 = 4,
    P1_PIN5 = 5,
    P1_PIN6 = 6,
    P1_PIN7 = 7,
#endif

#if defined(P2IFG)
    P2_PIN0 = 8,
    P2_PIN1 = 9,
    P2_PIN2 = 10,
    P2_PIN3 = 11,
    P2_PIN4 = 12,
    P2_PIN5 = 13,
    P2_PIN6 = 14,
    P2_PIN7 = 15,
#endif

#if defined(P3IFG)
    P3_PIN0 = 16,
    P3_PIN1 = 17,
    P3_PIN2 = 18,
    P3_PIN3 = 19,
    P3_PIN4 = 20,
    P3_PIN5 = 21,
    P3_PIN6 = 22,
    P3_PIN7 = 23,
#endif

#if defined(P4IFG)
    P4_PIN0 = 24,
    P4_PIN1 = 25,
    P4_PIN2 = 26,
    P4_PIN3 = 27,
    P4_PIN4 = 28,
    P4_PIN5 = 29,
    P4_PIN6 = 30,
    P4_PIN7 = 31,
#endif

#if defined(P5IFG)
    P5_PIN0 = 32,
    P5_PIN1 = 33,
    P5_PIN2 = 34,
    P5_PIN3 = 35,
    P5_PIN4 = 36,
    P5_PIN5 = 37,
    P5_PIN6 = 38,
    P5_PIN7 = 39,
#endif

#if defined(P6IFG)
    P6_PIN0 = 40,
    P6_PIN1 = 41,
    P6_PIN2 = 42,
    P6_PIN3 = 43,
    P6_PIN4 = 44,
    P6_PIN5 = 45,
    P6_PIN6 = 46,
    P6_PIN7 = 47,
#endif

#if defined(P7IFG)
    P7_PIN0 = 48,
    P7_PIN1 = 49,
    P7_PIN2 = 50,
    P7_PIN3 = 51,
    P7_PIN4 = 52,
    P7_PIN5 = 53,
    P7_PIN6 = 54,
    P7_PIN7 = 55,
#endif

#if defined(P8IFG)
    P8_PIN0 = 56,
    P8_PIN1 = 57,
    P8_PIN2 = 58,
    P8_PIN3 = 59,
    P8_PIN4 = 60,
    P8_PIN5 = 61,
    P8_PIN6 = 62,
    P8_PIN7 = 63,
#endif

#if defined(P9IFG)
    P9_PIN0 = 64,
    P9_PIN1 = 65,
    P9_PIN2 = 66,
    P9_PIN3 = 67,
    P9_PIN4 = 68,
    P9_PIN5 = 69,
    P9_PIN6 = 70,
    P9_PIN7 = 71,
#endif

#if defined(P10IFG)
    P10_PIN0 = 72,
    P10_PIN1 = 73,
    P10_PIN2 = 74,
    P10_PIN3 = 75,
    P10_PIN4 = 76,
    P10_PIN5 = 77,
    P10_PIN6 = 78,
    P10_PIN7 = 79,
#endif

#if defined(P11IFG)
    P11_PIN0 = 80,
    P11_PIN1 = 81,
    P11_PIN2 = 82,
    P11_PIN3 = 83,
    P11_PIN4 = 84,
    P11_PIN5 = 85,
    P11_PIN6 = 86,
    P11_PIN7 = 87,
#endif

#if defined(PJIFG)
    PJ_PIN0 = 88,
    PJ_PIN1 = 89,
    PJ_PIN2 = 90,
    PJ_PIN3 = 91,
    PJ_PIN4 = 92,
    PJ_PIN5 = 93,
    PJ_PIN6 = 94,
    PJ_PIN7 = 95,
#endif
};

template<typename ENUM, typename FUNC>
using IntHandlers = MT::Universal::Interrupt::IntHandlers<ENUM, FUNC>; /**< this pair represents the ISR -> first the Enum which refers to a vector and second the function to call */

template<typename ENUM, typename... Vector>
using Interrupt = MT::Universal::Interrupt::Interrupt<ENUM, Vector...>;

/**
* @ingroup groupFuncsMSP430GpioInt
****************************************************************
* @brief maker function for a complete callback registration
* @details
* Usage: \code {.cpp}
*
* using namespace MT::MSP430;
*
* GPIO::Interrupt::makeInterrupt(
*	GPIO::Interrupt::makeHandler(
*		GPIO::Interrupt::PORTS::PORT2,
*		[]() {
*			GPIO::Port1 p1{};
*			p1.toggleOutputOnPin(GPIO::PIN::P0);
*		})); \endcode
*@param t -> all entries to register first the port than the callback
*@return the copile time objects containing all registered callbacks
****************************************************************
*/
template<typename ENUM, typename... FUNC>
[[nodiscard]] constexpr auto makeInterrupt(IntHandlers<ENUM, FUNC>... t) noexcept {
    static_assert(MT::Misc::Meta::compareBareType<ENUM, PORTS>(), "input must be PORTS enum");
    return Interrupt<ENUM, FUNC...>{ std::move(t)... };
}

/**
* @ingroup groupFuncsMSP430GpioInt
****************************************************************
* @brief maker function for one callback entry
* @details
* Usage: cascade with makeInterrupt like: \code {.cpp}
* GPIO::Interrupt::makeInterrupt(
*	GPIO::Interrupt::makeHandler(
*		GPIO::Interrupt::PORTS::PORT2,
*		[]() {
*			GPIO::Port1 p1{};
*			p1.toggleOutputOnPin(GPIO::PIN::P0);
*		})); \endcode
*@param p the Enum
*@param t the callback
*@return one IntHandler (std::pair<GPIO::Interrupt::PORTS, FUNC>)
****************************************************************
*/
template<typename ENUM, typename FUNC>
[[nodiscard]] constexpr auto makeHandler(ENUM p, FUNC t) noexcept {
    static_assert(MT::Misc::Meta::compareBareType<ENUM, PORTS>(), "input must be PORTS enum");
    return IntHandlers<ENUM, FUNC>{ p, std::move(t) };
}

#else

/**
* @ingroup groupEnumsMSP430GpioInt
****************************************************************
* @brief Available Ports for interrupt callbacks
****************************************************************
*/
enum PORTS : uint_fast8_t {
#if defined(P1IFG)
    P1  = 0,
#endif

#if defined(P2IFG)
    P2  = 1,
#endif

#if defined(P3IFG)
    P3  = 2,
#endif

#if defined(P4IFG)
    P4  = 3,
#endif

#if defined(P5IFG)
    P5  = 4,
#endif

#if defined(P6IFG)
    P6  = 5,
#endif

#if defined(P7IFG)
    P7  = 6,
#endif

#if defined(P8IFG)
    P8  = 7,

#endif

#if defined(P9IFG)
    P9  = 8,
#endif

#if defined(P10IFG)
    P10 = 9,
#endif

#if defined(P11IFG)
    P11 = 10,
#endif

#if defined(PJIFG)
    PJ  = 11,
#endif

    NONE
};


extern std::array<void (*)(MT::MSP430::GPIO::PIN), PORTS::NONE> PortVectors;


/**
* @ingroup groupFuncsMSP430GpioInt
****************************************************************
* @brief runtime interrupt callback registration
* @details
* Usage:  \code {.cpp}
*
* using namespace MT::MSP430;
*
*   GPIO::Interrupt::registerCallback(GPIO::Interrupt::PORTS::P1, [](GPIO::PIN pin) {
*        if (pin == GPIO::PIN::P1) {
*            GPIO::Port1 p1{};
*            p1.toggleOutputOnPin(GPIO::PIN::P0);
*        }
*    });
*
* \endcode
*@param ports the port for which the callback should be registered (GPIO::Interrupt::PORTS)
*@param callback pointer to the callback function
****************************************************************
*/
constexpr void registerCallback(const PORTS ports, void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
    if (ports != NONE) PortVectors[ports] = callback;
};
#endif

}// namespace MT::MSP430::GPIO::Interrupt

#endif

#endif /* MICROTRAIT_MSP430_GPIO_GPIOINTERRUPT_HPP_ */

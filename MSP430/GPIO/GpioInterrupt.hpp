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

  constexpr static GPIO::Interrupt::Port1 int1{
    [](const GPIO::PIN pin) {  // use lambdas only!
        if (pin == GPIO::PIN::P1) {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }
    }
 };

  constexpr static GPIO::Interrupt::Port2 int2{
        [](const GPIO::PIN pin) {  // use lambdas only!
            if (pin == GPIO::PIN::P4) {
                GPIO::Port1 p1{};
                p1.toggleOutputOnPin(GPIO::PIN::P0);
            }
        }
    };

#endif
\endcode

* Usage Runtime time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;
#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

     GPIO::Interrupt::Port1 int1{};
    int1.registerCallback([](GPIO::PIN pin) {
        if (pin == GPIO::PIN::P1) {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }
    });

    GPIO::Interrupt::Port2 int2{};
    int2.registerCallback([](GPIO::PIN pin) {
        if (pin == GPIO::PIN::P4) {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }
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

#include "MicroTrait/MSP430/GPIO/Gpio.hpp"
#include "MicroTrait/Misc/Meta.hpp"
#include <type_traits>
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>
#include <tuple>

namespace MT::MSP430::GPIO::Interrupt {

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

#if defined(P1IFG)
template<typename FUNC>
struct Port1 {

    /**
	* @ingroup groupFuncsMSP430GpioInt
	****************************************************************
	* @brief constructor to register callback at compile time
	* @details
	* Usage: \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	*  constexpr static GPIO::Interrupt::Port1 int1{
    *    [](const GPIO::PIN pin) {  // use lambdas only!
    *        if (pin == GPIO::PIN::P1) {
    *            GPIO::Port1 p1{};
    *            p1.toggleOutputOnPin(GPIO::PIN::P0);
    *        }
    *    }
    * }; \endcode
	*@param fun -> register callback function -> gets called in case of interrupt and provides the pin number
	****************************************************************
	*/
    constexpr explicit Port1(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port1 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT1_VECTOR
    __interrupt void Port_1(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P1IV, P1IV_P1IFG7)) {
            case P1IV_NONE: break;
            case P1IV_P1IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P1IV_P1IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P1IV_P1IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P1IV_P1IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P1IV_P1IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P1IV_P1IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P1IV_P1IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P1IV_P1IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif


#if defined(P2IFG)
template<typename FUNC>
struct Port2 {

    constexpr explicit Port2(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port2 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
    __interrupt void
        Port_2(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P2IV, P2IV_P2IFG7)) {
            case P2IV_NONE: break;
            case P2IV_P2IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P2IV_P2IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P2IV_P2IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P2IV_P2IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P2IV_P2IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P2IV_P2IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P2IV_P2IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P2IV_P2IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif


#if defined(P3IFG)
template<typename FUNC>
struct Port3 {

    constexpr explicit Port3(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port3 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT3_VECTOR
    __interrupt void
        Port_3(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT3_VECTOR))) Port_3(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P3IV, P3IV_P3IFG7)) {
            case P3IV_NONE: break;
            case P3IV_P3IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P3IV_P3IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P3IV_P3IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P3IV_P3IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P3IV_P3IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P3IV_P3IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P3IV_P3IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P3IV_P3IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif

#if defined(P4IFG)
template<typename FUNC>
struct Port4 {

    constexpr explicit Port4(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port4 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT4_VECTOR
    __interrupt void
        Port_4(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT4_VECTOR))) Port_4(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P4IV, P4IV_P4IFG7)) {
            case P4IV_NONE: break;
            case P4IV_P4IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P4IV_P4IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P4IV_P4IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P4IV_P4IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P4IV_P4IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P4IV_P4IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P4IV_P4IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P4IV_P4IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif


#if defined(P5IFG)
template<typename FUNC>
struct Port5 {

    constexpr explicit Port5(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port5 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT5_VECTOR
    __interrupt void
        Port_5(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT5_VECTOR))) Port_5(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P5IV, P5IV_P5IFG7)) {
            case P5IV_NONE: break;
            case P5IV_P5IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P5IV_P5IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P5IV_P5IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P5IV_P5IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P5IV_P5IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P5IV_P5IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P5IV_P5IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P5IV_P5IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif

#if defined(P6IFG)
template<typename FUNC>
struct Port6 {

    constexpr explicit Port6(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port6 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT6_VECTOR
    __interrupt void
        Port_6(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT6_VECTOR))) Port_6(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P6IV, P6IV_P6IFG7)) {
            case P6IV_NONE: break;
            case P6IV_P6IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P6IV_P6IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P6IV_P6IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P6IV_P6IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P6IV_P6IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P6IV_P6IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P6IV_P6IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P6IV_P6IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif


#if defined(P7IFG)
template<typename FUNC>
struct Port7 {

    constexpr explicit Port7(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port7 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT7_VECTOR
    __interrupt void
        Port_7(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT7_VECTOR))) Port_7(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P7IV, P7IV_P7IFG7)) {
            case P7IV_NONE: break;
            case P7IV_P7IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P7IV_P7IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P7IV_P7IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P7IV_P7IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P7IV_P7IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P7IV_P7IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P7IV_P7IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P7IV_P7IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif

#if defined(P8IFG)
template<typename FUNC>
struct Port8 {

    constexpr explicit Port8(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port8 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT8_VECTOR
    __interrupt void
        Port_8(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT8_VECTOR))) Port_8(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P8IV, P8IV_P8IFG7)) {
            case P8IV_NONE: break;
            case P8IV_P8IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P8IV_P8IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P8IV_P8IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P8IV_P8IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P8IV_P8IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P8IV_P8IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P8IV_P8IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P8IV_P8IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }
        std::get<0>(m_vectors)(pin);
    }
};
#endif


#if defined(P9IFG)
template<typename FUNC>
struct Port9 {

    constexpr explicit Port9(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port9 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT9_VECTOR
    __interrupt void
        Port_9(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT9_VECTOR))) Port_9(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P9IV, P9IV_P9IFG7)) {
            case P9IV_NONE: break;
            case P9IV_P9IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P9IV_P9IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P9IV_P9IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P9IV_P9IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P9IV_P9IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P9IV_P9IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P9IV_P9IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P9IV_P9IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif

#if defined(P10IFG)
template<typename FUNC>
struct Port10 {

    constexpr explicit Port10(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port10 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT10_VECTOR
    __interrupt void
        Port_10(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT10_VECTOR))) Port_10(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P10IV, P10IV_P10IFG7)) {
            case P10IV_NONE: break;
            case P10IV_P10IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P10IV_P10IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P10IV_P10IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P10IV_P10IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P10IV_P10IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P10IV_P10IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P10IV_P10IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P10IV_P10IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }
        std::get<0>(m_vectors)(pin);
    }
};
#endif

#if defined(P11IFG)
template<typename FUNC>
struct Port11 {

    constexpr explicit Port11(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt port11 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT11_VECTOR
    __interrupt void
        Port_11(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT11_VECTOR))) Port_11(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P11IV, P11IV_P11IFG7)) {
            case P11IV_NONE: break;
            case P11IV_P11IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P11IV_P11IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P11IV_P11IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P11IV_P11IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P11IV_P11IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P11IV_P11IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P11IV_P11IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P11IV_P11IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif


#if defined(PJIFG)
template<typename FUNC>
struct PortJ {

    constexpr explicit PortJ(FUNC fun) : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const MT::MSP430::GPIO::PIN>, "Missing [](const GPIO::PIN pin) parameter for lambda interrupt portJ !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORTJ_VECTOR
    __interrupt void
        Port_J(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORTJ_VECTOR))) Port_J(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(PJIV, PJIV_PJIFG7)) {
            case PJIV_NONE: break;
            case PJIV_PJIFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case PJIV_PJIFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case PJIV_PJIFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case PJIV_PJIFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case PJIV_PJIFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case PJIV_PJIFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case PJIV_PJIFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case PJIV_PJIFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        std::get<0>(m_vectors)(pin);
    }
};
#endif

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


#if defined(P1IFG)
struct Port1 {

    /**
	* @ingroup groupFuncsMSP430GpioInt
	****************************************************************
	* @brief runtime interrupt callback registration
	* @details
	* Usage:  \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	*   GPIO::Interrupt::Port1 int1;
	*   int1.registerCallback([](GPIO::PIN pin) {
	*        if (pin == GPIO::PIN::P1) {
	*            GPIO::Port1 p1{};
	*            p1.toggleOutputOnPin(GPIO::PIN::P0);
	*        }
	*    });
	*
	* \endcode
	*@param callback pointer to the callback function
	****************************************************************
	*/
    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P1] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT1_VECTOR
    __interrupt void Port_1(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P1IV, P1IV_P1IFG7)) {
            case P1IV_NONE: break;
            case P1IV_P1IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P1IV_P1IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P1IV_P1IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P1IV_P1IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P1IV_P1IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P1IV_P1IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P1IV_P1IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P1IV_P1IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P1] != nullptr) PortVectors[PORTS::P1](pin);
    }
};
#endif


#if defined(P2IFG)
struct Port2 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P2] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
    __interrupt void
        Port_2(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P2IV, P2IV_P2IFG7)) {
            case P2IV_NONE: break;
            case P2IV_P2IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P2IV_P2IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P2IV_P2IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P2IV_P2IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P2IV_P2IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P2IV_P2IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P2IV_P2IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P2IV_P2IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P2] != nullptr) PortVectors[PORTS::P2](pin);
    }
};
#endif


#if defined(P3IFG)
struct Port3 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P3] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT3_VECTOR
    __interrupt void
        Port_3(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT3_VECTOR))) Port_3(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P3IV, P3IV_P3IFG7)) {
            case P3IV_NONE: break;
            case P3IV_P3IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P3IV_P3IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P3IV_P3IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P3IV_P3IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P3IV_P3IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P3IV_P3IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P3IV_P3IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P3IV_P3IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P3] != nullptr) PortVectors[PORTS::P3](pin);
    }
};
#endif


#if defined(P4IFG)
struct Port4 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P4] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT4_VECTOR
    __interrupt void
        Port_4(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT4_VECTOR))) Port_4(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P4IV, P4IV_P4IFG7)) {
            case P4IV_NONE: break;
            case P4IV_P4IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P4IV_P4IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P4IV_P4IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P4IV_P4IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P4IV_P4IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P4IV_P4IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P4IV_P4IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P4IV_P4IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P4] != nullptr) PortVectors[PORTS::P4](pin);
    }
};
#endif


#if defined(P5IFG)
struct Port5 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P5] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT5_VECTOR
    __interrupt void
        Port_5(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT5_VECTOR))) Port_5(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P5IV, P5IV_P5IFG7)) {
            case P5IV_NONE: break;
            case P5IV_P5IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P5IV_P5IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P5IV_P5IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P5IV_P5IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P5IV_P5IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P5IV_P5IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P5IV_P5IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P5IV_P5IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P5] != nullptr) PortVectors[PORTS::P5](pin);
    }
};
#endif

#if defined(P6IFG)
struct Port6 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P6] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT6_VECTOR
    __interrupt void
        Port_6(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT6_VECTOR))) Port_6(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P6IV, P6IV_P6IFG7)) {
            case P6IV_NONE: break;
            case P6IV_P6IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P6IV_P6IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P6IV_P6IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P6IV_P6IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P6IV_P6IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P6IV_P6IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P6IV_P6IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P6IV_P6IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P6] != nullptr) PortVectors[PORTS::P6](pin);
    }
};
#endif


#if defined(P7IFG)
struct Port7 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P7] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT7_VECTOR
    __interrupt void
        Port_7(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT7_VECTOR))) Port_7(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P7IV, P7IV_P7IFG7)) {
            case P7IV_NONE: break;
            case P7IV_P7IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P7IV_P7IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P7IV_P7IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P7IV_P7IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P7IV_P7IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P7IV_P7IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P7IV_P7IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P7IV_P7IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P7] != nullptr) PortVectors[PORTS::P7](pin);
    }
};
#endif

#if defined(P8IFG)
struct Port8 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P8] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT8_VECTOR
    __interrupt void
        Port_8(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT8_VECTOR))) Port_8(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P8IV, P8IV_P8IFG7)) {
            case P8IV_NONE: break;
            case P8IV_P8IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P8IV_P8IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P8IV_P8IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P8IV_P8IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P8IV_P8IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P8IV_P8IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P8IV_P8IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P8IV_P8IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P8] != nullptr) PortVectors[PORTS::P8](pin);
    }
};
#endif


#if defined(P9IFG)
struct Port9 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P9] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT9_VECTOR
    __interrupt void
        Port_9(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT9_VECTOR))) Port_9(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P9IV, P9IV_P9IFG7)) {
            case P9IV_NONE: break;
            case P9IV_P9IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P9IV_P9IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P9IV_P9IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P9IV_P9IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P9IV_P9IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P9IV_P9IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P9IV_P9IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P9IV_P9IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P9] != nullptr) PortVectors[PORTS::P9](pin);
    }
};
#endif


#if defined(P10IFG)
struct Port10 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P10] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT10_VECTOR
    __interrupt void
        Port_10(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT10_VECTOR))) Port_10(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P10IV, P10IV_P10IFG7)) {
            case P10IV_NONE: break;
            case P10IV_P10IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P10IV_P10IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P10IV_P10IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P10IV_P10IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P10IV_P10IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P10IV_P10IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P10IV_P10IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P10IV_P10IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P10] != nullptr) PortVectors[PORTS::P10](pin);
    }
};
#endif


#if defined(P11IFG)
struct Port11 {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::P11] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT11_VECTOR
    __interrupt void
        Port_11(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORT11_VECTOR))) Port_11(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(P11IV, P11IV_P11IFG7)) {
            case P11IV_NONE: break;
            case P11IV_P11IFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case P11IV_P11IFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case P11IV_P11IFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case P11IV_P11IFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case P11IV_P11IFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case P11IV_P11IFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case P11IV_P11IFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case P11IV_P11IFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::P11] != nullptr) PortVectors[PORTS::P11](pin);
    }
};
#endif


#if defined(PJIFG)
struct PortJ {

    constexpr void registerCallback(void (*callback)(MT::MSP430::GPIO::PIN)) noexcept {
        PortVectors[PORTS::PJ] = callback;
    };

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORTJ_VECTOR
    __interrupt void
        Port_J(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(PORTJ_VECTOR))) Port_J(void)
#else
#error Compiler not supported!
#endif
    {
        MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

        switch (__even_in_range(PJIV, PJIV_PJIFG7)) {
            case PJIV_NONE: break;
            case PJIV_PJIFG0:
                pin = MT::MSP430::GPIO::PIN::P0;
                break;
            case PJIV_PJIFG1:
                pin = MT::MSP430::GPIO::PIN::P1;
                break;
            case PJIV_PJIFG2:
                pin = MT::MSP430::GPIO::PIN::P2;
                break;
            case PJIV_PJIFG3:
                pin = MT::MSP430::GPIO::PIN::P3;
                break;
            case PJIV_PJIFG4:
                pin = MT::MSP430::GPIO::PIN::P4;
                break;
            case PJIV_PJIFG5:
                pin = MT::MSP430::GPIO::PIN::P5;
                break;
            case PJIV_PJIFG6:
                pin = MT::MSP430::GPIO::PIN::P6;
                break;
            case PJIV_PJIFG7:
                pin = MT::MSP430::GPIO::PIN::P7;
                break;
        }

        if (PortVectors[PORTS::PJ] != nullptr) PortVectors[PORTS::PJ](pin);
    }
};
#endif


#endif

}// namespace MT::MSP430::GPIO::Interrupt

#endif

#endif /* MICROTRAIT_MSP430_GPIO_GPIOINTERRUPT_HPP_ */

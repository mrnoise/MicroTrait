/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430EUSCIAInt Interrupt
 *  @ingroup groupMSP430EUSCI_A
* @brief functions to register Interrupt callbacks for Eusci A Interrupts at compile time or at runtime -> check settings.hpp
*
* @details
* Usage Compile time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef MT_MSP430_USE_EUSCIA_UART_COMPILE_TIME_CALLBACKS

constexpr static EUSCIA::UART::Interrupt::A0 int0{
   [](const EUSCIA::UART::INT src) {
	   if (src == EUSCIA::UART::INT::RECEIVE) {
			GPIO::Port1 p1;
			p1.setOutputHighOnPin(GPIO::PIN::P0);
		}
	}
};

#endif
\endcode

* Usage Runtime time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;
#ifndef MT_MSP430_USE_EUSCIA_UART_COMPILE_TIME_CALLBACKS

  EUSCIA::UART::Interrupt::A1 int1;
    int1.setIntrinsic(EUSCIA::UART::Interrupt::INTRINSICS::LEAVE_LOW_POWER);
    int1.registerCallback(
        []([[maybe_unused]] const EUSCIA::UART::INT src) {
                GPIO::Port1 p1;
                p1.setOutputHighOnPin(GPIO::PIN::P0);
                while (1)
                    ;
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

/** @defgroup groupFuncsMSP430EUSCIAInt Functions
*  @ingroup groupMSP430EUSCIAInt
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430EUSCIAInt Enums
*  @ingroup groupMSP430EUSCIAInt
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_EUSCI_EUSCIAINTERRUPT_HPP_
#define MICROTRAIT_MSP430_EUSCI_EUSCIAINTERRUPT_HPP_


#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include <MicroTrait/MSP430/EUSCI/EusciA.hpp>
#include "MicroTrait/Misc/Meta.hpp"
#include <type_traits>
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>
#include <tuple>

namespace MT::MSP430::EUSCIA::UART::Interrupt {

#ifdef MT_MSP430_USE_EUSCIA_UART_COMPILE_TIME_CALLBACKS

#if defined(USCI_A0_VECTOR)
template<typename FUNC>
struct A0 {

    /**
	* @ingroup groupFuncsMSP430EUSCIAInt
	****************************************************************
	* @brief constructor to register callback at compile time
	* @details
	* Usage: \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	* constexpr static EUSCIA::UART::Interrupt::A0 int0{
    *    [](const EUSCIA::UART::INT src) {
    *        if (src == EUSCIA::UART::INT::RECEIVE) {
    *            GPIO::Port1 p1;
    *            p1.setOutputHighOnPin(GPIO::PIN::P0);
    *        }
    *    }
    * }; \endcode
	* @param fun -> register callback function -> gets called in case of interrupt and provides the source of the interrupt
	****************************************************************
	*/
    constexpr explicit A0(FUNC fun) noexcept : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const EUSCIA::UART::INT>, "Missing [](const EUSCIA::UART::INT src) parameter for lambda interrupt A0 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A0_VECTOR
    __interrupt void USCI_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(USCI_A0_VECTOR))) USCI_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        EUSCIA::UART::INT src = EUSCIA::UART::INT::NONE;

        switch (__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG)) {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                src = EUSCIA::UART::INT::RECEIVE;
                break;
            case USCI_UART_UCTXIFG:
                src = EUSCIA::UART::INT::TRANSMIT;
                break;
            case USCI_UART_UCSTTIFG:
                src = EUSCIA::UART::INT::STARTBIT;
                break;
            case USCI_UART_UCTXCPTIFG:
                src = EUSCIA::UART::INT::TRANSMIT_COMPLETE;
                break;
        }
        std::get<0>(m_vectors)(src);
    }
};
#endif


#if defined(USCI_A1_VECTOR)
template<typename FUNC>
struct A1 {

    constexpr explicit A1(FUNC fun) noexcept : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const EUSCIA::UART::INT>, "Missing [](const EUSCIA::UART::INT src) parameter for lambda interrupt A1 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A1_VECTOR
    __interrupt void USCI_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(USCI_A1_VECTOR))) USCI_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        EUSCIA::UART::INT src = EUSCIA::UART::INT::NONE;

        switch (__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG)) {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                src = EUSCIA::UART::INT::RECEIVE;
                break;
            case USCI_UART_UCTXIFG:
                src = EUSCIA::UART::INT::TRANSMIT;
                break;
            case USCI_UART_UCSTTIFG:
                src = EUSCIA::UART::INT::STARTBIT;
                break;
            case USCI_UART_UCTXCPTIFG:
                src = EUSCIA::UART::INT::TRANSMIT_COMPLETE;
                break;
        }
        std::get<0>(m_vectors)(src);
    }
};
#endif


#if defined(USCI_A2_VECTOR)
template<typename FUNC>
struct A2 {

    constexpr explicit A2(FUNC fun) noexcept : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const EUSCIA::UART::INT>, "Missing [](const EUSCIA::UART::INT src) parameter for lambda interrupt A2 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A2_VECTOR
    __interrupt void USCI_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(USCI_A2_VECTOR))) USCI_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        EUSCIA::UART::INT src = EUSCIA::UART::INT::NONE;

        switch (__even_in_range(UCA2IV, USCI_UART_UCTXCPTIFG)) {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                src = EUSCIA::UART::INT::RECEIVE;
                break;
            case USCI_UART_UCTXIFG:
                src = EUSCIA::UART::INT::TRANSMIT;
                break;
            case USCI_UART_UCSTTIFG:
                src = EUSCIA::UART::INT::STARTBIT;
                break;
            case USCI_UART_UCTXCPTIFG:
                src = EUSCIA::UART::INT::TRANSMIT_COMPLETE;
                break;
        }
        std::get<0>(m_vectors)(src);
    }
};
#endif


#if defined(USCI_A3_VECTOR)
template<typename FUNC>
struct A3 {

    constexpr explicit A3(FUNC fun) noexcept : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const EUSCIA::UART::INT>, "Missing [](const EUSCIA::UART::INT src) parameter for lambda interrupt A3 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A3_VECTOR
    __interrupt void USCI_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(USCI_A3_VECTOR))) USCI_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        EUSCIA::UART::INT src = EUSCIA::UART::INT::NONE;

        switch (__even_in_range(UCA3IV, USCI_UART_UCTXCPTIFG)) {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                src = EUSCIA::UART::INT::RECEIVE;
                break;
            case USCI_UART_UCTXIFG:
                src = EUSCIA::UART::INT::TRANSMIT;
                break;
            case USCI_UART_UCSTTIFG:
                src = EUSCIA::UART::INT::STARTBIT;
                break;
            case USCI_UART_UCTXCPTIFG:
                src = EUSCIA::UART::INT::TRANSMIT_COMPLETE;
                break;
        }
        std::get<0>(m_vectors)(src);
    }
};
#endif


#else


enum class INTRINSICS {
    NONE            = 0,
    LEAVE_LOW_POWER = 1,
};

extern std::array<void (*)(const EUSCIA::UART::INT), 4> Vectors;
extern std::array<volatile INTRINSICS, 4>               Intrinsics;

#if defined(USCI_A0_VECTOR)
struct A0 {

    /**
	* @ingroup groupFuncsMSP430EUSCIAInt
	****************************************************************
	* @brief runtime interrupt callback registration
	* @details
	* Usage:  \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	*  EUSCIA::UART::Interrupt::A0 int1;
    *	int1.registerCallback(
    *    [](const EUSCIA::UART::INT src) {
    *           GPIO::Port1 p1;
    *           p1.setOutputHighOnPin(GPIO::PIN::P0);
    *   });
	*
	* \endcode
	*@param callback pointer to the callback function
	****************************************************************
	*/
    constexpr void registerCallback(void (*callback)(const EUSCIA::UART::INT)) noexcept {
        Vectors[0] = callback;
    }

    /**
	* @ingroup groupFuncsMSP430EUSCIAInt
	****************************************************************
	* @brief runs intrinsic on ISR leave
	* @details
	* Usage:  \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	*  EUSCIA::UART::Interrupt::A0 int1;
	*  int1.setIntrinsic(EUSCIA::UART::Interrupt::INTRINSICS::LEAVE_LOW_POWER);
	*
	* \endcode
	*@param callback pointer to the callback function
	****************************************************************
	*/
    constexpr void setIntrinsic(const INTRINSICS in) noexcept {
        Intrinsics[0] = in;
    }

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A0_VECTOR
    __interrupt void USCI_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(USCI_A0_VECTOR))) USCI_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        EUSCIA::UART::INT src = EUSCIA::UART::INT::NONE;

        switch (__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG)) {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                src = EUSCIA::UART::INT::RECEIVE;
                break;
            case USCI_UART_UCTXIFG:
                src = EUSCIA::UART::INT::TRANSMIT;
                break;
            case USCI_UART_UCSTTIFG:
                src = EUSCIA::UART::INT::STARTBIT;
                break;
            case USCI_UART_UCTXCPTIFG:
                src = EUSCIA::UART::INT::TRANSMIT_COMPLETE;
                break;
        }
        if (Vectors[0] != nullptr) Vectors[0](src);
        if (Intrinsics[0] == INTRINSICS::LEAVE_LOW_POWER) __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
    }
};
#endif


#if defined(USCI_A1_VECTOR)
struct A1 {

    constexpr void registerCallback(void (*callback)(const EUSCIA::UART::INT)) noexcept {
        Vectors[1] = callback;
    }

    constexpr void setIntrinsic(const INTRINSICS in) noexcept {
        Intrinsics[1] = in;
    }

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A1_VECTOR
    __interrupt void USCI_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(USCI_A1_VECTOR))) USCI_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        EUSCIA::UART::INT src = EUSCIA::UART::INT::NONE;

        switch (__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG)) {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                src = EUSCIA::UART::INT::RECEIVE;
                break;
            case USCI_UART_UCTXIFG:
                src = EUSCIA::UART::INT::TRANSMIT;
                break;
            case USCI_UART_UCSTTIFG:
                src = EUSCIA::UART::INT::STARTBIT;
                break;
            case USCI_UART_UCTXCPTIFG:
                src = EUSCIA::UART::INT::TRANSMIT_COMPLETE;
                break;
        }
        if (Vectors[1] != nullptr) Vectors[1](src);
        if (Intrinsics[1] == INTRINSICS::LEAVE_LOW_POWER) __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
    }
};
#endif


#if defined(USCI_A2_VECTOR)
struct A2 {

    constexpr void registerCallback(void (*callback)(const EUSCIA::UART::INT)) noexcept {
        Vectors[2] = callback;
    }

    constexpr void setIntrinsic(const INTRINSICS in) noexcept {
        Intrinsics[2] = in;
    }

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A2_VECTOR
    __interrupt void USCI_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(USCI_A2_VECTOR))) USCI_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        EUSCIA::UART::INT src = EUSCIA::UART::INT::NONE;

        switch (__even_in_range(UCA2IV, USCI_UART_UCTXCPTIFG)) {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                src = EUSCIA::UART::INT::RECEIVE;
                break;
            case USCI_UART_UCTXIFG:
                src = EUSCIA::UART::INT::TRANSMIT;
                break;
            case USCI_UART_UCSTTIFG:
                src = EUSCIA::UART::INT::STARTBIT;
                break;
            case USCI_UART_UCTXCPTIFG:
                src = EUSCIA::UART::INT::TRANSMIT_COMPLETE;
                break;
        }
        if (Vectors[2] != nullptr) Vectors[2](src);
        if (Intrinsics[2] == INTRINSICS::LEAVE_LOW_POWER) __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
    }
};
#endif


#if defined(USCI_A3_VECTOR)
struct A3 {

    constexpr void registerCallback(void (*callback)(const EUSCIA::UART::INT)) noexcept {
        Vectors[3] = callback;
    }

    constexpr void setIntrinsic(const INTRINSICS in) noexcept {
        Intrinsics[3] = in;
    }

  private:

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A3_VECTOR
    __interrupt void USCI_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(USCI_A3_VECTOR))) USCI_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        EUSCIA::UART::INT src = EUSCIA::UART::INT::NONE;

        switch (__even_in_range(UCA3IV, USCI_UART_UCTXCPTIFG)) {
            case USCI_NONE: break;
            case USCI_UART_UCRXIFG:
                src = EUSCIA::UART::INT::RECEIVE;
                break;
            case USCI_UART_UCTXIFG:
                src = EUSCIA::UART::INT::TRANSMIT;
                break;
            case USCI_UART_UCSTTIFG:
                src = EUSCIA::UART::INT::STARTBIT;
                break;
            case USCI_UART_UCTXCPTIFG:
                src = EUSCIA::UART::INT::TRANSMIT_COMPLETE;
                break;
        }
        if (Vectors[3] != nullptr) Vectors[3](src);
        if (Intrinsics[3] == INTRINSICS::LEAVE_LOW_POWER) __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
    }
};
#endif


#endif


}// namespace MT::MSP430::EUSCIA::UART::Interrupt

#endif
#endif /* MICROTRAIT_MSP430_EUSCI_EUSCIAINTERRUPT_HPP_ */

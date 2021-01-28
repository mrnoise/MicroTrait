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
   [](const EUSCIA::UART::INT src) { //-> use only lambdas for compile time registration!!
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
    int1.setIntrinsic(EUSCIA::UART::Interrupt::ISR_INTRINSICS::LEAVE_LOW_POWER);
    int1.registerCallback(
        []([[maybe_unused]] const EUSCIA::UART::INT src) {
                GPIO::Port1 p1;
                p1.setOutputHighOnPin(GPIO::PIN::P0);
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
#include "MicroTrait/MSP430/Types.hpp"
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
    *    [](const EUSCIA::UART::INT src) { //-> use only lambdas for compile time registration!!
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


using Callback = void (*)(const EUSCIA::UART::INT);

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
    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
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
 	*  int1.setIntrinsic(ISR_INTRINSICS::LEAVE_LOW_POWER);
 	*
 	* \endcode
 	*@param in Intrinsics which should be invoked prior to leaving the ISR
 	****************************************************************
 	*/
    constexpr static inline void setIntrinsic(const ISR_INTRINSICS in) noexcept {
        m_intrinsic = in;
    }

  private:
    static inline volatile ISR_INTRINSICS m_intrinsic = ISR_INTRINSICS::NONE;
    static inline volatile Callback       m_cb        = nullptr;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A0_VECTOR
    __interrupt static inline void        USCI_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(USCI_A0_VECTOR))) USCI_ISR(void)
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
        if (m_cb != nullptr) m_cb(src);
        if (m_intrinsic == ISR_INTRINSICS::LEAVE_LOW_POWER) __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
    }
};
#endif

#if defined(USCI_A1_VECTOR)
struct A1 {

    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
    }

    constexpr static inline void setIntrinsic(const ISR_INTRINSICS in) noexcept {
        m_intrinsic = in;
    }

  private:
    static inline volatile ISR_INTRINSICS m_intrinsic = ISR_INTRINSICS::NONE;
    static inline volatile Callback       m_cb        = nullptr;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A1_VECTOR
    __interrupt static inline void        USCI_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(USCI_A1_VECTOR))) USCI_ISR(void)
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
        if (m_cb != nullptr) m_cb(src);
        if (m_intrinsic == ISR_INTRINSICS::LEAVE_LOW_POWER) __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
    }
};
#endif


#if defined(USCI_A2_VECTOR)
struct A2 {

    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
    }

    constexpr static inline void setIntrinsic(const ISR_INTRINSICS in) noexcept {
        m_intrinsic = in;
    }

  private:
    static inline volatile ISR_INTRINSICS m_intrinsic = ISR_INTRINSICS::NONE;
    static inline volatile Callback       m_cb        = nullptr;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A2_VECTOR
    __interrupt static inline void        USCI_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(USCI_A2_VECTOR))) USCI_ISR(void)
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
        if (m_cb != nullptr) m_cb(src);
        if (m_intrinsic == ISR_INTRINSICS::LEAVE_LOW_POWER) __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
    }
};
#endif


#if defined(USCI_A3_VECTOR)
struct A3 {

    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
    }

    constexpr static inline void setIntrinsic(const ISR_INTRINSICS in) noexcept {
        m_intrinsic = in;
    }

  private:
    static inline volatile ISR_INTRINSICS m_intrinsic = ISR_INTRINSICS::NONE;
    static inline volatile Callback       m_cb        = nullptr;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_A3_VECTOR
    __interrupt static inline void        USCI_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(USCI_A3_VECTOR))) USCI_ISR(void)
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
        if (m_cb != nullptr) m_cb(src);
        if (m_intrinsic == ISR_INTRINSICS::LEAVE_LOW_POWER) __bic_SR_register_on_exit(CPUOFF);// Exit LPM0 on reti
    }
};
#endif

#endif


}// namespace MT::MSP430::EUSCIA::UART::Interrupt

#endif
#endif /* MICROTRAIT_MSP430_EUSCI_EUSCIAINTERRUPT_HPP_ */

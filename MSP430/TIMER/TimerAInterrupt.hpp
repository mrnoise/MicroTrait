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

  constexpr static TIMERA::Interrupt::TA0 int0{
        [](const TIMERA::Interrupt::SOURCE src) {  //-> use only lambdas for compile time registration!!
            if (TIMERA::Interrupt::isSet(src, TIMERA::Interrupt::SOURCE::REGISTER0)) {
                 GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
                TIMERA::TA0().setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, COMPARE_VALUE);
            }
        }
    };

#endif
\endcode

* Usage Runtime time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;
#ifndef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS

	TIMERA::Interrupt::TA0 int0;
    int0.registerCallback(
        [](const TIMERA::Interrupt::SOURCE src) {
            if (TIMERA::Interrupt::isSet(src, TIMERA::Interrupt::SOURCE::REGISTER0)) {
                 GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
                TIMERA::TA0().setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, COMPARE_VALUE);
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
#include "MicroTrait/MSP430/Types.hpp"
#include <type_traits>
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>
#include <tuple>


namespace MT::Misc {
enum class TIMERA_INT_SOURCE : uint16_t {
    NONE      = 0,
    REGISTER0 = (1U << 0U),
    REGISTER1 = (1U << 1U),
    REGISTER2 = (1U << 2U),
    REGISTER3 = (1U << 3U),
    REGISTER4 = (1U << 4U),
    REGISTER5 = (1U << 5U),
    REGISTER6 = (1U << 6U),
    REGISTER7 = (1U << 7U),
    OVERFLOW  = (1U << 8U)
};
template<>
struct enable_Enum_bits<TIMERA_INT_SOURCE> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile TIMERA_INT_SOURCE> {
    static constexpr bool enable = true;
};
}// namespace MT::Misc

namespace MT::MSP430::TIMERA::Interrupt {

/**
* @ingroup groupEnumsMSP430TimerAInt
****************************************************************
* @brief Interrupt source
****************************************************************
*/
using SOURCE = MT::Misc::TIMERA_INT_SOURCE;

/**
* @ingroup groupFuncsMSP430TimerAInt
****************************************************************
* @brief checks if the given interrupt is set
* @details
* Usage: \code {.cpp}
*        if (TIMERA::Interrupt::isSet(src, TIMERA::Interrupt::SOURCE::REGISTER0)) doSomething(); \endcode
*@param lhs left hand side of the comparison can be the source or the interrupt to check for if set
*@param rhs right hand side of the comparison can be the source or the interrupt to check for if set
****************************************************************
*/
constexpr bool isSet(const SOURCE lhs, const SOURCE rhs) noexcept { return MT::Misc::Cast::toUnderlyingType(lhs) & MT::Misc::Cast::toUnderlyingType(rhs); }

#ifdef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS


#if defined(TIMER0_A0_VECTOR) && defined(TIMER0_A1_VECTOR)
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
	*  constexpr static TIMERA::Interrupt::TA0 int0{
    *    [](const TIMERA::Interrupt::SOURCE src) {  //-> use only lambdas for compile time registration!!
    *       if (TIMERA::Interrupt::isSet(src, TIMERA::Interrupt::SOURCE::REGISTER0)) {
    *             GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
    *            TIMERA::TA0().setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, COMPARE_VALUE);
    *        }
    *    }
    * }; \endcode
	*@param fun -> register callback function -> gets called in case of interrupt and provides the pin number
	****************************************************************
	*/
    constexpr explicit TA0(FUNC fun) noexcept : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const TIMERA::Interrupt::SOURCE>, "Missing [](const TIMERA::Interrupt::SOURCE src) parameter for lambda interrupt TA0 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
    __interrupt void A0_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER0_A0_VECTOR))) A0_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        std::get<0>(m_vectors)(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A1_VECTOR
    __interrupt void A1_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER0_A1_VECTOR))) A1_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA0IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src |= SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src |= SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src |= SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src |= SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src |= SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src |= SOURCE::REGISTER6;
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


#if defined(TIMER1_A0_VECTOR) && defined(TIMER1_A1_VECTOR)
template<typename FUNC>
struct TA1 {

    constexpr explicit TA1(FUNC fun) noexcept : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const TIMERA::Interrupt::SOURCE>, "Missing [](const TIMERA::Interrupt::SOURCE src) parameter for lambda interrupt TA1 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A0_VECTOR
    __interrupt void A0_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER1_A0_VECTOR))) A0_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        std::get<0>(m_vectors)(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A1_VECTOR
    __interrupt void A1_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER1_A1_VECTOR))) A1_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA1IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src |= SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src |= SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src |= SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src |= SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src |= SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src |= SOURCE::REGISTER6;
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

#if defined(TIMER2_A0_VECTOR) && defined(TIMER2_A1_VECTOR)
template<typename FUNC>
struct TA2 {

    constexpr explicit TA2(FUNC fun) noexcept : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const TIMERA::Interrupt::SOURCE>, "Missing [](const TIMERA::Interrupt::SOURCE src) parameter for lambda interrupt TA2 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER2_A0_VECTOR
    __interrupt void A0_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER2_A0_VECTOR))) A0_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        std::get<0>(m_vectors)(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER2_A1_VECTOR
    __interrupt void A1_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER2_A1_VECTOR))) A1_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA2IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src |= SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src |= SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src |= SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src |= SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src |= SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src |= SOURCE::REGISTER6;
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


#if defined(TIMER3_A0_VECTOR) && defined(TIMER3_A1_VECTOR)
template<typename FUNC>
struct TA3 {

    constexpr explicit TA3(FUNC fun) noexcept : m_vectors{ std::move(fun) } {
        static_assert(std::is_invocable_v<FUNC, const TIMERA::Interrupt::SOURCE>, "Missing [](const TIMERA::Interrupt::SOURCE src) parameter for lambda interrupt TA3 !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER3_A0_VECTOR
    __interrupt void A0_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER3_A0_VECTOR))) A0_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        std::get<0>(m_vectors)(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER3_A1_VECTOR
    __interrupt void A1_ISR(void)
#elif defined(__GNUC__)
    void __attribute__((interrupt(TIMER3_A1_VECTOR))) A1_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA3IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src |= SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src |= SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src |= SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src |= SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src |= SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src |= SOURCE::REGISTER6;
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

using Callback = void (*)(const TIMERA::Interrupt::SOURCE);

#if defined(TIMER0_A0_VECTOR) && defined(TIMER0_A1_VECTOR)
struct TA0 {

    /**
	* @ingroup groupFuncsMSP430TimerAInt
	****************************************************************
	* @brief runtime interrupt callback registration
	* @details
	* Usage:  \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	*   TIMERA::Interrupt::TA0 int0;
    *	int0.registerCallback(
    *    [](const TIMERA::Interrupt::SOURCE src) {
    *       if (TIMERA::Interrupt::isSet(src, TIMERA::Interrupt::SOURCE::REGISTER0)) {
    *             GPIO::Port1().toggleOutputOnPin(GPIO::PIN::P0);
    *            TIMERA::TA0().setCompareValue(TIMERA::CAPTURE_COMPARE::REGISTER0, COMPARE_VALUE);
    *        }
    *    });
	*
	* \endcode
	*@param callback pointer to the callback function
	****************************************************************
	*/
    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
    };

    /**
	* @ingroup groupFuncsMSP430TimerAInt
	****************************************************************
	* @brief runs intrinsic on ISR leave
	* @details
	* Usage:  \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	*  TIMERA::Interrupt::TA1 int1;
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
#pragma vector = TIMER0_A0_VECTOR
    __interrupt static inline void A0_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(TIMER0_A0_VECTOR))) A0_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        if (m_cb != nullptr) m_cb(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A1_VECTOR
    __interrupt static inline void A1_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(TIMER0_A1_VECTOR))) A1_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA0IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src |= SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src |= SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src |= SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src |= SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src |= SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src |= SOURCE::REGISTER6;
                break;//CCR6
            case 14:
                src = SOURCE::OVERFLOW;
                break;//Overflow
            default: break;
        }
        if (m_cb != nullptr) m_cb(src);
    }
};
#endif


#if defined(TIMER1_A0_VECTOR) && defined(TIMER1_A1_VECTOR)
struct TA1 {

    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
    };

    constexpr static inline void setIntrinsic(const ISR_INTRINSICS in) noexcept {
        m_intrinsic = in;
    }

  private:
    static inline volatile ISR_INTRINSICS m_intrinsic = ISR_INTRINSICS::NONE;
    static inline volatile Callback       m_cb        = nullptr;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A0_VECTOR
    __interrupt static inline void A0_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(TIMER1_A0_VECTOR))) A0_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        if (m_cb != nullptr) m_cb(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A1_VECTOR
    __interrupt static inline void A1_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(TIMER1_A1_VECTOR))) A1_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA1IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src |= SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src |= SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src |= SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src |= SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src |= SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src |= SOURCE::REGISTER6;
                break;//CCR6
            case 14:
                src = SOURCE::OVERFLOW;
                break;//Overflow
            default: break;
        }
        if (m_cb != nullptr) m_cb(src);
    }
};
#endif


#if defined(TIMER2_A0_VECTOR) && defined(TIMER2_A1_VECTOR)
struct TA2 {

    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
    };

    constexpr static inline void setIntrinsic(const ISR_INTRINSICS in) noexcept {
        m_intrinsic = in;
    }

  private:
    static inline volatile ISR_INTRINSICS m_intrinsic = ISR_INTRINSICS::NONE;
    static inline volatile Callback       m_cb        = nullptr;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER2_A0_VECTOR
    __interrupt static inline void A0_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(TIMER2_A0_VECTOR))) A0_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        if (m_cb != nullptr) m_cb(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER2_A1_VECTOR
    __interrupt static inline void A1_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(TIMER2_A1_VECTOR))) A1_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA2IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src |= SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src |= SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src |= SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src |= SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src |= SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src |= SOURCE::REGISTER6;
                break;//CCR6
            case 14:
                src = SOURCE::OVERFLOW;
                break;//Overflow
            default: break;
        }
        if (m_cb != nullptr) m_cb(src);
    }
};
#endif


#if defined(TIMER3_A0_VECTOR) && defined(TIMER3_A1_VECTOR)
struct TA3 {

    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
    };

    constexpr static inline void setIntrinsic(const ISR_INTRINSICS in) noexcept {
        m_intrinsic = in;
    }

  private:
    static inline volatile ISR_INTRINSICS m_intrinsic = ISR_INTRINSICS::NONE;
    static inline volatile Callback       m_cb        = nullptr;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER3_A0_VECTOR
    __interrupt static inline void A0_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(TIMER3_A0_VECTOR))) A0_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        if (m_cb != nullptr) m_cb(SOURCE::REGISTER0);
    }

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER3_A1_VECTOR
    __interrupt static inline void A1_ISR(void)
#elif defined(__GNUC__)
    static inline void __attribute__((interrupt(TIMER3_A1_VECTOR))) A1_ISR(void)
#else
#error Compiler not supported!
#endif
    {
        SOURCE src = SOURCE::NONE;
        //Any access, read or write, of the TAIV register automatically resets the
        //highest "pending" interrupt flag
        switch (__even_in_range(TA3IV, 14)) {
            case 0: break;//No interrupt
            case 2:
                src |= SOURCE::REGISTER1;
                break;//CCR1
            case 4:
                src |= SOURCE::REGISTER2;
                break;//CCR2
            case 6:
                src |= SOURCE::REGISTER3;
                break;//CCR3
            case 8:
                src |= SOURCE::REGISTER4;
                break;//CCR4
            case 10:
                src |= SOURCE::REGISTER5;
                break;//CCR5
            case 12:
                src |= SOURCE::REGISTER6;
                break;//CCR6
            case 14:
                src = SOURCE::OVERFLOW;
                break;//Overflow
            default: break;
        }
        if (m_cb != nullptr) m_cb(src);
    }
};
#endif


#endif
}// namespace MT::MSP430::TIMERA::Interrupt

#endif

#endif /* MICROTRAIT_MSP430_TIMER_TIMERAINTERRUPT_HPP_ */

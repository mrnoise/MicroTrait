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
    constexpr static WDTA::Interrupt::WDT inter{  // use lambdas only!
        []() {
            GPIO::Port1 p1{};
            p1.toggleOutputOnPin(GPIO::PIN::P0);
        }
    };
#endif

\endcode

* Usage Runtime time: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifndef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS
    WDTA::Interrupt::WDT inter;
    inter.registerCallback([]() {
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

#include "MicroTrait/Misc/Meta.hpp"
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>
#include <tuple>
#include <functional>

namespace MT::MSP430::WDTA::Interrupt {

/**
* @ingroup groupEnumsMSP430WdtAInt
****************************************************************
* @brief Available Watchdog Timers for interrupt callbacks
****************************************************************
*/

#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

template<typename FUNC>
struct WDT {

    using Signature = void(void);

    /**
	* @ingroup groupFuncsMSP430WdtAInt
	****************************************************************
	* @brief constructor to register callback at compile time
	* @details
	* Usage: \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	*  constexpr static WDTA::Interrupt::WDT inter{  // use lambdas only!
    *    []() {
    *        GPIO::Port1 p1{};
    *        p1.toggleOutputOnPin(GPIO::PIN::P0);
    *    }
    * }; \endcode
	*@param fun -> register callback function -> gets called in case of interrupt
	****************************************************************
	*/
    constexpr explicit WDT(FUNC &&fun) noexcept : m_vectors{ std::forward<std::tuple<FUNC>>(fun) } {
        static_assert(std::is_convertible_v<FUNC &&, std::function<Signature>>, "remove parameters for lambda interrupt wdta !");
        static_assert(std::is_move_constructible_v<FUNC>, "Function isn`t a lambda for wdta !");
    }

  private:
    std::tuple<FUNC> m_vectors;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = WDT_VECTOR
    __interrupt
#elif defined(__GNUC__)
    __attribute__((interrupt(WDT_VECTOR)))
#endif
        void
        WDT_A_ISR(void) {

        std::get<0>(m_vectors)();
    }
};

#else

using Callback = void (*)();

struct WDT {

    /**
	* @ingroup groupFuncsMSP430WdtAInt
	****************************************************************
	* @brief runtime interrupt callback registration
	* @details
	* Usage:  \code {.cpp}
	*
	*	using namespace MT::MSP430;
	*
	*	WDTA::Interrupt::WDT inter;
    *		inter.registerCallback([]() { //-> use only lambdas for compile time registration!!
    *    	GPIO::Port1 p1{};
    *    	p1.toggleOutputOnPin(GPIO::PIN::P0);
    *	});
	* \endcode
	*@param callback pointer to the callback function
	****************************************************************
	*/
    constexpr static inline void registerCallback(Callback callback) noexcept {
        m_cb = callback;
    };


    /**
	* @ingroup groupFuncsMSP430WdtAInt
	****************************************************************
	* @brief runs intrinsic on ISR leave
	* @details
	* Usage:  \code {.cpp}
	*
	* using namespace MT::MSP430;
	*
	*  WDTA::Interrupt::WDT inter;
	*  inter.setIntrinsic(ISR_INTRINSICS::LEAVE_LOW_POWER);
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
#pragma vector = WDT_VECTOR
    __interrupt
#elif defined(__GNUC__)
    __attribute__((interrupt(WDT_VECTOR)))
#endif
        static inline void
        WDT_A_ISR(void) {
        if (m_cb != nullptr) m_cb();
    }
};

#endif

}// namespace MT::MSP430::WDTA::Interrupt

#endif

#endif /* MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_ */

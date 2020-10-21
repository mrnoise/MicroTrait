/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430GpioInt GPIO Interrupt
 *  @ingroup groupMSP430
* @brief functions to register Interrupt callbacks at compile time or at runtime -> check settings.hpp
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

#ifndef MICROTRAIT_MSP430_GPIO_PORTINTERRUPT_HPP_
#define MICROTRAIT_MSP430_GPIO_PORTINTERRUPT_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Interrupt.hpp"
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>

namespace MT {
namespace MSP430 {
    namespace GPIO {
        namespace Interrupt {

            /**
          	* @ingroup groupEnumsMSP430GpioInt
          	****************************************************************
          	* @brief Available Ports for interrupt callbacks
          	****************************************************************
          	*/
            enum class PORTS {
                PORT1 = 0,
                PORT2
            };

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

            template<typename ENUM, typename FUNC>
            using IntHandlers = MT::Universal::Interrupt::IntHandlers<ENUM, FUNC>; /**< this pair represents the ISR -> first the Enum which refers to a vector and second the function to call */

            template<typename... Vector>
            using Interrupt = MT::Universal::Interrupt::Interrupt<Vector...>;

            /**
			* @ingroup groupFuncsMSP430GpioInt
			****************************************************************
			* @brief maker function for a complete callback registration
			* @details
			* Usage: \code {.cpp}
			*
			* using namespace MT::MSP430;
			*
			*	GPIO::Interrupt::makeHandler(
			*		GPIO::Interrupt::PORTS::PORT2,
			*		[]() {
			*			GPIO::Port1 p1{};
			*			GPIO::Port2 p2{};
			*			p2.clearInterrupt(GPIO::PIN::P3);
			*			p1.toggleOutputOnPin(GPIO::PIN::P0);
			*		})); \endcode
			*@param t -> all entries to register first the port than the callback
			*@return the copile time objects containing all registered callbacks
			****************************************************************
			*/
            template<typename ENUM, typename... FUNC>
            [[nodiscard]] constexpr auto makeInterrupt(IntHandlers<ENUM, FUNC>... t) noexcept {
                static_assert(std::is_same<ENUM, PORTS>::value, "input must be PORTS enum");
                return Interrupt<ENUM, FUNC...>{ std::move(t)... };
            }

            /**
			* @ingroup groupFuncsInt
			****************************************************************
			* @brief maker function for one callback entry
			* @details
			* Usage: cascade with makeInterrupt like: \code {.cpp}
			*	GPIO::Interrupt::makeHandler(
			*		GPIO::Interrupt::PORTS::PORT2,
			*		[]() {
			*			GPIO::Port1 p1{};
			*			GPIO::Port2 p2{};
			*			p2.clearInterrupt(GPIO::PIN::P3);
			*			p1.toggleOutputOnPin(GPIO::PIN::P0);
			*		})); \endcode
			*@param p the Enum
			*@param t the callback
			*@return one IntHandler (std::pair<GPIO::Interrupt::PORTS, FUNC>)
			****************************************************************
			*/
            template<typename ENUM, typename FUNC>
            [[nodiscard]] constexpr auto makeHandler(ENUM p, FUNC t) noexcept {
                static_assert(std::is_same<ENUM, PORTS>::value, "input must be PORTS enum");
                return IntHandlers<ENUM, FUNC>{ p, std::move(t) };
            }

#else
            extern std::array<void (*)(), 2> PortVectors;

            /**
			* @ingroup groupFuncsInt
			****************************************************************
			* @brief runtime interrupt callback registration
			* @details
			* Usage:  \code {.cpp}
			*
			* using namespace MT::MSP430;
			*
			*	GPIO::Interrupt::registerCallback(GPIO::Interrupt::PORTS::PORT1, []() {
			*		GPIO::Port1 p1{};
			*		p1.clearInterrupt(GPIO::PIN::P4);
			*		p1.toggleOutputOnPin(GPIO::PIN::P0);
			*	});
			* \endcode
			*@param ports the port for which the callback should be registered (GPIO::Interrupt::PORTS)
			*@param callback pointer to the callback function
			****************************************************************
			*/
            constexpr void registerCallback(const PORTS ports, void (*callback)()) noexcept {
                PortVectors[ports] = callback;
            };
#endif
        }// namespace Interrupt
    }    // namespace GPIO
}// namespace MSP430
}// namespace MT

#endif

#endif /* MICROTRAIT_MSP430_GPIO_PORTINTERRUPT_HPP_ */

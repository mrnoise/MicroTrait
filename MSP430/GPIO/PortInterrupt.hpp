
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

            enum PORTS {
                PORT1 = 0,
                PORT2
            };

#ifdef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

            template<typename ENUM, typename FUNC>
            using IntHandlers = MT::Universal::Interrupt::IntHandlers<ENUM, FUNC>;

            template<typename... Vector>
            using Interrupt = MT::Universal::Interrupt::Interrupt<Vector...>;

            template<typename ENUM, typename... FUNC>
            [[nodiscard]] constexpr auto makeInterrupt(IntHandlers<ENUM, FUNC>... t) noexcept {
                static_assert(std::is_same<ENUM, PORTS>::value, "input must be PORTS enum");
                return Interrupt<ENUM, FUNC...>{ std::move(t)... };
            }

            template<typename ENUM, typename FUNC>
            [[nodiscard]] constexpr auto makeHandler(ENUM p, FUNC t) noexcept {
                static_assert(std::is_same<ENUM, PORTS>::value, "input must be PORTS enum");
                return IntHandlers<ENUM, FUNC>{ p, std::move(t) };
            }

#else
            extern std::array<void (*)(), 2> PortVectors;

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

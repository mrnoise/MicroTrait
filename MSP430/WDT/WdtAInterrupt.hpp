
#ifndef MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_
#define MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Interrupt.hpp"
#include <msp430.h>
#include <utility>
#include <limits>
#include <array>

namespace MT {
namespace MSP430 {
    namespace WDT {
        namespace Interrupt {

            enum WDT {
                WDTA = 0,
            };

#ifdef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

            template<typename ENUM, typename FUNC>
            using IntHandlers = MT::Universal::Interrupt::IntHandlers<ENUM, FUNC>;

            template<typename... Vector>
            using Interrupt = MT::Universal::Interrupt::Interrupt<Vector...>;

            template<typename ENUM, typename... FUNC>
            [[nodiscard]] constexpr auto makeInterrupt(IntHandlers<ENUM, FUNC>... t) noexcept {
                static_assert(std::is_same<ENUM, WDT>::value, "input must be WDT enum");
                return Interrupt<ENUM, FUNC...>{ std::move(t)... };
            }

            template<typename ENUM, typename FUNC>
            [[nodiscard]] constexpr auto makeHandler(ENUM p, FUNC t) noexcept {
                static_assert(std::is_same<ENUM, WDT>::value, "input must be WDT enum");
                return IntHandlers<ENUM, FUNC>{ p, std::move(t) };
            }

#else
            extern std::array<void (*)(), 1> WdtVectors;

            constexpr void registerCallback(void (*callback)()) noexcept {
                WdtVectors[WDTA] = callback;
            };
#endif

        }// namespace Interrupt
    }    // namespace WDT
}// namespace MSP430
}// namespace MT

#endif

#endif /* MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_ */


#ifndef MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_
#define MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_

#include "MicroTrait/MSP430/Settings.hpp"
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

            template<typename T>
            using IntHandlers = std::pair<WDT, T>;

            template<typename... Vector>
            struct Interrupt {

                constexpr explicit Interrupt(IntHandlers<Vector>... handler) noexcept
                  : m_indexes{ handler.first... }, m_vectors{ std::move(handler.second...) } {
                }

                [[nodiscard]] constexpr std::size_t get_index(const WDT p) const noexcept {

                    for (std::size_t idx = 0; idx < m_indexes.size(); ++idx) {
                        if (m_indexes[idx] == p) return idx;
                    }

                    return std::numeric_limits<std::size_t>::max();
                }

                std::array<WDT, sizeof...(Vector)> m_indexes;
                std::tuple<Vector...>              m_vectors;
            };


            template<typename... T>
            [[nodiscard]] constexpr auto makeInterrupt(IntHandlers<T>... t) noexcept {
                return Interrupt<T...>{ std::move(t)... };
            }

            template<typename T>
            [[nodiscard]] constexpr auto makeHandler(WDT p, T t) noexcept {
                return IntHandlers<T>{ p, std::move(t) };
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


#endif /* MICROTRAIT_MSP430_WDT_WDTAINTERRUPT_HPP_ */


#ifndef MICROTRAIT_MSP430_GPIO_PORTINTERRUPT_HPP_
#define MICROTRAIT_MSP430_GPIO_PORTINTERRUPT_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

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

            template<typename T>
            using IntHandlers = std::pair<PORTS, T>;

            template<typename... Vector>
            struct Interrupt {

                constexpr explicit Interrupt(IntHandlers<Vector>... handler) noexcept
                  : m_indexes{ handler.first... }, m_vectors{ std::move(handler.second...) } {
                }

                [[nodiscard]] constexpr std::size_t get_index(const PORTS p) const noexcept {

                    for (std::size_t idx = 0; idx < m_indexes.size(); ++idx) {
                        if (m_indexes[idx] == p) return idx;
                    }

                    return std::numeric_limits<std::size_t>::max();
                }

                std::array<PORTS, sizeof...(Vector)> m_indexes;
                std::tuple<Vector...>                m_vectors;
            };


            template<typename... T>
            [[nodiscard]] constexpr auto makeInterrupt(IntHandlers<T>... t) noexcept {
                return Interrupt<T...>{ std::move(t)... };
            }

            template<typename T>
            [[nodiscard]] constexpr auto makeHandler(PORTS p, T t) noexcept {
                return IntHandlers<T>{ p, std::move(t) };
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

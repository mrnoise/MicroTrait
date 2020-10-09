/*
 * PortInterrupt.hpp
 *
 *  Created on: 06.10.2020
 *      Author: steff
 */

#ifndef MICROTRAIT_MSP430_GPIO_PORTINTERRUPT_HPP_
#define MICROTRAIT_MSP430_GPIO_PORTINTERRUPT_HPP_

#include "MicroTrait/Universal/Interrupt.hpp"
#include <utility>

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

                constexpr std::size_t get_index(const PORTS p) const noexcept {

                    for (std::size_t idx = 0; idx < m_indexes.size(); ++idx) {
                        if (m_indexes[idx] == p) return idx;
                    }

                    return std::numeric_limits<std::size_t>::max();
                }

                std::array<PORTS, sizeof...(Vector)> m_indexes;
                std::tuple<Vector...>                m_vectors;
            };


            template<typename... T>
            constexpr auto makeInterrupt(IntHandlers<T>... t) noexcept {
                return Interrupt<T...>{ std::move(t)... };
            }

            template<typename T>
            constexpr auto makeHandler(PORTS p, T t) noexcept {
                return IntHandlers<T>{ p, std::move(t) };
            }


#else

            std::array<void (*)(), 2> PortVectors{};

            constexpr void registerCallback(const PORTS ports, void (*callback)()) noexcept {
                PortVectors[ports] = callback;
            };

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT1_VECTOR
            __interrupt void Port_1(void)
#elif defined(__GNUC__)
            void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
            {
                if (PortVectors[PORT1] != nullptr) PortVectors[PORT1]();
            }

// Port 2 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
            __interrupt void Port_2(void)
#elif defined(__GNUC__)
            void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
            {
                if (PortVectors[PORT2] != nullptr) PortVectors[PORT2]();
            }
#endif

        }// namespace Interrupt
    }    // namespace GPIO
}// namespace MSP430
}// namespace MT


#endif /* MICROTRAIT_MSP430_GPIO_PORTINTERRUPT_HPP_ */


#ifndef MICROTRAIT_UNIVERSAL_INTERRUPT_HPP_
#define MICROTRAIT_UNIVERSAL_INTERRUPT_HPP_

#include <stdint.h>
#include <array>
#include <tuple>
#include <limits>

namespace MT {
namespace Universal {
    namespace Interrupt {
        enum class VECTORS {
            VECTOR1 = 0,
            VECTOR2,
            VECTOR3,
            VECTOR4,
            VECTOR5,
            VECTOR6,
            VECTOR7,
            VECTOR8
        };

        template<typename T>
        using IntHandlers = std::pair<VECTORS, T>;

        template<typename... Vector>
        struct Interrupt {

            constexpr explicit Interrupt(IntHandlers<Vector>... handler) noexcept
              : m_indexes{ handler.first... }, m_vectors{ std::move(handler.second...) } {
            }

              [[nodiscard]] constexpr std::size_t get_index(const VECTORS p) const noexcept {

                for (std::size_t idx = 0; idx < m_indexes.size(); ++idx) {
                    if (m_indexes[idx] == p) return idx;
                }

                return std::numeric_limits<std::size_t>::max();
            }

            std::array<VECTORS, sizeof...(Vector)> m_indexes;
            std::tuple<Vector...>                  m_vectors;
        };


        template<typename... T>
        [[nodiscard]] constexpr auto makeInterrupt(IntHandlers<T>... t) noexcept {
            return Interrupt<T...>{ std::move(t)... };
        }

        template<typename T>
        [[nodiscard]] constexpr auto makeHandler(VECTORS p, T t) noexcept {
            return IntHandlers<T>{ p, std::move(t) };
        }

    }// namespace Interrupt
}// namespace Universal
}// namespace MT

#endif /* MICROTRAIT_UNIVERSAL_INTERRUPT_HPP_ */

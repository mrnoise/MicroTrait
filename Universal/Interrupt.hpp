
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

        template<typename ENUM, typename FUNC>
        using IntHandlers = std::pair<ENUM, FUNC>;

        template<typename ENUM, typename... Vector>
        struct Interrupt {

            constexpr explicit Interrupt(IntHandlers<ENUM, Vector>... handler) noexcept
              : m_indexes{ handler.first... }, m_vectors{ std::move(handler.second)... } {
            }

            [[nodiscard]] constexpr std::size_t get_index(const ENUM p) const noexcept {

                for (std::size_t idx = 0; idx < m_indexes.size(); ++idx) {
                    if (m_indexes[idx] == p) return idx;
                }

                return std::numeric_limits<std::size_t>::max();
            }

            std::array<ENUM, sizeof...(Vector)> m_indexes;
            std::tuple<Vector...>               m_vectors;
        };


        template<typename ENUM, typename... FUNC>
        [[nodiscard]] constexpr auto makeInterrupt(IntHandlers<ENUM, FUNC>... t) noexcept {
            return Interrupt<ENUM, FUNC...>{ std::move(t)... };
        }

        template<typename ENUM, typename FUNC>
        [[nodiscard]] constexpr auto makeHandler(ENUM p, FUNC t) noexcept {
            return IntHandlers<ENUM, FUNC>{ p, std::move(t) };
        }

    }// namespace Interrupt
}// namespace Universal
}// namespace MT

#endif /* MICROTRAIT_UNIVERSAL_INTERRUPT_HPP_ */


#ifndef MICROTRAIT_UNIVERSAL_REGISTER_HPP_
#define MICROTRAIT_UNIVERSAL_REGISTER_HPP_


#include <MicroTrait/Misc/Details.hpp>
#include <MicroTrait/Misc/EnumBits.hpp>
#include <stdint.h>
#include <type_traits>
#include <utility>

enum class BITS8 : uint8_t {
    B0 = (1U << 0U),
    B1 = (1U << 1U),
    B2 = (1U << 2U),
    B3 = (1U << 3U),
    B4 = (1U << 4U),
    B5 = (1U << 5U),
    B6 = (1U << 6U),
    B7 = (1U << 7U)
};
ENABLE_ENUM_BITS(BITS8);

enum class BITS16 : uint16_t {
    B0  = (1U << 0U),
    B1  = (1U << 1U),
    B2  = (1U << 2U),
    B3  = (1U << 3U),
    B4  = (1U << 4U),
    B5  = (1U << 5U),
    B6  = (1U << 6U),
    B7  = (1U << 7U),
    B8  = (1U << 8U),
    B9  = (1U << 9U),
    B10 = (1U << 10U),
    B11 = (1U << 11U),
    B12 = (1U << 12U),
    B13 = (1U << 13U),
    B14 = (1U << 14U),
    B15 = (1U << 15U)
};
ENABLE_ENUM_BITS(BITS16);

enum class BITS32 : uint32_t {
    B0  = (1UL << 0UL),
    B1  = (1UL << 1UL),
    B2  = (1UL << 2UL),
    B3  = (1UL << 3UL),
    B4  = (1UL << 4UL),
    B5  = (1UL << 5UL),
    B6  = (1UL << 6UL),
    B7  = (1UL << 7UL),
    B8  = (1UL << 8UL),
    B9  = (1UL << 9UL),
    B10 = (1UL << 10UL),
    B11 = (1UL << 11UL),
    B12 = (1UL << 12UL),
    B13 = (1UL << 13UL),
    B14 = (1UL << 14UL),
    B15 = (1UL << 15UL),
    B16 = (1UL << 16UL),
    B17 = (1UL << 17UL),
    B18 = (1UL << 18UL),
    B19 = (1UL << 19UL),
    B20 = (1UL << 20UL),
    B21 = (1UL << 21UL),
    B22 = (1UL << 22UL),
    B23 = (1UL << 23UL),
    B24 = (1UL << 24UL),
    B25 = (1UL << 25UL),
    B26 = (1UL << 26UL),
    B27 = (1UL << 27UL),
    B28 = (1UL << 28UL),
    B29 = (1UL << 29UL),
    B30 = (1UL << 30UL),
    B31 = (1UL << 31UL)
};
ENABLE_ENUM_BITS(BITS32);


namespace MT {
namespace Universal {
    using namespace MT::Details;

    template<volatile auto *reg>
    struct Register {

        template<typename... Vals>
        constexpr void set(const Vals &... vals) noexcept {
            *reg |= (vals | ...);
        }

        template<typename... Vals>
        constexpr void clear(const Vals &... vals) noexcept {
            *reg &= ~(vals | ...);
        }

        template<typename... Vals>
        constexpr void toggle(const Vals &... vals) noexcept {
            *reg ^= (vals | ...);
        }

        template<typename... Vals>
        constexpr void override(const Vals &... vals) noexcept {
            *reg = (vals | ...);
        }

        template<typename... Vals>
        constexpr bool compare(const Vals &... vals) noexcept {
            return (*reg & (vals | ...));
        }

        constexpr auto get() noexcept {
            return *reg;
        }

        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void set(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            *reg |= static_cast<underlying>(sum);
        }

        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void clear(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            *reg &= ~(static_cast<underlying>(sum));
        }

        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void toggle(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            *reg ^= (static_cast<underlying>(sum));
        }

        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void override(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            *reg                                                 = static_cast<underlying>(sum);
        }

        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr bool compare(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            return (*reg & static_cast<underlying>(sum));
        }
    };
}// namespace Universal
}// namespace MT


#endif /* MICROTRAIT_UNIVERSAL_REGISTER_HPP_ */

/*
 * EnumBits.hpp
 *
 *  Created on: 01.10.2020
 *      Author: steff
 */

#ifndef MICROTRAIT_MISC_ENUMBITS_HPP_
#define MICROTRAIT_MISC_ENUMBITS_HPP_

#include <type_traits>


#define ENABLE_ENUM_BITS(x)                  \
    template<>                               \
    struct enable_Enum_bits<x> {             \
        static constexpr bool enable = true; \
    };

template<typename E>
struct enable_Enum_bits {
    static constexpr bool enable = false;
};

template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E>::type constexpr operator|(const E lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E>::type constexpr operator&(const E lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E>::type constexpr operator^(const E lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E>::type constexpr operator~(const E lhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(
        ~static_cast<underlying>(lhs));
}

template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E &>::type constexpr operator|=(E &lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E &>::type constexpr operator&=(E &lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E &>::type constexpr operator^=(E &lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}

#endif /* MICROTRAIT_MISC_ENUMBITS_HPP_ */

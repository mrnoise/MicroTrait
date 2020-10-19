/** @defgroup groupMisc Misc
*  miscellaneous stuff
*/

/** @defgroup groupEnumBits Enumeration as Bits
 *  @ingroup groupMisc
* @brief free functions to treat a enumeration as bitpatterns
*
* @details
* Usage: \code {.cpp}

#include "MicroTrait/Misc/EnumBits.hpp"

   enum class MYBITS {
    B0 = (1U << 0U),
    B1 = (1U << 1U),
    B2 = (1U << 2U),
    B3 = (1U << 3U),
    B4 = (1U << 4U),
    B5 = (1U << 5U),
    B6 = (1U << 6U),
    B7 = (1U << 7U)
};
ENABLE_ENUM_BITS(MYBITS); // If define is not used functions provided here can`t be used -> safe guard for normal enums

\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupFuncsEnumBits Functions
*  @ingroup groupEnumBits
*  Functions in this module
*/

/** @defgroup groupEnumsEnumBits Enums
*  @ingroup groupEnumBits
*  Enums in this module
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

/**
* @ingroup groupFuncsEnumBits
****************************************************************
* @brief operator overload for logical or
* @details
* Usage: \code {.cpp}
*  MYBITS b = MYBITS::B0 | MYBITS::B1; \endcode
*@tparam E the enumeration provided
****************************************************************
*/
template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E>::type constexpr operator|(const E lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

/**
* @ingroup groupFuncsEnumBits
****************************************************************
* @brief operator overload for logical and
* @details
* Usage: \code {.cpp}
*  MYBITS b = MYBITS::B0 & MYBITS::B1; \endcode
*@tparam E the enumeration provided
****************************************************************
*/
template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E>::type constexpr operator&(const E lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

/**
* @ingroup groupFuncsEnumBits
****************************************************************
* @brief operator overload for logical xor
* @details
* Usage: \code {.cpp}
*  MYBITS b = MYBITS::B0 ^ MYBITS::B1; \endcode
*@tparam E the enumeration provided
****************************************************************
*/
template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E>::type constexpr operator^(const E lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(
        static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

/**
* @ingroup groupFuncsEnumBits
****************************************************************
* @brief operator overload for logical invertion
* @details
* Usage: \code {.cpp}
*  MYBITS b = ~MYBITS::B0; \endcode
*@tparam E the enumeration provided
****************************************************************
*/
template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E>::type constexpr operator~(const E lhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(
        ~static_cast<underlying>(lhs));
}

/**
* @ingroup groupFuncsEnumBits
****************************************************************
* @brief operator overload for logical or assignment
* @details
* Usage: \code {.cpp}
*  MYBITS b |= MYBITS::B0; \endcode
*@tparam E the enumeration provided
****************************************************************
*/
template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E &>::type constexpr operator|=(E &lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

/**
* @ingroup groupFuncsEnumBits
****************************************************************
* @brief operator overload for logical and assignment
* @details
* Usage: \code {.cpp}
*  MYBITS b &= MYBITS::B0; \endcode
*@tparam E the enumeration provided
****************************************************************
*/
template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E &>::type constexpr operator&=(E &lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

/**
* @ingroup groupFuncsEnumBits
****************************************************************
* @brief operator overload for logical xor assignment
* @details
* Usage: \code {.cpp}
*  MYBITS b ^= MYBITS::B0; \endcode
*@tparam E the enumeration provided
****************************************************************
*/
template<typename E>
typename std::enable_if<enable_Enum_bits<E>::enable, E &>::type constexpr operator^=(E &lhs, const E rhs) noexcept {
    typedef typename std::underlying_type<E>::type underlying;
    lhs = static_cast<E>(
        static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}

#endif /* MICROTRAIT_MISC_ENUMBITS_HPP_ */

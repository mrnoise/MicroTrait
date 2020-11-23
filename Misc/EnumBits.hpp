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

namespace MT {
namespace Misc {

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
		template<>
		struct enable_Enum_bits<MYBITS> {
			static constexpr bool enable = true;
		}; // If specialization is not used functions provided here can`t be used -> safe guard for normal enums

		template<>
		struct enable_Enum_bits<volatile MYBITS> { -> specialization if a volatile value is used
			static constexpr bool enable = true;
		}; // If specialization is not used functions provided here can`t be used -> safe guard for normal enums

	}
}
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

#include <MicroTrait/Misc/Cast.hpp>
#include <type_traits>

namespace MT::Misc {

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
typename std::enable_if_t<enable_Enum_bits<E>::enable, E> constexpr operator|(const E lhs, const E rhs) noexcept {
    return static_cast<E>(MT::Cast::toUnderlyingType(lhs) | MT::Cast::toUnderlyingType(rhs));
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
typename std::enable_if_t<enable_Enum_bits<E>::enable, E> constexpr operator&(const E lhs, const E rhs) noexcept {
    return static_cast<E>(MT::Cast::toUnderlyingType(lhs) & MT::Cast::toUnderlyingType(rhs));
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
typename std::enable_if_t<enable_Enum_bits<E>::enable, E> constexpr operator^(const E lhs, const E rhs) noexcept {
    return static_cast<E>(MT::Cast::toUnderlyingType(lhs) ^ MT::Cast::toUnderlyingType(rhs));
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
typename std::enable_if_t<enable_Enum_bits<E>::enable, E> constexpr operator~(const E lhs) noexcept {
    return static_cast<E>(~MT::Cast::toUnderlyingType(lhs));
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
    lhs = static_cast<E>(MT::Cast::toUnderlyingType(lhs) | MT::Cast::toUnderlyingType(rhs));
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
    lhs = static_cast<E>(MT::Cast::toUnderlyingType(lhs) & MT::Cast::toUnderlyingType(rhs));
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
    lhs = static_cast<E>(MT::Cast::toUnderlyingType(lhs) ^ MT::Cast::toUnderlyingType(rhs));
    return lhs;
}


}// namespace MT::Misc

#endif /* MICROTRAIT_MISC_ENUMBITS_HPP_ */

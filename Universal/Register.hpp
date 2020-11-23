/** @defgroup groupUniversal Universal
*  non microcontroller specific code
*/

/** @defgroup groupUniversalReg Register
 *  @ingroup groupUniversal
* @brief functions to get hardware register access without overhead
*
* @details
* Usage: \code {.cpp}

#include "MicroTrait/MT.hpp"

    static volatile uint16_t      fakeReg = 0; // Please use your real hw register provided in the header of your vendor
	MT::Universal::Register<&fakeReg> reg{};
	reg.set(0xFFFF);
	reg.clear(0xFFFF);
	reg.override(0xFFFF);

	reg.set(BITS16::B0 | BITS16::B1);
	reg.clear(BITS16::B0 | BITS16::B1);
	reg.override(BITS16::B0 | BITS16::B1);

\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupFuncsReg Functions
*  @ingroup groupUniversalReg
*  Functions in this module
*/

/** @defgroup groupEnumsReg Enums
*  @ingroup groupUniversalReg
*  Enums in this module
*/

#ifndef MICROTRAIT_UNIVERSAL_REGISTER_HPP_
#define MICROTRAIT_UNIVERSAL_REGISTER_HPP_

#include <MicroTrait/Misc/Cast.hpp>
#include "MicroTrait/Misc/EnumBits.hpp"
#include <stdint.h>
#include <type_traits>
#include <utility>

namespace MT::Misc {

/**
* @ingroup groupEnumsReg
****************************************************************
* @brief Bitwise register access with a width of 8bits
****************************************************************
*/
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
template<>
struct enable_Enum_bits<BITS8> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile BITS8> {
    static constexpr bool enable = true;
};

/**
* @ingroup groupEnumsReg
****************************************************************
* @brief Bitwise register access with a width of 16bits
****************************************************************
*/
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
template<>
struct enable_Enum_bits<BITS16> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile BITS16> {
    static constexpr bool enable = true;
};

/**
* @ingroup groupEnumsReg
****************************************************************
* @brief Bitwise register access with a width of 32bits
****************************************************************
*/
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
template<>
struct enable_Enum_bits<BITS32> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile BITS32> {
    static constexpr bool enable = true;
};
}// namespace MT::Misc

namespace MT::Universal {

template<volatile auto *REG>
struct Register {

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief sets the given bits via a logial or into the register
	* <br> equivalent to C register access -> reg |= value1 | value2 | ...
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  reg1.set(0xFF)
	*  reg1.set((1UL << 0UL)) \endcode
	*@tparam VALS bits or bitmask that should be ored into the defined register -> template specialization for integral types
	****************************************************************
	*/
    template<typename... VALS>
    constexpr void set(const VALS &... vals) noexcept {
        static_assert(std::is_integral_v<VALS...>, "Integral (e.g. uint8_t, uint16_t,..) value required.");
        *REG |= (vals | ...);
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief clears the given bits via a logial or into the register
	* <br> equivalent to C register access -> reg &= ~value1 | ~value2 | ~...
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  reg1.clear(0xFF)
	*  reg1.clear((1UL << 0UL)) \endcode
	*@tparam VALS bits or bitmask that should be inverted and put into the defined register via logical and -> template specialization for integral types
	****************************************************************
	*/
    template<typename... VALS>
    constexpr void clear(const VALS &... vals) noexcept {
        static_assert(std::is_integral_v<VALS...>, "Integral (e.g. uint8_t, uint16_t,..) value required.");
        *REG &= ~(vals | ...);
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief toggles the given bits via a logial xor in the register
	* <br> equivalent to C register access -> reg ^= value1 | value2 | ...
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  reg1.toggle(0xFF)
	*  reg1.toggle((1UL << 0UL)) \endcode
	*@tparam VALS bits or bitmask that should be toggeled and put into the defined register -> template specialization for integral types
	****************************************************************
	*/
    template<typename... VALS>
    constexpr void toggle(const VALS &... vals) noexcept {
        static_assert(std::is_integral_v<VALS...>, "Integral (e.g. uint8_t, uint16_t,..) value required.");
        *REG ^= (vals | ...);
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief sets the given bits in the register and overrides the leftover bits with zeros
	* <br> equivalent to C register access -> reg = value1 | value2 | ~...
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  reg1.override(0xFF)
	*  reg1.override((1UL << 0UL)) \endcode
	*@tparam VALS bits or bitmask that should be set into the defined register -> template specialization for integral types
	****************************************************************
	*/
    template<typename... VALS>
    constexpr void override(const VALS &... vals) noexcept {
        static_assert(std::is_integral_v<VALS...>, "Integral (e.g. uint8_t, uint16_t,..) value required.");
        *REG = (vals | ...);
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief compares the given bits with the bits in the register and returns true if there is a match
	* <br> equivalent to C register access -> return (*reg & (value1 | ...));
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  if (reg1.compare(0xFF) == true) doSomething();
	*  if (reg1.compare((1UL << 0UL)) == false) doSomeOtherThing(); \endcode
	*@tparam VALS bits or bitmask that should be set into the defined register -> template specialization for integral types
	*@return true if the bitpatterns match false if not
	****************************************************************
	*/
    template<typename... VALS>
    [[nodiscard]] constexpr bool compare(const VALS &... vals) noexcept {
        static_assert(std::is_integral_v<VALS...>, "Integral (e.g. uint8_t, uint16_t,..) value required.");
        return (*REG & (vals | ...));
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief returns the content of the underlyoing register
	* <br> equivalent to C register access -> return *REG;
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  if (reg1.get() == 0xFF00) doSomething();
	*  if (reg1.get() == 0x00FF) doSomeOtherThing(); \endcode
	*@return the content
	****************************************************************
	*/
    [[nodiscard]] constexpr auto get() noexcept {
        return *REG;
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief sets the given bits via a logial or into the register
	* <br> equivalent to C register access -> reg |= value1 | value2 | ...
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  reg1.set(BITS8::B0 | BITS8::B1); \endcode
	*@tparam BIT bit or bitmask that should be ored into the defined register -> template specialization for Enum types (Misc::BITS8,Misc::BITS16,Misc::BITS32)
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void set(const BIT &bit) noexcept {
        *REG |= (MT::Cast::toUnderlyingType(bit));
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief clears the given bits via a logial or into the register
	* <br> equivalent to C register access -> reg &= ~value1 | ~value2 | ~...
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  reg1.clear(BITS8::B0 | BITS8::B1) \endcode
	*@tparam BIT bit or bitmask that should be inverted and put into the defined register via logical and -> template specialization for Enum types (Misc::BITS8,Misc::BITS16,Misc::BITS32)
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void clear(const BIT &bit) noexcept {
        *REG &= ~(MT::Cast::toUnderlyingType(bit));
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief toggles the given bits via a logial xor in the register
	* <br> equivalent to C register access -> reg ^= value1 | value2 | ...
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  reg1.toggle(BITS8::B0 | BITS8::B1)\endcode
	*@tparam BIT bit or bitmask that should be toggeled and put into the defined register -> template specialization for Enum types (Misc::BITS8,Misc::BITS16,Misc::BITS32)
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void toggle(const BIT &bit) noexcept {
        *REG ^= (MT::Cast::toUnderlyingType(bit));
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief sets the given bits in the register and overrides the leftover bits with zeros
	* <br> equivalent to C register access -> reg = value1 | value2 | ~...
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  reg1.override(BITS8::B0 | BITS8::B1)\endcode
	*@tparam BIT bit or bitmask that should be set into the defined register -> template specialization for Enum types(Misc::BITS8,Misc::BITS16,Misc::BITS32)
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void override(const BIT &bit) noexcept {
        *REG = (MT::Cast::toUnderlyingType(bit));
    }

    /**
	* @ingroup groupFuncsReg
	****************************************************************
	* @brief compares the given bits with the bits in the register and returns true if there is a match
	* <br> equivalent to C register access -> return (*REG & (value1 | ...));
	* @details
	* Usage: \code {.cpp}
	*  MT::Universal::Register<&HWRegister> reg1;
	*  if (reg1.compare(BITS8::B0 | BITS8::B1) == true) doSomething();
	*  if (reg1.compare(BITS8::B6 | BITS8::B7) == false) doSomeOtherThing(); \endcode
	*@tparam BITS bits or bitmask that should be set into the defined register --> template specialization for Enum types (Misc::BITS8,Misc::BITS16,Misc::BITS32)
	*@return true if the bitpatterns match false if not
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    [[nodiscard]] constexpr bool compare(const BIT &bit) noexcept {
        return (*REG & MT::Cast::toUnderlyingType(bit));
    }
};
}// namespace MT::Universal


#endif /* MICROTRAIT_UNIVERSAL_REGISTER_HPP_ */

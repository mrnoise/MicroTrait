/** @defgroup groupUniversalReg Universal Register Access
*  a universal compile time register access
*/

/** @defgroup groupFuncs Functions
*  @ingroup groupUniversalReg
*  Functions in this module
*/

/** @defgroup groupEnums Enums
*  @ingroup groupUniversalReg
*  Enums in this module
*/

#ifndef MICROTRAIT_UNIVERSAL_REGISTER_HPP_
#define MICROTRAIT_UNIVERSAL_REGISTER_HPP_


#include <MicroTrait/Misc/Details.hpp>
#include <MicroTrait/Misc/EnumBits.hpp>
#include <stdint.h>
#include <type_traits>
#include <utility>


/**
* @ingroup groupEnums
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
ENABLE_ENUM_BITS(BITS8);

/**
* @ingroup groupEnums
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
ENABLE_ENUM_BITS(BITS16);

/**
* @ingroup groupEnums
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
ENABLE_ENUM_BITS(BITS32);


namespace MT {
namespace Universal {
    using namespace MT::Details;

    template<volatile auto *reg>
    struct Register {

        /**
    	* @ingroup groupFuncs
    	****************************************************************
    	* @brief sets the given bits via a logial or into the register
    	* <br> equivalent to C register access -> reg |= value1 | value2 | ...
    	* @details
    	* Usage: \code {.cpp}
    	* <br> MT::Universal::Register<&HWRegister> reg1;
    	* <br> reg1.set(0xFF)
    	* <br> reg1.set((1UL << 0UL)) \endcode
    	*@tparam Vals bits or bitmask that should be ored into the defined register -> template specialization for integral types
    	****************************************************************
    	*/
        template<typename... Vals>
        constexpr void set(const Vals &... vals) noexcept {
            static_assert(std::is_integral<Vals...>::value, "Integral (e.g. uint8_t, uint16_t,..) value required.");
            *reg |= (vals | ...);
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief clears the given bits via a logial or into the register
		* <br> equivalent to C register access -> reg &= ~value1 | ~value2 | ~...
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> reg1.clear(0xFF)
		* <br> reg1.clear((1UL << 0UL)) \endcode
		*@tparam Vals bits or bitmask that should be inverted and put into the defined register via logical and -> template specialization for integral types
		****************************************************************
		*/
        template<typename... Vals>
        constexpr void clear(const Vals &... vals) noexcept {
            static_assert(std::is_integral<Vals...>::value, "Integral (e.g. uint8_t, uint16_t,..) value required.");
            *reg &= ~(vals | ...);
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief toggles the given bits via a logial xor in the register
		* <br> equivalent to C register access -> reg ^= value1 | value2 | ...
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> reg1.toggle(0xFF)
		* <br> reg1.toggle((1UL << 0UL)) \endcode
		*@tparam Vals bits or bitmask that should be toggeled and put into the defined register -> template specialization for integral types
		****************************************************************
		*/
        template<typename... Vals>
        constexpr void toggle(const Vals &... vals) noexcept {
            static_assert(std::is_integral<Vals...>::value, "Integral (e.g. uint8_t, uint16_t,..) value required.");
            *reg ^= (vals | ...);
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief sets the given bits in the register and overrides the leftover bits with zeros
		* <br> equivalent to C register access -> reg = value1 | value2 | ~...
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> reg1.override(0xFF)
		* <br> reg1.override((1UL << 0UL)) \endcode
		*@tparam Vals bits or bitmask that should be set into the defined register -> template specialization for integral types
		****************************************************************
		*/
        template<typename... Vals>
        constexpr void override(const Vals &... vals) noexcept {
            static_assert(std::is_integral<Vals...>::value, "Integral (e.g. uint8_t, uint16_t,..) value required.");
            *reg = (vals | ...);
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief compares the given bits with the bits in the register and returns true if there is a match
		* <br> equivalent to C register access -> return (*reg & (value1 | ...));
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> if (reg1.compare(0xFF) == true) doSomething();
		* <br> if (reg1.compare((1UL << 0UL)) == false) doSomeOtherThing(); \endcode
		*@tparam Vals bits or bitmask that should be set into the defined register -> template specialization for integral types
		*@return true if the bitpatterns match false if not
		****************************************************************
		*/
        template<typename... Vals>
        [[nodiscard]] constexpr bool compare(const Vals &... vals) noexcept {
            static_assert(std::is_integral<Vals...>::value, "Integral (e.g. uint8_t, uint16_t,..) value required.");
            return (*reg & (vals | ...));
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief returns the content of the underlyoing register
		* <br> equivalent to C register access -> return *reg;
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> if (reg1.get() == 0xFF00) doSomething();
		* <br> if (reg1.get() == 0x00FF) doSomeOtherThing(); \endcode
		*@return the content
		****************************************************************
		*/
        [[nodiscard]] constexpr auto get() noexcept {
            return *reg;
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief sets the given bits via a logial or into the register
		* <br> equivalent to C register access -> reg |= value1 | value2 | ...
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> reg1.set(BITS8::B0 | BITS8::B1); \endcode
		*@tparam Vals bits or bitmask that should be ored into the defined register -> template specialization for Enum types (#BITS8,#BITS16,BITS32)
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void set(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            *reg |= static_cast<underlying>(sum);
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief clears the given bits via a logial or into the register
		* <br> equivalent to C register access -> reg &= ~value1 | ~value2 | ~...
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> reg1.clear(BITS8::B0 | BITS8::B1) \endcode
		*@tparam Vals bits or bitmask that should be inverted and put into the defined register via logical and -> template specialization for Enum types (#BITS8,#BITS16,BITS32)
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void clear(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            *reg &= ~(static_cast<underlying>(sum));
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief toggles the given bits via a logial xor in the register
		* <br> equivalent to C register access -> reg ^= value1 | value2 | ...
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> reg1.toggle(BITS8::B0 | BITS8::B1)\endcode
		*@tparam Vals bits or bitmask that should be toggeled and put into the defined register -> template specialization for Enum types (#BITS8,#BITS16,BITS32)
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void toggle(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            *reg ^= (static_cast<underlying>(sum));
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief sets the given bits in the register and overrides the leftover bits with zeros
		* <br> equivalent to C register access -> reg = value1 | value2 | ~...
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> reg1.override(BITS8::B0 | BITS8::B1)\endcode
		*@tparam Vals bits or bitmask that should be set into the defined register -> template specialization for Enum types (#BITS8,#BITS16,BITS32)
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void override(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            *reg                                                 = static_cast<underlying>(sum);
        }

        /**
		* @ingroup groupFuncs
		****************************************************************
		* @brief compares the given bits with the bits in the register and returns true if there is a match
		* <br> equivalent to C register access -> return (*reg & (value1 | ...));
		* @details
		* Usage: \code {.cpp}
		* <br> MT::Universal::Register<&HWRegister> reg1;
		* <br> if (reg1.compare(BITS8::B0 | BITS8::B1) == true) doSomething();
		* <br> if (reg1.compare(BITS8::B6 | BITS8::B7) == false) doSomeOtherThing(); \endcode
		*@tparam Vals bits or bitmask that should be set into the defined register --> template specialization for Enum types (#BITS8,#BITS16,BITS32)
		*@return true if the bitpatterns match false if not
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        [[nodiscard]] constexpr bool compare(const BIT &bit, const BITS &... bits) noexcept {
            typedef typename std::underlying_type<BIT>::type underlying;
            const BIT                                        sum = orSum(bit, bits...);
            return (*reg & static_cast<underlying>(sum));
        }
    };
}// namespace Universal
}// namespace MT


#endif /* MICROTRAIT_UNIVERSAL_REGISTER_HPP_ */

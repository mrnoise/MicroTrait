/** @defgroup groupUniversal Universal
*  non microcontroller specific code
*/

/** @defgroup groupInterrupt Interrupt
 *  @ingroup groupUniversal
* @brief Functions to register callbacks for interrupt service routines at compile time
*
* @details
* Usage: \code {.cpp}

#include "MicroTrait/MT.hpp"

	enum class VECTORS {
			VECTOR1 = 0,
			VECTOR2
		  };


	using namespace MT::Universal;

	constexpr auto isr = Interrupt::makeInterrupt(

	Interrupt::makeHandler(
		VECTOR1,
		 []() {
		   //put your interrupt code here
		}),

	Interrupt::makeHandler(
	   VECTOR2,
		[]() {
		   //put your interrupt code here
	}));


	// put this into your interrupt vector 1
	std::get<isr.get_index(VECTORS::VECTOR1)>(isr.m_vectors)();

	// put this into your interrupt vector 2
	std::get<isr.get_index(VECTORS::VECTOR2)>(isr.m_vectors)();
\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/

/** @defgroup groupFuncsInt Functions
*  @ingroup groupInterrupt
*  Functions in this module
*/

/** @defgroup groupEnumsInt Enums
*  @ingroup groupInterrupt
*  Enums in this module
*/


#ifndef MICROTRAIT_UNIVERSAL_INTERRUPT_HPP_
#define MICROTRAIT_UNIVERSAL_INTERRUPT_HPP_

#include <stdint.h>
#include <array>
#include <tuple>
#include <limits>

namespace MT::Universal::Interrupt {

template<typename ENUM, typename FUNC>
using IntHandlers = std::pair<ENUM, FUNC>; /**< this pair represents the ISR -> first the Enum which refers to a vector and second the function to call */

template<typename ENUM, typename... VECTOR>
struct Interrupt {

    /**
	* @ingroup groupFuncsInt
	****************************************************************
	* @brief constructor of the interrupt
	* @details
	* Usage: use maker functions -> makeInterrupt (makeHandler());
	*@tparam handler std::pair with the enum and the corresponding callback function (std::pair<ENUM, FUNC>)
	****************************************************************
	*/
    constexpr explicit Interrupt(IntHandlers<ENUM, VECTOR>... handler) noexcept
      : m_indexes{ handler.first... }, m_vectors{ std::move(handler.second)... } {
    }

    /**
	* @ingroup groupFuncsInt
	****************************************************************
	* @brief returns the index to given enum
	* @details
	* Usage: \code {.cpp}
	*  std::get<isr.get_index(VECTORS::VECTOR1)>(isr.m_vectors)(); \endcode
	*@param p the enum for which the index should returned
	*@return the index to the given enum
	****************************************************************
	*/
    [[nodiscard]] constexpr std::size_t get_index(const ENUM p) const noexcept {

        for (std::size_t idx = 0; idx < m_indexes.size(); ++idx) {
            if (m_indexes[idx] == p) return idx;
        }

        return std::numeric_limits<std::size_t>::max();
    }


    std::array<ENUM, sizeof...(VECTOR)> m_indexes; /**< array of indexes -> Enums which refer to the callback */
    std::tuple<VECTOR...>               m_vectors; /**< tuple  which holds the actual callback function */
};

/**
* @ingroup groupFuncsInt
****************************************************************
* @brief maker function for a complete callback registration
* @details
* Usage: \code {.cpp}
*   constexpr auto isr = makeInterrupt(
*            makeHandler(
*                VECTORS::VECTOR1,
*                []() {
*                    toggle = false;
*                })); \endcode
*@param t -> all entries to register (std::pair<ENUM, FUNC>)
*@return the copile time objects containing all registered callbacks
****************************************************************
*/
template<typename ENUM, typename... FUNC>
[[nodiscard]] constexpr auto makeInterrupt(IntHandlers<ENUM, FUNC>... t) noexcept {
    return Interrupt<ENUM, FUNC...>{ std::move(t)... };
}

/**
* @ingroup groupFuncsInt
****************************************************************
* @brief maker function for one callback entry
* @details
* Usage: cascade with makeInterrupt like: \code {.cpp}
*   constexpr auto isr = makeInterrupt(
   *            makeHandler(
   *                VECTORS::VECTOR1,
   *                []() {
   *                    toggle = false;
   *                })); \endcode
*@param p the Enum
*@param t the callback
*@return one IntHandler (std::pair<ENUM, FUNC>)
****************************************************************
*/
template<typename ENUM, typename FUNC>
[[nodiscard]] constexpr auto makeHandler(ENUM p, FUNC t) noexcept {
    return IntHandlers<ENUM, FUNC>{ p, std::move(t) };
}
}// namespace MT::Universal::Interrupt


#endif /* MICROTRAIT_UNIVERSAL_INTERRUPT_HPP_ */

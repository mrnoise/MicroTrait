/** @defgroup groupCast Type casting
 *  @ingroup groupMisc
* @brief free functions to help to cast types
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/

/** @defgroup groupFuncsCast Functions
*  @ingroup groupCast
*  Functions in this module
*/

/** @defgroup groupTypesCast Types
*  @ingroup groupCast
*  Types in this module
*/

#ifndef MICROTRAIT_MISC_DETAILS_CPP_
#define MICROTRAIT_MISC_DETAILS_CPP_

#include <type_traits>

namespace MT::Misc::Cast {

/**
* @ingroup groupFuncsCast
****************************************************************
* @brief cast the given type to the underlying type
* @details
* Usage: \code {.cpp}
*
*  enum class Test : uint8_t {
*      T1 = 0,
*      T2 = 1,
*  };
*
*  static_assert(MT::Misc::Cast::toUnderlyingType(Test::T2) == 1); \endcode
*@tparam T type
*@return the underlying type
****************************************************************
*/
template<typename T>
[[nodiscard]] constexpr auto toUnderlyingType(const T arg) noexcept {
    typedef typename std::underlying_type<T>::type underlying;
    return static_cast<underlying>(arg);
}


}// namespace MT::Misc::Cast

#endif /* MICROTRAIT_MISC_DETAILS_CPP_ */

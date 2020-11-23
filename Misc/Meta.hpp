/** @defgroup groupMeta Metaprogramming
 *  @ingroup groupMisc
* @brief free functions to help to do meta programming
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/

/** @defgroup groupFuncsMeta Functions
*  @ingroup groupMeta
*  Functions in this module
*/

/** @defgroup groupTypesMeta Types
*  @ingroup groupMeta
*  Types in this module
*/


#ifndef MICROTRAIT_MISC_META_HPP_
#define MICROTRAIT_MISC_META_HPP_

#include <type_traits>

namespace MT::Misc::Meta {

/**
* @ingroup groupTypesMeta
****************************************************************
* @brief makes a new type with striped off const or volatile qualifiers
*@tparam T type
****************************************************************
*/
template<class T>
using BareType = std::remove_cv_t<std::remove_reference_t<T>>;


/**
* @ingroup groupFuncsMeta
****************************************************************
* @brief compare (std::is_same) two types and automatically strip off any const or volatile qualifiers
* @details
* Usage: \code {.cpp}
*    static_assert(MT::Misc::Meta::compareBareType<const volatile int, int>(), "ints are not equal");// will compile! \endcode
*@tparam T1 first type
*@tparam T2 second type
****************************************************************
*/
template<typename T1, typename T2>
constexpr bool compareBareType() noexcept {
    return std::is_same<BareType<T1>, BareType<T2>>::value;
}


}// namespace MT::Misc::Meta
#endif /* MICROTRAIT_MISC_META_HPP_ */

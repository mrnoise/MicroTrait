
#ifndef MICROTRAIT_MISC_DETAILS_CPP_
#define MICROTRAIT_MISC_DETAILS_CPP_

#include <type_traits>

namespace MT::Cast {

template<typename T>
[[nodiscard]] constexpr auto toUnderlyingType(const T arg) noexcept {
    typedef typename std::underlying_type<T>::type underlying;
    return static_cast<underlying>(arg);
}


}// namespace MT::Cast

#endif /* MICROTRAIT_MISC_DETAILS_CPP_ */

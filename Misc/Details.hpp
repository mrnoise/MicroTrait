
#ifndef MICROTRAIT_MISC_DETAILS_CPP_
#define MICROTRAIT_MISC_DETAILS_CPP_

#include <type_traits>

namespace MT::Details {

template<typename T>
[[nodiscard]] constexpr T orSum(const T &arg) noexcept {
    return arg;
}

template<typename T, typename... ARGS>
[[nodiscard]] constexpr T orSum(const T &arg, const ARGS &... args) noexcept {
    return arg | orSum(args...);
}

template<typename T>
[[nodiscard]] constexpr auto castToUnderlyingType(const T arg) noexcept {
    typedef typename std::underlying_type<T>::type underlying;
    return static_cast<underlying>(arg);
}


}// namespace MT::Details

#endif /* MICROTRAIT_MISC_DETAILS_CPP_ */

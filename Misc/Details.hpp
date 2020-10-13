
#ifndef MICROTRAIT_MISC_DETAILS_CPP_
#define MICROTRAIT_MISC_DETAILS_CPP_

namespace MT {

namespace Details {

    template<typename T>
    [[nodiscard]] constexpr T orSum(const T &arg) noexcept {
        return arg;
    }

    template<typename T, typename... ARGS>
    [[nodiscard]] constexpr T orSum(const T &arg, const ARGS &... args) noexcept {
        return arg | orSum(args...);
    }

}// namespace Details
}// namespace MT

#endif /* MICROTRAIT_MISC_DETAILS_CPP_ */

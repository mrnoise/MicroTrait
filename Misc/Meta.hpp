#ifndef MICROTRAIT_MISC_META_HPP_
#define MICROTRAIT_MISC_META_HPP_

#include <type_traits>


namespace MT::Meta {

template<class T>
using BareType = std::remove_cv_t<std::remove_reference_t<T>>;

template<typename T1, typename T2>
constexpr bool compareBareType() noexcept {
    return std::is_same<BareType<T1>, BareType<T2>>::value;
}


}// namespace MT::Meta
#endif /* MICROTRAIT_MISC_META_HPP_ */

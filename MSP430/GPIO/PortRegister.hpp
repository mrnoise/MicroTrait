
#ifndef MICROTRAIT_MSP430_GPIO_PORTREGISTER_HPP_
#define MICROTRAIT_MSP430_GPIO_PORTREGISTER_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Misc/Details.hpp"
#include "MicroTrait/Misc/EnumBits.hpp"
#include "MicroTrait/Universal/Register.hpp"
#include <stdint.h>
#include <type_traits>
#include <cstddef>
#include <msp430.h>

#define GPIO_REGISTER_WIDTH uint8_t

enum class GPIO_PIN : GPIO_REGISTER_WIDTH {
    P0 = (1U << 0U),
    P1 = (1U << 1U),
    P2 = (1U << 2U),
    P3 = (1U << 3U),
    P4 = (1U << 4U),
    P5 = (1U << 5U),
    P6 = (1U << 6U),
    P7 = (1U << 7U)
};
ENABLE_ENUM_BITS(GPIO_PIN);


enum class INT_FLAG : uint8_t {
    FALSE = 0,
    TRUE
};

namespace MT {
namespace MSP430 {
    namespace GPIO {

        enum class INT_EDGE : uint8_t {
            LOW_TO_HIGH = 0,
            HIGH_TO_LOW
        };

        enum class MODULE_FUNC : uint8_t {
            GPIO = 0,
            PRIMARY,
            SECONDARY,
            TERNARY,
        };

        enum class PIN_STATE : uint8_t {
            LOW = 0,
            HIGH
        };


        namespace Internal {

            template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *P1SEL, volatile auto *IESREG, volatile auto *IEREG, volatile auto *IFGREG>
            struct PortWithInt {

              private:
                MT::Universal::Register<INREG>   m_in{};
                MT::Universal::Register<OUTREG>  m_out{};
                MT::Universal::Register<DIRREG>  m_dir{};
                MT::Universal::Register<PRENREG> m_pull{};
                MT::Universal::Register<IESREG>  m_intEdge{};
                MT::Universal::Register<IEREG>   m_intEn{};
                MT::Universal::Register<IFGREG>  m_intFlg{};
                MT::Universal::Register<P0SEL>   m_p0sel{};
                MT::Universal::Register<P1SEL>   m_p1sel{};

              public:
                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsOutputPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsPeripheralModuleFunctionOutputPin(const MODULE_FUNC func, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_dir.set(bit, bits...);
                    switch (func) {
                        case MODULE_FUNC::GPIO:
                            m_p0sel.clear(bit, bits...);
                            m_p1sel.clear(bit, bits...);
                            break;
                        case MODULE_FUNC::PRIMARY:
                            m_p0sel.set(bit, bits...);
                            m_p1sel.clear(bit, bits...);
                            break;
                        case MODULE_FUNC::SECONDARY:
                            m_p0sel.clear(bit, bits...);
                            m_p1sel.set(bit, bits...);
                            break;
                        case MODULE_FUNC::TERNARY:
                            m_p0sel.set(bit, bits...);
                            m_p1sel.set(bit, bits...);
                            break;
                        default:
                            break;
                    }
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsPeripheralModuleFunctionInputPin(const MODULE_FUNC func, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_dir.clear(bit, bits...);
                    switch (func) {
                        case MODULE_FUNC::GPIO:
                            m_p0sel.clear(bit, bits...);
                            m_p1sel.clear(bit, bits...);
                            break;
                        case MODULE_FUNC::PRIMARY:
                            m_p0sel.set(bit, bits...);
                            m_p1sel.clear(bit, bits...);
                            break;
                        case MODULE_FUNC::SECONDARY:
                            m_p0sel.clear(bit, bits...);
                            m_p1sel.set(bit, bits...);
                            break;
                        case MODULE_FUNC::TERNARY:
                            m_p0sel.set(bit, bits...);
                            m_p1sel.set(bit, bits...);
                            break;
                        default:
                            break;
                    }
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setOutputHighOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_out.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setOutputLowOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_out.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void toggleOutputOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_out.toggle(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPinWithPullDown(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.set(bit, bits...);
                    m_out.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPinWithPullUp(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.set(bit, bits...);
                    m_out.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                [[nodiscard]] constexpr PIN_STATE getInputPinValue(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    if (m_in.compare(bit, bits...)) return PIN_STATE::HIGH;
                    else
                        return PIN_STATE::LOW;
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void enableInterrupt(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_intEn.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void disableInterrupt(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_intEn.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                [[nodiscard]] constexpr INT_FLAG getInterruptStatus(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    if (m_intFlg.compare(bit, bits...)) return INT_FLAG::TRUE;
                    else
                        return INT_FLAG::FALSE;
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void clearInterrupt(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_intFlg.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void selectInterruptEdge(const INT_EDGE edge, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    if (edge == INT_EDGE::LOW_TO_HIGH) m_intEdge.clear(bit, bits...);
                    else
                        m_intEdge.set(bit, bits...);
                }
            };

            template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *P1SEL>
            struct Port {

              private:
                MT::Universal::Register<INREG>   m_in{};
                MT::Universal::Register<OUTREG>  m_out{};
                MT::Universal::Register<DIRREG>  m_dir{};
                MT::Universal::Register<PRENREG> m_pull{};
                MT::Universal::Register<P0SEL>   m_p0sel{};
                MT::Universal::Register<P1SEL>   m_p1sel{};

              public:
                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsOutputPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsPeripheralModuleFunctionOutputPin(const MODULE_FUNC func, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_dir.set(bit, bits...);
                    switch (func) {
                        case MODULE_FUNC::GPIO:
                            m_p0sel.clear(bit, bits...);
                            m_p1sel.clear(bit, bits...);
                            break;
                        case MODULE_FUNC::PRIMARY:
                            m_p0sel.set(bit, bits...);
                            m_p1sel.clear(bit, bits...);
                            break;
                        case MODULE_FUNC::SECONDARY:
                            m_p0sel.clear(bit, bits...);
                            m_p1sel.set(bit, bits...);
                            break;
                        case MODULE_FUNC::TERNARY:
                            m_p0sel.set(bit, bits...);
                            m_p1sel.set(bit, bits...);
                            break;
                        default:
                            break;
                    }
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsPeripheralModuleFunctionInputPin(const MODULE_FUNC func, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_dir.clear(bit, bits...);
                    switch (func) {
                        case MODULE_FUNC::GPIO:
                            m_p0sel.clear(bit, bits...);
                            m_p1sel.clear(bit, bits...);
                            break;
                        case MODULE_FUNC::PRIMARY:
                            m_p0sel.set(bit, bits...);
                            m_p1sel.clear(bit, bits...);
                            break;
                        case MODULE_FUNC::SECONDARY:
                            m_p0sel.clear(bit, bits...);
                            m_p1sel.set(bit, bits...);
                            break;
                        case MODULE_FUNC::TERNARY:
                            m_p0sel.set(bit, bits...);
                            m_p1sel.set(bit, bits...);
                            break;
                        default:
                            break;
                    }
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setOutputHighOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_out.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setOutputLowOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_out.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void toggleOutputOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    m_out.toggle(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPinWithPullDown(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.set(bit, bits...);
                    m_out.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPinWithPullUp(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.set(bit, bits...);
                    m_out.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                [[nodiscard]] constexpr PIN_STATE getInputPinValue(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<GPIO_PIN, BIT>::value, "input must be GPIO_PIN enum");
                    if (m_in.compare(bit, bits...)) return PIN_STATE::HIGH;
                    else
                        return PIN_STATE::LOW;
                }
            };
        }// namespace Internal

#ifdef __MSP430_HAS_PORT1_R__
        using Port1 = Internal::PortWithInt<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0, &P1SEL1, &P1IES, &P1IE, &P1IFG>;
#endif
#ifdef __MSP430_HAS_PORT2_R__
        using Port2 = Internal::PortWithInt<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0, &P2SEL1, &P2IES, &P2IE, &P2IFG>;
#endif
#ifdef __MSP430_HAS_PORT3_R__
        using Port3 = Internal::Port<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0, &P3SEL1>;
#endif
#ifdef __MSP430_HAS_PORT4_R__
        using Port4 = Internal::Port<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0, &P4SEL1>;
#endif
#ifdef __MSP430_HAS_PORT5_R__
        using Port5 = Internal::Port<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0, &P5SEL1>;
#endif
#ifdef __MSP430_HAS_PORT6_R__
        using Port6 = Internal::Port<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0, &P6SEL1>;
#endif
#ifdef __MSP430_HAS_PORT7_R__
        using Port7 = Internal::Port<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0, &P7SEL1>;
#endif
#ifdef __MSP430_HAS_PORT8_R__
        using Port8 = Internal::Port<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0, &P8SEL1>;
#endif
#ifdef __MSP430_HAS_PORT9_R__
        using Port9 = Internal::Port<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0, &P9SEL1>;
#endif
#ifdef __MSP430_HAS_PORT10_R__
        using Port10 = Internal::Port<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0, &P10SEL1>;
#endif
#ifdef __MSP430_HAS_PORTJ_R__
        using PortJ = Internal::Port<&PJIN, &PJOUT, &PJDIR, &PJREN, &PJSEL0, &PJSEL1>;
#endif
    }// namespace GPIO
}// namespace MSP430
}// namespace MT

#endif

#endif /* MICROTRAIT_MSP430_GPIO_PORTREGISTER_HPP_ */

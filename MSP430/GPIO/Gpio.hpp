/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430Gpio GPIO
 *  @ingroup groupMSP430
* @brief functions for GPIO hardware access for TIs MSP430 -> Ti Driverlib equivalent naming
*
* @details
* Usage: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

    GPIO::Port1 p1{};
    GPIO::Port2 p2{};
    p1.setOutputLowOnPin(GPIO::PIN::P0);
    p1.setAsOutputPin(GPIO::PIN::P0);

    p2.setAsInputPinWithPullUp(GPIO::PIN::P3);
    p2.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P3);
    p2.enableInterrupt(GPIO::PIN::P3);
    p2.clearInterrupt(GPIO::PIN::P3);

    p1.setAsInputPinWithPullUp(GPIO::PIN::P4);
    p1.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P4);
    p1.enableInterrupt(GPIO::PIN::P4);
    p1.clearInterrupt(GPIO::PIN::P4);

\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupFuncsMSP430Gpio Functions
*  @ingroup groupMSP430Gpio
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430Gpio Enums
*  @ingroup groupMSP430Gpio
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_GPIO_GPIO_HPP_
#define MICROTRAIT_MSP430_GPIO_GPIO_HPP_

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

namespace MT {
namespace Misc {

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
    template<>
    struct enable_Enum_bits<GPIO_PIN> {
        static constexpr bool enable = true;
    };

}// namespace Misc


namespace MSP430 {


    /**
	* @ingroup groupEnumsMSP430Gpio
	****************************************************************
	* @brief MSP430 Interrupt Flag match
	****************************************************************
	*/
    enum class INT_MASK_MATCH : uint8_t {
        FALSE = 0,
        TRUE
    };

    namespace GPIO {

        /**
		* @ingroup groupEnumsMSP430Gpio
		****************************************************************
		* @brief MSP430 GPIO PINs
		****************************************************************
		*/
        using PIN = MT::Misc::GPIO_PIN;

        /**
		* @ingroup groupEnumsMSP430Gpio
		****************************************************************
		* @brief Interrupt edge selection
		****************************************************************
		*/
        enum class INT_EDGE : uint8_t {
            LOW_TO_HIGH = 0,
            HIGH_TO_LOW
        };

        /**
		* @ingroup groupEnumsMSP430Gpio
		****************************************************************
		* @brief GPIO module selection
		****************************************************************
		*/
        enum class MODULE_FUNC : uint8_t {
            GPIO = 0,
            PRIMARY,
            SECONDARY,
            TERNARY,
        };

        /**
		* @ingroup groupEnumsMSP430Gpio
		****************************************************************
		* @brief GPIO pin state
		****************************************************************
		*/
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
                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief sets the given Pins as a output
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
    			*  p1.setAsOutputPin(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsOutputPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.set(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief sets the given Pins as a input
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.setAsInputPin(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.clear(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief sets for the given Pins the module function as a output -> check device datasheet
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.setAsPeripheralModuleFunctionOutputPin(GPIO::MODULE_FUNC::PRIMARY, GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@param func the function for the pin  (GPIO::MODULE_FUNC)
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsPeripheralModuleFunctionOutputPin(const MODULE_FUNC func, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
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

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief sets for the given Pins the module function as a input -> check device datasheet
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.setAsPeripheralModuleFunctionInputPin(GPIO::MODULE_FUNC::PRIMARY, GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@param func the function for the pin  (GPIO::MODULE_FUNC)
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsPeripheralModuleFunctionInputPin(const MODULE_FUNC func, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
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

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief sets the given Pins high if configured as a output
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.setOutputHighOnPin(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setOutputHighOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_out.set(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief sets the given Pins low if configured as a output
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.setOutputLowOnPin(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setOutputLowOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_out.clear(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief toggles the given Pins if configured as a output
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.toggleOutputOnPin(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void toggleOutputOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_out.toggle(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief set the given Pins as a input with Pulldown enabled
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.setAsInputPinWithPullDown(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPinWithPullDown(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.set(bit, bits...);
                    m_out.clear(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief set the given Pins as a input with Pullup enabled
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.setAsInputPinWithPullUp(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPinWithPullUp(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.set(bit, bits...);
                    m_out.set(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief returns the Pin state (high or low) if configured as a input
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  if(p1.getInputPinValue(GPIO::PIN::P0) == GPIO::PIN_STATE::HIGH) doSomething(); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				*@return the Pin state (GPIO::PIN_STATE)
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                [[nodiscard]] constexpr PIN_STATE getInputPinValue(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    if (m_in.compare(bit, bits...)) return PIN_STATE::HIGH;
                    else
                        return PIN_STATE::LOW;
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief enables for the given pins the Interrupt -> Port must be interrupt capable (normally Port1/2)
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.enableInterrupt(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void enableInterrupt(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_intEn.set(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief disables for the given pins the Interrupt -> Port must be interrupt capable (normally Port1/2)
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.disableInterrupt(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void disableInterrupt(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_intEn.clear(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief compares the given pins with the interrupt flags set in the hw register -> Port must be interrupt capable (normally Port1/2)
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  if(p1.getInterruptStatus(GPIO::PIN::P0) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				*@return if all the given bits are set or not (INT_MASK_MATCH)
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                [[nodiscard]] constexpr INT_MASK_MATCH getInterruptStatus(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    if (m_intFlg.compare(bit, bits...)) return INT_MASK_MATCH::TRUE;
                    else
                        return INT_MASK_MATCH::FALSE;
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief clears the interrupt flags for the given Pins  -> Port must be interrupt capable (normally Port1/2)
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.clearInterrupt(GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void clearInterrupt(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_intFlg.clear(bit, bits...);
                }

                /**
				* @ingroup groupFuncsMSP430Gpio
				****************************************************************
				* @brief selects the interrupt edge (high or low going edge) for the given Pins -> Port must be interrupt capable (normally Port1/2)
				* @details
				* Usage: \code {.cpp}
				* using namespace MT::MSP430;
				*
				*  GPIO::Port1 p1{};
				*  p1.selectInterruptEdge(GPIO::INT_EDGE::HIGH_TO_LOW, GPIO::PIN::P0 | GPIO::PIN::P1);  \endcode
				*@tparam BITS use enumeration GPIO::PIN
				****************************************************************
				*/
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void selectInterruptEdge(const INT_EDGE edge, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
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
                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsOutputPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsPeripheralModuleFunctionOutputPin(const MODULE_FUNC func, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
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

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsPeripheralModuleFunctionInputPin(const MODULE_FUNC func, const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
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

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setOutputHighOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_out.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setOutputLowOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_out.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void toggleOutputOnPin(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
                    m_out.toggle(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPinWithPullDown(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.set(bit, bits...);
                    m_out.clear(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                constexpr void setAsInputPinWithPullUp(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                    m_p0sel.clear(bit, bits...);
                    m_p1sel.clear(bit, bits...);
#endif
                    m_dir.clear(bit, bits...);
                    m_pull.set(bit, bits...);
                    m_out.set(bit, bits...);
                }

                template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
                [[nodiscard]] constexpr PIN_STATE getInputPinValue(const BIT &bit, const BITS &... bits) noexcept {
                    static_assert(std::is_same<MT::MSP430::GPIO::PIN, BIT>::value, "input must be GPIO::PIN enum");
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

#endif /* MICROTRAIT_MSP430_GPIO_GPIO_HPP_ */

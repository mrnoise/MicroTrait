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
#include "MicroTrait/MSP430/Types.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Misc/Meta.hpp"
#include "MicroTrait/Misc/Cast.hpp"
#include "MicroTrait/Misc/EnumBits.hpp"
#include "MicroTrait/Universal/Register.hpp"
#include <stdint.h>
#include <type_traits>
#include <array>
#include <msp430.h>


#define GPIO_REGISTER_WIDTH uint8_t

namespace MT::Misc {
enum class GPIO_PIN : GPIO_REGISTER_WIDTH {
    NONE = 0,
    P0   = (1U << 0U),
    P1   = (1U << 1U),
    P2   = (1U << 2U),
    P3   = (1U << 3U),
    P4   = (1U << 4U),
    P5   = (1U << 5U),
    P6   = (1U << 6U),
    P7   = (1U << 7U),
    ALL  = (0xFF)
};

template<>
struct enable_Enum_bits<GPIO_PIN> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile GPIO_PIN> {
    static constexpr bool enable = true;
};

}// namespace MT::Misc

namespace MT::MSP430::GPIO {

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
enum class MODULE_FUNC : uint_fast8_t {
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
enum class PIN_STATE : uint_fast8_t {
    LOW = 0,
    HIGH
};

#if defined(__MSP430F5XX_6XX_FAMILY__)
/**
* @ingroup groupEnumsMSP430Gpio
****************************************************************
* @brief GPIO drive strength -> only available for MSP430F5xx/6xx Family
****************************************************************
*/
enum class DRV_STRENGTH : uint_fast8_t {
    REDUCED = 0,
    FULL
};
#endif


namespace Internal {

    using namespace MT::Misc::Meta;

    template<volatile auto *INREG, volatile auto *OUTREG>
    struct PortCommon {

      private:
        MT::Universal::Register<INREG>  m_in{};
        MT::Universal::Register<OUTREG> m_out{};

      public:
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
		*@param pin to use -> GPIO::PIN
		****************************************************************
		*/
        constexpr void setOutputHighOnPin(const MT::MSP430::GPIO::PIN pin) noexcept {
            m_out.set(pin);
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
		*@param pin to use -> GPIO::PIN
		****************************************************************
		*/
        constexpr void setOutputLowOnPin(const MT::MSP430::GPIO::PIN pin) noexcept {
            m_out.clear(pin);
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
		*@param pin to use -> GPIO::PIN
		****************************************************************
		*/
        constexpr void toggleOutputOnPin(const MT::MSP430::GPIO::PIN pin) noexcept {
            m_out.toggle(pin);
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
		*@param pin to use -> GPIO::PIN
		*@return the Pin state (GPIO::PIN_STATE)
		****************************************************************
		*/
        [[nodiscard]] constexpr PIN_STATE getInputPinValue(const MT::MSP430::GPIO::PIN pin) noexcept {
            if (m_in.compare(pin)) return PIN_STATE::HIGH;
            else
                return PIN_STATE::LOW;
        }
    };


    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, typename SELTYPE, SELTYPE... SELX>
    struct PortSelx {

      private:
        MT::Universal::Register<INREG>   m_in{};
        MT::Universal::Register<OUTREG>  m_out{};
        MT::Universal::Register<DIRREG>  m_dir{};
        MT::Universal::Register<PRENREG> m_pull{};

        constexpr static SELTYPE m_selx[]{ SELX... };
        constexpr static size_t  m_size{ sizeof(m_selx) / sizeof(SELTYPE) };
        constexpr static bool    m_hasSel0and1 = (m_size == 2);
        constexpr static bool    m_hasSel0     = (m_size >= 1);
        constexpr static bool    m_hasNoSel    = (m_size == 0);
        constexpr static size_t  m_sel0Index   = 0;
        constexpr static size_t  m_sel1Index   = 1;

        constexpr inline void setModuleFunction(const MODULE_FUNC func, const MT::MSP430::GPIO::PIN pin) noexcept {

            switch (func) {
                case MODULE_FUNC::GPIO:

                    if constexpr (m_hasSel0) {
                        MT::Universal::Register<m_selx[m_sel0Index]> p0sel;
                        p0sel.clear(pin);
                    }

                    if constexpr (m_hasSel0and1) {
                        MT::Universal::Register<m_selx[m_sel1Index]> p1sel;
                        p1sel.clear(pin);
                    }

                    break;
                case MODULE_FUNC::PRIMARY:

                    if constexpr (m_hasSel0) {
                        MT::Universal::Register<m_selx[m_sel0Index]> p0sel;
                        p0sel.set(pin);
                    }

                    if constexpr (m_hasSel0and1) {
                        MT::Universal::Register<m_selx[m_sel1Index]> p1sel;
                        p1sel.clear(pin);
                    }
                    break;
                case MODULE_FUNC::SECONDARY:
                    if constexpr (m_hasSel0) {
                        MT::Universal::Register<m_selx[m_sel0Index]> p0sel;
                        p0sel.clear(pin);
                    }

                    if constexpr (m_hasSel0and1) {
                        MT::Universal::Register<m_selx[m_sel1Index]> p1sel;
                        p1sel.set(pin);
                    }
                    break;
                case MODULE_FUNC::TERNARY:
                    if constexpr (m_hasSel0) {
                        MT::Universal::Register<m_selx[m_sel0Index]> p0sel;
                        p0sel.set(pin);
                    }

                    if constexpr (m_hasSel0and1) {
                        MT::Universal::Register<m_selx[m_sel1Index]> p1sel;
                        p1sel.set(pin);
                    }
                    break;
                default:
                    break;
            }
        }


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
  		*@tparam STATE if the register is in the reset state or not -> MT::MSP430::REGISTER_STATE
  		*@param pin to use -> GPIO::PIN
  		****************************************************************
  		*/
        template<REGISTER_STATE STATE = REGISTER_STATE::RESET>
        constexpr void setAsOutputPin(const MT::MSP430::GPIO::PIN pin) noexcept {
            if constexpr (STATE != REGISTER_STATE::RESET) setModuleFunction(MODULE_FUNC::GPIO, pin);
            m_dir.set(pin);
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
  		*@tparam STATE if the register is in the reset state or not -> MT::MSP430::REGISTER_STATE
  		*@param pin to use -> GPIO::PIN
  		****************************************************************
  		*/
        template<REGISTER_STATE STATE = REGISTER_STATE::RESET>
        constexpr void setAsInputPin(const MT::MSP430::GPIO::PIN pin) noexcept {
            if constexpr (STATE != REGISTER_STATE::RESET) setModuleFunction(MODULE_FUNC::GPIO, pin);
            m_dir.clear(pin);
            m_pull.clear(pin);
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
  		*@param pin to use -> GPIO::PIN
  		****************************************************************
  		*/
        constexpr void setAsPeripheralModuleFunctionOutputPin(const MODULE_FUNC func, const MT::MSP430::GPIO::PIN pin) noexcept {
            m_dir.set(pin);
            setModuleFunction(func, pin);
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
  		*@param pin to use -> GPIO::PIN
  		****************************************************************
  		*/
        constexpr void setAsPeripheralModuleFunctionInputPin(const MODULE_FUNC func, const MT::MSP430::GPIO::PIN pin) noexcept {
            m_dir.clear(pin);
            setModuleFunction(func, pin);
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
  		*@tparam STATE if the register is in the reset state or not -> MT::MSP430::REGISTER_STATE
  		*@param pin to use -> GPIO::PIN
  		****************************************************************
  		*/
        template<REGISTER_STATE STATE = REGISTER_STATE::RESET>
        constexpr void setAsInputPinWithPullDown(const MT::MSP430::GPIO::PIN pin) noexcept {
            if constexpr (STATE != REGISTER_STATE::RESET) setModuleFunction(MODULE_FUNC::GPIO, pin);

            m_dir.clear(pin);
            m_pull.set(pin);
            m_out.clear(pin);
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
  		*@tparam STATE if the register is in the reset state or not -> MT::MSP430::REGISTER_STATE
  		*@param pin to use -> GPIO::PIN
  		****************************************************************
  		*/
        template<REGISTER_STATE STATE = REGISTER_STATE::RESET>
        constexpr void setAsInputPinWithPullUp(const MT::MSP430::GPIO::PIN pin) noexcept {
            if constexpr (STATE != REGISTER_STATE::RESET) setModuleFunction(MODULE_FUNC::GPIO, pin);

            m_dir.clear(pin);
            m_pull.set(pin);
            m_out.set(pin);
        }
    };

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *P0SEL, volatile auto *P1SEL>
    struct PortSel0and1WithoutPull {

      private:
        MT::Universal::Register<INREG>  m_in{};
        MT::Universal::Register<OUTREG> m_out{};
        MT::Universal::Register<DIRREG> m_dir{};
        MT::Universal::Register<P0SEL>  m_p0sel{};
        MT::Universal::Register<P1SEL>  m_p1sel{};

        constexpr inline void setModuleFunction(const MODULE_FUNC func, const MT::MSP430::GPIO::PIN pin) noexcept {
            switch (func) {
                case MODULE_FUNC::GPIO:
                    m_p0sel.clear(pin);
                    m_p1sel.clear(pin);
                    break;
                case MODULE_FUNC::PRIMARY:
                    m_p0sel.set(pin);
                    m_p1sel.clear(pin);
                    break;
                case MODULE_FUNC::SECONDARY:
                    m_p0sel.clear(pin);
                    m_p1sel.set(pin);
                    break;
                case MODULE_FUNC::TERNARY:
                    m_p0sel.set(pin);
                    m_p1sel.set(pin);
                    break;
                default:
                    break;
            }
        }

      public:
        template<REGISTER_STATE STATE = REGISTER_STATE::RESET>
        constexpr void setAsOutputPin(const MT::MSP430::GPIO::PIN pin) noexcept {
            if constexpr (STATE != REGISTER_STATE::RESET) setModuleFunction(MODULE_FUNC::GPIO, pin);
            m_dir.set(pin);
        }

        template<REGISTER_STATE STATE = REGISTER_STATE::RESET>
        constexpr void setAsInputPin(const MT::MSP430::GPIO::PIN pin) noexcept {
            if constexpr (STATE != REGISTER_STATE::RESET) setModuleFunction(MODULE_FUNC::GPIO, pin);
            m_dir.clear(pin);
        }


        constexpr void setAsPeripheralModuleFunctionOutputPin(const MODULE_FUNC func, const MT::MSP430::GPIO::PIN pin) noexcept {
            m_dir.set(pin);
            setModuleFunction(func, pin);
        }


        constexpr void setAsPeripheralModuleFunctionInputPin(const MODULE_FUNC func, const MT::MSP430::GPIO::PIN pin) noexcept {
            m_dir.clear(pin);
            setModuleFunction(func, pin);
        }
    };// namespace Internal


    template<volatile auto *IESREG, volatile auto *IEREG, volatile auto *IFGREG>
    struct PortInt {

      private:
        MT::Universal::Register<IESREG> m_intEdge{};
        MT::Universal::Register<IEREG>  m_intEn{};
        MT::Universal::Register<IFGREG> m_intFlg{};

      public:
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
		*@param pin to use -> GPIO::PIN
		****************************************************************
		*/
        constexpr void enableInterrupt(const MT::MSP430::GPIO::PIN pin) noexcept {
            m_intEn.set(pin);
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
		*@param pin to use -> GPIO::PIN
		****************************************************************
		*/
        constexpr void disableInterrupt(const MT::MSP430::GPIO::PIN pin) noexcept {
            m_intEn.clear(pin);
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
		*@param pin to use -> GPIO::PIN
		*@return if all the given bits are set or not (INT_MASK_MATCH)
		****************************************************************
		*/
        [[nodiscard]] constexpr INT_MASK_MATCH getInterruptStatus(const MT::MSP430::GPIO::PIN pin) noexcept {
            if (m_intFlg.compare(pin)) return INT_MASK_MATCH::TRUE;
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
		*@param pin to use -> GPIO::PIN
		****************************************************************
		*/
        constexpr void clearInterrupt(const MT::MSP430::GPIO::PIN pin) noexcept {
            m_intFlg.clear(pin);
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
		*
		*@param edge setting for the interrupt -> GPIO::PIN
		*@param pin to use -> GPIO::PIN
		****************************************************************
		*/
        constexpr void selectInterruptEdge(const INT_EDGE edge, const MT::MSP430::GPIO::PIN pin) noexcept {
            if (edge == INT_EDGE::LOW_TO_HIGH) m_intEdge.clear(pin);
            else
                m_intEdge.set(pin);
        }
    };// namespace Internal

    template<volatile auto *DRVREG>
    struct PortWithDrv {

      private:
        MT::Universal::Register<DRVREG> m_drv{};

      public:
#if defined(__MSP430F5XX_6XX_FAMILY__)
        /**
		* @ingroup groupFuncsMSP430Gpio
		****************************************************************
		* @brief sets the drive strength for the selected port pin  -> only available for MSP430F5xx/6xx Family
		* @details
		* Usage: \code {.cpp}
		* using namespace MT::MSP430;
		*
		*  GPIO::Port1 p1{};
		*  p1.setDriveStrength(GPIO::DRV_STRENGTH::REDUCED, GPIO::PIN::P0 | GPIO::PIN::P1); \endcode
		*
		*@param drv strength for the pin to set -> GPIO::DRV_STRENGTH
		*@param pin to use -> GPIO::PIN
		****************************************************************
		*/
        constexpr void setDriveStrength(const DRV_STRENGTH drv, const MT::MSP430::GPIO::PIN pin) noexcept {
            if (drv == DRV_STRENGTH::REDUCED) m_drv.clear(pin);
            else
                m_drv.set(pin);
        }
#endif
    };

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *P1SEL, volatile auto *IESREG, volatile auto *IEREG, volatile auto *IFGREG, volatile auto *DRVREG>
    struct PortWithIntDrv : PortCommon<INREG, OUTREG>
      , PortInt<IESREG, IEREG, IFGREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(P0SEL), P0SEL, P1SEL>
      , PortWithDrv<DRVREG> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *P1SEL, volatile auto *DRVREG>
    struct PortDrv : PortCommon<INREG, OUTREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(P0SEL), P0SEL, P1SEL>
      , PortWithDrv<DRVREG> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *IESREG, volatile auto *IEREG, volatile auto *IFGREG, volatile auto *DRVREG>
    struct PortWithIntSel0Drv : PortCommon<INREG, OUTREG>
      , PortInt<IESREG, IEREG, IFGREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(P0SEL), P0SEL>
      , PortWithDrv<DRVREG> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *DRVREG>
    struct PortSel0Drv : PortCommon<INREG, OUTREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(P0SEL), P0SEL>
      , PortWithDrv<DRVREG> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *DRVREG>
    struct PortSelOffDrv : PortCommon<INREG, OUTREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(INREG)>
      , PortWithDrv<DRVREG> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *P0SEL, volatile auto *P1SEL, volatile auto *IESREG, volatile auto *IEREG, volatile auto *IFGREG, volatile auto *DRVREG>
    struct PortWithIntNoPullDrv : PortCommon<INREG, OUTREG>
      , PortInt<IESREG, IEREG, IFGREG>
      , PortSel0and1WithoutPull<INREG, OUTREG, DIRREG, P0SEL, P1SEL>
      , PortWithDrv<DRVREG> {};


    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *P1SEL, volatile auto *IESREG, volatile auto *IEREG, volatile auto *IFGREG>
    struct PortWithInt : PortCommon<INREG, OUTREG>
      , PortInt<IESREG, IEREG, IFGREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(P0SEL), P0SEL, P1SEL> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *P1SEL>
    struct Port : PortCommon<INREG, OUTREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(P0SEL), P0SEL, P1SEL> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL, volatile auto *IESREG, volatile auto *IEREG, volatile auto *IFGREG>
    struct PortWithIntSel0 : PortCommon<INREG, OUTREG>
      , PortInt<IESREG, IEREG, IFGREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(P0SEL), P0SEL> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG, volatile auto *P0SEL>
    struct PortSel0 : PortCommon<INREG, OUTREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(P0SEL), P0SEL> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *PRENREG>
    struct PortSelOff : PortCommon<INREG, OUTREG>
      , PortSelx<INREG, OUTREG, DIRREG, PRENREG, decltype(INREG)> {};

    template<volatile auto *INREG, volatile auto *OUTREG, volatile auto *DIRREG, volatile auto *P0SEL, volatile auto *P1SEL, volatile auto *IESREG, volatile auto *IEREG, volatile auto *IFGREG>
    struct PortWithIntNoPull : PortCommon<INREG, OUTREG>
      , PortInt<IESREG, IEREG, IFGREG>
      , PortSel0and1WithoutPull<INREG, OUTREG, DIRREG, P0SEL, P1SEL> {};

}// namespace Internal

#if defined(__MSP430_HAS_PORT1_R__) || defined(__MSP430_HAS_PORT1__)
#if defined(P1IES) && defined(P1IE) && defined(P1IFG) && defined(P1SEL0) && defined(P1SEL1) && defined(P1REN) && defined(P1DS)
using Port1 = Internal::PortWithIntDrv<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0, &P1SEL1, &P1IES, &P1IE, &P1IFG, &P1DS>;
#elif defined(P1IES) && defined(P1IE) && defined(P1IFG) && defined(P1SEL0) && defined(P1SEL1) && defined(P1REN)
using Port1  = Internal::PortWithInt<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0, &P1SEL1, &P1IES, &P1IE, &P1IFG>;
#elif defined(P1IES) && defined(P1IE) && defined(P1IFG) && defined(P1SEL0) && defined(P1SEL1) && defined(P1DS)
using Port1  = Internal::PortWithIntNoPullDrv<&P1IN, &P1OUT, &P1DIR, &P1SEL0, &P1SEL1, &P1IES, &P1IE, &P1IFG, &P1DS>;
#elif defined(P1IES) && defined(P1IE) && defined(P1IFG) && defined(P1SEL0) && defined(P1SEL1)
using Port1  = Internal::PortWithIntNoPull<&P1IN, &P1OUT, &P1DIR, &P1SEL0, &P1SEL1, &P1IES, &P1IE, &P1IFG>;
#elif defined(P1IES) && defined(P1IE) && defined(P1IFG) && defined(P1REN) && defined(P1DS)
using Port1  = Internal::PortWithIntSel0Drv<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0, &P1IES, &P1IE, &P1IFG, &P1DS>;
#elif defined(P1IES) && defined(P1IE) && defined(P1IFG) && defined(P1REN)
using Port1  = Internal::PortWithIntSel0<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0, &P1IES, &P1IE, &P1IFG>;
#elif defined(P1SEL0) && defined(P1SEL1) && defined(P1REN) && defined(P1DS)
using Port1  = Internal::PortDrv<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0, &P1SEL1, &P1DS>;
#elif defined(P1SEL0) && defined(P1SEL1) && defined(P1REN)
using Port1  = Internal::Port<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0, &P1SEL1>;
#elif defined(P1SEL0) && defined(P1REN) && defined(P1DS)
using Port1  = Internal::PortSel0Drv<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0, &P1DS>;
#elif defined(P1SEL0) && defined(P1REN)
using Port1  = Internal::PortSel0<&P1IN, &P1OUT, &P1DIR, &P1REN, &P1SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT2_R__) || defined(__MSP430_HAS_PORT2__)
#if defined(P2IES) && defined(P2IE) && defined(P2IFG) && defined(P2SEL0) && defined(P2SEL1) && defined(P2REN) && defined(P2DS)
using Port2 = Internal::PortWithIntDrv<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0, &P2SEL1, &P2IES, &P2IE, &P2IFG, &P2DS>;
#elif defined(P2IES) && defined(P2IE) && defined(P2IFG) && defined(P2SEL0) && defined(P2SEL1) && defined(P2REN)
using Port2  = Internal::PortWithInt<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0, &P2SEL1, &P2IES, &P2IE, &P2IFG>;
#elif defined(P2IES) && defined(P2IE) && defined(P2IFG) && defined(P2SEL0) && defined(P2SEL1) && defined(P2DS)
using Port2  = Internal::PortWithIntNoPullDrv<&P2IN, &P2OUT, &P2DIR, &P2SEL0, &P2SEL1, &P2IES, &P2IE, &P2IFG, &P2DS>;
#elif defined(P2IES) && defined(P2IE) && defined(P2IFG) && defined(P2SEL0) && defined(P2SEL1)
using Port2  = Internal::PortWithIntNoPull<&P2IN, &P2OUT, &P2DIR, &P2SEL0, &P2SEL1, &P2IES, &P2IE, &P2IFG>;
#elif defined(P2IES) && defined(P2IE) && defined(P2IFG) && defined(P2REN) && defined(P2DS)
using Port2  = Internal::PortWithIntSel0Drv<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0, &P2IES, &P2IE, &P2IFG, &P2DS>;
#elif defined(P2IES) && defined(P2IE) && defined(P2IFG) && defined(P2REN)
using Port2  = Internal::PortWithIntSel0<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0, &P2IES, &P2IE, &P2IFG>;
#elif defined(P2SEL0) && defined(P2SEL1) && defined(P2REN) && defined(P2DS)
using Port2  = Internal::PortDrv<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0, &P2SEL1, &P2DS>;
#elif defined(P2SEL0) && defined(P2SEL1) && defined(P2REN)
using Port2  = Internal::Port<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0, &P2SEL1>;
#elif defined(P2SEL0) && defined(P2REN) && defined(P2DS)
using Port2  = Internal::PortSel0Drv<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0, &P2DS>;
#elif defined(P2SEL0) && defined(P2REN)
using Port2  = Internal::PortSel0<&P2IN, &P2OUT, &P2DIR, &P2REN, &P2SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT3_R__) || defined(__MSP430_HAS_PORT3__)
#if defined(P3IES) && defined(P3IE) && defined(P3IFG) && defined(P3SEL0) && defined(P3SEL1) && defined(P3REN) && defined(P3DS)
using Port3 = Internal::PortWithIntDrv<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0, &P3SEL1, &P3IES, &P3IE, &P3IFG, &P3DS>;
#elif defined(P3IES) && defined(P3IE) && defined(P3IFG) && defined(P3SEL0) && defined(P3SEL1) && defined(P3REN)
using Port3  = Internal::PortWithInt<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0, &P3SEL1, &P3IES, &P3IE, &P3IFG>;
#elif defined(P3IES) && defined(P3IE) && defined(P3IFG) && defined(P3SEL0) && defined(P3SEL1) && defined(P3DS)
using Port3  = Internal::PortWithIntNoPullDrv<&P3IN, &P3OUT, &P3DIR, &P3SEL0, &P3SEL1, &P3IES, &P3IE, &P3IFG, &P3DS>;
#elif defined(P3IES) && defined(P3IE) && defined(P3IFG) && defined(P3SEL0) && defined(P3SEL1)
using Port3  = Internal::PortWithIntNoPull<&P3IN, &P3OUT, &P3DIR, &P3SEL0, &P3SEL1, &P3IES, &P3IE, &P3IFG>;
#elif defined(P3IES) && defined(P3IE) && defined(P3IFG) && defined(P3REN) && defined(P3DS)
using Port3  = Internal::PortWithIntSel0Drv<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0, &P3IES, &P3IE, &P3IFG, &P3DS>;
#elif defined(P3IES) && defined(P3IE) && defined(P3IFG) && defined(P3REN)
using Port3  = Internal::PortWithIntSel0<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0, &P3IES, &P3IE, &P3IFG>;
#elif defined(P3SEL0) && defined(P3SEL1) && defined(P3REN) && defined(P3DS)
using Port3  = Internal::PortDrv<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0, &P3SEL1, &P3DS>;
#elif defined(P3SEL0) && defined(P3SEL1) && defined(P3REN)
using Port3  = Internal::Port<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0, &P3SEL1>;
#elif defined(P3SEL0) && defined(P3REN) && defined(P3DS)
using Port3  = Internal::PortSel0Drv<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0, &P3DS>;
#elif defined(P3SEL0) && defined(P3REN)
using Port3  = Internal::PortSel0<&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT4_R__) || defined(__MSP430_HAS_PORT4__)
#if defined(P4IES) && defined(P4IE) && defined(P4IFG) && defined(P4SEL0) && defined(P4SEL1) && defined(P4REN) && defined(P4DS)
using Port4 = Internal::PortWithIntDrv<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0, &P4SEL1, &P4IES, &P4IE, &P4IFG, &P4DS>;
#elif defined(P4IES) && defined(P4IE) && defined(P4IFG) && defined(P4SEL0) && defined(P4SEL1) && defined(P4REN)
using Port4  = Internal::PortWithInt<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0, &P4SEL1, &P4IES, &P4IE, &P4IFG>;
#elif defined(P4IES) && defined(P4IE) && defined(P4IFG) && defined(P4SEL0) && defined(P4SEL1) && defined(P4DS)
using Port4  = Internal::PortWithIntNoPullDrv<&P4IN, &P4OUT, &P4DIR, &P4SEL0, &P4SEL1, &P4IES, &P4IE, &P4IFG, &P4DS>;
#elif defined(P4IES) && defined(P4IE) && defined(P4IFG) && defined(P4SEL0) && defined(P4SEL1)
using Port4  = Internal::PortWithIntNoPull<&P4IN, &P4OUT, &P4DIR, &P4SEL0, &P4SEL1, &P4IES, &P4IE, &P4IFG>;
#elif defined(P4IES) && defined(P4IE) && defined(P4IFG) && defined(P4REN) && defined(P4DS)
using Port4  = Internal::PortWithIntSel0Drv<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0, &P4IES, &P4IE, &P4IFG, &P4DS>;
#elif defined(P4IES) && defined(P4IE) && defined(P4IFG) && defined(P4REN)
using Port4  = Internal::PortWithIntSel0<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0, &P4IES, &P4IE, &P4IFG>;
#elif defined(P4SEL0) && defined(P4SEL1) && defined(P4REN) && defined(P4DS)
using Port4  = Internal::PortDrv<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0, &P4SEL1, &P4DS>;
#elif defined(P4SEL0) && defined(P4SEL1) && defined(P4REN)
using Port4  = Internal::Port<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0, &P4SEL1>;
#elif defined(P4SEL0) && defined(P4REN) && defined(P4DS)
using Port4  = Internal::PortSel0Drv<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0, &P4DS>;
#elif defined(P4SEL0) && defined(P4REN)
using Port4  = Internal::PortSel0<&P4IN, &P4OUT, &P4DIR, &P4REN, &P4SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT5_R__) || defined(__MSP430_HAS_PORT5__)
#if defined(P5IES) && defined(P5IE) && defined(P5IFG) && defined(P5SEL0) && defined(P5SEL1) && defined(P5REN) && defined(P5DS)
using Port5 = Internal::PortWithIntDrv<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0, &P5SEL1, &P5IES, &P5IE, &P5IFG, &P5DS>;
#elif defined(P5IES) && defined(P5IE) && defined(P5IFG) && defined(P5SEL0) && defined(P5SEL1) && defined(P5REN)
using Port5  = Internal::PortWithInt<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0, &P5SEL1, &P5IES, &P5IE, &P5IFG>;
#elif defined(P5IES) && defined(P5IE) && defined(P5IFG) && defined(P5SEL0) && defined(P5SEL1) && defined(P5DS)
using Port5  = Internal::PortWithIntNoPullDrv<&P5IN, &P5OUT, &P5DIR, &P5SEL0, &P5SEL1, &P5IES, &P5IE, &P5IFG, &P5DS>;
#elif defined(P5IES) && defined(P5IE) && defined(P5IFG) && defined(P5SEL0) && defined(P5SEL1)
using Port5  = Internal::PortWithIntNoPull<&P5IN, &P5OUT, &P5DIR, &P5SEL0, &P5SEL1, &P5IES, &P5IE, &P5IFG>;
#elif defined(P5IES) && defined(P5IE) && defined(P5IFG) && defined(P5REN) && defined(P5DS)
using Port5  = Internal::PortWithIntSel0Drv<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0, &P5IES, &P5IE, &P5IFG, &P5DS>;
#elif defined(P5IES) && defined(P5IE) && defined(P5IFG) && defined(P5REN)
using Port5  = Internal::PortWithIntSel0<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0, &P5IES, &P5IE, &P5IFG>;
#elif defined(P5SEL0) && defined(P5SEL1) && defined(P5REN) && defined(P5DS)
using Port5  = Internal::PortDrv<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0, &P5SEL1, &P5DS>;
#elif defined(P5SEL0) && defined(P5SEL1) && defined(P5REN)
using Port5  = Internal::Port<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0, &P5SEL1>;
#elif defined(P5SEL0) && defined(P5REN) && defined(P5DS)
using Port5  = Internal::PortSel0Drv<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0, &P5DS>;
#elif defined(P5SEL0) && defined(P5REN)
using Port5  = Internal::PortSel0<&P5IN, &P5OUT, &P5DIR, &P5REN, &P5SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT6_R__) || defined(__MSP430_HAS_PORT6__)
#if defined(P6IES) && defined(P6IE) && defined(P6IFG) && defined(P6SEL0) && defined(P6SEL1) && defined(P6REN) && defined(P6DS)
using Port6 = Internal::PortWithIntDrv<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0, &P6SEL1, &P6IES, &P6IE, &P6IFG, &P6DS>;
#elif defined(P6IES) && defined(P6IE) && defined(P6IFG) && defined(P6SEL0) && defined(P6SEL1) && defined(P6REN)
using Port6  = Internal::PortWithInt<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0, &P6SEL1, &P6IES, &P6IE, &P6IFG>;
#elif defined(P6IES) && defined(P6IE) && defined(P6IFG) && defined(P6SEL0) && defined(P6SEL1) && defined(P6DS)
using Port6  = Internal::PortWithIntNoPullDrv<&P6IN, &P6OUT, &P6DIR, &P6SEL0, &P6SEL1, &P6IES, &P6IE, &P6IFG, &P6DS>;
#elif defined(P6IES) && defined(P6IE) && defined(P6IFG) && defined(P6SEL0) && defined(P6SEL1)
using Port6  = Internal::PortWithIntNoPull<&P6IN, &P6OUT, &P6DIR, &P6SEL0, &P6SEL1, &P6IES, &P6IE, &P6IFG>;
#elif defined(P6IES) && defined(P6IE) && defined(P6IFG) && defined(P6REN) && defined(P6DS)
using Port6  = Internal::PortWithIntSel0Drv<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0, &P6IES, &P6IE, &P6IFG, &P6DS>;
#elif defined(P6IES) && defined(P6IE) && defined(P6IFG) && defined(P6REN)
using Port6  = Internal::PortWithIntSel0<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0, &P6IES, &P6IE, &P6IFG>;
#elif defined(P6SEL0) && defined(P6SEL1) && defined(P6REN) && defined(P6DS)
using Port6  = Internal::PortDrv<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0, &P6SEL1, &P6DS>;
#elif defined(P6SEL0) && defined(P6SEL1) && defined(P6REN)
using Port6  = Internal::Port<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0, &P6SEL1>;
#elif defined(P6SEL0) && defined(P6REN) && defined(P6DS)
using Port6  = Internal::PortSel0Drv<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0, &P6DS>;
#elif defined(P6SEL0) && defined(P6REN)
using Port6  = Internal::PortSel0<&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT7_R__) || defined(__MSP430_HAS_PORT7__)
#if defined(P7IES) && defined(P7IE) && defined(P7IFG) && defined(P7SEL0) && defined(P7SEL1) && defined(P7REN) && defined(P7DS)
using Port7 = Internal::PortWithIntDrv<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0, &P7SEL1, &P7IES, &P7IE, &P7IFG, &P7DS>;
#elif defined(P7IES) && defined(P7IE) && defined(P7IFG) && defined(P7SEL0) && defined(P7SEL1) && defined(P7REN)
using Port7  = Internal::PortWithInt<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0, &P7SEL1, &P7IES, &P7IE, &P7IFG>;
#elif defined(P7IES) && defined(P7IE) && defined(P7IFG) && defined(P7SEL0) && defined(P7SEL1) && defined(P7DS)
using Port7  = Internal::PortWithIntNoPullDrv<&P7IN, &P7OUT, &P7DIR, &P7SEL0, &P7SEL1, &P7IES, &P7IE, &P7IFG, &P7DS>;
#elif defined(P7IES) && defined(P7IE) && defined(P7IFG) && defined(P7SEL0) && defined(P7SEL1)
using Port7  = Internal::PortWithIntNoPull<&P7IN, &P7OUT, &P7DIR, &P7SEL0, &P7SEL1, &P7IES, &P7IE, &P7IFG>;
#elif defined(P7IES) && defined(P7IE) && defined(P7IFG) && defined(P7REN) && defined(P7DS)
using Port7  = Internal::PortWithIntSel0Drv<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0, &P7IES, &P7IE, &P7IFG, &P7DS>;
#elif defined(P7IES) && defined(P7IE) && defined(P7IFG) && defined(P7REN)
using Port7  = Internal::PortWithIntSel0<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0, &P7IES, &P7IE, &P7IFG>;
#elif defined(P7SEL0) && defined(P7SEL1) && defined(P7REN) && defined(P7DS)
using Port7  = Internal::PortDrv<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0, &P7SEL1, &P7DS>;
#elif defined(P7SEL0) && defined(P7SEL1) && defined(P7REN)
using Port7  = Internal::Port<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0, &P7SEL1>;
#elif defined(P7SEL0) && defined(P7REN) && defined(P7DS)
using Port7  = Internal::PortSel0Drv<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0, &P7DS>;
#elif defined(P7SEL0) && defined(P7REN)
using Port7  = Internal::PortSel0<&P7IN, &P7OUT, &P7DIR, &P7REN, &P7SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT8_R__) || defined(__MSP430_HAS_PORT8__)
#if defined(P8IES) && defined(P8IE) && defined(P8IFG) && defined(P8SEL0) && defined(P8SEL1) && defined(P8REN) && defined(P8DS)
using Port8 = Internal::PortWithIntDrv<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0, &P8SEL1, &P8IES, &P8IE, &P8IFG, &P8DS>;
#elif defined(P8IES) && defined(P8IE) && defined(P8IFG) && defined(P8SEL0) && defined(P8SEL1) && defined(P8REN)
using Port8  = Internal::PortWithInt<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0, &P8SEL1, &P8IES, &P8IE, &P8IFG>;
#elif defined(P8IES) && defined(P8IE) && defined(P8IFG) && defined(P8SEL0) && defined(P8SEL1) && defined(P8DS)
using Port8  = Internal::PortWithIntNoPullDrv<&P8IN, &P8OUT, &P8DIR, &P8SEL0, &P8SEL1, &P8IES, &P8IE, &P8IFG, &P8DS>;
#elif defined(P8IES) && defined(P8IE) && defined(P8IFG) && defined(P8SEL0) && defined(P8SEL1)
using Port8  = Internal::PortWithIntNoPull<&P8IN, &P8OUT, &P8DIR, &P8SEL0, &P8SEL1, &P8IES, &P8IE, &P8IFG>;
#elif defined(P8IES) && defined(P8IE) && defined(P8IFG) && defined(P8REN) && defined(P8DS)
using Port8  = Internal::PortWithIntSel0Drv<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0, &P8IES, &P8IE, &P8IFG, &P8DS>;
#elif defined(P8IES) && defined(P8IE) && defined(P8IFG) && defined(P8REN)
using Port8  = Internal::PortWithIntSel0<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0, &P8IES, &P8IE, &P8IFG>;
#elif defined(P8SEL0) && defined(P8SEL1) && defined(P8REN) && defined(P8DS)
using Port8  = Internal::PortDrv<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0, &P8SEL1, &P8DS>;
#elif defined(P8SEL0) && defined(P8SEL1) && defined(P8REN)
using Port8  = Internal::Port<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0, &P8SEL1>;
#elif defined(P8SEL0) && defined(P8REN) && defined(P8DS)
using Port8  = Internal::PortSel0Drv<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0, &P8DS>;
#elif defined(P8SEL0) && defined(P8REN)
using Port8  = Internal::PortSel0<&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT9_R__) || defined(__MSP430_HAS_PORT9__)
#if defined(P9IES) && defined(P9IE) && defined(P9IFG) && defined(P9SEL0) && defined(P9SEL1) && defined(P9REN) && defined(P9DS)
using Port9 = Internal::PortWithIntDrv<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0, &P9SEL1, &P9IES, &P9IE, &P9IFG, &P9DS>;
#elif defined(P9IES) && defined(P9IE) && defined(P9IFG) && defined(P9SEL0) && defined(P9SEL1) && defined(P9REN)
using Port9  = Internal::PortWithInt<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0, &P9SEL1, &P9IES, &P9IE, &P9IFG>;
#elif defined(P9IES) && defined(P9IE) && defined(P9IFG) && defined(P9SEL0) && defined(P9SEL1) && defined(P9DS)
using Port9  = Internal::PortWithIntNoPullDrv<&P9IN, &P9OUT, &P9DIR, &P9SEL0, &P9SEL1, &P9IES, &P9IE, &P9IFG, &P9DS>;
#elif defined(P9IES) && defined(P9IE) && defined(P9IFG) && defined(P9SEL0) && defined(P9SEL1)
using Port9  = Internal::PortWithIntNoPull<&P9IN, &P9OUT, &P9DIR, &P9SEL0, &P9SEL1, &P9IES, &P9IE, &P9IFG>;
#elif defined(P9IES) && defined(P9IE) && defined(P9IFG) && defined(P9REN) && defined(P9DS)
using Port9  = Internal::PortWithIntSel0Drv<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0, &P9IES, &P9IE, &P9IFG, &P9DS>;
#elif defined(P9IES) && defined(P9IE) && defined(P9IFG) && defined(P9REN)
using Port9  = Internal::PortWithIntSel0<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0, &P9IES, &P9IE, &P9IFG>;
#elif defined(P9SEL0) && defined(P9SEL1) && defined(P9REN) && defined(P9DS)
using Port9  = Internal::PortDrv<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0, &P9SEL1, &P9DS>;
#elif defined(P9SEL0) && defined(P9SEL1) && defined(P9REN)
using Port9  = Internal::Port<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0, &P9SEL1>;
#elif defined(P9SEL0) && defined(P9REN) && defined(P9DS)
using Port9  = Internal::PortSel0Drv<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0, &P9DS>;
#elif defined(P9SEL0) && defined(P9REN)
using Port9  = Internal::PortSel0<&P9IN, &P9OUT, &P9DIR, &P9REN, &P9SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT10_R__) || defined(__MSP430_HAS_PORT10__)
#if defined(P10IES) && defined(P10IE) && defined(P10IFG) && defined(P10SEL0) && defined(P10SEL1) && defined(P10REN) && defined(P10DS)
using Port10 = Internal::PortWithIntDrv<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0, &P10SEL1, &P10IES, &P10IE, &P10IFG, &P10DS>;
#elif defined(P10IES) && defined(P10IE) && defined(P10IFG) && defined(P10SEL0) && defined(P10SEL1) && defined(P10REN)
using Port10 = Internal::PortWithInt<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0, &P10SEL1, &P10IES, &P10IE, &P10IFG>;
#elif defined(P10IES) && defined(P10IE) && defined(P10IFG) && defined(P10SEL0) && defined(P10SEL1) && defined(P10DS)
using Port10 = Internal::PortWithIntNoPullDrv<&P10IN, &P10OUT, &P10DIR, &P10SEL0, &P10SEL1, &P10IES, &P10IE, &P10IFG, &P10DS>;
#elif defined(P10IES) && defined(P10IE) && defined(P10IFG) && defined(P10SEL0) && defined(P10SEL1)
using Port10 = Internal::PortWithIntNoPull<&P10IN, &P10OUT, &P10DIR, &P10SEL0, &P10SEL1, &P10IES, &P10IE, &P10IFG>;
#elif defined(P10IES) && defined(P10IE) && defined(P10IFG) && defined(P10REN) && defined(P10DS)
using Port10 = Internal::PortWithIntSel0Drv<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0, &P10IES, &P10IE, &P10IFG, &P10DS>;
#elif defined(P10IES) && defined(P10IE) && defined(P10IFG) && defined(P10REN)
using Port10 = Internal::PortWithIntSel0<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0, &P10IES, &P10IE, &P10IFG>;
#elif defined(P10SEL0) && defined(P10SEL1) && defined(P10REN) && defined(P10DS)
using Port10 = Internal::PortDrv<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0, &P10SEL1, &P10DS>;
#elif defined(P10SEL0) && defined(P10SEL1) && defined(P10REN)
using Port10 = Internal::Port<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0, &P10SEL1>;
#elif defined(P10SEL0) && defined(P10REN) && defined(P10DS)
using Port10 = Internal::PortSel0Drv<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0, &P10DS>;
#elif defined(P10SEL0) && defined(P10REN)
using Port10 = Internal::PortSel0<&P10IN, &P10OUT, &P10DIR, &P10REN, &P10SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORT11_R__) || defined(__MSP430_HAS_PORT11__)
#if defined(P11IES) && defined(P11IE) && defined(P11IFG) && defined(P11SEL0) && defined(P11SEL1) && defined(P11REN) && defined(P11DS)
using Port11 = Internal::PortWithIntDrv<&P11IN, &P11OUT, &P11DIR, &P11REN, &P11SEL0, &P11SEL1, &P11IES, &P11IE, &P11IFG, &P11DS>;
#elif defined(P11IES) && defined(P11IE) && defined(P11IFG) && defined(P11SEL0) && defined(P11SEL1) && defined(P11REN)
using Port11 = Internal::PortWithInt<&P11IN, &P11OUT, &P11DIR, &P11REN, &P11SEL0, &P11SEL1, &P11IES, &P11IE, &P11IFG>;
#elif defined(P11IES) && defined(P11IE) && defined(P11IFG) && defined(P11SEL0) && defined(P11SEL1) && defined(P11DS)
using Port11 = Internal::PortWithIntNoPullDrv<&P11IN, &P11OUT, &P11DIR, &P11SEL0, &P11SEL1, &P11IES, &P11IE, &P11IFG, &P11DS>;
#elif defined(P11IES) && defined(P11IE) && defined(P11IFG) && defined(P11SEL0) && defined(P11SEL1)
using Port11 = Internal::PortWithIntNoPull<&P11IN, &P11OUT, &P11DIR, &P11SEL0, &P11SEL1, &P11IES, &P11IE, &P11IFG>;
#elif defined(P11IES) && defined(P11IE) && defined(P11IFG) && defined(P11REN) && defined(P11DS)
using Port11 = Internal::PortWithIntSel0Drv<&P11IN, &P11OUT, &P11DIR, &P11REN, &P11SEL0, &P11IES, &P11IE, &P11IFG, &P11DS>;
#elif defined(P11IES) && defined(P11IE) && defined(P11IFG) && defined(P11REN)
using Port11 = Internal::PortWithIntSel0<&P11IN, &P11OUT, &P11DIR, &P11REN, &P11SEL0, &P11IES, &P11IE, &P11IFG>;
#elif defined(P11SEL0) && defined(P11SEL1) && defined(P11REN) && defined(P11DS)
using Port11 = Internal::PortDrv<&P11IN, &P11OUT, &P11DIR, &P11REN, &P11SEL0, &P11SEL1, &P11DS>;
#elif defined(P11SEL0) && defined(P11SEL1) && defined(P11REN)
using Port11 = Internal::Port<&P11IN, &P11OUT, &P11DIR, &P11REN, &P11SEL0, &P11SEL1>;
#elif defined(P11SEL0) && defined(P11REN) && defined(P11DS)
using Port11 = Internal::PortSel0Drv<&P11IN, &P11OUT, &P11DIR, &P11REN, &P11SEL0, &P11DS>;
#elif defined(P11SEL0) && defined(P11REN)
using Port11 = Internal::PortSel0<&P11IN, &P11OUT, &P11DIR, &P11REN, &P11SEL0>;
#endif
#endif


#if defined(__MSP430_HAS_PORTJ_R__) || defined(__MSP430_HAS_PORTJ__)
#if defined(__MSP430FR5XX_6XX_FAMILY__) || defined(__MSP430FR57XX_FAMILY__)
using PortJ = Internal::Port<&PJIN, &PJOUT, &PJDIR, &PJREN, &PJSEL0, &PJSEL1>;
#elif defined(__MSP430F5XX_6XX_FAMILY__)
using PortJ  = Internal::PortSelOffDrv<&PJIN, &PJOUT, &PJDIR, &PJREN, &PJDS>;
#endif
#endif

}// namespace MT::MSP430::GPIO

#endif
#endif /* MICROTRAIT_MSP430_GPIO_GPIO_HPP_ */

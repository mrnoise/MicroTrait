/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430Sfr SFR
 *  @ingroup groupMSP430
* @brief functions for SFR(special function register) register access for TIs MSP430 -> Ti Driverlib equivalent naming
*
* @details
* Usage: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

    Sfr sfr{};
    sfr.enableInterrupt(SFR::INT::WATCHDOG_INTERVAL_TIMER);

\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupFuncsMSP430Sfr Functions
*  @ingroup groupMSP430Sfr
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430Sfr Enums
*  @ingroup groupMSP430Sfr
*  Enums in this module
*/


#ifndef MICROTRAIT_MSP430_SFR_SFR_HPP_
#define MICROTRAIT_MSP430_SFR_SFR_HPP_

#include "MicroTrait/MSP430/Settings.hpp"
#include "MicroTrait/MSP430/Types.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Register.hpp"
#include <msp430.h>
#include <utility>
#include <type_traits>

#ifdef __MSP430_HAS_SFR__

namespace MT {
namespace Misc {

    enum class SFR_INT : uint16_t {
#if not defined(__MSP430_HAS_MSP430I_CPU__)
        JTAG_OUTBOX = (JMBOUTIE),
        JTAG_INBOX  = (JMBINIE),
#endif
        NMI_PIN                 = (NMIIE),
        VACANT_MEMORY_ACCESS    = (VMAIE),
        OSCILLATOR_FAULT        = (OFIE),
        WATCHDOG_INTERVAL_TIMER = (WDTIE),
#if defined(__MSP430F5XX_6XX_FAMILY__) || defined(__MSP430_HAS_MSP430I_CPU__)
        FLASH_CONTROLLER_ACCESS_VIOLATION = (ACCVIE),
#endif

#if defined(__MSP430_HAS_MSP430I_CPU__)
        EXTERNAL_RESET  = (RSTIFG),
        BROWN_OUT_RESET = (BORIFG),
#endif
    };
    template<>
    struct enable_Enum_bits<SFR_INT> {
        static constexpr bool enable = true;
    };

}// namespace Misc


namespace MSP430 {
    namespace SFR {

        /**
		* @ingroup groupEnumsMSP430Sfr
		****************************************************************
		* @brief SFR interrupt types
		****************************************************************
		*/
        using INT = MT::Misc::SFR_INT;

#if not defined(__MSP430_HAS_MSP430I_CPU__)
        /**
		* @ingroup groupEnumsMSP430Sfr
		****************************************************************
		* @brief Reset pin Pullup/down or disable -> not available for MSP430i2xx Family
		****************************************************************
		*/
        enum class RST_RESISTOR : uint16_t {
            DISABLE  = (!(SYSRSTRE + SYSRSTUP)),
            PULLUP   = (SYSRSTRE + SYSRSTUP),
            PULLDOWN = (SYSRSTRE),
        };

        /**
		* @ingroup groupEnumsMSP430Sfr
		****************************************************************
		* @brief Reset (NMI) edge selection -> not available for MSP430i2xx Family
		****************************************************************
		*/
        enum class NMI_EDGE : uint16_t {
            RISING  = (!(SYSNMIIES)),
            FALLING = (SYSNMIIES)
        };

        /**
		* @ingroup groupEnumsMSP430Sfr
		****************************************************************
		* @brief Reset pin function -> not available for MSP430i2xx Family
		****************************************************************
		*/
        enum class RST_FUNC : uint16_t {
            RESET = (!(SYSNMI)),
            NMI   = (SYSNMI)
        };
#endif

    }// namespace SFR

    struct Sfr {

      private:
        MT::Universal::Register<&SFRIE1>  m_ie{};
        MT::Universal::Register<&SFRIFG1> m_if{};
        MT::Universal::Register<&SFRRPCR> m_reset{};

      public:
        /**
		* @ingroup groupFuncsMSP430Sfr
		****************************************************************
		* @brief enables the given interrupts
		* @details
		* Usage: \code {.cpp}
		* using namespace MT::MSP430;
		*
		*  Sfr sfr{};
		*  sfr.enableInterrupt(SFR::INT::WATCHDOG_INTERVAL_TIMER | SFR::INT::OSCILLATOR_FAULT); \endcode
		*@tparam BITS use enumeration SFR::INT
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void enableInterrupt(const BIT &bit, const BITS &... bits) noexcept {
            static_assert(std::is_same<MT::MSP430::SFR::INT, BIT>::value, "input must be SFR::INT enum");
            m_ie.set(bit, bits...);
        }

        /**
		* @ingroup groupFuncsMSP430Sfr
		****************************************************************
		* @brief disables the given interrupts
		* @details
		* Usage: \code {.cpp}
		* using namespace MT::MSP430;
		*
		*  Sfr sfr{};
		*  sfr.disableInterrupt(SFR::INT::WATCHDOG_INTERVAL_TIMER | SFR::INT::OSCILLATOR_FAULT); \endcode
		*@tparam BITS use enumeration SFR::INT
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void disableInterrupt(const BIT &bit, const BITS &... bits) noexcept {
            static_assert(std::is_same<MT::MSP430::SFR::INT, BIT>::value, "input must be SFR::INT enum");
            m_ie.clear(bit, bits...);
        }

        /**
		* @ingroup groupFuncsMSP430Sfr
		****************************************************************
		* @brief compares the given SFR_INT(s) with the interrupt flags set in the hw register
		* @details
		* Usage: \code {.cpp}
		* using namespace MT::MSP430;
		*
		*  Sfr sfr{};
		*  if(sfr.getInterruptStatus(SFR::INT::WATCHDOG_INTERVAL_TIMER | SFR::INT::OSCILLATOR_FAULT) == INT_MASK_MATCH::TRUE) doSomething();  \endcode
		*@tparam BITS use enumeration SFR::INT
		*@return if all the given bits are set or not (MT::MSP430::INT_MASK_MATCH)
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        [[nodiscard]] constexpr INT_MASK_MATCH getInterruptStatus(const BIT &bit, const BITS &... bits) noexcept {
            static_assert(std::is_same<MT::MSP430::SFR::INT, BIT>::value, "input must be SFR::INT enum");
            if (m_if.compare(bit, bits...)) return INT_MASK_MATCH::TRUE;
            else
                return INT_MASK_MATCH::FALSE;
        }

        /**
		* @ingroup groupFuncsMSP430Sfr
		****************************************************************
		* @brief clear the given interrupts
		* @details
		* Usage: \code {.cpp}
		* using namespace MT::MSP430;
		*
		*  Sfr sfr{};
		*  sfr.clearInterruptStatus(SFR::INT::WATCHDOG_INTERVAL_TIMER | SFR::INT::OSCILLATOR_FAULT); \endcode
		*@tparam BITS use enumeration SFR::INT
		****************************************************************
		*/
        template<typename BIT, typename = typename std::enable_if<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void clearInterruptStatus(const BIT &bit, const BITS &... bits) noexcept {
            static_assert(std::is_same<MT::MSP430::SFR::INT, BIT>::value, "input must be SFR::INT enum");
            m_if.clear(bit, bits...);
        }

#if not defined(__MSP430_HAS_MSP430I_CPU__)
        /**
		* @ingroup groupFuncsMSP430Sfr
		****************************************************************
		* @brief sets the Pullup/down/disable configuration of the reset pin -> not available for MSP430i2xx Family
		* @details
		* Usage: \code {.cpp}
		* using namespace MT::MSP430;
		*
		*  Sfr sfr{};
		*  sfr.setResetPinPullResistor(SFR::RST_RESISTOR::PULLUP); \endcode
		*@param rst the configuration (#RST_RESISTOR)
		****************************************************************
		*/
        constexpr void setResetPinPullResistor(const SFR::RST_RESISTOR rst) noexcept {
            m_reset.clear(SYSRSTRE + SYSRSTUP);
            m_reset.set(static_cast<uint16_t>(rst));
        }

        /**
		* @ingroup groupFuncsMSP430Sfr
		****************************************************************
		* @brief sets the edge configuration of the reset pin -> not available for MSP430i2xx Family
		* @details
		* Usage: \code {.cpp}
		* using namespace MT::MSP430;
		*
		*  Sfr sfr{};
		*  sfr.setNMIEdge(SFR::NMI_EDGE::RISING); \endcode
		*@param edge the configuration (#NMI_EDGE)
		****************************************************************
		*/
        constexpr void setNMIEdge(const SFR::NMI_EDGE edge) noexcept {
            m_reset.clear(SYSNMIIES);
            m_reset.set(static_cast<uint16_t>(edge));
        }

        /**
		* @ingroup groupFuncsMSP430Sfr
		****************************************************************
		* @brief sets function of the reset pin -> not available for MSP430i2xx Family
		* @details
		* Usage: \code {.cpp}
		* using namespace MT::MSP430;
		*
		*  Sfr sfr{};
		*  sfr.setResetNMIPinFunction(SFR::RST_FUNC::RESET); \endcode
		*@param func the configuration (#RST_FUNC)
		****************************************************************
		*/
        constexpr void setResetNMIPinFunction(const SFR::RST_FUNC func) noexcept {
            m_reset.clear(SYSNMI);
            m_reset.set(static_cast<uint16_t>(func));
        }
#endif
    };
}// namespace MSP430
}// namespace MT

#endif
#endif
#endif /* MICROTRAIT_MSP430_SFR_SFR_HPP_ */

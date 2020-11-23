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
#include "MicroTrait/Misc/Meta.hpp"
#include <msp430.h>
#include <utility>
#include <type_traits>

#ifdef __MSP430_HAS_SFR__

namespace MT::Misc {
enum class SFR_INT : uint8_t {
    NMI_PIN                 = (NMIIE),
    OSCILLATOR_FAULT        = (OFIE),
    WATCHDOG_INTERVAL_TIMER = (WDTIE),

#if not defined(__MSP430_HAS_MSP430I_CPU__)
    JTAG_OUTBOX          = (JMBOUTIE),
    JTAG_INBOX           = (JMBINIE),
    VACANT_MEMORY_ACCESS = (VMAIE),
#endif

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

template<>
struct enable_Enum_bits<volatile SFR_INT> {
    static constexpr bool enable = true;
};

}// namespace MT::Misc


namespace MT::MSP430::SFR {

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

}// namespace MT::MSP430::SFR

namespace MT::MSP430 {

struct Sfr {

  private:
    MT::Universal::Register<&SFRIE1_L>  m_ie{};
    MT::Universal::Register<&SFRIFG1_L> m_if{};
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    MT::Universal::Register<&SFRRPCR> m_reset{};
#endif

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
	*@tparam BIT use enumeration SFR::INT
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void enableInterrupt(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::SFR::INT, BIT>(), "input must be SFR::INT enum");
        m_ie.set(bit);
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
	*@tparam BIT use enumeration SFR::INT
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void disableInterrupt(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::SFR::INT, BIT>(), "input must be SFR::INT enum");
        m_ie.clear(bit);
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
	*@tparam BIT use enumeration SFR::INT
	*@return if all the given bits are set or not (MT::MSP430::INT_MASK_MATCH)
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    [[nodiscard]] constexpr INT_MASK_MATCH getInterruptStatus(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::SFR::INT, BIT>(), "input must be SFR::INT enum");
        if (m_if.compare(bit)) return INT_MASK_MATCH::TRUE;
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
	*@tparam BIT use enumeration SFR::INT
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void clearInterruptStatus(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::SFR::INT, BIT>(), "input must be SFR::INT enum");
        m_if.clear(bit);
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
}// namespace MT::MSP430

#endif
#endif
#endif /* MICROTRAIT_MSP430_SFR_SFR_HPP_ */

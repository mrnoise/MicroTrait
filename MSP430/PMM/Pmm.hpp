/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430Pmm PMM
 *  @ingroup groupMSP430
* @brief functions for PMM(power management module) register access for TIs MSP430 -> Ti Driverlib equivalent naming
*
* @details
* Usage: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

 Pmm pmm{};
 pmm.unlockLPM5();

\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/

/** @defgroup groupMSP430FRAMPmm FRAM specific
*  @ingroup groupMSP430Pmm
*  Functions for MSP430 FRAM Family
*/

/** @defgroup groupFuncsMSP430FRAMPmm Functions
*  @ingroup groupMSP430FRAMPmm
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430FRAMPmm Enums
*  @ingroup groupMSP430FRAMPmm
*  Enums in this module
*/


/** @defgroup groupMSP430FPmm F5xx/6xx specific
*  @ingroup groupMSP430Pmm
*  Functions for MSP430F5xx/6xx Family
*/

/** @defgroup groupFuncsMSP430FPmm Functions
*  @ingroup groupMSP430FPmm
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430FPmm Enums
*  @ingroup groupMSP430FPmm
*  Enums in this module
*/


/** @defgroup groupMSP430IPmm i2xx specific
*  @ingroup groupMSP430Pmm
*  Functions for MSP430i2xx Family
*/

/** @defgroup groupFuncsMSP430IPmm Functions
*  @ingroup groupMSP430IPmm
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430IPmm Enums
*  @ingroup groupMSP430IPmm
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_PMM_PMM_HPP_
#define MICROTRAIT_MSP430_PMM_PMM_HPP_

#include "MicroTrait/MSP430/Settings.hpp"
#include "MicroTrait/MSP430/Types.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Register.hpp"
#include "MicroTrait/Misc/Meta.hpp"
#include <msp430.h>
#include <utility>
#include <type_traits>

#if defined(__MSP430_HAS_PMM__) || defined(__MSP430_HAS_PMM_FR5xx__) || defined(__MSP430_HAS_PMM_FRAM__)

#if defined(__MSP430_HAS_PMM_FRAM__) || defined(__MSP430_HAS_PMM_FR5xx__)
namespace MT::Misc {
#if defined(__MSP430_HAS_PMM_FRAM__)
enum class PMM_INT : uint16_t {
    BOR  = (PMMBORIFG),
    RST  = (PMMRSTIFG),
    POR  = (PMMPORIFG),
    SVSH = (SVSHIFG),
    LPM5 = (PMMLPM5IFG),
    ALL  = (0xA7)
};
template<>
struct enable_Enum_bits<PMM_INT> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile PMM_INT> {
    static constexpr bool enable = true;
};

#elif defined(__MSP430_HAS_PMM_FR5xx__)
enum class PMM_INT : uint16_t {
    BOR  = (PMMBORIFG),
    RST  = (PMMRSTIFG),
    POR  = (PMMPORIFG),
    SVSH = (SVSHIFG),
    SVSL = (SVSLIFG),
    LPM5 = (PMMLPM5IFG),
    ALL  = (0xB7)
};
template<>
struct enable_Enum_bits<PMM_INT> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile PMM_INT> {
    static constexpr bool enable = true;
};
#endif
}// namespace MT::Misc


namespace MT::MSP430::PMM {
/**
* @ingroup groupEnumsMSP430FRAMPmm
****************************************************************
* @brief PMM interrupt types
****************************************************************
*/
using INT = MT::Misc::PMM_INT;

#if defined(__MSP430FR2XX_4XX_FAMILY__)
/**
* @ingroup groupEnumsMSP430FRAMPmm
****************************************************************
* @brief Bandgap mode -> only available for MSP430FR2xx/4xx Family
****************************************************************
*/
enum class BANDGAP_MODE : uint_fast8_t {
    STATIC = 0,
    SAMPLE
};

/**
* @ingroup groupEnumsMSP430FRAMPmm
****************************************************************
* @brief Bandgap active or not -> only available for MSP430FR2xx/4xx Family
****************************************************************
*/
enum class BANDGAP : uint_fast8_t {
    INACTIVE = 0,
    ACTIVE
};

/**
* @ingroup groupEnumsMSP430FRAMPmm
****************************************************************
* @brief Reference generator active or not -> only available for MSP430FR2xx/4xx Family
****************************************************************
*/
enum class REFGEN : uint_fast8_t {
    INACTIVE = 0,
    ACTIVE
};

/**
* @ingroup groupEnumsMSP430FRAMPmm
****************************************************************
* @brief Bandgap status -> only available for MSP430FR2xx/4xx Family
****************************************************************
*/
enum class BANDGAP_STATUS : uint_fast8_t {
    NOTREADY = 0,
    READY
};

/**
* @ingroup groupEnumsMSP430FRAMPmm
****************************************************************
* @brief reference generator status -> only available for MSP430FR2xx/4xx Family
****************************************************************
*/
enum class REFGEN_STATUS : uint_fast8_t {
    NOTREADY = 0,
    READY
};

#if defined(REFVSEL)
/**
* @ingroup groupEnumsMSP430FRAMPmm
****************************************************************
* @brief reference voltage selection -> only available for MSP430FR2xx/4xx Family
****************************************************************
*/
enum class REF_VOLT_SELECT : uint16_t {
    V1_5 = (REFVSEL_0),
    V2_0 = (REFVSEL_1),
    V2_5 = (REFVSEL_2)
};
#endif
#endif
}// namespace MT::MSP430::PMM

namespace MT::MSP430 {
struct Pmm {

  private:
    MT::Universal::Register<&PMMCTL0_L> m_ctl0{};
    MT::Universal::Register<&PMMCTL0_H> m_ctl0pwd{};
#if defined(__MSP430FR2XX_4XX_FAMILY__)
    MT::Universal::Register<&PMMCTL1> m_ctl1{};
    MT::Universal::Register<&PMMCTL2> m_ctl2{};
#endif
    MT::Universal::Register<&PMMIFG>  m_if{};
    MT::Universal::Register<&PM5CTL0> m_lpm5{};

  public:
    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief enables the voltage supervisor high side -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSVSH(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSVSH() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl0.set(SVSHE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief disables the voltage supervisor high side -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSVSH(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSVSH() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl0.clear(SVSHE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Makes the LDO remain ON when going into LPM 3/4 -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.turnOnRegulator(); \endcode
	*
	****************************************************************
	*/
    constexpr void turnOnRegulator() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl0.clear(PMMREGOFF);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Turns off the LDO when going into LPM3/4, thus the system will enter LPM3.5 or LPM4.5 respectively -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.turnOffRegulator(); \endcode
	*
	****************************************************************
	*/
    constexpr void turnOffRegulator() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl0.set(PMMREGOFF);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief triggers a software Power On Reset (POR) -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.trigPOR(); \endcode
	*
	****************************************************************
	*/
    constexpr void trigPOR() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl0.set(PMMSWPOR);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief triggers a software Brown Out Rest (BOR) -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.trigBOR(); \endcode
	*
	****************************************************************
	*/
    constexpr void trigBOR() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl0.set(PMMSWBOR);
        m_ctl0pwd.override(0x00);
    }


    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief clears the interrupt flags for the given mask -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.clearInterrupt(PMM::INT::BOR | PMM::INT::POR); \endcode
	*@tparam BIT use enumeration PMM::INT
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void clearInterrupt(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::PMM::INT, BIT>(), "input must be PMM::INT enum");
        m_ctl0pwd.override(PMMPW_H);
        m_if.clear(bit);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief compares the given pins with the interrupt flags set in the hw register -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.getInterruptStatus(PMM::INT::BOR | PMM::INT::POR) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
	*@tparam BIT use enumeration PMM::INT
	*@return if all the given bits are set or not (INT_MASK_MATCH)
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    [[nodiscard]] constexpr INT_MASK_MATCH getInterruptStatus(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::PMM::INT, BIT>(), "input must be PMM::INT enum");
        if (m_if.compare(bit)) return INT_MASK_MATCH::TRUE;
        else
            return INT_MASK_MATCH::FALSE;
    }


    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Disable the GPIO power-on default high-impedance mode to activate previously configured port settings -> only available for MSP430 FRAM Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.unlockLPM5(); \endcode
	*
	****************************************************************
	*/
    constexpr void unlockLPM5() noexcept {
        m_lpm5.clear(LOCKLPM5);
    }

#if defined(__MSP430_HAS_PMM_FR5xx__)
    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief enables the voltage supervisor low side -> only available for MSP430FR5xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSVSL(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSVSL() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl0.set(SVSLE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief disables the voltage supervisor low side-> only available for MSP430FR5xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSVSL(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSVSL() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl0.clear(SVSLE);
        m_ctl0pwd.override(0x00);
    }
#endif

#if defined(__MSP430FR2XX_4XX_FAMILY__)
    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief returns the bandgap mode of the PMM module -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.getBandgapMode() == PMM::BANDGAP_MODE::SAMPLE) doSomething(); \endcode
	*@return the curretn bandgap mode (PMM::BANDGAP_MODE)
	****************************************************************
	*/
    [[nodiscard]] constexpr PMM::BANDGAP_MODE getBandgapMode() noexcept {
        if (m_ctl2.compare(BGMODE)) return PMM::BANDGAP_MODE::SAMPLE;
        else
            return PMM::BANDGAP_MODE::STATIC;
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief returns the active status of the bandgap in the PMM module -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.isBandgapActive() == PMM::BANDGAP::ACTIVE) doSomething(); \endcode
	*@return if the bandgap is active or not (PMM::BANDGAP)
	****************************************************************
	*/
    [[nodiscard]] constexpr PMM::BANDGAP isBandgapActive() noexcept {
        if (m_ctl2.compare(REFBGACT)) return PMM::BANDGAP::ACTIVE;
        else
            return PMM::BANDGAP::INACTIVE;
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief the active status of the reference generator in the PMM module -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.isRefGenActive() == PMM::BANDGAP::ACTIVE) doSomething(); \endcode
	*@return if the reference generator is active or not (PMM::REFGEN)
	****************************************************************
	*/
    [[nodiscard]] constexpr PMM::REFGEN isRefGenActive() noexcept {
        if (m_ctl2.compare(REFGENACT)) return PMM::REFGEN::ACTIVE;
        else
            return PMM::REFGEN::INACTIVE;
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief returns the active status of the buffered bandgap voltage in the PMM -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.getBufferedBandgapVoltageStatus() == PMM::BANDGAP_STATUS::READY) doSomething(); \endcode
	*@return if the bandgap status is ready or not (PMM::BANDGAP_STATUS)
	****************************************************************
	*/
    [[nodiscard]] constexpr PMM::BANDGAP_STATUS getBufferedBandgapVoltageStatus() noexcept {
        if (m_ctl2.compare(REFBGRDY)) return PMM::BANDGAP_STATUS::READY;
        else
            return PMM::BANDGAP_STATUS::NOTREADY;
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief returns the status of the variable reference voltage in the PMM -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.getVariableReferenceVoltageStatus() == PMM::REFGEN_STATUS::READY) doSomething(); \endcode
	*@return if the variable reference status is ready or not(PMM::REFGEN_STATUS)
	****************************************************************
	*/
    [[nodiscard]] constexpr PMM::REFGEN_STATUS getVariableReferenceVoltageStatus() noexcept {
        if (m_ctl2.compare(REFGENRDY)) return PMM::REFGEN_STATUS::READY;
        else
            return PMM::REFGEN_STATUS::NOTREADY;
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Disables the internal temperature sensor to save power consumption -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableTempSensor(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableTempSensor() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl2.clear(TSENSOREN);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Enables the internal temperature sensor to save power consumption -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableTempSensor(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableTempSensor() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl2.set(TSENSOREN);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Disables the external reference output -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableExternalReference(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableExternalReference() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl2.clear(EXTREFEN);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Enables the external reference output -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableExternalReference(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableExternalReference() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl2.set(EXTREFEN);
        m_ctl0pwd.override(0x00);
    }


    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Disables the internal reference output -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableInternalReference(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableInternalReference() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ctl2.clear(INTREFEN);
        m_ctl0pwd.override(0x00);
    }

#if defined(REFVSEL)
    /**
	* @ingroup groupFuncsMSP430FRAMPmm
	****************************************************************
	* @brief Selects reference voltage level -> only available for MSP430FR2xx/4xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.selectVoltageReference(PMM::REF_VOLT_SELECT::V1_5); \endcode
	*
	****************************************************************
	*/
    constexpr void selectVoltageReference(const PMM::REF_VOLT_SELECT sel) noexcept {
        m_ctl2.clear(REFVSEL);
        typedef typename std::underlying_type<PMM::REF_VOLT_SELECT>::type underlying;
        m_ctl2.set(static_cast<underlying>(sel));
    }
#endif
#endif
};
}// namespace MT::MSP430


#elif defined(__MSP430_HAS_PMM__) && defined(__MSP430F5XX_6XX_FAMILY__)

namespace MT::Misc {
enum class PMM_INT : uint16_t {
    SVSM_LOWSIDE_DELY_EXP  = (SVSMLDLYIFG),
    SVM_LOWSIDE            = (SVMLIFG),
    SVM_LOWSIDE_REACHED    = (SVMLVLRIFG),
    SVSM_HIGHSIDE_DELY_EXP = (SVSMHDLYIFG),
    SVM_HIGHSIDE           = (SVMHIFG),
    SVM_HIGHSIDE_REACHED   = (SVMHVLRIFG),
    BOR                    = (PMMBORIFG),
    RST                    = (PMMRSTIFG),
    POR                    = (PMMPORIFG),
    SVS_HIGHSIDE           = (SVSHIFG),
    SVS_LOWSIDE            = (SVSLIFG),
    LPM5                   = (PMMLPM5IFG)
};
template<>
struct enable_Enum_bits<PMM_INT> {
    static constexpr bool enable = true;
};
}// namespace MT::Misc

namespace MT::MSP430::PMM {

/**
* @ingroup groupEnumsMSP430FPmm
****************************************************************
* @brief PMM interrupt types
****************************************************************
*/
using INT = MT::Misc::PMM_INT;

/**
* @ingroup groupEnumsMSP430FPmm
****************************************************************
* @brief core voltage selection -> only available for MSP430F5xx/6xx Family
****************************************************************
*/
enum class COREVOLT : uint16_t {
    LEVEL0 = (PMMCOREV_0),
    LEVEL1 = (PMMCOREV_1),
    LEVEL2 = (PMMCOREV_2),
    LEVEL3 = (PMMCOREV_3)
};
}// namespace MT::MSP430::PMM

namespace MT::MSP430 {
struct Pmm {

  private:
    MT::Universal::Register<&PMMCTL0_L> m_ctl0{};
    MT::Universal::Register<&PMMCTL0_H> m_ctl0pwd{};
    MT::Universal::Register<&PMMIFG>    m_if{};
    MT::Universal::Register<&PM5CTL0>   m_lpm5{};
    MT::Universal::Register<&SVSMHCTL>  m_svsmh{};
    MT::Universal::Register<&SVSMLCTL>  m_svsml{};
    MT::Universal::Register<&SVSMIO>    m_svsmio{};
    MT::Universal::Register<&PMMRIE>    m_ie{};

  public:
    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the voltage supervisor low side -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSVSL(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSVSL() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.set(SVSLE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the voltage supervisor low side -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSVSL(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSVSL() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.clear(SVSLE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the low-side SVM circuitry -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSVML(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSVML() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.set(SVMLE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the low-side SVM circuitry -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSVML(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSVML() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.clear(SVMLE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the voltage supervisor high side -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSVSH(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSVSH() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.set(SVSHE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the voltage supervisor high side -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSVSH(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSVSH() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.clear(SVSHE);
        m_ctl0pwd.override(0x00);
    }


    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the high-side SVM circuitry -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSVMH(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSVMH() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.set(SVMHE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the high-side SVM circuitry -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSVMH(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSVMH() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.clear(SVMHE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the low-side SVS and SVM circuitry -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvsLSvmL(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvsLSvmL() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.set(SVSLE + SVMLE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the low-side SVS and SVM circuitry -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvsLSvmL(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvsLSvmL() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.clear(SVSLE + SVMLE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the high-side SVS and SVM circuitry -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvsHSvmH(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvsHSvmH() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.set(SVSHE + SVMHE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the high-side SVS and SVM circuitry -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvsHSvmH(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvsHSvmH() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.clear(SVSHE + SVMHE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief  enables the POR signal generation when a low-voltage event is registered by the low-side SVS -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvsLReset(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvsLReset() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ie.set(SVSLPE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief  disables the POR signal generation when a low-voltage event is registered by the low-side SVS -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvsLReset(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvsLReset() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ie.clear(SVSLPE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the interrupt generation when a low-voltage event is registered by the low-side SVM -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvmLInterrupt(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvmLInterrupt() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ie.set(SVMLIE);
        m_ctl0pwd.override(0x00);
    }


    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the interrupt generation when a low-voltage event is registered by the low-side SVM -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvmLInterrupt(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvmLInterrupt() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ie.clear(SVMLIE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the POR signal generation when a low-voltage event is registered by the high-side SVS -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvsHReset(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvsHReset() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ie.set(SVSHPE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the POR signal generation when a low-voltage event is registered by the high-side SVS -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvsHReset(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvsHReset() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ie.clear(SVSHPE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief enables the interrupt generation when a low-voltage event is registered by the high-side SVM -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvmHInterrupt(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvmHInterrupt() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ie.set(SVMHIE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables the interrupt generation when a low-voltage event is registered by the high-side SVM -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvmHInterrupt(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvmHInterrupt() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_ie.clear(SVMHIE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief clear all interrupt flags for the PMM
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.clearPMMIFGS(); \endcode
	*
	****************************************************************
	*/
    constexpr void clearPMMIFGS() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_if.override(0);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief  enables supervisor low side in LPM with twake-up-fast from LPM2, LPM3, and LPM4 -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvsLInLPMFastWake(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvsLInLPMFastWake() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.set(SVSLFP + SVSLMD);
        m_svsml.clear(SVSMLACE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief  enables supervisor low side in LPM with twake-up-slow from LPM2, LPM3, and LPM4 -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvsLInLPMSlowWake(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvsLInLPMSlowWake() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.set(SVSLMD);
        m_svsml.clear(SVSLFP + SVSMLACE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief  disables supervisor low side in LPM with twake-up-fast from LPM2, LPM3, and LPM4 -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvsLInLPMFastWake(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvsLInLPMFastWake() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.set(SVSLFP);
        m_svsml.clear(SVSLMD + SVSMLACE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief  disables supervisor low side in LPM with twake-up-slow from LPM2, LPM3, and LPM4 -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvsLInLPMSlowWake(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvsLInLPMSlowWake() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.clear(SVSLFP + SVSMLACE + SVSLMD);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief  Enables supervisor high side in LPM with tpd = 20 s -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvsHInLPMNormPerf(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvsHInLPMNormPerf() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.set(SVSHMD);
        m_svsmh.clear(SVSMHACE + SVSHFP);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief  Enables supervisor high side in LPM with tpd = 2.5 s -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableSvsHInLPMFullPerf(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableSvsHInLPMFullPerf() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.set(SVSHMD + SVSHFP);
        m_svsmh.clear(SVSMHACE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables supervisor high side in LPM with tpd = 20 s -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvsHInLPMNormPerf(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvsHInLPMNormPerf() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.clear(SVSMHACE + SVSHFP + SVSHMD);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief disables supervisor high side in LPM with tpd = 2.5 s -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableSvsHInLPMFullPerf(); \endcode
	*
	****************************************************************
	*/
    constexpr void disableSvsHInLPMFullPerf() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsmh.set(SVSHFP);
        m_svsmh.clear(SVSMHACE + SVSHMD);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief optimized to provide twake-up-fast from LPM2, LPM3, and LPM4 with least power -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.optimizeSvsLInLPMFastWake(); \endcode
	*
	****************************************************************
	*/
    constexpr void optimizeSvsLInLPMFastWake() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.set(SVSLFP + SVSLMD + SVSMLACE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief optimized to provide tpd = 2.5 s in LPM with least power -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.optimizeSvsHInLPMFullPerf (); \endcode
	*
	****************************************************************
	*/
    constexpr void optimizeSvsHInLPMFullPerf() noexcept {
        m_ctl0pwd.override(PMMPW_H);
        m_svsml.set(SVSHMD + SVSHFP + SVSMHACE);
        m_ctl0pwd.override(0x00);
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief Decrease Vcore by one level -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.setVCoreDown(PMM::COREVOLT::LEVEL0) == STATUS::FAIL) doSomething(); \endcode
	*@param lev level to which Vcore needs to be decreased (PMM::COREVOLT)
	*@return the status of the cmoannd execution(STATUS)
	****************************************************************
	*/
    [[nodiscard]] constexpr STATUS setVCoreDown(PMM::COREVOLT lev) noexcept {

        //The code flow for increasing the Vcore has been altered to work around
        //the erratum FLASH37.
        //Please refer to the Errata sheet to know if a specific device is affected
        //DO NOT ALTER THIS FUNCTION

        typedef typename std::underlying_type<PMM::COREVOLT>::type underlying;

        //Open PMM registers for write access
        m_ctl0pwd.override(PMMPW_H);

        //Disable dedicated Interrupts
        //Backup all registers
        const uint16_t PMMRIE_backup = m_ie.get();
        m_ie.clear(SVMHVLRPE | SVSHPE | SVMLVLRPE | SVSLPE | SVMHVLRIE | SVMHIE | SVSMHDLYIE | SVMLVLRIE | SVMLIE | SVSMLDLYIE);

        uint16_t SVSMHCTL_backup = m_svsmh.get();
        uint16_t SVSMLCTL_backup = m_svsml.get();

        m_if.override(0);//Clear flags
        //Set SVM highside to new level and check if a VCore increase is possible

        m_svsmh.override(SVMHE | SVSHE | (SVSMHRRL0 * static_cast<underlying>(lev)));

        //Wait until SVM highside is settled
        while (!m_if.compare(SVSMHDLYIFG))
            ;
        m_if.clear(SVSMHDLYIFG);

        //Check if a VCore increase is possible
        if (m_if.compare(SVMHIFG)) {

            m_if.clear(SVSMHDLYIFG);
            m_svsmh.override(SVSMHCTL_backup);

            //Wait until SVM highside is settled
            while (!m_if.compare(SVSMHDLYIFG) == 0)
                ;

            m_if.clear(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG);
            //Restore PMM interrupt enable register
            m_ie.override(PMMRIE_backup);

            m_ctl0pwd.override(0x00);
            return STATUS::FAIL;
        }

        //Set also SVS highside to new level
        //Vcc is high enough for a Vcore increase
        m_svsmh.override(SVSMHRRL0 * static_cast<underlying>(lev));

        //Wait until SVM highside is settled
        while (!m_if.compare(SVSMHDLYIFG))
            ;
        m_if.clear(SVSMHDLYIFG);

        m_ctl0.override(PMMCOREV0 * static_cast<underlying>(lev));

        //Set SVM, SVS low side to new level
        m_svsml.override(SVMLE | (SVSMLRRL0 * static_cast<underlying>(lev)) | SVSLE | (SVSLRVL0 * static_cast<underlying>(lev)));

        //Wait until SVM highside is settled
        while (!m_if.compare(SVSMLDLYIFG))
            ;
        m_if.clear(SVSMLDLYIFG);

        //Restore Low side settings
        //Clear all other bits _except_ level settings
        m_svsml.clear(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

        //Clear level settings in the backup register,keep all other bits
        SVSMLCTL_backup &= ~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

        //Restore low-side SVS monitor settings
        m_svsml.override(SVSMLCTL_backup);

        //Restore High side settings
        //Clear all other bits except level settings
        m_svsmh.clear(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

        //Clear level settings in the backup register,keep all other bits
        SVSMHCTL_backup &= ~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);
        m_svsmh.set(SVSMHCTL_backup);//Restore backup

        //Wait until high side, low side settled
        while ((!m_if.compare(SVSMLDLYIFG)) || (!m_if.compare(SVSMHDLYIFG)))
            ;
        m_if.clear(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG);
        m_ie.override(PMMRIE_backup);
        m_ctl0pwd.override(0x00);
        return STATUS::SUCCESS;
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief Increase Vcore by one level -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.setVCoreUp(PMM::COREVOLT::LEVEL0) == STATUS::FAIL) doSomething(); \endcode
	*@param lev level to which Vcore needs to be increased (PMM::COREVOLT)
	*@return the status of the cmoannd execution(STATUS)
	****************************************************************
	*/
    [[nodiscard]] constexpr STATUS setVCoreUp(PMM::COREVOLT lev) noexcept {

        //The code flow for increasing the Vcore has been altered to work around
        //the erratum FLASH37.
        //Please refer to the Errata sheet to know if a specific device is affected
        //DO NOT ALTER THIS FUNCTION

        typedef typename std::underlying_type<PMM::COREVOLT>::type underlying;

        //Open PMM registers for write access
        m_ctl0pwd.override(PMMPW_H);

        //Disable dedicated Interrupts
        //Backup all registers
        const uint16_t PMMRIE_backup = m_ie.get();
        m_ie.clear(SVMHVLRPE | SVSHPE | SVMLVLRPE | SVSLPE | SVMHVLRIE | SVMHIE | SVSMHDLYIE | SVMLVLRIE | SVMLIE | SVSMLDLYIE);

        uint16_t SVSMHCTL_backup = m_svsmh.get();
        uint16_t SVSMLCTL_backup = m_svsml.get();

        m_if.clear(SVMHIFG | SVSMHDLYIFG | SVMLIFG | SVSMLDLYIFG);//Clear flags

        //Set SVM, SVS high & low side to new settings in normal mode
        m_svsmh.override(SVMHE | (SVSMHRRL0 * static_cast<underlying>(lev)) | SVSHE | (SVSHRVL0 * static_cast<underlying>(lev)));
        m_svsml.override(SVMLE | (SVSMLRRL0 * static_cast<underlying>(lev)) | SVSLE | (SVSLRVL0 * static_cast<underlying>(lev)));

        while ((!m_if.compare(SVSMHDLYIFG)) || (!m_if.compare(SVSMLDLYIFG)))
            ;
        m_if.clear(SVSMHDLYIFG + SVSMLDLYIFG);

        //Set VCore to new level
        m_ctl0.override(PMMCOREV0 * static_cast<underlying>(lev));

        //Restore Low side settings
        //Clear all other bits _except_ level settings
        m_svsml.clear(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

        //Clear level settings in the backup register,keep all other bits
        SVSMLCTL_backup &= ~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

        //Restore low-side SVS monitor settings
        m_svsml.set(SVSMLCTL_backup);

        //Restore High side settings
        //Clear all other bits except level settings
        m_svsmh.clear(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

        //Clear level settings in the backup register,keep all other bits
        SVSMHCTL_backup &= ~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);
        m_svsmh.set(SVSMHCTL_backup);//Restore backup


        //Wait until high side, low side settled
        while ((!m_if.compare(SVSMLDLYIFG)) || (!m_if.compare(SVSMHDLYIFG)))
            ;

        m_if.clear(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG | SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG);
        m_ie.override(PMMRIE_backup);
        m_ctl0pwd.override(0x00);
        return STATUS::SUCCESS;
    }

    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief Increase Vcore by one level -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.setVCore(PMM::COREVOLT::LEVEL0) == STATUS::FAIL) doSomething(); \endcode
	*@param lev level to which Vcore needs to be decreased/increased (PMM::COREVOLT)
	*@return the status of the cmoannd execution(STATUS)
	****************************************************************
	*/
    [[nodiscard]] STATUS setVCore(PMM::COREVOLT lev) noexcept {

        STATUS status = STATUS::SUCCESS;

        typedef typename std::underlying_type<PMM::COREVOLT>::type underlying;

        uint16_t level = static_cast<underlying>(lev);

        //Set Mask for Max. level
        level &= PMMCOREV_3;

        //Get actual VCore
        uint16_t actlevel = (m_ctl0.get() & PMMCOREV_3);

        //Disable interrupts because certain peripherals will not
        //work during VCORE change
        const uint16_t interruptState = __get_interrupt_state();
        __disable_interrupt();
        __no_operation();

        //step by step increase or decrease
        while ((level != actlevel) && (status == STATUS::SUCCESS)) {
            if (level > actlevel) {
                status = setVCoreUp(static_cast<PMM::COREVOLT>(++actlevel));
            } else {
                status = setVCoreDown(static_cast<PMM::COREVOLT>(--actlevel));
            }
        }

        //Re-enable interrupt state to whatever it was before
        if (interruptState & GIE) {
            __enable_interrupt();
        }

        return status;
    }


    /**
	* @ingroup groupFuncsMSP430FPmm
	****************************************************************
	* @brief compares the given pins with the interrupt flags set in the hw register -> only available for MSP430F5xx/6xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  if(pmm.getInterruptStatus(PMM::INT::BOR | PMM::INT::POR) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
	*@tparam BIT use enumeration PMM::INT
	*@return if all the given bits are set or not (INT_MASK_MATCH)
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    [[nodiscard]] constexpr INT_MASK_MATCH getInterruptStatus(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::PMM::INT, BIT>(), "input must be PMM::INT enum");
        if (m_if.compare(bit)) return INT_MASK_MATCH::TRUE;
        else
            return INT_MASK_MATCH::FALSE;
    }
};
}// namespace MT::MSP430

#elif defined(__MSP430_HAS_PMM__) && defined(__MSP430_HAS_MSP430I_CPU__)

namespace MT::Misc {
enum class PMM_INT : uint16_t {
    VMON  = (VMONIE),
    LPM45 = (LPM45IFG)
};
template<>
struct enable_Enum_bits<PMM_INT> {
    static constexpr bool enable = true;
};
}// namespace MT::Misc


namespace MT::MSP430::PMM {

/**
* @ingroup groupEnumsMSP430IPmm
****************************************************************
* @brief PMM interrupt types
****************************************************************
*/
using INT = MT::Misc::PMM_INT;

/**
* @ingroup groupEnumsMSP430IPmm
****************************************************************
* @brief voltage monitor -> only available for MSP430i2xx Family
****************************************************************
*/
enum class VOLT_MONITOR : uint16_t {
    DISABLE       = (VMONLVL_0),
    DVCC_2350MV   = (VMONLVL_1),
    DVCC_2650MV   = (VMONLVL_2),
    DVCC_2850MV   = (VMONLVL_3),
    VMONIN_1160MV = (VMONLVL_7)
};

/**
* @ingroup groupEnumsMSP430IPmm
****************************************************************
* @brief voltage monitor -> only available for MSP430i2xx Family
****************************************************************
*/
enum class REGULATOR : uint8_t {
    ON  = (0x00),
    OFF = (0x10)
};
}// namespace MT::MSP430::PMM

namespace MT::MSP430 {

struct Pmm {

  private:
    MT::Universal::Register<&LPM45CTL> m_lpm45{};
    MT::Universal::Register<&VMONCTL>  m_vmon{};
    MT::Universal::Register<&REFCAL0>  m_rcal0{};
    MT::Universal::Register<&REFCAL1>  m_rcal1{};

  public:
    /**
	* @ingroup groupFuncsMSP430IPmm
	****************************************************************
	* @brief sets up the voltage monitor -> only available for MSP430i2xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.setupVoltageMonitor(PMM::VOLT_MONITOR::DVCC_2350MV); \endcode
	*@param mon new voltage monitor level
	****************************************************************
	*/
    constexpr void setupVoltageMonitor(const PMM::VOLT_MONITOR mon) noexcept {
        uint8_t currentStatus = m_vmon.get();
        currentStatus &= ~(0x07);
        currentStatus |= static_cast<uint8_t>(mon);
        m_vmon.override(currentStatus);
    }

    /**
	* @ingroup groupFuncsMSP430IPmm
	****************************************************************
	* @brief  sets up the calibration of the internal reference -> only available for MSP430i2xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.calibrateReference(); \endcode
	*
	****************************************************************
	*/
    constexpr void calibrateReference() noexcept {
        m_rcal0.override(TLV_START + TLV_CAL_REFCAL0);
        m_rcal1.override(TLV_START + TLV_CAL_REFCAL1);
    }

    /**
	* @ingroup groupFuncsMSP430IPmm
	****************************************************************
	* @brief sets the status of the PMM regulator -> only available for MSP430i2xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.setRegulatorStatus(PMM::REGULATOR::ON); \endcode
	*@param reg regulator on or off
	****************************************************************
	*/
    constexpr void setRegulatorStatus(const PMM::REGULATOR reg) noexcept {
        uint8_t currentStatus = m_lpm45.get();
        currentStatus &= ~(PMMREGOFF);
        currentStatus |= static_cast<uint8_t>(reg);
        m_lpm45.override(currentStatus);
    }

    /**
	* @ingroup groupFuncsMSP430IPmm
	****************************************************************
	* @brief  unlocks the IO -> only available for MSP430i2xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.unlockIOConfiguration(); \endcode
	*
	****************************************************************
	*/
    constexpr void unlockIOConfiguration() noexcept {
        m_lpm45.clear(LOCKLPM45);
    }

    /**
	* @ingroup groupFuncsMSP430IPmm
	****************************************************************
	* @brief  enables interrupts -> only available for MSP430i2xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.enableInterrupt(PMM::INT::LPM45); \endcode
	*
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void enableInterrupt(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::PMM::INT, BIT>(), "input must be PMM::INT enum");
        m_vmon.set(bit);
    }

    /**
	* @ingroup groupFuncsMSP430IPmm
	****************************************************************
	* @brief  disables interrupts -> only available for MSP430i2xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableInterrupt(PMM::INT::LPM45); \endcode
	*@tparam BIT use enumeration PMM::INT
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void disableInterrupt(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::PMM::INT, BIT>(), "input must be PMM::INT enum");
        m_vmon.clear(bit);
    }


    /**
	* @ingroup groupFuncsMSP430IPmm
	****************************************************************
	* @brief  disables interrupts -> only available for MSP430i2xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableInterrupt(PMM::INT::LPM45); \endcode
	*@tparam BIT use enumeration PMM::INT
	*@return if all the given bits are set or not (INT_MASK_MATCH)
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr INT_MASK_MATCH disableInterrupt(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::PMM::INT, BIT>(), "input must be PMM::INT enum");

        const BIT     sum  = MT::Details::orSum(bit);
        const uint8_t mask = static_cast<uint8_t>(sum);

        if ((mask & VMONIE) && (VMONCTL & VMONIFG)) return INT_MASK_MATCH::TRUE;
        else if (mask & LPM45IFG)
            return INT_MASK_MATCH::TRUE;

        return INT_MASK_MATCH::FALSE;
    }

    /**
	* @ingroup groupFuncsMSP430IPmm
	****************************************************************
	* @brief  disables interrupts -> only available for MSP430i2xx Family
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  Pmm pmm{};
	*  pmm.disableInterrupt(PMM::INT::LPM45); \endcode
	*@tparam BIT use enumeration PMM::INT
	****************************************************************
	*/
    template<typename BIT, typename = std::enable_if_t<MT::Misc::enable_Enum_bits<BIT>::enable, BIT>>
    constexpr void clearInterrupt(const BIT &bit) noexcept {
        static_assert(MT::Misc::Meta::compareBareType<MT::MSP430::PMM::INT, BIT>(), "input must be PMM::INT enum");
        const BIT     sum  = MT::Details::orSum(bit);
        const uint8_t mask = static_cast<uint8_t>(sum);
        m_lpm45.clear(mask);
    }
};
}// namespace MT::MSP430

#endif
#endif
#endif
#endif /* MICROTRAIT_MSP430_PMM_PMM_HPP_ */

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



\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupFuncsMSP430Pmm Functions
*  @ingroup groupMSP430Pmm
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430Pmm Enums
*  @ingroup groupMSP430Pmm
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_PMM_PMM_HPP_
#define MICROTRAIT_MSP430_PMM_PMM_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Register.hpp"
#include <msp430.h>
#include <utility>
#include <type_traits>


namespace MT {
namespace Misc {

#ifdef __MSP430_HAS_PMM_FRAM__
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
#endif

#ifdef __MSP430_HAS_PMM_FR5xx__
    enum class PMM_INT : uint16_t {
        BOR  = (PMMBORIFG),
        RST  = (PMMRSTIFG),
        POR  = (PMMPORIFG),
        SVSH = (SVSHIFG),
        SVSH = (SVSLIFG),
        LPM5 = (PMMLPM5IFG),
        ALL  = (0xB7)
    };
    template<>
    struct enable_Enum_bits<PMM_INT> {
        static constexpr bool enable = true;
    };
#endif

#ifdef __MSP430F5XX_6XX_FAMILY__
#ifdef __MSP430_HAS_PMM__
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
#endif
#endif

#ifdef __MSP430_HAS_MSP430I_CPU__
#ifdef __MSP430_HAS_PMM__
    enum class PMM_INT : uint16_t {
        VMON  = (VMONIE),
        LPM45 = (LPM45IFG)
    };
    template<>
    struct enable_Enum_bits<PMM_INT> {
        static constexpr bool enable = true;
    };
#endif
#endif

}// namespace Misc

namespace MSP430 {
    namespace PMM {

        /**
		* @ingroup groupEnumsMSP430Pmm
		****************************************************************
		* @brief PMM interrupt types
		****************************************************************
		*/
        using INT = MT::Misc::SFR_INT;

#ifdef __MSP430FR2XX_4XX_FAMILY__
#ifdef __MSP430_HAS_PMM_FRAM__
        /**
		* @ingroup groupEnumsMSP430Pmm
		****************************************************************
		* @brief Bandgap mode
		****************************************************************
		*/
        enum class BANDGAP_MODE : uint16_t {
            STATIC = (0x0),
            SAMPLE = (BGMODE)
        };

        /**
		* @ingroup groupEnumsMSP430Pmm
		****************************************************************
		* @brief Bandgap active or not
		****************************************************************
		*/
        enum class BANDGAP : uint16_t {
            INACTIVE = (0x0),
            ACTIVE   = (REFBGACT)
        };

        /**
		* @ingroup groupEnumsMSP430Pmm
		****************************************************************
		* @brief Reference generator active or not
		****************************************************************
		*/
        enum class REFGEN : uint16_t {
            INACTIVE = (0x0),
            ACTIVE   = (REFGENACT)
        };

        /**
		* @ingroup groupEnumsMSP430Pmm
		****************************************************************
		* @brief Bandgap status
		****************************************************************
		*/
        enum class BANDGAP_STATUS : uint16_t {
            NOTREADY = (0x0),
            READY    = (REFBGRDY)
        };

        /**
		* @ingroup groupEnumsMSP430Pmm
		****************************************************************
		* @brief reference generator status
		****************************************************************
		*/
        enum class REFGEN_STATUS : uint16_t {
            NOTREADY = (0x0),
            READY    = (REFGENRDY)
        };

        /**
		* @ingroup groupEnumsMSP430Pmm
		****************************************************************
		* @brief reference voltage selection
		****************************************************************
		*/
    /*    enum class REF_VOLT_SELECT : uint16_t {
            V1_5 = (REFVSEL_0),
            V2_0 = (REFVSEL_1),
            V2_5 = (REFVSEL_2)
        };*/
#endif
#endif

    }// namespace PMM

    struct Pmm {

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


    };


}// namespace MSP430
}// namespace MT

#endif
#endif /* MICROTRAIT_MSP430_PMM_PMM_HPP_ */

#ifndef MICROTRAIT_MSP430_SFR_SFR_HPP_
#define MICROTRAIT_MSP430_SFR_SFR_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Register.hpp"
#include <msp430.h>
#include <utility>
#include <type_traits>


enum class SFR_INT : uint16_t {
    JTAG_OUTBOX             = (JMBOUTIE),
    JTAG_INBOX              = (JMBINIE),
    NMI_PIN                 = (NMIIE),
    VACANT_MEMORY_ACCESS    = (VMAIE),
    OSCILLATOR_FAULT        = (OFIE),
    WATCHDOG_INTERVAL_TIMER = (WDTIE)
};
ENABLE_ENUM_BITS(SFR_INT);

namespace MT {
namespace MSP430 {
    namespace SFR {

        enum class RST_RESISTOR : uint16_t {
            DISABLE  = (!(SYSRSTRE + SYSRSTUP)),
            PULLUP   = (SYSRSTRE + SYSRSTUP),
            PULLDOWN = (SYSRSTRE),
        };

        enum class NMI_EDGE : uint16_t {
            RISING  = (!(SYSNMIIES)),
            FALLING = (SYSNMIIES)
        };

        enum class RST_FUNC : uint16_t {
            RESET = (!(SYSNMI)),
            NMI   = (SYSNMI)
        };

    }// namespace SFR

#ifdef __MSP430_HAS_SFR__

    struct Sfr {

      private:
        MT::Universal::Register<&SFRIE1>  m_ie{};
        MT::Universal::Register<&SFRIFG1> m_if{};
        MT::Universal::Register<&SFRRPCR> m_reset{};

      public:
        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void enableInterrupt(const BIT &bit, const BITS &... bits) noexcept {
            static_assert(std::is_same<SFR_INT, BIT>::value, "input must be SFR_INT enum");
            m_ie.set(bit, bits...);
        }

        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void disableInterrupt(const BIT &bit, const BITS &... bits) noexcept {
            static_assert(std::is_same<SFR_INT, BIT>::value, "input must be SFR_INT enum");
            m_ie.clear(bit, bits...);
        }


        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        [[nodiscard]] constexpr INT_FLAG getInterruptStatus(const BIT &bit, const BITS &... bits) noexcept {
            static_assert(std::is_same<SFR_INT, BIT>::value, "input must be SFR_INT enum");
            if (m_if.compare(bit, bits...)) return INT_FLAG::TRUE;
            else
                return INT_FLAG::FALSE;
        }

        template<typename BIT, typename = typename std::enable_if<enable_Enum_bits<BIT>::enable, BIT>::type, typename... BITS>
        constexpr void clearInterruptStatus(const BIT &bit, const BITS &... bits) noexcept {
            static_assert(std::is_same<SFR_INT, BIT>::value, "input must be SFR_INT enum");
            m_if.clear(bit, bits...);
        }

        constexpr void setResetPinPullResistor(const SFR::RST_RESISTOR rst) noexcept {
            m_reset.clear(SYSRSTRE + SYSRSTUP);
            m_reset.set(static_cast<uint16_t>(rst));
        }

        constexpr void setNMIEdge(const SFR::NMI_EDGE edge) noexcept {
            m_reset.clear(SYSNMIIES);
            m_reset.set(static_cast<uint16_t>(edge));
        }

        constexpr void setResetNMIPinFunction(const SFR::RST_FUNC func) noexcept {
            m_reset.clear(SYSNMI);
            m_reset.set(static_cast<uint16_t>(func));
        }
    };

#endif


}// namespace MSP430
}// namespace MT

#endif

#endif /* MICROTRAIT_MSP430_SFR_SFR_HPP_ */

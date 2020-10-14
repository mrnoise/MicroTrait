#ifndef MICROTRAIT_MSP430_WDT_WDTA_HPP_
#define MICROTRAIT_MSP430_WDT_WDTA_HPP_

#include "MicroTrait/MSP430/Settings.hpp"
#include <MicroTrait/Universal/Register.hpp>
#include <msp430.h>
#include <utility>


namespace MT {
namespace MSP430 {
    namespace WDT {

        enum class CLOCKSOURCE : uint16_t {
            SMCLK  = (WDTSSEL_0),
            ACLK   = (WDTSSEL_1),
            VLOCLK = (WDTSSEL_2),
            XCLK   = (WDTSSEL_3)
        };

        enum class CLOCKDIVIDER : uint16_t {
            DIV2G    = (WDTIS_0),
            DIV128M  = (WDTIS_1),
            DIV8192K = (WDTIS_2),
            DIV512K  = (WDTIS_3),
            DIV32K   = (WDTIS_4),
            DIV8192  = (WDTIS_5),
            DIV512   = (WDTIS_6),
            DIV64    = (WDTIS_7)
        };


#ifdef __MSP430_HAS_WDT_A__

        struct WdtA {

          private:
            MT::Universal::Register<&WDTCTL> m_ctl{};

          public:
            constexpr void hold() noexcept {
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                const auto state = ((m_ctl.get() & 0x00FF) | WDTHOLD);
                m_ctl.override(WDTPW + state);
#else
                m_ctl.override(WDTPW | WDTHOLD);
#endif
            }

            constexpr void start() noexcept {
                const auto state = ((m_ctl.get() & 0x00FF) & ~(WDTHOLD));
                m_ctl.override(WDTPW + state);
            }

            constexpr void resetTimer() noexcept {
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
                const auto state = ((m_ctl.get() & 0x00FF) | WDTCNTCL);
                m_ctl.override(WDTPW + state);
#else
                m_ctl.override(WDTPW | WDTCNTCL);
#endif
            }

            constexpr void initWatchdogTimer(const CLOCKSOURCE src, const CLOCKDIVIDER div) noexcept {
                m_ctl.override(WDTPW | WDTCNTCL | WDTHOLD | (static_cast<uint16_t>(src)) | (static_cast<uint16_t>(div)));
            }

            constexpr void initIntervalTimer(const CLOCKSOURCE src, const CLOCKDIVIDER div) noexcept {
                m_ctl.override(WDTPW | WDTCNTCL | WDTHOLD | WDTTMSEL | (static_cast<uint16_t>(src)) | (static_cast<uint16_t>(div)));
            }

#ifndef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
            constexpr void startWatchdogTimer(const CLOCKSOURCE src, const CLOCKDIVIDER div) noexcept {
                m_ctl.override(WDTPW | WDTCNTCL | WDTTMSEL | (static_cast<uint16_t>(src)) | (static_cast<uint16_t>(div)));
            }

            constexpr void startIntervalTimer(const CLOCKSOURCE src, const CLOCKDIVIDER div) noexcept {
                m_ctl.override(WDTPW | WDTCNTCL | WDTTMSEL | (static_cast<uint16_t>(src)) | (static_cast<uint16_t>(div)));
            }
#endif
        };

#endif


    }// namespace WDT
}// namespace MSP430
}// namespace MT


#endif /* MICROTRAIT_MSP430_WDT_WDTA_HPP_ */

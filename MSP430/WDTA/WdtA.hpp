/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430WdtA WDT A
 *  @ingroup groupMSP430
* @brief functions for Watchdog A register access for TIs MSP430 -> Ti Driverlib equivalent naming
*
* @details
* Usage: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
    WdtA wdt{};
    wdt.initIntervalTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K);
    wdt.start();
#else
    WdtA wdt{};
    wdt.startIntervalTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K);
#endif

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


/** @defgroup groupFuncsMSP430WdtA Functions
*  @ingroup groupMSP430WdtA
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430WdtA Enums
*  @ingroup groupMSP430WdtA
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_WDT_WDTA_HPP_
#define MICROTRAIT_MSP430_WDT_WDTA_HPP_

#include "MicroTrait/MSP430/Settings.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Register.hpp"
#include <msp430.h>
#include <utility>

namespace MT::MSP430::WDTA {

#if defined(__MSP430_HAS_WDT_A__) || defined(__MSP430_HAS_WDT__)

/**
* @ingroup groupEnumsMSP430WdtA
****************************************************************
* @brief Clocksource for the Watchdog Timer
****************************************************************
*/
enum class CLOCKSOURCE : uint16_t {
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    SMCLK  = (WDTSSEL_0),
    ACLK   = (WDTSSEL_1),
    VLOCLK = (WDTSSEL_2),
    XCLK   = (WDTSSEL_3)
#else
    SMCLK   = (0x0000),
    ACLK    = (WDTSSEL)
#endif
};

/**
* @ingroup groupEnumsMSP430WdtA
****************************************************************
* @brief Clockdivider for the Watchdog Timer
****************************************************************
*/
enum class CLOCKDIVIDER : uint16_t {
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    DIV2G    = (WDTIS_0),
    DIV128M  = (WDTIS_1),
    DIV8192K = (WDTIS_2),
    DIV512K  = (WDTIS_3),
    DIV32K   = (WDTIS_4),
    DIV8192  = (WDTIS_5),
    DIV512   = (WDTIS_6),
    DIV64    = (WDTIS_7)
#else
    DIV32K  = (0x0000),
    DIV8192 = (WDTIS0),
    DIV512  = (WDTIS1),
    DIV64   = (WDTIS0 | WDTIS1)
#endif
};
}

namespace MT::MSP430 {
struct WdtA {

  private:
    MT::Universal::Register<&WDTCTL> m_ctl{};

  public:
    /**
	* @ingroup groupFuncsMSP430WdtA
	****************************************************************
	* @brief stops the watchdog timer from running
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  WdtA wdt{};
	*  wdt.hold(); \endcode
	*
	****************************************************************
	*/
    constexpr void hold() noexcept {
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
        const auto state = ((m_ctl.get() & 0x00FF) | WDTHOLD);
        m_ctl.override(WDTPW + state);
#else
        m_ctl.override(WDTPW | WDTHOLD);
#endif
    }

    /**
	* @ingroup groupFuncsMSP430WdtA
	****************************************************************
	* @brief starts the Watchdog Timer
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  WdtA wdt{};
	*  wdt.start(); \endcode
	*
	****************************************************************
	*/
    constexpr void start() noexcept {
        const auto state = ((m_ctl.get() & 0x00FF) & ~(WDTHOLD));
        m_ctl.override(WDTPW + state);
    }

    /**
	* @ingroup groupFuncsMSP430WdtA
	****************************************************************
	* @brief resets the watchdog timer to 0x0000
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  WdtA wdt{};
	*  wdt.resetTimer(); \endcode
	*
	****************************************************************
	*/
    constexpr void resetTimer() noexcept {
#ifdef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
        const auto state = ((m_ctl.get() & 0x00FF) | WDTCNTCL);
        m_ctl.override(WDTPW + state);
#else
        m_ctl.override(WDTPW | WDTCNTCL);
#endif
    }

    /**
	* @ingroup groupFuncsMSP430WdtA
	****************************************************************
	* @brief sets the watchdog timer in watchdog mode, which will cause a PUC when the timer overflows
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  WdtA wdt{};
	*  wdt.initWatchdogTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K);
	*  wdt.start();\endcode
	*@param src the clocksource (WDTA::CLOCKSOURCE)
	*@param div the clockdivider (WDTA::CLOCKDIVIDER)
	****************************************************************
	*/
    constexpr void initWatchdogTimer(const WDTA::CLOCKSOURCE src, const WDTA::CLOCKDIVIDER div) noexcept {
        m_ctl.override(WDTPW | WDTCNTCL | WDTHOLD | (static_cast<uint16_t>(src)) | (static_cast<uint16_t>(div)));
    }

    /**
	* @ingroup groupFuncsMSP430WdtA
	****************************************************************
	* @brief sets the watchdog timer as timer interval mode, which will assert an interrupt without causing a PUC
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  WdtA wdt{};
	*  wdt.initIntervalTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K);
	*  wdt.start();\endcode
	*@param src the clocksource (WDTA::CLOCKSOURCE)
	*@param div the clockdivider (WDTA::CLOCKDIVIDER)
	****************************************************************
	*/
    constexpr void initIntervalTimer(const WDTA::CLOCKSOURCE src, const WDTA::CLOCKDIVIDER div) noexcept {
        m_ctl.override(WDTPW | WDTCNTCL | WDTHOLD | WDTTMSEL | (static_cast<uint16_t>(src)) | (static_cast<uint16_t>(div)));
    }

#ifndef MT_MSP430_USE_DRIVERLIB_COMPATIBILITY
    /**
	* @ingroup groupFuncsMSP430WdtA
	****************************************************************
	* @brief sets and starts the watchdog timer in watchdog mode, which will cause a PUC when the timer overflows
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  WdtA wdt{};
	*  wdt.startWatchdogTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K);	\endcode
	*@param src the clocksource (WDTA::CLOCKSOURCE)
	*@param div the clockdivider (WDTA::CLOCKDIVIDER)
	****************************************************************
	*/
    constexpr void startWatchdogTimer(const WDTA::CLOCKSOURCE src, const WDTA::CLOCKDIVIDER div) noexcept {
        m_ctl.override(WDTPW | WDTCNTCL | WDTTMSEL | (static_cast<uint16_t>(src)) | (static_cast<uint16_t>(div)));
    }

    /**
	* @ingroup groupFuncsMSP430WdtA
	****************************************************************
	* @brief sets and starts the watchdog timer as timer interval mode, which will assert an interrupt without causing a PUC
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  WdtA wdt{};
	*  wdt.startIntervalTimer(WDTA::CLOCKSOURCE::SMCLK, WDTA::CLOCKDIVIDER::DIV32K); \endcode
	*@param src the clocksource (WDTA::CLOCKSOURCE)
	*@param div the clockdivider (WDTA::CLOCKDIVIDER)
	****************************************************************
	*/
    constexpr void startIntervalTimer(const WDTA::CLOCKSOURCE src, const WDTA::CLOCKDIVIDER div) noexcept {
        m_ctl.override(WDTPW | WDTCNTCL | WDTTMSEL | (static_cast<uint16_t>(src)) | (static_cast<uint16_t>(div)));
    }
#endif
};

#endif
}// namespace MT::MSP430::WDTA


#endif
#endif /* MICROTRAIT_MSP430_WDT_WDTA_HPP_ */

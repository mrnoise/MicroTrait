/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430TimerA Timer A
 *  @ingroup groupMSP430
* @brief functions for Timer A register access for TIs MSP430 -> Ti Driverlib equivalent naming
*
* @details
* Usage: \code {.cpp}

#include "MicroTrait/MT.hpp"

using namespace MT::MSP430;

	TIMERA::TA0 ta0;

	constexpr TIMERA::initContinuous param{
		TIMERA::CLOCKSOURCE::SMCLK,
		TIMERA::CLOCK_DIV::DIV1,
		TIMERA::GLOBAL_INT::DISABLE,
		TIMERA::CLEAR_COUNT_DIR::ENABLE,
		false
	};

	ta0.initContinuousMode(param);

\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupFuncsMSP430TimerA Functions
*  @ingroup groupMSP430TimerA
*  Functions in this module
*/

/** @defgroup groupEnumsMSP430TimerA Enums
*  @ingroup groupMSP430TimerA
*  Enums in this module
*/
#ifndef MICROTRAIT_MSP430_TIMERA_TIMERA_HPP_
#define MICROTRAIT_MSP430_TIMERA_TIMERA_HPP_

#include "MicroTrait/MSP430/Settings.hpp"
#include "MicroTrait/MSP430/Types.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Register.hpp"
#include "MicroTrait/Misc/Details.hpp"
#include <msp430.h>
#include <utility>
#include <type_traits>

//#include "msp430i2021.h"

#if defined(__MSP430_HAS_T0A2__) || defined(__MSP430_HAS_T1A2__) || defined(__MSP430_HAS_T2A2__) || defined(__MSP430_HAS_T3A2__)    \
    || defined(__MSP430_HAS_T0A3__) || defined(__MSP430_HAS_T1A3__) || defined(__MSP430_HAS_T2A3__) || defined(__MSP430_HAS_T3A3__) \
    || defined(__MSP430_HAS_T0A5__) || defined(__MSP430_HAS_T1A5__) || defined(__MSP430_HAS_T2A5__) || defined(__MSP430_HAS_T3A5__) \
    || defined(__MSP430_HAS_T0A7__) || defined(__MSP430_HAS_T1A7__) || defined(__MSP430_HAS_T2A7__) || defined(__MSP430_HAS_T3A7__)

namespace MT::Misc {
enum class TIMERA_INT : uint16_t {
    CAPTURE_OVERFLOW  = (COV),
    CAPTURE_INTERRUPT = (CCIFG)
};
template<>
struct enable_Enum_bits<TIMERA_INT> {
    static constexpr bool enable = true;
};
}// namespace MT::Misc


namespace MT::MSP430::TIMERA {

/**
* @ingroup groupEnumsMSP430Sfr
****************************************************************
* @brief Timer A interrupt types
****************************************************************
*/
using INT = MT::Misc::TIMERA_INT;

/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Clockdivider for Timer A
****************************************************************
*/
enum class CLOCK_DIV : uint16_t {
#if defined(__MSP430_HAS_MSP430I_CPU__)
    DIV1 = (0x00),
    DIV2 = (0x08),
    DIV4 = (0x10),
    DIV8 = (0x18)
#else
    DIV1  = (0x00),
    DIV2  = (0x08),
    DIV3  = (0x02),
    DIV4  = (0x10),
    DIV5  = (0x04),
    DIV6  = (0x05),
    DIV7  = (0x06),
    DIV8  = (0x18),
    DIV10 = (0x0C),
    DIV12 = (0x0D),
    DIV14 = (0x0E),
    DIV16 = (0x0F),
    DIV20 = (0x14),
    DIV24 = (0x15),
    DIV28 = (0x16),
    DIV32 = (0x17),
    DIV40 = (0x1C),
    DIV48 = (0x1D),
    DIV56 = (0x1E),
    DIV64 = (0x1F)
#endif
};

/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Timer mode for Timer A
****************************************************************
*/
enum class MODE : uint16_t {
    STOP       = (MC_0),
    UP         = (MC_1),
    CONTINUOUS = (MC_2),
    UPDOWN     = (MC_3)
};

/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Clears (if enabled)the count direction, the clock divider and the current count for Timer A
****************************************************************
*/
enum class CLEAR_COUNT_DIR : uint16_t {
    ENABLE = (TACLR),
    SKIP   = (0x0000)
};

/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Clocksource for Timer A
****************************************************************
*/
enum class CLOCKSOURCE : uint16_t {
    EXTERNAL          = (TASSEL_0),
    ACLK              = (TASSEL_1),
    SMCLK             = (TASSEL_2),
    EXTERNAL_INVERTED = (TASSEL_3)
};

/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Global interrupt enable for Timer A
****************************************************************
*/
enum class GLOBAL_INT : uint16_t {
    ENABLE  = (TAIE),
    DISABLE = (0x0000)
};

/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Compare interrupt enable for Timer A
****************************************************************
*/
enum class CAPTURE_COMPARE_INT : uint16_t {
    ENABLE  = (CCIE),
    DISABLE = (0x0000)
};


/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Capture input selection for Timer A
****************************************************************
*/
enum class CAPTURE_INPUT : uint16_t {
    CCIXA = (CCIS_0),
    CCIXB = (CCIS_1),
    GND   = (CCIS_2),
    VCC   = (CCIS_3)
};


/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Compare output selection for Timer A
****************************************************************
*/
enum class COMPARE_OUTPUT : uint16_t {
    BITVALUE     = (OUTMOD_0),
    SET          = (OUTMOD_1),
    TOGGLE_RESET = (OUTMOD_2),
    SET_RESET    = (OUTMOD_3),
    TOGGLE       = (OUTMOD_4),
    RESET        = (OUTMOD_5),
    TOGGLE_SET   = (OUTMOD_6),
    RESET_SET    = (OUTMOD_7)
};

/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Capture/compare register for Timer A
****************************************************************
*/
enum class CAPTURE_COMPARE : uint16_t {
    REGISTER0 = (0x02),
    REGISTER1 = (0x04),
    REGISTER2 = (0x06),
#if not defined(__MSP430_HAS_MSP430I_CPU__) && not defined(__MSP430FR2XX_4XX_FAMILY__)
    REGISTER3 = (0x08),
    REGISTER4 = (0x0A),
    REGISTER5 = (0x0C),
    REGISTER6 = (0x0E)
#endif
};


/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Capture mode selection for Timer A
****************************************************************
*/
enum class CAPTURE_MODE : uint16_t {
    OFF                     = (CM_0),
    RISING_EDGE             = (CM_1),
    FALLIG_EDGE             = (CM_2),
    RISING_AND_FALLING_EDGE = (CM_3)
};


/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Capture async/sync selection for Timer A
****************************************************************
*/
enum class CAPTURE : uint16_t {
    ASYNCHRONOUS = (0x0000),
    SYNCHRONOUS  = (SCS)
};


/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Capture/Comapre input read selection for Timer A
****************************************************************
*/
enum class CAPTURE_COMPARE_READ_INPUT : uint16_t {
    SYNCED     = (SCCI),
    NOT_SYNCED = (CCI)
};

/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Capture/Comapre input low or high for Timer A
****************************************************************
*/
enum class CAPTURE_COMPARE_INPUT : uint16_t {
    HIGH = (0x0001),
    LOW  = (0x0000)
};


/**
* @ingroup groupEnumsMSP430TimerA
****************************************************************
* @brief Comapre output bit value low or high for Timer A
****************************************************************
*/
enum class COMPARE_OUT_BIT : uint16_t {
    HIGH = (OUT),
    LOW  = (0x0000)
};


using initContinuous = struct {
    CLOCKSOURCE     src;
    CLOCK_DIV       div;
    GLOBAL_INT      global_int_en;
    CLEAR_COUNT_DIR clearTimer;
    bool            startTimer;
};


using initUp = struct {
    CLOCKSOURCE         src;
    CLOCK_DIV           div;
    uint16_t            timerPeriod;
    GLOBAL_INT          global_int_en;
    CAPTURE_COMPARE_INT ccr_in_en;
    CLEAR_COUNT_DIR     clearTimer;
    bool                startTimer;
};

using initUpDown = initUp;

using initCapture = struct {
    CAPTURE_COMPARE     reg;
    CAPTURE_MODE        mode;
    CAPTURE_INPUT       input;
    CAPTURE             sync;
    CAPTURE_COMPARE_INT int_en;
    COMPARE_OUTPUT      out;
};

using initCompare = struct {
    CAPTURE_COMPARE     reg;
    CAPTURE_COMPARE_INT int_en;
    COMPARE_OUTPUT      out;
    uint16_t            compareValue;
};

using initPWM = struct {
    CLOCKSOURCE     src;
    CLOCK_DIV       div;
    uint16_t        timerPeriod;
    CAPTURE_COMPARE reg;
    COMPARE_OUTPUT  out;
    uint16_t        dutyCycle;
};

}// namespace MT::MSP430::TIMERA

namespace MT::MSP430::TIMERA::Internal {

using namespace MT::Details;

template<volatile auto *CTLREG, volatile auto *COUNTREG, volatile auto *CCTL0REG>
struct Base {

  private:
    MT::Universal::Register<CTLREG>   m_ctl{};
    MT::Universal::Register<COUNTREG> m_count{};
    MT::Universal::Register<CCTL0REG> m_cctl0{};

  public:
    /**
	* @ingroup groupFuncsMSP430TimerA
	****************************************************************
	* @brief Starts Timer_A counter
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  TIMERA::A1 a1{};
	*  a1.startCounter(TIMERA::MODE::UP); \endcode
	*@param mode -> stop,up,continuous,up/down -> use enumeration TIMERA::MODE
	****************************************************************
	*/
    constexpr void startCounter(const TIMERA::MODE mode) noexcept {
        m_ctl.clear(MC_3);
        m_ctl.set(castToUnderlyingType(mode));
    }

    /**
	* @ingroup groupFuncsMSP430TimerA
	****************************************************************
	* @brief Configures Timer_A in continuous mode
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  TIMERA::TA0 ta0;
	*
	* constexpr TIMERA::initContinuous param{
	*	TIMERA::CLOCKSOURCE::SMCLK,
	*	TIMERA::CLOCK_DIV::DIV1,
	*	TIMERA::GLOBAL_INT::DISABLE,
	*	TIMERA::CLEAR_COUNT_DIR::ENABLE,
	*	false
	* };
	*
	* ta0.initContinuousMode(param);; \endcode
	*@param param -> settings for this mode -> use type initContinuous
	****************************************************************
	*/
    constexpr void initContinuousMode(const initContinuous &param) noexcept {
        m_ctl.override(castToUnderlyingType(param.src) + castToUnderlyingType(param.clearTimer) + castToUnderlyingType(param.global_int_en) + ((castToUnderlyingType(param.div) >> 3) << 6));
        if (param.startTimer) m_ctl.set(castToUnderlyingType(MODE::CONTINUOUS));
    }

    /**
   	* @ingroup groupFuncsMSP430TimerA
   	****************************************************************
   	* @brief Configures Timer_A in up mode
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430;
   	*
   	*  TIMERA::TA0 ta0;
   	*
   	* constexpr TIMERA::initContinuous param{
   	*	TIMERA::CLOCKSOURCE::SMCLK,
   	*	TIMERA::CLOCK_DIV::DIV1,
   	*	TIMERA::GLOBAL_INT::DISABLE,
   	*	TIMERA::CLEAR_COUNT_DIR::ENABLE,
   	*	false
   	* };
   	*
   	* ta0.initContinuousMode(param);; \endcode
   	*@param param -> settings for this mode -> use type initUp
   	****************************************************************
   	*/
    constexpr void initUpMode(const initContinuous &param) noexcept {
        m_ctl.override(castToUnderlyingType(param.src) + castToUnderlyingType(param.clearTimer) + castToUnderlyingType(param.global_int_en) + ((castToUnderlyingType(param.div) >> 3) << 6));
        if (param.startTimer) m_ctl.set(castToUnderlyingType(MODE::CONTINUOUS));
    }
};


template<volatile auto *CTLREG, volatile auto *COUNTREG, volatile auto *CCTL0REG, volatile auto *EX0REG>
struct BaseEX0 {

  private:
    MT::Universal::Register<CTLREG>   m_ctl{};
    MT::Universal::Register<COUNTREG> m_count{};
    MT::Universal::Register<CCTL0REG> m_cctl0{};
    MT::Universal::Register<EX0REG>   m_ex0{};

  public:
    constexpr void startCounter(const TIMERA::MODE mode) noexcept {
        m_ctl.clear(MC_3);
        m_ctl.set(castToUnderlyingType(mode));
    }

    constexpr void initContinuousMode(const initContinuous &param) noexcept {
        m_ex0.override((castToUnderlyingType(param.div)) & 0x7000);
        m_ctl.override(castToUnderlyingType(param.src) + castToUnderlyingType(param.clearTimer) + castToUnderlyingType(param.global_int_en) + ((castToUnderlyingType(param.div) >> 3) << 6));
        if (param.startTimer) m_ctl.set(castToUnderlyingType(MODE::CONTINUOUS));
    }
};


template<volatile auto *CTLREG, volatile auto *COUNTREG, volatile auto *CCTL0REG>
struct CCTL0_2 {

  private:
    MT::Universal::Register<CTLREG>   m_ctl{};
    MT::Universal::Register<COUNTREG> m_count{};
    MT::Universal::Register<CCTL0REG> m_cctl0{};

  public:
};


template<volatile auto *TAXCTL, volatile auto *TAXR, volatile auto *TAXCCTL0, volatile auto *TAXEX0>
struct TxA2withEX0 : BaseEX0<TAXCTL, TAXR, TAXCCTL0, TAXEX0> {};

template<volatile auto *TAXCTL, volatile auto *TAXR, volatile auto *TAXCCTL0>
struct TxA2 : Base<TAXCTL, TAXR, TAXCCTL0> {};


}// namespace MT::MSP430::TIMERA::Internal


namespace MT::MSP430::TIMERA {


using TA0 = Internal::TxA2withEX0<&TA0CTL, &TA0R, &TA0CCTL0, &TA0EX0>;

#if not defined(__MSP430_HAS_MSP430I_CPU__)
#if defined(__MSP430_HAS_T0A2__)
#elif defined(__MSP430_HAS_T0A3__)
#elif defined(__MSP430_HAS_T0A5__)
#elif defined(__MSP430_HAS_T0A7__)
#endif
#else
#if defined(__MSP430_HAS_T0A2__)
#elif defined(__MSP430_HAS_T0A3__)
#endif
#endif


#if not defined(__MSP430_HAS_MSP430I_CPU__)
#if defined(__MSP430_HAS_T1A2__)
#elif defined(__MSP430_HAS_T1A3__)
#elif defined(__MSP430_HAS_T1A5__)
#elif defined(__MSP430_HAS_T1A7__)
#endif
#else
#if defined(__MSP430_HAS_T1A2__)
#elif defined(__MSP430_HAS_T1A3__)
#endif
#endif


#if not defined(__MSP430_HAS_MSP430I_CPU__)
#if defined(__MSP430_HAS_T2A2__)
#elif defined(__MSP430_HAS_T2A3__)
#elif defined(__MSP430_HAS_T2A5__)
#elif defined(__MSP430_HAS_T2A7__)
#endif
#else
#if defined(__MSP430_HAS_T2A2__)
#elif defined(__MSP430_HAS_T2A3__)
#endif
#endif


#if not defined(__MSP430_HAS_MSP430I_CPU__)
#if defined(__MSP430_HAS_T3A2__)
#elif defined(__MSP430_HAS_T3A3__)
#elif defined(__MSP430_HAS_T3A5__)
#elif defined(__MSP430_HAS_T3A7__)
#endif
#else
#if defined(__MSP430_HAS_T3A2__)
#elif defined(__MSP430_HAS_T3A3__)
#endif
#endif

}// namespace MT::MSP430::TIMERA
#endif
#endif
#endif /* MICROTRAIT_MSP430_TIMERA_TIMERA_HPP_ */

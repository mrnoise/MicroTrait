/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430EUSCI_A EUSCI A
 *  @ingroup groupMSP430
* @brief functions for EUSCI A register access for TIs MSP430 -> Ti Driverlib equivalent naming
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


/** @defgroup groupFuncsMSP430UART_EUSCI_A UART Functions
*  @ingroup groupMSP430EUSCI_A
*  Functions in this module for UART mode
*/

/** @defgroup groupEnumsMSP430UART_EUSCI_A UART Enums
*  @ingroup groupMSP430EUSCI_A
*  Enums in this module for UART mode
*/

/** @defgroup groupParamsMSP430UART_EUSCI_A UART Parameter
*  @ingroup groupMSP430EUSCI_A
*  Parameterstructures in this module for UART mode
*/


/** @defgroup groupFuncsMSP430SPI_EUSCI_A SPI Functions
*  @ingroup groupMSP430EUSCI_A
*  Functions in this module for SPI mode
*/

/** @defgroup groupEnumsMSP430SPI_EUSCI_A SPI Enums
*  @ingroup groupMSP430EUSCI_A
*  Enums in this module for SPI mode
*/

/** @defgroup groupParamsMSP430SPI_EUSCI_A SPI Parameter
*  @ingroup groupMSP430EUSCI_A
*  Parameterstructures in this module for SPI mode
*/

#ifndef MICROTRAIT_MSP430_EUSCI_EUSCIA_HPP_
#define MICROTRAIT_MSP430_EUSCI_EUSCIA_HPP_

#include "MicroTrait/MSP430/Settings.hpp"
#include "MicroTrait/MSP430/Types.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Register.hpp"
#include "MicroTrait/MSP430/Types.hpp"
#include <msp430.h>

#if defined(__MSP430_HAS_EUSCI_A0__) || defined(__MSP430_HAS_EUSCI_A1__) || defined(__MSP430_HAS_EUSCI_A2__) || defined(__MSP430_HAS_EUSCI_A3__)

namespace MT::Misc {

enum class EUSCIA_UART_INT : uint16_t {
    RECEIVE           = (UCRXIE),
    TRANSMIT          = (UCTXIE),
    STARTBIT          = (UCSTTIE),
    TRANSMIT_COMPLETE = (UCTXCPTIE)
};
template<>
struct enable_Enum_bits<EUSCIA_UART_INT> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile EUSCIA_UART_INT> {
    static constexpr bool enable = true;
};

enum class EUSCIA_UART_INT_EXT : uint16_t {
    RECEIVE_ERROR = (UCRXEIE),
    BREAKCHAR     = (UCBRKIE)
};
template<>
struct enable_Enum_bits<EUSCIA_UART_INT_EXT> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile EUSCIA_UART_INT_EXT> {
    static constexpr bool enable = true;
};


enum class EUSCIA_UART_STATUS : uint16_t {
    LISTEN_ENABLE    = (UCLISTEN),
    FRAMING_ERROR    = (UCFE),
    OVERRUN_ERROR    = (UCOE),
    PARITY_ERROR     = (UCPE),
    BREAK_DETECT     = (UCBRK),
    RECEIVE_ERROR    = (UCRXERR),
    ADDRESS_RECEIVED = (UCADDR),
    IDLELINE         = (UCIDLE),
    BUSY             = (UCBUSY),

};
template<>
struct enable_Enum_bits<EUSCIA_UART_STATUS> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile EUSCIA_UART_STATUS> {
    static constexpr bool enable = true;
};


enum class EUSCIA_SPI_INT : uint16_t {
    RECEIVE  = (UCRXIE),
    TRANSMIT = (UCTXIE)
};
template<>
struct enable_Enum_bits<EUSCIA_SPI_INT> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile EUSCIA_SPI_INT> {
    static constexpr bool enable = true;
};
}// namespace MT::Misc

namespace MT::MSP430::EUSCIA::UART {

/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief EUSCI A UART interrupt types
****************************************************************
*/
using INT = MT::Misc::EUSCIA_UART_INT;


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief EUSCI A UART interrupt types extentions
****************************************************************
*/
using INT_EXT = MT::Misc::EUSCIA_UART_INT_EXT;


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief EUSCI A UART status types
****************************************************************
*/
using STATUS = MT::Misc::EUSCIA_UART_STATUS;


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief UART Parity options
****************************************************************
*/
enum class PARITY : uint8_t {
    NO   = (0x00),
    ODD  = (0x01),
    EVEN = (0x01)
};


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief UART Endianness -> MSB or LSB First
****************************************************************
*/
enum class ENDIAN : uint16_t {
    LSB_FIRST = (0x0000),
    MSB_FIRST = (UCMSB)
};


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief UART Modes
****************************************************************
*/
enum class MODE : uint16_t {
    UART                         = (UCMODE_0),
    IDLE_LINE_MULTI_PROCESSOR    = (UCMODE_1),
    ADDRESS_BIT_MULTI_PROCESSOR  = (UCMODE_2),
    AUTOMATIC_BAUDRATE_DETECTION = (UCMODE_3)
};


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief UART Clocksources
****************************************************************
*/
enum class CLOCKSOURCE : uint16_t {
#if defined(UCSSEL__UCLK)
    UCLK = (UCSSEL__UCLK),
#endif

#if defined(UCSSEL__SMCLK)
    SMCLK = (UCSSEL__SMCLK),
#endif

#if defined(UCSSEL__ACLK)
    ACLK = (UCSSEL__ACLK),
#endif

#if defined(UCSSEL__MODCLK)
    MODCLK = (UCSSEL__MODCLK)
#endif
};


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief UART Stop Bits options
****************************************************************
*/
enum class STOPBIT : uint16_t {
    ONE = (0x0000),
    TWO = (UCSPB)
};


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief UART Baudrate generation options
****************************************************************
*/
enum class BAUD_GENERATION : uint8_t {
    OVERSAMPLING  = (0x01),
    LOW_FREQUENCY = (0x00)
};


/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief UART Deglitch time in ns options
****************************************************************
*/
enum class DEGLITCH : uint16_t {
    TIME_2NS   = (0x00),
    TIME_50NS  = (UCGLIT0),
    TIME_100NS = (UCGLIT1),
    TIME_200NS = (UCGLIT0 + UCGLIT1)
};


#if defined(__MSP430FR2XX_4XX_FAMILY__)
/**
* @ingroup groupEnumsMSP430UART_EUSCI_A
****************************************************************
* @brief UART Pin remaping options
****************************************************************
*/
enum class REMAP_PINS : uint16_t {
    FALSE = (0x0000),
    TRUE  = (USCIARMP)
};
#endif

/**
* @ingroup groupParamsMSP430UART_EUSCI_A
****************************************************************
* @brief Parameter structure to init UART
****************************************************************
*/
using initParam = struct {
    CLOCKSOURCE     clkSource;
    uint16_t        clockPrescalar;
    uint8_t         firstModReg;
    uint8_t         secondModReg;
    PARITY          parity;
    ENDIAN          msbOrLsbFirst;
    STOPBIT         stopBits;
    MODE            mode;
    BAUD_GENERATION gen;
};

}// namespace MT::MSP430::EUSCIA::UART


namespace MT::MSP430::EUSCIA::SPI {

/**
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief EUSCI A SPI interrupt types
****************************************************************
*/
using INT = MT::Misc::EUSCIA_SPI_INT;


}// namespace MT::MSP430::EUSCIA::SPI


namespace MT::MSP430::EUSCIA::UART::INTERNAL {

template<volatile auto *CTLW0, volatile auto *CTLW1, volatile auto *BRW, volatile auto *MCTLW, volatile auto *STATW, volatile auto *RXBUF, volatile auto *TXBUF, volatile auto *ABCTL, volatile auto *IRCTL, volatile auto *IE, volatile auto *IFG>
struct UART {

  private:
    MT::Universal::Register<CTLW0> m_ctlw0{};
    MT::Universal::Register<CTLW1> m_ctlw1{};
    MT::Universal::Register<BRW>   m_brw{};
    MT::Universal::Register<MCTLW> m_mctlw{};
    MT::Universal::Register<STATW> m_statw{};
    MT::Universal::Register<RXBUF> m_rxbuf{};
    MT::Universal::Register<TXBUF> m_txbuf{};
    MT::Universal::Register<ABCTL> m_abctl{};
    MT::Universal::Register<IRCTL> m_irctl{};
    MT::Universal::Register<IE>    m_ie{};
    MT::Universal::Register<IFG>   m_ifg{};


  public:
    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Starts Timer_A counter
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430;
	*
	*  TIMERA::A0 a0;
	*  a0.startCounter(TIMERA::MODE::UP); \endcode
	*@param mode -> stop,up,continuous,up/down -> use enumeration TIMERA::MODE
	****************************************************************
	*/
};
}// namespace MT::MSP430::EUSCIA::UART::INTERNAL


namespace MT::MSP430::EUSCIA::UART {


#if defined(__MSP430_HAS_EUSCI_A0__)
using A0 = INTERNAL::UART<&UCA0CTLW0, &UCA0CTLW1, &UCA0BRW, &UCA0MCTLW, &UCA0STATW, &UCA0RXBUF, &UCA0TXBUF, &UCA0ABCTL, &UCA0IRCTL, &UCA0IE, &UCA0IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A1__)
using A1 = INTERNAL::UART<&UCA1CTLW0, &UCA1CTLW1, &UCA1BRW, &UCA1MCTLW, &UCA1STATW, &UCA1RXBUF, &UCA1TXBUF, &UCA1ABCTL, &UCA1IRCTL, &UCA1IE, &UCA1IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A2__)
using A2 = INTERNAL::UART<&UCA2CTLW0, &UCA2CTLW1, &UCA2BRW, &UCA2MCTLW, &UCA2STATW, &UCA2RXBUF, &UCA2TXBUF, &UCA2ABCTL, &UCA2IRCTL, &UCA2IE, &UCA2IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A3__)
using A3 = INTERNAL::UART<&UCA3CTLW0, &UCA3CTLW1, &UCA3BRW, &UCA3MCTLW, &UCA3STATW, &UCA3RXBUF, &UCA3TXBUF, &UCA3ABCTL, &UCA3IRCTL, &UCA3IE, &UCA3IFG>;
#endif


}// namespace MT::MSP430::EUSCIA::UART


#endif
#endif
#endif /* MICROTRAIT_MSP430_EUSCI_EUSCIA_HPP_ */

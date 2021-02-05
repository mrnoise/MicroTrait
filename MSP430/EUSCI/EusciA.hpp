/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430EUSCI_A EUSCI A
 *  @ingroup groupMSP430
* @brief functions for EUSCI A register access for TIs MSP430 -> Ti Driverlib equivalent naming
*
* @details
* Usage: \code {.cpp}
*
*#include "MicroTrait/MT.hpp"
*
* using namespace MT::MSP430;
*
*  EUSCIA::UART::initParam param{
*    EUSCIA::UART::CLOCKSOURCE::SMCLK,
*    6,
*    8,
*    17,
*    EUSCIA::UART::PARITY::EVEN,
*    EUSCIA::UART::ENDIAN::MSB_FIRST,
*    EUSCIA::UART::STOPBIT::TWO,
*    EUSCIA::UART::MODE::UART,
*    EUSCIA::UART::BAUD_GENERATION::OVERSAMPLING
*	};
*
* EUSCIA::UART::A0 a0;
* a0.init(param);
*
*
* EUSCIA::SPI::initMasterParam param{
*    EUSCIA::SPI::CLOCKSOURCE::SMCLK,
*    1'000'000,
*    400'000,
*    EUSCIA::SPI::ENDIAN::MSB_FIRST,
*    EUSCIA::SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
*    EUSCIA::SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
*    EUSCIA::SPI::MODE::WITHOUT_CHIPSELECT
* };
*
*  EUSCIA::SPI::A1 a1;
*  a1.initMaster(param);
*
* \endcode
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
    NONE              = (0x0000),
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
    NONE          = (0x0000),
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
    BUSY             = (UCBUSY)
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


enum class EUSCIA_SPI_STATUS : uint16_t {
    LISTEN_ENABLE = (UCLISTEN),
    FRAMING_ERROR = (UCFE),
    OVERRUN_ERROR = (UCOE),
    BUSY          = (UCBUSY)
};
template<>
struct enable_Enum_bits<EUSCIA_SPI_STATUS> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile EUSCIA_SPI_STATUS> {
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
enum class PARITY : uint16_t {
    NO   = (0x00),
    ODD  = (UCPEN),
    EVEN = (UCPEN | UCPAR)
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
* @brief EUSCI A SPI interrupt type
****************************************************************
*/
using INT = MT::Misc::EUSCIA_SPI_INT;


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief EUSCI A SPI status type
****************************************************************
*/
using STATUS = MT::Misc::EUSCIA_SPI_STATUS;


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief SPI Clockphase
****************************************************************
*/
enum class CLOCKPHASE : uint16_t {
    DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT = (0x0000),
    DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT = (UCCKPH)
};

/**
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief SPI Endianness -> MSB or LSB First
****************************************************************
*/
enum class ENDIAN : uint16_t {
    LSB_FIRST = (0x0000),
    MSB_FIRST = (UCMSB)
};


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief SPI Clockphase
****************************************************************
*/
enum class CLOCKPOLARITY : uint16_t {
    INACTIVITY_LOW  = (0x0000),
    INACTIVITY_HIGH = (UCCKPL)
};

/**
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief SPI Clocksources
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
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief SPI Operating modes
****************************************************************
*/
enum class MODE : uint16_t {
    WITHOUT_CHIPSELECT     = (UCMODE_0),
    CHIPSELECT_ACTIVE_HIGH = (UCMODE_1),
    CHIPSELECT_ACTIVE_LOW  = (UCMODE_2)
};


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief SPI 4 Pin functionality
****************************************************************
*/
enum class FUNCIONALITY_4PINS : uint16_t {
    PREVENT_CONFLICTS_WITH_OTHER_MASTERS = (0x0000),
    ENABLE_SIGNAL_FOR_4WIRE_SLAVE        = (UCSTEM)
};


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_A
****************************************************************
* @brief SPI Busy state
****************************************************************
*/
enum class BUSY : uint16_t {
    NO  = (0x0000),
    YES = (UCBUSY)
};


/**
* @ingroup groupParamsMSP430SPI_EUSCI_A
****************************************************************
* @brief Parameter structure to init SPI master
****************************************************************
*/
using initMasterParam = struct {
    CLOCKSOURCE   clkSource;
    uint32_t      clkSourceFrequencyInHz;
    uint32_t      desiredSpiClockInHz;
    ENDIAN        msbOrLsbFirst;
    CLOCKPHASE    clkPhase;
    CLOCKPOLARITY clkPolarity;
    MODE          mode;
};

/**
* @ingroup groupParamsMSP430SPI_EUSCI_A
****************************************************************
* @brief Parameter structure to init SPI slave
****************************************************************
*/
using initSlaveParam = struct {
    ENDIAN        msbOrLsbFirst;
    CLOCKPHASE    clkPhase;
    CLOCKPOLARITY clkPolarity;
    MODE          mode;
};

/**
* @ingroup groupParamsMSP430SPI_EUSCI_A
****************************************************************
* @brief Parameter structure to change SPI master clock
****************************************************************
*/
using changeMasterClockParam = struct {
    uint32_t clkSourceFrequencyInHz;
    uint32_t desiredSpiClockInHz;
};

}// namespace MT::MSP430::EUSCIA::SPI


namespace MT::MSP430::EUSCIA::UART::Internal {

using namespace MT::Misc::Cast;

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
	* @brief initialization routine for the UART block
	* calculate Baudrate -> http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	*  UART::initParam param{
    *    UART::CLOCKSOURCE::SMCLK,
    *    6,
    *    8,
    *    17,
    *    UART::PARITY::EVEN,
    *    UART::ENDIAN::MSB_FIRST,
    *    UART::STOPBIT::TWO,
    *    UART::MODE::UART,
    *    UART::BAUD_GENERATION::OVERSAMPLING
    *	};
	*
	* UART::A0 a0;
    * a0.init(param); \endcode
    *
	*@param param -> parameter to initialize UART -> use parameter struct UART::initParam
	****************************************************************
	*/
    constexpr void init(const initParam &param) noexcept {
        m_ctlw0.override(UCSWRST | toUnderlyingType(param.clkSource) | toUnderlyingType(param.msbOrLsbFirst) | toUnderlyingType(param.stopBits) | toUnderlyingType(param.parity) | toUnderlyingType(param.mode));
        m_brw.override(param.clockPrescalar);
        m_mctlw.override((param.secondModReg << 8) + (param.firstModReg << 4) + toUnderlyingType(param.gen));
    }


    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Transmits a byte from the UART Module
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
    * a0.transmitData(127); \endcode
    *
    *@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@param data -> data byte to transmit
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT>
    constexpr void transmitData(const uint8_t data) noexcept {

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            while (!(m_ifg.get() & UCTXIFG))
                ;
        }

        m_txbuf.override(data);
    }

    /**
   	* @ingroup groupFuncsMSP430UART_EUSCI_A
   	****************************************************************
   	* @brief Receives a byte that has been sent to the UART Module
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIA;
   	*
   	* UART::A0 a0;
	* const uint8_t byte = a0.receiveData(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
   	*@return the byte received
   	****************************************************************
   	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT>
    [[nodiscard]] constexpr uint8_t receiveData() noexcept {

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            while (!(m_ifg.get() & UCRXIFG))
                ;
        }
        return m_rxbuf.get();
    }


    /**
 	* @ingroup groupFuncsMSP430UART_EUSCI_A
 	****************************************************************
 	* @brief Enables individual UART interrupt sources
 	* @details
 	* Usage: \code {.cpp}
 	* using namespace MT::MSP430::EUSCIA;
 	*
 	* UART::A0 a0;
	* a0.enableInterrupt(UART::INT::RECEIVE | UART::INT::TRANSMIT, UART::INT_EXT::RECEIVE_ERROR); \endcode
	*
 	*@param base -> base interrupt sources to enable -> use Enumeration UART::INT
 	*@param ext -> additional interrupt sources to enable -> use Enumeration UART::INT_EXT
 	****************************************************************
 	*/
    constexpr void enableInterrupt(const INT base, const INT_EXT ext) noexcept {
        m_ie.set(base);
        m_ctlw0.set(ext);
    }

    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Disables individual UART interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* a0.disableInterrupt(UART::INT::RECEIVE | UART::INT::TRANSMIT, UART::INT_EXT::RECEIVE_ERROR); \endcode
	*
	*@param base -> base interrupt sources to disable -> use Enumeration UART::INT
	*@param ext -> additional interrupt sources to disable -> use Enumeration UART::INT_EXT
	****************************************************************
	*/
    constexpr void disableInterrupt(const INT base, const INT_EXT ext) noexcept {
        m_ie.clear(base);
        m_ctlw0.clear(ext);
    }

    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Gets the current UART interrupt status
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* if(a0.getInterruptStatus(UART::INT::RECEIVE | UART::INT::TRANSMIT) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
	*
	*@param base -> base interrupt sources to check for status -> use Enumeration UART::INT
	*@return if all the given base flags are set or not (MT::MSP430::MASK_MATCH)
	****************************************************************
	*/
    [[nodiscard]] constexpr MASK_MATCH getInterruptStatus(const INT base) noexcept {
        if (m_ifg.compare(base)) return MASK_MATCH::TRUE;
        else
            return MASK_MATCH::FALSE;
    }


    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Clears UART interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* a0.clearInterrupt(UART::INT::RECEIVE | UART::INT::TRANSMIT); \endcode
	*
	*@param base -> base interrupt sources to clear -> use Enumeration UART::INT
	****************************************************************
	*/
    constexpr void clearInterrupt(const INT base) noexcept {
        m_ifg.clear(base);
    }

    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Enables the UART block
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* a0.enable(); \endcode
	*
	****************************************************************
	*/
    constexpr void enable() noexcept {
        m_ctlw0.clear(UCSWRST);
    }

    /**
  	* @ingroup groupFuncsMSP430UART_EUSCI_A
  	****************************************************************
  	* @brief Disables the UART block
  	* @details
  	* Usage: \code {.cpp}
  	* using namespace MT::MSP430::EUSCIA;
  	*
  	* UART::A0 a0;
  	* a0.disable(); \endcode
  	*
  	****************************************************************
  	*/
    constexpr void disable() noexcept {
        m_ctlw0.set(UCSWRST);
    }


    /**
   	* @ingroup groupFuncsMSP430UART_EUSCI_A
   	****************************************************************
   	* @brief Gets the current SPI status flags
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIA;
   	*
   	* SPI::A1 a1;
   	* if(a1.queryStatusFlags(UART::STATUS::RECEIVE_ERROR | UART::STATUS::FRAMING_ERROR) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
   	*
   	*@param stat -> status flags to check for -> use Enumeration SPI::STATUS
   	*@return if all the given status flags are set or not (MT::MSP430::MASK_MATCH)
   	****************************************************************
   	*/
    [[nodiscard]] constexpr MASK_MATCH queryStatusFlags(const STATUS stat) noexcept {
        if (m_statw.compare(stat)) return MASK_MATCH::TRUE;
        else
            return MASK_MATCH::FALSE;
    }


    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Sets the UART module in dormant mode
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* a0.setDormant(); \endcode
	*
	****************************************************************
	*/
    constexpr void setDormant() noexcept {
        m_ctlw0.set(UCDORM);
    }


    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Re-enables UART module from dormant mode
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* a0.resetDormant(); \endcode
	*
	****************************************************************
	*/
    constexpr void resetDormant() noexcept {
        m_ctlw0.clear(UCDORM);
    }


    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief  Transmits the next byte to be transmitted marked as address
	* 		  depending on selected multiprocessor mode
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* a0.transmitAddress(127); \endcode
	*
	*@param transmitAddr is the next byte to be transmitted
	****************************************************************
	*/
    constexpr void transmitAddress(const uint8_t transmitAddr) noexcept {
        m_ctlw0.set(UCTXADDR);
        m_txbuf.override(transmitAddr);
    }


    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief  Transmits a break with the next write to the transmit buffer
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* a0.transmitBreak(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT>
    constexpr void transmitBreak() noexcept {
        m_ctlw0.set(UCTXBRK);
        if (m_ctlw0.compare(toUnderlyingType(MODE::AUTOMATIC_BAUDRATE_DETECTION))) m_txbuf.override(0x55);
        else
            m_txbuf.override(0x00);

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            while (!(m_ifg.get() & UCTXIFG))
                ;
        }
    }

    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Returns the address of the RX Buffer of the UART for the DMA module
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* const auto rxBufAdr = a0.getReceiveBufferAddress(); \endcode
	*
	*@return Address of RX Buffer
	****************************************************************
	*/
    [[nodiscard]] constexpr auto getReceiveBufferAddress() noexcept {
        return m_rxbuf.getAddress();
    }

    /**
	* @ingroup groupFuncsMSP430UART_EUSCI_A
	****************************************************************
	* @brief Returns the address of the TX Buffer of the UART for the DMA module
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* UART::A0 a0;
	* const auto txBufAdr = a0.getTransmitBufferAddress(); \endcode
	*
	*@return Address of TX Buffer
	****************************************************************
	*/
    [[nodiscard]] constexpr auto getTransmitBufferAddress() noexcept {
        return m_txbuf.getAddress();
    }


    /**
   	* @ingroup groupFuncsMSP430UART_EUSCI_A
   	****************************************************************
   	* @brief  Transmits the next byte to be transmitted marked as address
   	* 		  depending on selected multiprocessor mode
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIA;
   	*
   	* UART::A0 a0;
   	* a0.selectDeglitchTime(UART::DEGLITCH::TIME_200NS); \endcode
   	*
   	*@param time is the selected deglitch time
   	****************************************************************
   	*/
    constexpr void selectDeglitchTime(const DEGLITCH time) noexcept {
        m_ctlw1.override(toUnderlyingType(time));
    }
};


}// namespace MT::MSP430::EUSCIA::UART::Internal


namespace MT::MSP430::EUSCIA::SPI::Internal {

using namespace MT::Misc::Cast;

template<volatile auto *CTLW0, volatile auto *BRW, volatile auto *MCTLW, volatile auto *STATW, volatile auto *RXBUF, volatile auto *TXBUF, volatile auto *IE, volatile auto *IFG>
struct SPI {

  private:
    MT::Universal::Register<CTLW0> m_ctlw0{};
    MT::Universal::Register<BRW>   m_brw{};
    MT::Universal::Register<MCTLW> m_mctlw{};
    MT::Universal::Register<STATW> m_statw{};
    MT::Universal::Register<RXBUF> m_rxbuf{};
    MT::Universal::Register<TXBUF> m_txbuf{};
    MT::Universal::Register<IE>    m_ie{};
    MT::Universal::Register<IFG>   m_ifg{};

  public:
    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Initializes the SPI Master block
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	*  SPI::initMasterParam param{
    *    SPI::CLOCKSOURCE::SMCLK,
    *    1'000'000,
    *    400'000,
    *    SPI::ENDIAN::MSB_FIRST,
    *    SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
    *    SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
    *    SPI::MODE::WITHOUT_CHIPSELECT
    * };
	*
	* SPI::A1 a1;
	* a1.initMaster(param); \endcode
	*
	*@param param -> parameter to initialize SPI master -> use parameter struct SPI::initMasterParam
	****************************************************************
	*/
    constexpr void initMaster(const initMasterParam &param) noexcept {

        const uint16_t stem = m_ctlw0.get() & UCSTEM;

        m_ctlw0.override(UCSWRST | toUnderlyingType(param.clkSource) | toUnderlyingType(param.msbOrLsbFirst) | toUnderlyingType(param.clkPhase)
                         | toUnderlyingType(param.clkPolarity) | (UCMST) | (UCSYNC) | toUnderlyingType(param.mode) | (stem));
        m_brw.override(static_cast<uint16_t>(param.clkSourceFrequencyInHz / param.desiredSpiClockInHz));
        m_mctlw.override(0);
    }

    /**
   	* @ingroup groupFuncsMSP430SPI_EUSCI_A
   	****************************************************************
   	* @brief Selects 4-Pin Functionality
   	*
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIA;
   	*
   	* SPI::A1 a1;
   	* a1.select4PinFunctionality(SPI::FUNCIONALITY_4PINS::ENABLE_SIGNAL_FOR_4WIRE_SLAVE); \endcode
   	*
   	*@param pins -> functionality for 4 pin SPI mode -> use enumeration SPI::FUNCIONALITY_4PINS
   	****************************************************************
   	*/
    constexpr void select4PinFunctionality(const FUNCIONALITY_4PINS pins) noexcept {
        m_ctlw0.clear(UCSTEM);
        m_ctlw0.set(toUnderlyingType(pins));
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief  Changes the SPI Master clock. At the end of this function call, SPI module is left enabled.
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	*  SPI::changeMasterClockParam clkParam{
	*    1'000'000,
	*    400'000
	* };
	*
	* SPI::A1 a1;
	* a1.changeMasterClock(clkParam); \endcode
	*
	*@param param -> parameter to change SPI master clock -> use parameter struct SPI::changeMasterClockParam
	****************************************************************
	*/
    constexpr void changeMasterClock(const changeMasterClockParam &param) noexcept {
        m_ctlw0.set(UCSWRST);
        m_brw.override(static_cast<uint16_t>(param.clkSourceFrequencyInHz / param.desiredSpiClockInHz));
        m_ctlw0.clear(UCSWRST);
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Initializes the SPI Slave block
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	*  SPI::initSlaveParam param{
	*    SPI::ENDIAN::MSB_FIRST,
	*    SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
	*    SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
	*    SPI::MODE::WITHOUT_CHIPSELECT
	* };
	*
	* SPI::A1 a1;
	* a1.initSlave(param); \endcode
	*
	*@param param -> parameter to initialize SPI slave -> use parameter struct SPI::initSlaveParam
	****************************************************************
	*/
    constexpr void initSlave(const initSlaveParam &param) noexcept {
        m_ctlw0.override(UCSWRST | toUnderlyingType(param.msbOrLsbFirst) | toUnderlyingType(param.clkPhase)
                         | toUnderlyingType(param.clkPolarity) | (UCSYNC) | toUnderlyingType(param.mode));
    }


    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Changes the SPI clock phase and polarity. At the end of this function call, SPI module is left enabled.
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* SPI::A1 a1;
	* a1.changeClockPhasePolarity(SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,SPI::CLOCKPOLARITY::INACTIVITY_HIGH); \endcode
	*
	*@param phase -> clockphase to set -> use enumeration SPI::CLOCKPHASE
	*@param pol -> clockpolarity to set -> use enumeration SPI::CLOCKPOLARITY
	****************************************************************
	*/
    constexpr void changeClockPhasePolarity(const CLOCKPHASE phase, const CLOCKPOLARITY pol) noexcept {
        m_ctlw0.set(UCSWRST);
        m_ctlw0.clear(UCCKPH | UCCKPL);
        m_ctlw0.set(toUnderlyingType(phase) | toUnderlyingType(pol));
        m_ctlw0.clear(UCSWRST);
    }


    /**
   	* @ingroup groupFuncsMSP430SPI_EUSCI_A
   	****************************************************************
   	* @brief Transmits a byte from the SPI Module
   	*
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIA;
   	*
   	* SPI::A1 a1;
   	* a1.transmitData(127); \endcode
   	*
   	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
   	*@param data -> data to send over SPI
   	****************************************************************
   	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT>
    constexpr void transmitData(const uint8_t data) noexcept {

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            while (!(m_ifg.get() & UCTXIFG))
                ;
        }
        m_txbuf.override(data);
    }


    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Receives a byte that has been sent to the SPI Module
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* SPI::A1 a1;
	* const uint8_t byte = a1.receiveData(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@return data -> data recieved over SPI
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT>
    [[nodiscard]] constexpr uint8_t receiveData() noexcept {

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            while (!(m_ifg.get() & UCRXIFG))
                ;
        }
        return m_rxbuf.get();
    }

    /**
 	* @ingroup groupFuncsMSP430SPI_EUSCI_A
 	****************************************************************
 	* @brief Enables individual SPI interrupt sources
 	* @details
 	* Usage: \code {.cpp}
 	* using namespace MT::MSP430::EUSCIA;
 	*
 	* SPI::A1 a1;
	* a1.enableInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT); \endcode
	*
 	*@param base -> base interrupt sources to enable -> use Enumeration SPI::INT
 	****************************************************************
 	*/
    constexpr void enableInterrupt(const INT base) noexcept {
        m_ie.set(base);
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Disables individual SPI interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* SPI::A1 a1;
	* a1.disableInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT); \endcode
	*
	*@param base -> base interrupt sources to disable -> use Enumeration SPI::INT
	****************************************************************
	*/
    constexpr void disableInterrupt(const INT base) noexcept {
        m_ie.clear(base);
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Gets the current SPI interrupt status
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* SPI::A1 a1;
	* if(a1.getInterruptStatus(SPI::INT::RECEIVE | SPI::INT::TRANSMIT) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
	*
	*@param base -> base interrupt sources to check for status -> use Enumeration SPI::INT
	*@return if all the given base flags are set or not (MT::MSP430::MASK_MATCH)
	****************************************************************
	*/
    [[nodiscard]] constexpr MASK_MATCH getInterruptStatus(const INT base) noexcept {
        if (m_ifg.compare(base)) return MASK_MATCH::TRUE;
        else
            return MASK_MATCH::FALSE;
    }


    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Clears SPI interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* SPI::A1 a1;
	* a1.clearInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT); \endcode
	*
	*@param base -> base interrupt sources to clear -> use Enumeration SPI::INT
	****************************************************************
	*/
    constexpr void clearInterrupt(const INT base) noexcept {
        m_ifg.clear(base);
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Enables the SPI block
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* SPI::A1 a1;
	* a1.enable(); \endcode
	*
	****************************************************************
	*/
    constexpr void enable() noexcept {
        m_ctlw0.clear(UCSWRST);
    }

    /**
  	* @ingroup groupFuncsMSP430SPI_EUSCI_A
  	****************************************************************
  	* @brief Disables the SPI block
  	* @details
  	* Usage: \code {.cpp}
  	* using namespace MT::MSP430::EUSCIA;
  	*
  	* SPI::A1 a1;
  	* a1.disable(); \endcode
  	*
  	****************************************************************
  	*/
    constexpr void disable() noexcept {
        m_ctlw0.set(UCSWRST);
    }

    /**
   	* @ingroup groupFuncsMSP430SPI_EUSCI_A
   	****************************************************************
   	* @brief Returns the address of the RX Buffer of the SPI for the DMA module
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIA;
   	*
   	* SPI::A1 a1;
   	* const auto rxBufAdr = a1.getReceiveBufferAddress(); \endcode
   	*
   	*@return Address of RX Buffer
   	****************************************************************
   	*/
    [[nodiscard]] constexpr auto getReceiveBufferAddress() noexcept {
        return m_rxbuf.getAddress();
    }

    /**
   	* @ingroup groupFuncsMSP430SPI_EUSCI_A
   	****************************************************************
   	* @brief Returns the address of the TX Buffer of the SPI for the DMA module
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIA;
   	*
   	* SPI::A1 a1;
   	* const auto txBufAdr = a1.getTransmitBufferAddress(); \endcode
   	*
   	*@return Address of TX Buffer
   	****************************************************************
   	*/
    [[nodiscard]] constexpr auto getTransmitBufferAddress() noexcept {
        return m_txbuf.getAddress();
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Indicates whether or not the SPI bus is busy.
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* SPI::A1 a1;
	* if(a1.isBusy()) doSomething(); \endcode
	*
	*@return Address of TX Buffer
	****************************************************************
	*/
    [[nodiscard]] constexpr bool isBusy() noexcept {
        return (m_statw.get() & UCBUSY);
    }


    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_A
	****************************************************************
	* @brief Gets the current SPI status flags
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIA;
	*
	* SPI::A1 a1;
	* if(a1.queryStatusFlags(SPI::STATUS::FRAMING_ERROR | SPI::STATUS::OVERRUN_ERROR) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
	*
	*@param stat -> status flags to check for -> use Enumeration SPI::STATUS
	*@return if all the given status flags are set or not (MT::MSP430::MASK_MATCH)
	****************************************************************
	*/
    [[nodiscard]] constexpr MASK_MATCH queryStatusFlags(const STATUS stat) noexcept {
        if (m_statw.compare(stat)) return MASK_MATCH::TRUE;
        else
            return MASK_MATCH::FALSE;
    }
};
}// namespace MT::MSP430::EUSCIA::SPI::Internal

namespace MT::MSP430::EUSCIA::UART {

#if defined(__MSP430_HAS_EUSCI_A0__)
using A0 = Internal::UART<&UCA0CTLW0, &UCA0CTLW1, &UCA0BRW, &UCA0MCTLW, &UCA0STATW, &UCA0RXBUF, &UCA0TXBUF, &UCA0ABCTL, &UCA0IRCTL, &UCA0IE, &UCA0IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A1__)
using A1 = Internal::UART<&UCA1CTLW0, &UCA1CTLW1, &UCA1BRW, &UCA1MCTLW, &UCA1STATW, &UCA1RXBUF, &UCA1TXBUF, &UCA1ABCTL, &UCA1IRCTL, &UCA1IE, &UCA1IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A2__)
using A2 = Internal::UART<&UCA2CTLW0, &UCA2CTLW1, &UCA2BRW, &UCA2MCTLW, &UCA2STATW, &UCA2RXBUF, &UCA2TXBUF, &UCA2ABCTL, &UCA2IRCTL, &UCA2IE, &UCA2IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A3__)
using A3 = Internal::UART<&UCA3CTLW0, &UCA3CTLW1, &UCA3BRW, &UCA3MCTLW, &UCA3STATW, &UCA3RXBUF, &UCA3TXBUF, &UCA3ABCTL, &UCA3IRCTL, &UCA3IE, &UCA3IFG>;
#endif

}// namespace MT::MSP430::EUSCIA::UART


namespace MT::MSP430::EUSCIA::SPI {

#if defined(__MSP430_HAS_EUSCI_A0__)
using A0 = Internal::SPI<&UCA0CTLW0, &UCA0BRW, &UCA0MCTLW, &UCA0STATW, &UCA0RXBUF, &UCA0TXBUF, &UCA0IE, &UCA0IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A1__)
using A1 = Internal::SPI<&UCA1CTLW0, &UCA1BRW, &UCA1MCTLW, &UCA1STATW, &UCA1RXBUF, &UCA1TXBUF, &UCA1IE, &UCA1IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A2__)
using A2 = Internal::UART<&UCA2CTLW0, &UCA2BRW, &UCA2MCTLW, &UCA2STATW, &UCA2RXBUF, &UCA2TXBUF, &UCA2IE, &UCA2IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_A3__)
using A3 = Internal::UART<&UCA3CTLW0, &UCA3BRW, &UCA3MCTLW, &UCA3STATW, &UCA3RXBUF, &UCA3TXBUF, &UCA3IE, &UCA3IFG>;
#endif

}// namespace MT::MSP430::EUSCIA::SPI


#endif
#endif
#endif /* MICROTRAIT_MSP430_EUSCI_EUSCIA_HPP_ */

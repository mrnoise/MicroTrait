/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430EUSCI_B EUSCI B
 *  @ingroup groupMSP430
* @brief functions for EUSCI B register access for TIs MSP430 -> Ti Driverlib equivalent naming
*
* @details
* Usage: \code {.cpp}
*
*#include "MicroTrait/MT.hpp"
*
* using namespace MT::MSP430;
*
*  EUSCIB::I2C::initMasterParam param{
*    EUSCIB::I2C::CLOCKSOURCE::SMCLK,
*    1'000'000,
*    EUSCIB::I2C::DATARATE::_100KBPS,
*    255,
*    EUSCIB::I2C::AUTOSTOP::OFF
* };
*
* EUSCIB::I2C::B0 b0;
* b0.initMaster(param);
*
*
* EUSCIB::SPI::initMasterParam param{
*    EUSCIB::SPI::CLOCKSOURCE::SMCLK,
*    1'000'000,
*    400'000,
*    EUSCIB::SPI::ENDIAN::MSB_FIRST,
*    EUSCIB::SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
*    EUSCIB::SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
*    EUSCIB::SPI::MODE::WITHOUT_CHIPSELECT
* };
*
*  EUSCIB::SPI::B1 b1;
*  b1.initMaster(param);\endcode
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupFuncsMSP430I2C_EUSCI_B I2C Functions
*  @ingroup groupMSP430EUSCI_B
*  Functions in this module for I2C mode
*/

/** @defgroup groupEnumsMSP430I2C_EUSCI_B I2C Enums
*  @ingroup groupMSP430EUSCI_B
*  Enums in this module for I2C mode
*/

/** @defgroup groupParamsMSP430I2C_EUSCI_B I2C Parameter
*  @ingroup groupMSP430EUSCI_B
*  Parameterstructures in this module for I2C mode
*/


/** @defgroup groupFuncsMSP430SPI_EUSCI_B SPI Functions
*  @ingroup groupMSP430EUSCI_B
*  Functions in this module for SPI mode
*/

/** @defgroup groupEnumsMSP430SPI_EUSCI_B SPI Enums
*  @ingroup groupMSP430EUSCI_B
*  Enums in this module for SPI mode
*/

/** @defgroup groupParamsMSP430SPI_EUSCI_B SPI Parameter
*  @ingroup groupMSP430EUSCI_B
*  Parameterstructures in this module for SPI mode
*/

#ifndef MICROTRAIT_MSP430_EUSCI_EUSCIB_HPP_
#define MICROTRAIT_MSP430_EUSCI_EUSCIB_HPP_

#include "MicroTrait/MSP430/Settings.hpp"
#include "MicroTrait/MSP430/Types.hpp"

#ifdef MT_USE_MSP430_LIB

#include "MicroTrait/Universal/Register.hpp"
#include "MicroTrait/MSP430/Types.hpp"
#include <msp430.h>

#if defined(__MSP430_HAS_EUSCI_B0__) || defined(__MSP430_HAS_EUSCI_B1__) || defined(__MSP430_HAS_EUSCI_B2__) || defined(__MSP430_HAS_EUSCI_B3__)

namespace MT::Misc {

enum class EUSCIB_I2C_INT : uint16_t {
    NONE              = (0x0000),
    NAK               = (UCNACKIE),
    ARBITRATIONLOST   = (UCALIE),
    STOP              = (UCSTPIE),
    START             = (UCSTTIE),
    TRANSMIT_0        = (UCTXIE0),
    TRANSMIT_1        = (UCTXIE1),
    TRANSMIT_2        = (UCTXIE2),
    TRANSMIT_3        = (UCTXIE3),
    RECEIVE_0         = (UCRXIE0),
    RECEIVE_1         = (UCRXIE1),
    RECEIVE_2         = (UCRXIE2),
    RECEIVE_3         = (UCRXIE3),
    BIT9_POSITION     = (UCBIT9IE),
    CLOCK_LOW_TIMEOUT = (UCCLTOIE),
    BYTE_COUNTER      = (UCBCNTIE)
};
template<>
struct enable_Enum_bits<EUSCIB_I2C_INT> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile EUSCIB_I2C_INT> {
    static constexpr bool enable = true;
};

enum class EUSCIB_SPI_INT : uint16_t {
    RECEIVE  = (UCRXIE),
    TRANSMIT = (UCTXIE)
};
template<>
struct enable_Enum_bits<EUSCIB_SPI_INT> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile EUSCIB_SPI_INT> {
    static constexpr bool enable = true;
};


enum class EUSCIB_SPI_STATUS : uint16_t {
    LISTEN_ENABLE = (UCLISTEN),
    FRAMING_ERROR = (UCFE),
    OVERRUN_ERROR = (UCOE),
    BUSY          = (UCBUSY)
};
template<>
struct enable_Enum_bits<EUSCIB_SPI_STATUS> {
    static constexpr bool enable = true;
};

template<>
struct enable_Enum_bits<volatile EUSCIB_SPI_STATUS> {
    static constexpr bool enable = true;
};

}// namespace MT::Misc


namespace MT::MSP430::EUSCIB::I2C {

/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief EUSCI A I2C interrupt type
****************************************************************
*/
using INT = MT::Misc::EUSCIB_I2C_INT;

/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Autostopgeneration
****************************************************************
*/
enum class AUTOSTOP : uint16_t {
    OFF                                            = (UCASTP_0),
    SET_BYTECOUNT_THRESHOLD_FLAG                   = (UCASTP_1),
    SEND_STOP_AUTOMATICALLY_ON_BYTECOUNT_THRESHOLD = (UCASTP_2)
};


/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Datarate
****************************************************************
*/
enum class DATARATE : uint32_t {
    _400KBPS = (400'000),
    _100KBPS = (100'000)
};


/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Clocksources
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
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Slave address offset referred to- 'x' value of UCBxI2COAx
****************************************************************
*/
enum class SLAVE_ADDRESS_OFFSET : uint8_t {
    _0 = 0,
    _1 = 1,
    _2 = 2,
    _3 = 3
};

/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Slave address enabled or disabled
****************************************************************
*/
enum class SLAVE_ADDRESS : uint16_t {
    ENABLED  = (UCOAEN),
    DISABLED = (0x0000)
};

/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C mode -> RX or TX
****************************************************************
*/
enum class MODE : uint16_t {
    TX = (UCTR),
    RX = (0x0000)
};

/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Busy state
****************************************************************
*/
enum class BUSY : uint16_t {
    NO  = (0x0000),
    YES = (UCBUSY)
};

/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Stop state
****************************************************************
*/
enum class STOP_STATE : uint16_t {
    SEND_COMPLETE = (0x0000),
    SENDING       = (UCTXSTP)
};


/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Start state
****************************************************************
*/
enum class START_STATE : uint16_t {
    SEND_COMPLETE = (0x0000),
    SENDING       = (UCTXSTT)
};


/**
* @ingroup groupEnumsMSP430I2C_EUSCI_B
****************************************************************
* @brief I2C Timeout values
****************************************************************
*/
enum class TIMEOUT : uint16_t {
    DISABLED = (UCCLTO_0),
    _28_MS   = (UCCLTO_1),
    _31_MS   = (UCCLTO_2),
    _34_MS   = (UCCLTO_3)
};

/**
* @ingroup groupParamsMSP430I2C_EUSCI_B
****************************************************************
* @brief Parameter structure to init I2C master
****************************************************************
*/
using initMasterParam = struct {
    CLOCKSOURCE clkSource;
    uint32_t    clkSourceFrequencyInHz;
    DATARATE    datarate;
    uint8_t     byteCounterThreshold;
    AUTOSTOP    autostop;
};

/**
* @ingroup groupParamsMSP430I2C_EUSCI_B
****************************************************************
* @brief Parameter structure to init I2C slave
****************************************************************
*/
using initSlaveParam = struct {
    uint8_t              slaveAddress;
    SLAVE_ADDRESS_OFFSET adrOffset;
    SLAVE_ADDRESS        onOff;
};

}// namespace MT::MSP430::EUSCIB::I2C


namespace MT::MSP430::EUSCIB::SPI {

/**
* @ingroup groupEnumsMSP430SPI_EUSCI_B
****************************************************************
* @brief EUSCI A SPI interrupt type
****************************************************************
*/
using INT = MT::Misc::EUSCIB_SPI_INT;


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_B
****************************************************************
* @brief EUSCI A SPI status type
****************************************************************
*/
using STATUS = MT::Misc::EUSCIB_SPI_STATUS;


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_B
****************************************************************
* @brief SPI Clockphase
****************************************************************
*/
enum class CLOCKPHASE : uint16_t {
    DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT = (0x0000),
    DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT = (UCCKPH)
};

/**
* @ingroup groupEnumsMSP430SPI_EUSCI_B
****************************************************************
* @brief SPI Endianness -> MSB or LSB First
****************************************************************
*/
enum class ENDIAN : uint16_t {
    LSB_FIRST = (0x0000),
    MSB_FIRST = (UCMSB)
};


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_B
****************************************************************
* @brief SPI Clockphase
****************************************************************
*/
enum class CLOCKPOLARITY : uint16_t {
    INACTIVITY_LOW  = (0x0000),
    INACTIVITY_HIGH = (UCCKPL)
};

/**
* @ingroup groupEnumsMSP430SPI_EUSCI_B
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
* @ingroup groupEnumsMSP430SPI_EUSCI_B
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
* @ingroup groupEnumsMSP430SPI_EUSCI_B
****************************************************************
* @brief SPI 4 Pin functionality
****************************************************************
*/
enum class FUNCIONALITY_4PINS : uint16_t {
    PREVENT_CONFLICTS_WITH_OTHER_MASTERS = (0x0000),
    ENABLE_SIGNAL_FOR_4WIRE_SLAVE        = (UCSTEM)
};


/**
* @ingroup groupEnumsMSP430SPI_EUSCI_B
****************************************************************
* @brief SPI Busy state
****************************************************************
*/
enum class BUSY : uint16_t {
    NO  = (0x0000),
    YES = (UCBUSY)
};


/**
* @ingroup groupParamsMSP430SPI_EUSCI_B
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
* @ingroup groupParamsMSP430SPI_EUSCI_B
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
* @ingroup groupParamsMSP430SPI_EUSCI_B
****************************************************************
* @brief Parameter structure to change SPI master clock
****************************************************************
*/
using changeMasterClockParam = struct {
    uint32_t clkSourceFrequencyInHz;
    uint32_t desiredSpiClockInHz;
};

}// namespace MT::MSP430::EUSCIB::SPI


namespace MT::MSP430::EUSCIB::I2C::Internal {

using namespace MT::Misc::Cast;

template<
    volatile auto *CTLW0,
    volatile auto *CTLW1,
    volatile auto *BRW,
    volatile auto *STATW,
    volatile auto *TBCNT,
    volatile auto *RXBUF,
    volatile auto *TXBUF,
    volatile auto *A0,
    volatile auto *A1,
    volatile auto *A2,
    volatile auto *A3,
    volatile auto *ADDR,
    volatile auto *ADDMASK,
    volatile auto *SA,
    volatile auto *IE,
    volatile auto *IFG>
struct I2C {

  private:
    MT::Universal::Register<CTLW0>   m_ctlw0{};
    MT::Universal::Register<CTLW1>   m_ctlw1{};
    MT::Universal::Register<BRW>     m_brw{};
    MT::Universal::Register<STATW>   m_statw{};
    MT::Universal::Register<TBCNT>   m_tbcnt{};
    MT::Universal::Register<RXBUF>   m_rxbuf{};
    MT::Universal::Register<TXBUF>   m_txbuf{};
    MT::Universal::Register<A0>      m_a0{};
    MT::Universal::Register<A1>      m_a1{};
    MT::Universal::Register<A2>      m_a2{};
    MT::Universal::Register<A3>      m_a3{};
    MT::Universal::Register<ADDR>    m_addr{};
    MT::Universal::Register<ADDMASK> m_addmask{};
    MT::Universal::Register<SA>      m_sa{};
    MT::Universal::Register<IE>      m_ie{};
    MT::Universal::Register<IFG>     m_ifg{};

  public:
    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Initializes the I2C Master block
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	*  I2C::initMasterParam param{
    *    I2C::CLOCKSOURCE::SMCLK,
    *    1'000'000,
    *    I2C::DATARATE::_100KBPS,
    *    255,
    *    I2C::AUTOSTOP::OFF
    * };
	*
	* I2C::B0 b0;
	* b0.initMaster(param); \endcode
	*
	*@param param -> parameter to initialize I2C master -> use parameter struct I2C::initMasterParam
	****************************************************************
	*/
    constexpr void initMaster(const initMasterParam &param) noexcept {

        m_ctlw0.override(UCSWRST | toUnderlyingType(param.clkSource) | UCMST | UCMODE_3 | UCSYNC);
        m_ctlw1.set(toUnderlyingType(param.autostop));
        m_tbcnt.override(static_cast<uint16_t>(param.byteCounterThreshold));
        m_brw.override(static_cast<uint16_t>(param.clkSourceFrequencyInHz / toUnderlyingType(param.datarate)));
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Initializes the I2C Slave block
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::initSlaveParam param{
    *    0x0A,
    *    I2C::SLAVE_ADDRESS_OFFSET::_0,
    *    I2C::SLAVE_ADDRESS::DISABLED
    * };
    *
    * I2C::B0 b0;
    * b0.initSlave(param); \endcode
	*
	*@param param -> parameter to initialize I2C slave -> use parameter struct I2C::initSlaveParam
	****************************************************************
	*/
    constexpr void initSlave(const initSlaveParam &param) noexcept {

        m_ctlw0.override(UCSWRST | UCMODE_3 | UCSYNC);

        switch (param.adrOffset) {
            case SLAVE_ADDRESS_OFFSET::_0:
                m_a0.override(static_cast<uint16_t>(param.slaveAddress) + toUnderlyingType(param.onOff));
                break;
            case SLAVE_ADDRESS_OFFSET::_1:
                m_a1.override(static_cast<uint16_t>(param.slaveAddress) + toUnderlyingType(param.onOff));
                break;
            case SLAVE_ADDRESS_OFFSET::_2:
                m_a2.override(static_cast<uint16_t>(param.slaveAddress) + toUnderlyingType(param.onOff));
                break;
            case SLAVE_ADDRESS_OFFSET::_3:
                m_a3.override(static_cast<uint16_t>(param.slaveAddress) + toUnderlyingType(param.onOff));
                break;
        }
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Enables the I2C block
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.enable(); \endcode
	*
	****************************************************************
	*/
    constexpr void enable() noexcept {
        m_ctlw0.clear(UCSWRST);
    }

    /**
  	* @ingroup groupFuncsMSP430I2C_EUSCI_B
  	****************************************************************
  	* @brief Disables the I2C block
  	* @details
  	* Usage: \code {.cpp}
  	* using namespace MT::MSP430::EUSCIB;
  	*
  	* I2C::B0 b0;
  	* b0.disable(); \endcode
  	*
  	****************************************************************
  	*/
    constexpr void disable() noexcept {
        m_ctlw0.set(UCSWRST);
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief  Sets the address that the I2C Master will place on the bus
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.setSlaveAddress(0x0A); \endcode
	*
	*@param addr -> 7-bit slave address
	****************************************************************
	*/
    constexpr void setSlaveAddress(uint8_t const addr) noexcept {
        m_sa.override(static_cast<uint16_t>(addr));
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief  Sets the mode (rx or tx) of the I2C device
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.setMode(I2C::MODE::TX); \endcode
	*
	*@param mode -> use enumeration I2C::MODE
	****************************************************************
	*/
    constexpr void setMode(const MODE mode) noexcept {
        m_ctlw0.clear(UCTR);
        m_ctlw0.set(toUnderlyingType(mode));
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief  Gets the mode (rx or tx) of the I2C device
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* if(b0.getMode() == I2C::MODE::TX) doSomething(); \endcode
	*
	*@return mode -> the mode the device is in -> enumeration I2C::MODE
	****************************************************************
	*/
    [[nodiscard]] constexpr MODE getMode() noexcept {
        return static_cast<MODE>(m_ctlw0.get() & UCTR);
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Transmits a byte from the I2C Module
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B1 b0;
	* b0.slavePutData(127); \endcode
	*
	*@param data -> data to send over I2C
	****************************************************************
	*/
    constexpr void slavePutData(const uint8_t data) noexcept {
        m_txbuf.override(data);
    }

    /**
   	* @ingroup groupFuncsMSP430I2C_EUSCI_B
   	****************************************************************
   	* @brief Receives a byte that has been sent to the I2C Module
   	*
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* I2C::B0 b0;
   	* const uint8_t byte = b0.slaveGetData(); \endcode
   	*
   	*@return data received over I2C
   	****************************************************************
   	*/
    [[nodiscard]] constexpr uint8_t slaveGetData() noexcept {
        return m_rxbuf.get();
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Indicates whether or not the I2C bus is busy
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* const auto busy = b0.isBusBusy(); \endcode
	*
	*@return if the bus is busy or not -> enumeration I2C::BUSY
	****************************************************************
	*/
    [[nodiscard]] constexpr BUSY isBusBusy() noexcept {
        return static_cast<BUSY>(m_statw.get() & UCBBUSY);
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Indicates whether STOP got sent
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* if(b0.masterIsStopSent() == I2C::STOP_STATE::SEND_COMPLETE) doSomething(); \endcode
	*
	*@return indicating whether the stop was sent -> enumeration I2C::STOP_STATE
	****************************************************************
	*/
    [[nodiscard]] constexpr STOP_STATE masterIsStopSent() noexcept {
        return static_cast<STOP_STATE>(m_ctlw0.get() & UCTXSTP);
    }


    /**
   	* @ingroup groupFuncsMSP430I2C_EUSCI_B
   	****************************************************************
   	* @brief Indicates whether Start got sent
   	*
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* I2C::B0 b0;
   	* if(b0.masterIsStartSent() == I2C::START_STATE::SEND_COMPLETE) doSomething(); \endcode
   	*
   	*@return indicating whether the start was sent -> enumeration I2C::START_STATE
   	****************************************************************
   	*/
    [[nodiscard]] constexpr START_STATE masterIsStartSent() noexcept {
        return static_cast<START_STATE>(m_ctlw0.get() & UCTXSTT);
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Enables individual I2C interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.enableInterrupt(I2C::INT::RECEIVE | I2C::INT::TRANSMIT); \endcode
	*
	*@param base -> base interrupt sources to enable -> use Enumeration I2C::INT
	****************************************************************
	*/
    constexpr void enableInterrupt(const INT base) noexcept {
        m_ie.set(base);
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Disables individual I2C interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.disableInterrupt(I2C::INT::RECEIVE | I2C::INT::TRANSMIT); \endcode
	*
	*@param base -> base interrupt sources to disable -> use Enumeration I2C::INT
	****************************************************************
	*/
    constexpr void disableInterrupt(const INT base) noexcept {
        m_ie.clear(base);
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Clears I2C interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.clearInterrupt(I2C::INT::RECEIVE | I2C::INT::TRANSMIT); \endcode
	*
	*@param base -> base interrupt sources to clear -> use Enumeration I2C::INT
	****************************************************************
	*/
    constexpr void clearInterrupt(const INT base) noexcept {
        m_ifg.clear(base);
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Gets the current I2C interrupt status
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* if(b0.getInterruptStatus(I2C::INT::RECEIVE | I2C::INT::TRANSMIT) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
	*
	*@param base -> base interrupt sources to check for status -> use Enumeration I2C::INT
	*@return if all the given base flags are set or not (MT::MSP430::MASK_MATCH)
	****************************************************************
	*/
    [[nodiscard]] constexpr MASK_MATCH getInterruptStatus(const INT base) noexcept {
        if (m_ifg.compare(base)) return MASK_MATCH::TRUE;
        else
            return MASK_MATCH::FALSE;
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Does single byte transmission from Master to Slave -> does Interrupt polling
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* if (b0.masterSendSingleByte<100>(127) == STATUS::FAIL) doSomething(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@tparam TIMEOUT set for a timeout in cycles (flag polling) -> returns STATUS::FAIL is timeout was reached -> default is off -> 0
	*@param data is the byte to be transmitted
	*@return if succcess or fail -> use enumeration MT::MSP430::STATUS
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT, uint32_t TIMEOUT = 0>
    [[nodiscard]] constexpr STATUS masterSendSingleByte(const uint8_t data) noexcept {

        const uint16_t ieStat = m_ie.get() & UCTXIE;
        m_ie.clear(UCTXIE);
        m_ctlw0.set(UCTR | UCTXSTT);

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout = TIMEOUT;
                while (!(m_ifg.get() & UCTXIFG) && --timeout)
                    ;

                if (!timeout) return STATUS::FAIL;
            } else {
                while (!(m_ifg.get() & UCTXIFG))
                    ;
            }
        }

        m_txbuf.override(data);

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout1 = TIMEOUT;
                while (!(m_ifg.get() & UCTXIFG) && --timeout1)
                    ;
                if (!timeout1) return STATUS::FAIL;
            } else {
                while (!(m_ifg.get() & UCTXIFG))
                    ;
            }
        }

        m_ctlw0.set(UCTXSTP);
        m_ifg.clear(UCTXIFG);
        m_ie.set(ieStat);
        return STATUS::SUCCESS;
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Does single byte reception from Slave -> does Interrupt polling
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* const uint8_t byte = b0.masterReceiveSingleByte(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@tparam TIMEOUT set for a timeout in cycles (flag polling) -> default is off -> 0
	*@return data received over I2C
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT, uint32_t TIMEOUT = 0>
    [[nodiscard]] constexpr uint8_t masterReceiveSingleByte() noexcept {

        m_ctlw0.clear(UCTR);
        m_ctlw0.set(UCTXSTT);

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout = TIMEOUT;
                while ((m_ctlw0.get() & UCTXSTT) && --timeout)
                    ;
            } else {
                while (m_ctlw0.get() & UCTXSTT)
                    ;
            }
        }

        m_ctlw0.set(UCTXSTP);

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout1 = TIMEOUT;
                while (!(m_ifg.get() & UCRXIFG) && --timeout1)
                    ;
            } else {
                while (!(m_ifg.get() & UCRXIFG))
                    ;
            }
        }

        return m_rxbuf.get();
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Starts multi-byte transmission from Master to Slave
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* if (b0.masterSendMultiByteStart<100>(127) == STATUS::FAIL) doSomething(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@tparam TIMEOUT set for a timeout in cycles (flag polling) -> returns STATUS::FAIL is timeout was reached -> default is off -> 0
	*@param data is the byte to be transmitted
	*@return if succcess or fail -> use enumeration MT::MSP430::STATUS
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT, uint32_t TIMEOUT = 0>
    [[nodiscard]] constexpr STATUS masterSendMultiByteStart(const uint8_t data) noexcept {

        const auto ieStat = m_ie.get() & UCTXIE;
        m_ie.clear(UCTXIE);
        m_ctlw0.set(UCTR | UCTXSTT);

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout = TIMEOUT;
                while (!(m_ifg.get() & UCTXIFG) && --timeout)
                    ;
                if (!timeout) return STATUS::FAIL;
            } else {
                while (!(m_ifg.get() & UCTXIFG))
                    ;
            }
        }

        m_txbuf.override(data);
        m_ie.set(ieStat);
        return STATUS::SUCCESS;
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Continues multi-byte transmission from Master to Slave
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* if (b0.masterSendMultiByteNext(127) == STATUS::FAIL) doSomething(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@tparam TIMEOUT set for a timeout in cycles (flag polling) -> returns STATUS::FAIL is timeout was reached -> default is off -> 0
	*@param data is the byte to be transmitted
	*@return if succcess or fail -> use enumeration MT::MSP430::STATUS
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT, uint32_t TIMEOUT = 0>
    [[nodiscard]] constexpr STATUS masterSendMultiByteNext(const uint8_t data) noexcept {

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout = TIMEOUT;
                while (!(m_ifg.get() & UCTXIFG) && --timeout)
                    ;
                if (!timeout) return STATUS::FAIL;
            } else {
                while (!(m_ifg.get() & UCTXIFG))
                    ;
            }
        }

        m_txbuf.override(data);
        return STATUS::SUCCESS;
    }

    /**
  	* @ingroup groupFuncsMSP430I2C_EUSCI_B
  	****************************************************************
  	* @brief Finishes multi-byte transmission from Master to Slave
  	* @details
  	* Usage: \code {.cpp}
  	* using namespace MT::MSP430::EUSCIB;
  	*
  	* I2C::B0 b0;
  	* if (b0.masterSendMultiByteFinish(127) == STATUS::FAIL) doSomething(); \endcode
  	*
  	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
  	*@tparam TIMEOUT set for a timeout in cycles (flag polling) -> returns STATUS::FAIL is timeout was reached -> default is off -> 0
  	*@param data is the byte to be transmitted
  	*@return if succcess or fail -> use enumeration MT::MSP430::STATUS
  	****************************************************************
  	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT, uint32_t TIMEOUT = 0>
    [[nodiscard]] constexpr STATUS masterSendMultiByteFinish(const uint8_t data) noexcept {

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout = TIMEOUT;
                while (!(m_ifg.get() & UCTXIFG) && --timeout)
                    ;
                if (!timeout) return STATUS::FAIL;
            } else {
                while (!(m_ifg.get() & UCTXIFG))
                    ;
            }
        }

        m_txbuf.override(data);

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout1 = TIMEOUT;
                while (!(m_ifg.get() & UCTXIFG) && --timeout1)
                    ;
                if (!timeout1) return STATUS::FAIL;
            } else {
                while (!(m_ifg.get() & UCTXIFG))
                    ;
            }
        }

        m_ctlw0.set(UCTXSTP);

        return STATUS::SUCCESS;
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief This function is used by the Master module to initiate START
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.masterSendStart(); \endcode
	*
	****************************************************************
	*/
    constexpr void masterSendStart() noexcept {
        m_ctlw0.set(UCTXSTT);
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Send STOP byte at the end of a multi-byte transmission from Master to Slave
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.masterSendMultiByteStop(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
  	*@tparam TIMEOUT set for a timeout in cycles (flag polling) -> returns STATUS::FAIL is timeout was reached -> default is off -> 0
  	*@return if succcess or fail -> use enumeration MT::MSP430::STATUS
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT, uint32_t TIMEOUT = 0>
    [[nodiscard]] constexpr STATUS masterSendMultiByteStop() noexcept {

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout = TIMEOUT;
                while (!(m_ifg.get() & UCTXIFG) && --timeout)
                    ;
                if (!timeout) return STATUS::FAIL;
            } else {
                while (!(m_ifg.get() & UCTXIFG))
                    ;
            }
        }

        m_ctlw0.set(UCTXSTP);
        return STATUS::SUCCESS;
    }

    /**
  	* @ingroup groupFuncsMSP430I2C_EUSCI_B
  	****************************************************************
  	* @brief Starts reception at the Master end
  	* @details
  	* Usage: \code {.cpp}
  	* using namespace MT::MSP430::EUSCIB;
  	*
  	* I2C::B0 b0;
  	* b0.masterReceiveStart(); \endcode
  	*
  	****************************************************************
  	*/
    constexpr void masterReceiveStart() noexcept {
        m_ctlw0.clear(UCTR);
        m_ctlw0.set(UCTXSTT);
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Starts multi-byte reception at the Master end one byte at a time
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* const auto data = b0.masterReceiveMultiByteNext(); \endcode
	*
	*@return received data
	****************************************************************
	*/
    [[nodiscard]] constexpr uint8_t masterReceiveMultiByteNext() noexcept {
        return m_rxbuf.get();
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Finishes multi-byte reception at the Master end
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* const uint8_t byte = b0.masterReceiveMultiByteFinish(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@tparam TIMEOUT set for a timeout in cycles (flag polling) -> default is off -> 0
	*@return data received over I2C
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT, uint32_t TIMEOUT = 0>
    [[nodiscard]] constexpr uint8_t masterReceiveMultiByteFinish() noexcept {

        m_ctlw0.set(UCTXSTP);

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            if constexpr (TIMEOUT != 0) {
                auto timeout = TIMEOUT;
                while ((m_ctlw0.get() & UCTXSTP) && --timeout)
                    ;
            } else {
                while (m_ctlw0.get() & UCTXSTP)
                    ;
            }

            if constexpr (TIMEOUT != 0) {
                auto timeout1 = TIMEOUT;
                while (!(m_ifg.get() & UCRXIFG) && --timeout1)
                    ;
            } else {
                while (!(m_ifg.get() & UCRXIFG))
                    ;
            }
        }
        return m_rxbuf.get();
    }

    /**
   	* @ingroup groupFuncsMSP430I2C_EUSCI_B
   	****************************************************************
   	* @brief Sends the STOP at the end of a multi-byte reception at the Master end
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* I2C::B0 b0;
   	* b0.masterReceiveMultiByteStop(); \endcode
   	*
   	****************************************************************
   	*/
    constexpr void masterReceiveMultiByteStop() noexcept {
        m_ctlw0.set(UCTXSTP);
    }


    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Enables Multi Master Mode
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.enableMultiMasterMode(); \endcode
	*
	****************************************************************
	*/
    constexpr void enableMultiMasterMode() noexcept {
        m_ctlw0.set(UCSWRST | UCMM);
    }


    /**
   	* @ingroup groupFuncsMSP430I2C_EUSCI_B
   	****************************************************************
   	* @brief Disables Multi Master Mode
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* I2C::B0 b0;
   	* b0.disableMultiMasterMode(); \endcode
   	*
   	****************************************************************
   	*/
    constexpr void disableMultiMasterMode() noexcept {
        m_ctlw0.set(UCSWRST);
        m_ctlw0.clear(UCMM);
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief receives a byte that has been sent to the I2C Master Module
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* const uint8_t byte = b0.masterReceiveSingle(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@return data received over I2C
	****************************************************************
	*/
    template<USAGE_CONTEXT CONTEXT = USAGE_CONTEXT::IN_INTERRUPT>
    [[nodiscard]] constexpr uint8_t masterReceiveSingle() noexcept {

        if constexpr (CONTEXT == USAGE_CONTEXT::POLLING) {
            while (!(m_ifg.get() & UCRXIFG))
                ;
        }
        return m_rxbuf.get();
    }

    /**
   	* @ingroup groupFuncsMSP430I2C_EUSCI_B
   	****************************************************************
   	* @brief Returns the address of the RX Buffer of the I2C for the DMA module
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* I2C::B0 b0;
   	* const auto rxBufAdr = b0.getReceiveBufferAddress(); \endcode
   	*
   	*@return Address of RX Buffer
   	****************************************************************
   	*/
    [[nodiscard]] constexpr auto getReceiveBufferAddress() noexcept {
        return m_rxbuf.getAddress();
    }

    /**
   	* @ingroup groupFuncsMSP430I2C_EUSCI_B
   	****************************************************************
   	* @brief Returns the address of the TX Buffer of the I2C for the DMA module
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* I2C::B0 b0;
   	* const auto txBufAdr = b0.getTransmitBufferAddress(); \endcode
   	*
   	*@return Address of TX Buffer
   	****************************************************************
   	*/
    [[nodiscard]] constexpr auto getTransmitBufferAddress() noexcept {
        return m_txbuf.getAddress();
    }

    /**
	* @ingroup groupFuncsMSP430I2C_EUSCI_B
	****************************************************************
	* @brief Enforces a timeout if the I2C clock is held low longer than a defined time.
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* I2C::B0 b0;
	* b0.setTimeout(I2C::TIMEOUT::_34_MS); \endcode
	*
	*@param time timeout -> use enumeration I2C::TIMEOUT
	****************************************************************
	*/
    constexpr void setTimeout(const TIMEOUT time) noexcept {
        const auto ctlw0 = m_ctlw0.get();
        m_ctlw0.set(UCSWRST);
        m_ctlw1.override((m_ctlw1.get() & (~UCCLTO_3)) | toUnderlyingType(time));
        m_ctlw0.override(ctlw0);
    }

};// namespace MT::MSP430::EUSCIB::I2C::Internal
}// namespace MT::MSP430::EUSCIB::I2C::Internal


namespace MT::MSP430::EUSCIB::SPI::Internal {

using namespace MT::Misc::Cast;

template<volatile auto *CTLW0, volatile auto *BRW, volatile auto *STATW, volatile auto *RXBUF, volatile auto *TXBUF, volatile auto *IE, volatile auto *IFG>
struct SPI {

  private:
    MT::Universal::Register<CTLW0> m_ctlw0{};
    MT::Universal::Register<BRW>   m_brw{};
    MT::Universal::Register<STATW> m_statw{};
    MT::Universal::Register<RXBUF> m_rxbuf{};
    MT::Universal::Register<TXBUF> m_txbuf{};
    MT::Universal::Register<IE>    m_ie{};
    MT::Universal::Register<IFG>   m_ifg{};

  public:
    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Initializes the SPI Master block
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
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
	* SPI::B1 b1;
	* b1.initMaster(param); \endcode
	*
	*@param param -> parameter to initialize SPI master -> use parameter struct SPI::initMasterParam
	****************************************************************
	*/
    constexpr void initMaster(const initMasterParam &param) noexcept {

        const uint16_t stem = m_ctlw0.get() & UCSTEM;

        m_ctlw0.override(UCSWRST | toUnderlyingType(param.clkSource) | toUnderlyingType(param.msbOrLsbFirst) | toUnderlyingType(param.clkPhase)
                         | toUnderlyingType(param.clkPolarity) | (UCMST) | (UCSYNC) | toUnderlyingType(param.mode) | (stem));
        m_brw.override(static_cast<uint16_t>(param.clkSourceFrequencyInHz / param.desiredSpiClockInHz));
    }

    /**
   	* @ingroup groupFuncsMSP430SPI_EUSCI_B
   	****************************************************************
   	* @brief Selects 4-Pin Functionality
   	*
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* SPI::B1 b1;
   	* b1.select4PinFunctionality(SPI::FUNCIONALITY_4PINS::ENABLE_SIGNAL_FOR_4WIRE_SLAVE); \endcode
   	*
   	*@param pins -> functionality for 4 pin SPI mode -> use enumeration SPI::FUNCIONALITY_4PINS
   	****************************************************************
   	*/
    constexpr void select4PinFunctionality(const FUNCIONALITY_4PINS pins) noexcept {
        m_ctlw0.clear(UCSTEM);
        m_ctlw0.set(toUnderlyingType(pins));
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief  Changes the SPI Master clock. At the end of this function call, SPI module is left enabled.
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	*  SPI::changeMasterClockParam clkParam{
	*    1'000'000,
	*    400'000
	* };
	*
	* SPI::B1 b1;
	* b1.changeMasterClock(clkParam); \endcode
	*
	*@param param -> parameter to change SPI master clock -> use parameter struct SPI::changeMasterClockParam
	****************************************************************
	*/
    constexpr void changeMasterClock(const changeMasterClockParam &param) noexcept {
        m_ctlw0.set(UCSWRST);
        m_brw.override(param.clkSourceFrequencyInHz / param.desiredSpiClockInHz);
        m_ctlw0.clear(UCSWRST);
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Initializes the SPI Slave block
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	*  SPI::initSlaveParam param{
	*    SPI::ENDIAN::MSB_FIRST,
	*    SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
	*    SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
	*    SPI::MODE::WITHOUT_CHIPSELECT
	* };
	*
	* SPI::B1 b1;
	* b1.initSlave(param); \endcode
	*
	*@param param -> parameter to initialize SPI slave -> use parameter struct SPI::initSlaveParam
	****************************************************************
	*/
    constexpr void initSlave(const initSlaveParam &param) noexcept {
        m_ctlw0.override(UCSWRST | toUnderlyingType(param.msbOrLsbFirst) | toUnderlyingType(param.clkPhase)
                         | toUnderlyingType(param.clkPolarity) | (UCSYNC) | toUnderlyingType(param.mode));
    }


    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Changes the SPI clock phase and polarity. At the end of this function call, SPI module is left enabled.
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* SPI::B1 b1;
	* b1.changeClockPhasePolarity(SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,SPI::CLOCKPOLARITY::INACTIVITY_HIGH); \endcode
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
   	* @ingroup groupFuncsMSP430SPI_EUSCI_B
   	****************************************************************
   	* @brief Transmits a byte from the SPI Module
   	*
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* SPI::B1 b1;
   	* b1.transmitData(127); \endcode
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
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Receives a byte that has been sent to the SPI Module
	*
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* SPI::B1 b1;
	* const uint8_t byte = b1.receiveData(); \endcode
	*
	*@tparam CONTEXT -> usage context of the function -> default is in interrupt context set to USAGE_CONTEXT::POLLING if used outside ISR
	*@return data -> data received over SPI
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
 	* @ingroup groupFuncsMSP430SPI_EUSCI_B
 	****************************************************************
 	* @brief Enables individual SPI interrupt sources
 	* @details
 	* Usage: \code {.cpp}
 	* using namespace MT::MSP430::EUSCIB;
 	*
 	* SPI::B1 b1;
	* b1.enableInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT); \endcode
	*
 	*@param base -> base interrupt sources to enable -> use Enumeration SPI::INT
 	****************************************************************
 	*/
    constexpr void enableInterrupt(const INT base) noexcept {
        m_ie.set(base);
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Disables individual SPI interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* SPI::B1 b1;
	* b1.disableInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT); \endcode
	*
	*@param base -> base interrupt sources to disable -> use Enumeration SPI::INT
	****************************************************************
	*/
    constexpr void disableInterrupt(const INT base) noexcept {
        m_ie.clear(base);
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Gets the current SPI interrupt status
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* SPI::B1 b1;
	* if(b1.getInterruptStatus(SPI::INT::RECEIVE | SPI::INT::TRANSMIT) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
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
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Clears SPI interrupt sources
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* SPI::B1 b1;
	* b1.clearInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT); \endcode
	*
	*@param base -> base interrupt sources to clear -> use Enumeration SPI::INT
	****************************************************************
	*/
    constexpr void clearInterrupt(const INT base) noexcept {
        m_ifg.clear(base);
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Enables the SPI block
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* SPI::B1 b1;
	* b1.enable(); \endcode
	*
	****************************************************************
	*/
    constexpr void enable() noexcept {
        m_ctlw0.clear(UCSWRST);
    }

    /**
  	* @ingroup groupFuncsMSP430SPI_EUSCI_B
  	****************************************************************
  	* @brief Disables the SPI block
  	* @details
  	* Usage: \code {.cpp}
  	* using namespace MT::MSP430::EUSCIB;
  	*
  	* SPI::B1 b1;
  	* b1.disable(); \endcode
  	*
  	****************************************************************
  	*/
    constexpr void disable() noexcept {
        m_ctlw0.set(UCSWRST);
    }

    /**
   	* @ingroup groupFuncsMSP430SPI_EUSCI_B
   	****************************************************************
   	* @brief Returns the address of the RX Buffer of the SPI for the DMA module
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* SPI::B1 b1;
   	* const auto rxBufAdr = b1.getReceiveBufferAddress(); \endcode
   	*
   	*@return Address of RX Buffer
   	****************************************************************
   	*/
    [[nodiscard]] constexpr auto getReceiveBufferAddress() noexcept {
        return m_rxbuf.getAddress();
    }

    /**
   	* @ingroup groupFuncsMSP430SPI_EUSCI_B
   	****************************************************************
   	* @brief Returns the address of the TX Buffer of the SPI for the DMA module
   	* @details
   	* Usage: \code {.cpp}
   	* using namespace MT::MSP430::EUSCIB;
   	*
   	* SPI::B1 b1;
   	* const auto txBufAdr = b1.getTransmitBufferAddress(); \endcode
   	*
   	*@return Address of TX Buffer
   	****************************************************************
   	*/
    [[nodiscard]] constexpr auto getTransmitBufferAddress() noexcept {
        return m_txbuf.getAddress();
    }

    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Indicates whether or not the SPI bus is busy.
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* SPI::B1 b1;
	* if(b1.isBusy()) doSomething(); \endcode
	*
	*@return Address of TX Buffer
	****************************************************************
	*/
    [[nodiscard]] constexpr bool isBusy() noexcept {
        return (m_statw.get() & UCBUSY);
    }


    /**
	* @ingroup groupFuncsMSP430SPI_EUSCI_B
	****************************************************************
	* @brief Gets the current SPI status flags
	* @details
	* Usage: \code {.cpp}
	* using namespace MT::MSP430::EUSCIB;
	*
	* SPI::B1 b1;
	* if(b1.queryStatusFlags(SPI::STATUS::FRAMING_ERROR | SPI::STATUS::OVERRUN_ERROR) == INT_MASK_MATCH::TRUE) doSomething(); \endcode
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
}// namespace MT::MSP430::EUSCIB::SPI::Internal

namespace MT::MSP430::EUSCIB::I2C {


#if defined(__MSP430_HAS_EUSCI_B0__)
using B0 = Internal::I2C<&UCB0CTLW0, &UCB0CTLW1, &UCB0BRW, &UCB0STATW, &UCB0TBCNT, &UCB0RXBUF, &UCB0TXBUF, &UCB0I2COA0, &UCB0I2COA1, &UCB0I2COA2, &UCB0I2COA3, &UCB0ADDRX, &UCB0ADDMASK, &UCB0I2CSA, &UCB0IE, &UCB0IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_B1__)
using B1 = Internal::I2C<&UCB1CTLW0, &UCB1CTLW1, &UCB1BRW, &UCB1STATW, &UCB1TBCNT, &UCB1RXBUF, &UCB1TXBUF, &UCB1I2COA0, &UCB1I2COA1, &UCB1I2COA2, &UCB1I2COA3, &UCB1ADDRX, &UCB1ADDMASK, &UCB1I2CSA, &UCB1IE, &UCB1IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_B2__)
using B2 = Internal::I2C<&UCB2CTLW0, &UCB2CTLW1, &UCB2BRW, &UCB2STATW, &UCB2TBCNT, &UCB2RXBUF, &UCB2TXBUF, &UCB2I2COA0, &UCB2I2COA1, &UCB2I2COA2, &UCB2I2COA3, &UCB2ADDRX, &UCB2ADDMASK, &UCB2I2CSA, &UCB2IE, &UCB2IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_B3__)
using B3 = Internal::I2C<&UCB3CTLW0, &UCB3CTLW1, &UCB3BRW, &UCB3STATW, &UCB3TBCNT, &UCB3RXBUF, &UCB3TXBUF, &UCB3I2COA0, &UCB3I2COA1, &UCB3I2COA2, &UCB3I2COA3, &UCB3ADDRX, &UCB3ADDMASK, &UCB3I2CSA, &UCB3IE, &UCB3IFG>;
#endif

}// namespace MT::MSP430::EUSCIB::I2C


namespace MT::MSP430::EUSCIB::SPI {

#if defined(__MSP430_HAS_EUSCI_B0__)
using B0 = Internal::SPI<&UCB0CTLW0, &UCB0BRW, &UCB0STATW, &UCB0RXBUF, &UCB0TXBUF, &UCB0IE, &UCB0IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_B1__)
using B1 = Internal::SPI<&UCB1CTLW0, &UCB1BRW, &UCB1STATW, &UCB1RXBUF, &UCB1TXBUF, &UCB1IE, &UCB1IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_B2__)
using B2 = Internal::SPI<&UCB2CTLW0, &UCB2BRW, &UCB2STATW, &UCB2RXBUF, &UCB2TXBUF, &UCB2IE, &UCB2IFG>;
#endif

#if defined(__MSP430_HAS_EUSCI_B3__)
using B3 = Internal::SPI<&UCB3CTLW0, &UCB3BRW, &UCB3STATW, &UCB3RXBUF, &UCB3TXBUF, &UCB3IE, &UCB3IFG>;
#endif

}// namespace MT::MSP430::EUSCIB::SPI

#endif
#endif
#endif /* MICROTRAIT_MSP430_EUSCI_EUSCIB_HPP_ */

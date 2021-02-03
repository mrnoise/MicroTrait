#ifndef MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_

#include <MicroTrait/MSP430/Types.hpp>
#include <MicroTrait/MSP430/EUSCI/EusciA.hpp>
#include <assert.h>

namespace MT::Tests::MSP430::EUSCIA::Internal {

using namespace MT::MSP430::EUSCIA;
using namespace MT::MSP430;


void runUart() noexcept {

    UART::initParam param{
        // Baudrate 9600 at 1MHz SMCLCK
        UART::CLOCKSOURCE::SMCLK,
        6,
        8,
        17,
        UART::PARITY::EVEN,
        UART::ENDIAN::MSB_FIRST,
        UART::STOPBIT::TWO,
        UART::MODE::UART,
        UART::BAUD_GENERATION::OVERSAMPLING
    };

    UART::A0 a0;
    a0.init(param);
    assert(UCA0CTLW0 == (UCSWRST | UCSSEL__SMCLK | UCPAR | UCPEN | UCMSB | UCSPB));
    assert(UCA0BRW == 6);
    assert(UCA0MCTLW & UCOS16);
    assert(UCA0MCTLW & 0x1181);

    param.parity = UART::PARITY::ODD;
    a0.init(param);
    assert(UCA0CTLW0 == (UCSWRST | UCSSEL__SMCLK | UCPEN | UCMSB | UCSPB));

    param.parity = UART::PARITY::NO;
    a0.init(param);
    assert(UCA0CTLW0 == (UCSWRST | UCSSEL__SMCLK | UCMSB | UCSPB));

    a0.transmitData(127);
    assert(UCA0TXBUF == 127);

    a0.enable();
    assert((UCA0CTLW0 & UCSWRST) == 0);

    UCA0IE |= UCRXIE;
    const auto rxByte = a0.receiveData();
    assert(rxByte == 0);
    UCA0IE = 0;

    a0.disable();
    assert(UCA0CTLW0 & UCSWRST);
}

void runUartInterrupt() noexcept {

    UCA0CTLW0 &= ~UCSWRST;
    UCA0IFG = 0;

    UART::A0 a0;
    a0.enableInterrupt(UART::INT::RECEIVE | UART::INT::TRANSMIT, UART::INT_EXT::RECEIVE_ERROR);
    assert(UCA0IE & (UCRXIE | UCTXIE));
    assert(UCA0CTLW0 & UCRXEIE);

    a0.disableInterrupt(UART::INT::RECEIVE | UART::INT::TRANSMIT, UART::INT_EXT::RECEIVE_ERROR);
    assert((UCA0IE & (UCRXIE | UCTXIE)) == 0);
    assert((UCA0CTLW0 & UCRXEIE) == 0);

    UCA0IFG |= UCRXIFG | UCTXIFG;
    const auto flags = a0.getInterruptStatus(UART::INT::RECEIVE | UART::INT::TRANSMIT);
    assert(flags == MASK_MATCH::TRUE);

    a0.clearInterrupt(UART::INT::RECEIVE | UART::INT::TRANSMIT);
    assert(UCA0IFG == 0);

    UCA0CTLW0 |= UCSWRST;
}


void runUartMisc() noexcept {

    UCA0CTLW0 &= ~UCSWRST;
    UCA0IFG = 0;

    UART::A0 a0;

    UCA0STATW |= UCRXERR | UCFE;
    const auto flags = a0.queryStatusFlags(UART::STATUS::RECEIVE_ERROR | UART::STATUS::FRAMING_ERROR);
    assert(flags == MASK_MATCH::TRUE);
    UCA0STATW = 0;

    a0.setDormant();
    assert(UCA0CTLW0 & UCDORM);

    a0.resetDormant();
    assert((UCA0CTLW0 & UCDORM) == 0);

    a0.transmitAddress(127);
    assert(UCA0CTLW0 & UCTXADDR);
    assert(UCA0TXBUF == 127);
    UCA0CTLW0 &= ~UCTXADDR;

    UCA0CTLW0 |= UCMODE_3;
    a0.transmitBreak();
    assert(UCA0TXBUF == 0x55);
    UCA0CTLW0 &= ~UCMODE_3;
    a0.transmitBreak();
    assert(UCA0TXBUF == 0x00);

    const auto rxBufAdr = a0.getReceiveBufferAddress();
    assert(rxBufAdr == std::addressof(UCA0RXBUF));

    const auto txBufAdr = a0.getTransmitBufferAddress();
    assert(txBufAdr == std::addressof(UCA0TXBUF));

    a0.selectDeglitchTime(UART::DEGLITCH::TIME_200NS);
    assert(UCA0CTLW1 & UCGLIT_3);

    a0.selectDeglitchTime(UART::DEGLITCH::TIME_2NS);
    assert(UCA0CTLW1 == 0);

    UCA0CTLW0 |= UCSWRST;
}


void runSpiMaster() noexcept {
    UCA1CTLW0 = 0;
    UCA1BRW   = 0;
    UCA1MCTLW = 0;

    SPI::initMasterParam param{
        SPI::CLOCKSOURCE::SMCLK,
        1'000'000,
        400'000,
        SPI::ENDIAN::MSB_FIRST,
        SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
        SPI::MODE::WITHOUT_CHIPSELECT
    };

    SPI::A1 a1;
    a1.select4PinFunctionality(SPI::FUNCIONALITY_4PINS::ENABLE_SIGNAL_FOR_4WIRE_SLAVE);
    a1.initMaster(param);
    assert(UCA1CTLW0 == (UCSWRST | UCCKPH | UCCKPL | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK | UCSTEM));
    assert(UCA1BRW == 2);
    assert(UCA1MCTLW == 0);
    a1.select4PinFunctionality(SPI::FUNCIONALITY_4PINS::PREVENT_CONFLICTS_WITH_OTHER_MASTERS);

    param.clkPhase = SPI::CLOCKPHASE::DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    a1.initMaster(param);
    assert(UCA1CTLW0 == (UCSWRST | UCCKPL | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK));

    param.clkPolarity = SPI::CLOCKPOLARITY::INACTIVITY_LOW;
    a1.initMaster(param);
    assert(UCA1CTLW0 == (UCSWRST | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK));

    param.mode = SPI::MODE::CHIPSELECT_ACTIVE_HIGH;
    a1.initMaster(param);
    assert(UCA1CTLW0 == (UCSWRST | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK | UCMODE_1));

    param.mode = SPI::MODE::CHIPSELECT_ACTIVE_LOW;
    a1.initMaster(param);
    assert(UCA1CTLW0 == (UCSWRST | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK | UCMODE_2));

    SPI::changeMasterClockParam clkParam{
        16'000'000,
        4'000'000
    };
    a1.changeMasterClock(clkParam);
    assert(UCA1BRW == 4);

    a1.enable();
    assert((UCA1CTLW0 & UCSWRST) == 0);

    a1.disable();
    assert(UCA1CTLW0 & UCSWRST);

    assert(!a1.isBusy());
}

void runSpiSlave() noexcept {
    UCA1CTLW0 = 0;

    SPI::initSlaveParam param{
        SPI::ENDIAN::MSB_FIRST,
        SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
        SPI::MODE::WITHOUT_CHIPSELECT
    };

    SPI::A1 a1;
    a1.initSlave(param);
    assert(UCA1CTLW0 == (UCSWRST | UCCKPH | UCCKPL | UCMSB | UCSYNC));

    param.clkPhase = SPI::CLOCKPHASE::DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    a1.initSlave(param);
    assert(UCA1CTLW0 == (UCSWRST | UCCKPL | UCMSB | UCSYNC));

    param.clkPolarity = SPI::CLOCKPOLARITY::INACTIVITY_LOW;
    a1.initSlave(param);
    assert(UCA1CTLW0 == (UCSWRST | UCMSB | UCSYNC));

    param.mode = SPI::MODE::CHIPSELECT_ACTIVE_HIGH;
    a1.initSlave(param);
    assert(UCA1CTLW0 == (UCSWRST | UCMSB | UCSYNC | UCMODE_1));

    param.mode = SPI::MODE::CHIPSELECT_ACTIVE_LOW;
    a1.initSlave(param);
    assert(UCA1CTLW0 == (UCSWRST | UCMSB | UCSYNC | UCMODE_2));
}

void runSpiMisc() noexcept {

    UCA1CTLW0 = 0;
    SPI::A1 a1;
    a1.changeClockPhasePolarity(SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT, SPI::CLOCKPOLARITY::INACTIVITY_HIGH);
    assert(UCA1CTLW0 == (UCCKPH | UCCKPL));

    a1.changeClockPhasePolarity(SPI::CLOCKPHASE::DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT, SPI::CLOCKPOLARITY::INACTIVITY_HIGH);
    assert(UCA1CTLW0 == (UCCKPL));

    a1.changeClockPhasePolarity(SPI::CLOCKPHASE::DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT, SPI::CLOCKPOLARITY::INACTIVITY_LOW);
    assert(UCA1CTLW0 == 0);

    a1.transmitData(127);
    assert(UCA1TXBUF == 127);

    const auto rxByte = a1.receiveData();
    assert(rxByte == 0);

    const auto rxBufAdr = a1.getReceiveBufferAddress();
    assert(rxBufAdr == std::addressof(UCA1RXBUF));

    const auto txBufAdr = a1.getTransmitBufferAddress();
    assert(txBufAdr == std::addressof(UCA1TXBUF));

    UCA1STATW |= UCFE | UCOE;
    const auto match = a1.queryStatusFlags(SPI::STATUS::FRAMING_ERROR | SPI::STATUS::OVERRUN_ERROR);
    assert(match == MASK_MATCH::TRUE);
}

void runSpiInterrupt() noexcept {
    UCA1IE  = 0;
    UCA1IFG = 0;
    UCA1CTLW0 &= ~UCSWRST;

    SPI::A1 a1;
    a1.enableInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT);
    assert(UCA1IE & (UCRXIE | UCTXIE));

    a1.disableInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT);
    assert((UCA1IE & (UCRXIE | UCTXIE)) == 0);

    UCA1IFG |= UCRXIFG | UCTXIFG;
    const auto flags = a1.getInterruptStatus(SPI::INT::RECEIVE | SPI::INT::TRANSMIT);
    assert(flags == MASK_MATCH::TRUE);

    a1.clearInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT);
    assert(UCA1IFG == 0);

    UCA1CTLW0 |= UCSWRST;
}

}// namespace MT::Tests::MSP430::EUSCIA::Internal


namespace MT::Tests::MSP430::EUSCIA {
void run() noexcept {
#if defined(__MSP430_HAS_EUSCI_A0__) && defined(__MSP430_HAS_EUSCI_A1__)
    Internal::runUart();
    Internal::runUartInterrupt();
    Internal::runUartMisc();

    Internal::runSpiMaster();
    Internal::runSpiSlave();
    Internal::runSpiMisc();
    Internal::runSpiInterrupt();
#else
    assert(1 == 2);// Test not executed!!
#endif
}
}// namespace MT::Tests::MSP430::EUSCIA

#endif /* MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_ */


#ifndef MICROTRAIT_TESTS_MSP430_TESTEUSCIB_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTEUSCIB_HPP_

#include <MicroTrait/MSP430/Types.hpp>
#include <MicroTrait/MSP430/EUSCI/EusciB.hpp>
#include <assert.h>

namespace MT::Tests::MSP430::EUSCIB::Internal {

using namespace MT::MSP430::EUSCIB;
using namespace MT::MSP430;


void runI2cMaster() noexcept {
    UCB0CTLW0 = 0;
    UCB0CTLW1 = 0;
    UCB0BRW   = 0;
    UCB0TBCNT = 0;

    I2C::initMasterParam param{
        I2C::CLOCKSOURCE::SMCLK,
        1'000'000,
        I2C::DATARATE::_100KBPS,
        255,
        I2C::AUTOSTOP::OFF
    };

    I2C::B0 b0;
    b0.initMaster(param);
    assert(UCB0CTLW0 == (UCSWRST | UCMST | UCMODE_3 | UCSYNC | UCSSEL__SMCLK));
    assert(UCB0CTLW1 == UCASTP_0);
    assert(UCB0TBCNT == 255);
    assert(UCB0BRW == 10);

    param.datarate             = I2C::DATARATE::_400KBPS;
    param.byteCounterThreshold = 0;
    param.autostop             = I2C::AUTOSTOP::SEND_STOP_AUTOMATICALLY_ON_BYTECOUNT_THRESHOLD;
    b0.initMaster(param);
    assert(UCB0CTLW0 == (UCSWRST | UCMST | UCMODE_3 | UCSYNC | UCSSEL__SMCLK));
    assert(UCB0CTLW1 == UCASTP_2);
    assert(UCB0TBCNT == 0);
    assert(UCB0BRW == 2);

    b0.enable();
    assert((UCB0CTLW0 & UCSWRST) == 0);

    b0.disable();
    assert(UCB0CTLW0 & UCSWRST);

    b0.setSlaveAddress(0x0A);
    assert(UCB0I2CSA == 0x0A);

    b0.setMode(I2C::MODE::TX);
    assert(UCB0CTLW0 & UCTR);

    b0.setMode(I2C::MODE::RX);
    assert((UCB0CTLW0 & UCTR) == 0);

    assert(b0.isBusBusy() == I2C::BUSY::NO);

    UCB0CTLW0 |= UCTXSTP;
    assert(b0.masterIsStopSent() == I2C::STOP_STATE::SENDING);
    UCB0CTLW0 &= ~UCTXSTP;
    assert(b0.masterIsStopSent() == I2C::STOP_STATE::SEND_COMPLETE);

    UCB0CTLW0 |= UCTXSTT;
    assert(b0.masterIsStartSent() == I2C::START_STATE::SENDING);
    UCB0CTLW0 &= ~UCTXSTT;
    assert(b0.masterIsStartSent() == I2C::START_STATE::SEND_COMPLETE);

    assert(b0.masterSendSingleByte(127) == STATUS::SUCCESS);
    assert(b0.masterReceiveSingleByte() == 0);
    assert(b0.masterSendMultiByteStart(127) == STATUS::SUCCESS);
    assert(b0.masterSendMultiByteNext(127) == STATUS::SUCCESS);
    assert(b0.masterSendMultiByteFinish(127) == STATUS::SUCCESS);
    b0.masterSendStart();
    assert(b0.masterIsStartSent() == I2C::START_STATE::SENDING);
    assert(b0.masterSendMultiByteStop() == STATUS::SUCCESS);

    b0.masterReceiveStart();
    assert(UCB0CTLW0 & UCTXSTT);
    assert((UCB0CTLW0 & UCTR) == 0);
    assert(b0.masterReceiveMultiByteNext() == 0);
    assert(b0.masterReceiveMultiByteFinish() == 0);
    assert(UCB0CTLW0 & UCTXSTP);
    b0.masterReceiveMultiByteStop();
    assert(UCB0CTLW0 & UCTXSTP);

    b0.enableMultiMasterMode();
    assert(UCB0CTLW0 & (UCSWRST | UCMM));
    b0.disableMultiMasterMode();
    assert(UCB0CTLW0 & (UCSWRST));
    assert(b0.masterReceiveSingle() == 0);
}


void runI2cSlave() noexcept {

    UCB0CTLW0  = 0;
    UCB0I2COA0 = 0;
    UCB0I2COA1 = 0;
    UCB0I2COA2 = 0;
    UCB0I2COA3 = 0;

    I2C::initSlaveParam param{
        0x0A,
        I2C::SLAVE_ADDRESS_OFFSET::_0,
        I2C::SLAVE_ADDRESS::DISABLED
    };

    I2C::B0 b0;
    b0.initSlave(param);
    assert(UCB0CTLW0 == (UCSWRST | UCMODE_3 | UCSYNC));
    assert(UCB0I2COA0 == 0x0A);

    param.onOff = I2C::SLAVE_ADDRESS::ENABLED;
    b0.initSlave(param);
    assert(UCB0CTLW0 == (UCSWRST | UCMODE_3 | UCSYNC));
    assert(UCB0I2COA0 == (0x0A | UCOAEN));

    param.adrOffset = I2C::SLAVE_ADDRESS_OFFSET::_1;
    b0.initSlave(param);
    assert(UCB0I2COA1 == (0x0A | UCOAEN));

    param.adrOffset = I2C::SLAVE_ADDRESS_OFFSET::_2;
    b0.initSlave(param);
    assert(UCB0I2COA2 == (0x0A | UCOAEN));

    param.adrOffset = I2C::SLAVE_ADDRESS_OFFSET::_3;
    b0.initSlave(param);
    assert(UCB0I2COA3 == (0x0A | UCOAEN));

    b0.slavePutData(127);
    assert(UCB0TXBUF == 127);
    assert(UCB0RXBUF == b0.slaveGetData());
}

void runI2cInterrupt() noexcept {

    UCB0IE  = 0;
    UCB0IFG = 0;
    UCB0CTLW0 &= ~UCSWRST;

    I2C::B0 b0;
    b0.enableInterrupt(I2C::INT::RECEIVE_0 | I2C::INT::TRANSMIT_0);
    assert(UCB0IE & (UCRXIE0 | UCTXIE0));

    b0.disableInterrupt(I2C::INT::RECEIVE_0 | I2C::INT::TRANSMIT_0);
    assert((UCB0IE & (UCRXIE0 | UCTXIE0)) == 0);

    UCB0IFG |= UCRXIFG0 | UCTXIFG0;
    const auto flags = b0.getInterruptStatus(I2C::INT::RECEIVE_0 | I2C::INT::TRANSMIT_0);
    assert(flags == MASK_MATCH::TRUE);

    b0.clearInterrupt(I2C::INT::RECEIVE_0 | I2C::INT::TRANSMIT_0);
    assert(UCB0IFG == 0);

    UCB0CTLW0 |= UCSWRST;
}

void runI2cMisc() noexcept {
    UCB0CTLW0 = 0;

    I2C::B0 b0;
    b0.setMode(I2C::MODE::TX);
    assert(UCB0CTLW0 & UCTR);
    assert(b0.getMode() == I2C::MODE::TX);

    b0.setMode(I2C::MODE::RX);
    assert((UCB0CTLW0 & UCTR) == 0);
    assert(b0.getMode() == I2C::MODE::RX);

    const auto rxBufAdr = b0.getReceiveBufferAddress();
    assert(rxBufAdr == std::addressof(UCB0RXBUF));

    const auto txBufAdr = b0.getTransmitBufferAddress();
    assert(txBufAdr == std::addressof(UCB0TXBUF));

    b0.setTimeout(I2C::TIMEOUT::_34_MS);
    assert(UCB0CTLW1 & UCCLTO_3);

    b0.setTimeout(I2C::TIMEOUT::DISABLED);
    assert((UCB0CTLW1 & UCCLTO_0) == 0);
}

void runSpiMaster() noexcept {
    UCB1CTLW0 = 0;
    UCB1BRW   = 0;

    SPI::initMasterParam param{
        SPI::CLOCKSOURCE::SMCLK,
        1'000'000,
        400'000,
        SPI::ENDIAN::MSB_FIRST,
        SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
        SPI::MODE::WITHOUT_CHIPSELECT
    };

    SPI::B1 b1;
    b1.select4PinFunctionality(SPI::FUNCIONALITY_4PINS::ENABLE_SIGNAL_FOR_4WIRE_SLAVE);
    b1.initMaster(param);
    assert(UCB1CTLW0 == (UCSWRST | UCCKPH | UCCKPL | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK | UCSTEM));
    assert(UCB1BRW == 2);
    b1.select4PinFunctionality(SPI::FUNCIONALITY_4PINS::PREVENT_CONFLICTS_WITH_OTHER_MASTERS);

    param.clkPhase = SPI::CLOCKPHASE::DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    b1.initMaster(param);
    assert(UCB1CTLW0 == (UCSWRST | UCCKPL | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK));

    param.clkPolarity = SPI::CLOCKPOLARITY::INACTIVITY_LOW;
    b1.initMaster(param);
    assert(UCB1CTLW0 == (UCSWRST | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK));

    param.mode = SPI::MODE::CHIPSELECT_ACTIVE_HIGH;
    b1.initMaster(param);
    assert(UCB1CTLW0 == (UCSWRST | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK | UCMODE_1));

    param.mode = SPI::MODE::CHIPSELECT_ACTIVE_LOW;
    b1.initMaster(param);
    assert(UCB1CTLW0 == (UCSWRST | UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK | UCMODE_2));

    SPI::changeMasterClockParam clkParam{
        16'000'000,
        4'000'000
    };
    b1.changeMasterClock(clkParam);
    assert(UCB1BRW == 4);

    b1.enable();
    assert((UCB1CTLW0 & UCSWRST) == 0);

    b1.disable();
    assert(UCB1CTLW0 & UCSWRST);

    assert(!b1.isBusy());
}

void runSpiSlave() noexcept {
    UCB1CTLW0 = 0;

    SPI::initSlaveParam param{
        SPI::ENDIAN::MSB_FIRST,
        SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        SPI::CLOCKPOLARITY::INACTIVITY_HIGH,
        SPI::MODE::WITHOUT_CHIPSELECT
    };

    SPI::B1 b1;
    b1.initSlave(param);
    assert(UCB1CTLW0 == (UCSWRST | UCCKPH | UCCKPL | UCMSB | UCSYNC));

    param.clkPhase = SPI::CLOCKPHASE::DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    b1.initSlave(param);
    assert(UCB1CTLW0 == (UCSWRST | UCCKPL | UCMSB | UCSYNC));

    param.clkPolarity = SPI::CLOCKPOLARITY::INACTIVITY_LOW;
    b1.initSlave(param);
    assert(UCB1CTLW0 == (UCSWRST | UCMSB | UCSYNC));

    param.mode = SPI::MODE::CHIPSELECT_ACTIVE_HIGH;
    b1.initSlave(param);
    assert(UCB1CTLW0 == (UCSWRST | UCMSB | UCSYNC | UCMODE_1));

    param.mode = SPI::MODE::CHIPSELECT_ACTIVE_LOW;
    b1.initSlave(param);
    assert(UCB1CTLW0 == (UCSWRST | UCMSB | UCSYNC | UCMODE_2));
}

void runSpiMisc() noexcept {

    UCB1CTLW0 = 0;
    SPI::B1 b1;
    b1.changeClockPhasePolarity(SPI::CLOCKPHASE::DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT, SPI::CLOCKPOLARITY::INACTIVITY_HIGH);
    assert(UCB1CTLW0 == (UCCKPH | UCCKPL | UCSYNC));

    b1.changeClockPhasePolarity(SPI::CLOCKPHASE::DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT, SPI::CLOCKPOLARITY::INACTIVITY_HIGH);
    assert(UCB1CTLW0 == (UCCKPL | UCSYNC));

    b1.changeClockPhasePolarity(SPI::CLOCKPHASE::DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT, SPI::CLOCKPOLARITY::INACTIVITY_LOW);
    assert(UCB1CTLW0 == UCSYNC);

    b1.transmitData(127);
    assert(UCB1TXBUF == 127);

    const auto rxByte = b1.receiveData();
    assert(rxByte == 0);

    const auto rxBufAdr = b1.getReceiveBufferAddress();
    assert(rxBufAdr == std::addressof(UCB1RXBUF));

    const auto txBufAdr = b1.getTransmitBufferAddress();
    assert(txBufAdr == std::addressof(UCB1TXBUF));

    UCB1STATW |= UCFE | UCOE;
    const auto match = b1.queryStatusFlags(SPI::STATUS::FRAMING_ERROR | SPI::STATUS::OVERRUN_ERROR);
    assert(match == MASK_MATCH::TRUE);
}

void runSpiInterrupt() noexcept {
    UCB1IE  = 0;
    UCB1IFG = 0;
    UCB1CTLW0 &= ~UCSWRST;

    SPI::B1 b1;
    b1.enableInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT);
    assert(UCB1IE & (UCRXIE | UCTXIE));

    b1.disableInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT);
    assert((UCB1IE & (UCRXIE | UCTXIE)) == 0);

    UCB1IFG |= UCRXIFG | UCTXIFG;
    const auto flags = b1.getInterruptStatus(SPI::INT::RECEIVE | SPI::INT::TRANSMIT);
    assert(flags == MASK_MATCH::TRUE);

    b1.clearInterrupt(SPI::INT::RECEIVE | SPI::INT::TRANSMIT);
    assert(UCB1IFG == 0);

    UCB1CTLW0 |= UCSWRST;
}

}// namespace MT::Tests::MSP430::EUSCIB::Internal


namespace MT::Tests::MSP430::EUSCIB {
void run() noexcept {
#if defined(__MSP430_HAS_EUSCI_B0__) && defined(__MSP430_HAS_EUSCI_B1__)

    Internal::runI2cMaster();
    Internal::runI2cSlave();
    Internal::runI2cInterrupt();
    Internal::runI2cMisc();

    Internal::runSpiMaster();
    Internal::runSpiSlave();
    Internal::runSpiMisc();
    Internal::runSpiInterrupt();
#else
    assert(1 == 2);// Test not executed!!
#endif
}

}// namespace MT::Tests::MSP430::EUSCIB

#endif /* MICROTRAIT_TESTS_MSP430_TESTEUSCIB_HPP_ */

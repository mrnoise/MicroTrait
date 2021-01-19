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

    assert(UCA0CTLW0 & UCSWRST);
    assert(UCA0CTLW0 & UCSSEL__SMCLK);
    assert(UCA0CTLW0 & UCPAR);
    assert(UCA0CTLW0 & UCPEN);
    assert(UCA0CTLW0 & UCMSB);
    assert(UCA0CTLW0 & UCSPB);
    assert((UCA0CTLW0 & UCMODE_0) == 0);
    assert((UCA0CTLW0 & UCSYNC) == 0);
    assert((UCA0CTLW0 & UC7BIT) == 0);
    assert((UCA0CTLW0 & UCRXEIE) == 0);
    assert((UCA0CTLW0 & UCBRKIE) == 0);
    assert((UCA0CTLW0 & UCDORM) == 0);
    assert((UCA0CTLW0 & UCTXADDR) == 0);
    assert((UCA0CTLW0 & UCTXBRK) == 0);

    assert(UCA0BRW == 6);
    assert(UCA0MCTLW & UCOS16);
    assert(UCA0MCTLW & 0x1181);

    param.parity = UART::PARITY::ODD;
    a0.init(param);
    assert(UCA0CTLW0 & UCSWRST);
    assert(UCA0CTLW0 & UCSSEL__SMCLK);
    assert((UCA0CTLW0 & UCPAR) == 0);
    assert(UCA0CTLW0 & UCPEN);
    assert(UCA0CTLW0 & UCMSB);
    assert(UCA0CTLW0 & UCSPB);
    assert((UCA0CTLW0 & UCMODE_0) == 0);
    assert((UCA0CTLW0 & UCSYNC) == 0);
    assert((UCA0CTLW0 & UC7BIT) == 0);
    assert((UCA0CTLW0 & UCRXEIE) == 0);
    assert((UCA0CTLW0 & UCBRKIE) == 0);
    assert((UCA0CTLW0 & UCDORM) == 0);
    assert((UCA0CTLW0 & UCTXADDR) == 0);
    assert((UCA0CTLW0 & UCTXBRK) == 0);

    param.parity = UART::PARITY::NO;
    a0.init(param);
    assert(UCA0CTLW0 & UCSWRST);
    assert(UCA0CTLW0 & UCSSEL__SMCLK);
    assert((UCA0CTLW0 & UCPAR) == 0);
    assert((UCA0CTLW0 & UCPEN) == 0);
    assert(UCA0CTLW0 & UCMSB);
    assert(UCA0CTLW0 & UCSPB);
    assert((UCA0CTLW0 & UCMODE_0) == 0);
    assert((UCA0CTLW0 & UCSYNC) == 0);
    assert((UCA0CTLW0 & UC7BIT) == 0);
    assert((UCA0CTLW0 & UCRXEIE) == 0);
    assert((UCA0CTLW0 & UCBRKIE) == 0);
    assert((UCA0CTLW0 & UCDORM) == 0);
    assert((UCA0CTLW0 & UCTXADDR) == 0);
    assert((UCA0CTLW0 & UCTXBRK) == 0);

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
    assert(flags == INT_MASK_MATCH::TRUE);

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
    assert(flags == INT_MASK_MATCH::TRUE);
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
    assert(rxBufAdr == UCA0RXBUF);

    const auto txBufAdr = a0.getTransmitBufferAddress();
    assert(txBufAdr == UCA0TXBUF);

    a0.selectDeglitchTime(UART::DEGLITCH::TIME_200NS);
    assert(UCA0CTLW1 & UCGLIT_3);

    a0.selectDeglitchTime(UART::DEGLITCH::TIME_2NS);
    assert(UCA0CTLW1 == 0);

    UCA0CTLW0 |= UCSWRST;
}

}// namespace MT::Tests::MSP430::EUSCIA::Internal


namespace MT::Tests::MSP430::EUSCIA {
void run() noexcept {
#if defined(__MSP430_HAS_EUSCI_A0__)
    Internal::runUart();
    Internal::runUartInterrupt();
    Internal::runUartMisc();
#else
    assert(1 == 2);// Test not executed!!
#endif
}
}// namespace MT::Tests::MSP430::EUSCIA

#endif /* MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_ */

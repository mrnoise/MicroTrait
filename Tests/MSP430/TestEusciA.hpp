#ifndef MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_

#include <MicroTrait/MSP430/Types.hpp>
#include <MicroTrait/MSP430/EUSCI/EusciA.hpp>
#include <assert.h>

namespace MT::Tests::MSP430::EUSCIA::Internal {

using namespace MT::MSP430::EUSCIA;
using namespace MT::MSP430;


void runUART() noexcept {

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
    // assert(UCA0MCTLW & UCOS16);
}


}// namespace MT::Tests::MSP430::EUSCIA::Internal


namespace MT::Tests::MSP430::EUSCIA {
void run() noexcept {
#if defined(__MSP430_HAS_EUSCI_A0__)
    Internal::runUART();
#else
    assert(1 == 2);// Test not executed!!
#endif
}
}// namespace MT::Tests::MSP430::EUSCIA

#endif /* MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_ */

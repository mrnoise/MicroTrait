#ifndef MICROTRAIT_TESTS_MSP430_TESTGPIO_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTGPIO_HPP_

#include "MicroTrait/MSP430/GPIO/Gpio.hpp"
#include "MicroTrait/MSP430/GPIO/GpioInterrupt.hpp"
#include <assert.h>


namespace MT::Tests::MSP430::GPIO::Internal {

using namespace MT::MSP430::GPIO;

template<typename PORT>
void testOut(PORT p, volatile uint16_t *reg) noexcept {
}


void runPortDirection() noexcept {

#if defined(__MSP430_HAS_PORT1_R__) || defined(__MSP430_HAS_PORT1__)
    Port1 p1{};
    p1.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1DIR == 0b01010101);

    p1.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1DIR == 0b10101010);

    p1.setAsOutputPin(PIN::ALL);
    assert(P1DIR == 0xFF);

    p1.setAsInputPin(PIN::ALL);
    assert(P1DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT2_R__) || defined(__MSP430_HAS_PORT2__)
    Port2 p2{};
    p2.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2DIR == 0b01010101);

    p2.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2DIR == 0b10101010);

    p2.setAsOutputPin(PIN::ALL);
    assert(P2DIR == 0xFF);

    p2.setAsInputPin(PIN::ALL);
    assert(P2DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT3_R__) || defined(__MSP430_HAS_PORT3__)
    Port3 p3{};
    p3.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3DIR == 0b01010101);

    p3.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3DIR == 0b10101010);

    p3.setAsOutputPin(PIN::ALL);
    assert(P3DIR == 0xFF);

    p3.setAsInputPin(PIN::ALL);
    assert(P3DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT4_R__) || defined(__MSP430_HAS_PORT4__)
    Port4 p4{};
    p4.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4DIR == 0b01010101);

    p4.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4DIR == 0b10101010);

    p4.setAsOutputPin(PIN::ALL);
    assert(P4DIR == 0xFF);

    p4.setAsInputPin(PIN::ALL);
    assert(P4DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT5_R__) || defined(__MSP430_HAS_PORT5__)
    Port5 p5{};
    p5.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p5.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P5DIR == 0b01010101);

    p5.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p5.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P5DIR == 0b10101010);

    p5.setAsOutputPin(PIN::ALL);
    assert(P5DIR == 0xFF);

    p5.setAsInputPin(PIN::ALL);
    assert(P5DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT6_R__) || defined(__MSP430_HAS_PORT6__)
    Port6 p6{};
    p6.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p6.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P6DIR == 0b01010101);

    p6.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p6.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P6DIR == 0b10101010);

    p6.setAsOutputPin(PIN::ALL);
    assert(P6DIR == 0xFF);

    p6.setAsInputPin(PIN::ALL);
    assert(P6DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT7_R__) || defined(__MSP430_HAS_PORT7__)
    Port7 p7{};
    p7.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p7.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P7DIR == 0b01010101);

    p7.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p7.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P7DIR == 0b10101010);

    p7.setAsOutputPin(PIN::ALL);
    assert(P7DIR == 0xFF);

    p7.setAsInputPin(PIN::ALL);
    assert(P7DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT8_R__) || defined(__MSP430_HAS_PORT8__)
    Port8 p8{};
    p8.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p8.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P8DIR == 0b01010101);

    p8.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p8.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P8DIR == 0b10101010);

    p8.setAsOutputPin(PIN::ALL);
    assert(P8DIR == 0xFF);

    p8.setAsInputPin(PIN::ALL);
    assert(P8DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT9_R__) || defined(__MSP430_HAS_PORT9__)
    Port9 p9{};
    p9.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p9.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P9DIR == 0b01010101);

    p9.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p9.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P9DIR == 0b10101010);

    p9.setAsOutputPin(PIN::ALL);
    assert(P9DIR == 0xFF);

    p9.setAsInputPin(PIN::ALL);
    assert(P9DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT10_R__) || defined(__MSP430_HAS_PORT10__)
    Port10 p10{};
    p10.setAsOutputPin(PIN::P0 | PIN::P2);
    p10.setAsInputPin(PIN::P1);
    assert(P10DIR == 0b0000101);

    p10.setAsInputPin(PIN::P0 | PIN::P2);
    p10.setAsOutputPin(PIN::P1);
    assert(P10DIR == 0b00000010);

    p10.setAsInputPin(PIN::ALL);
    assert(P10DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT11_R__) || defined(__MSP430_HAS_PORT11__)
    Port11 p11{};
    p11.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p11.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P11DIR == 0b01010101);

    p11.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p11.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P11DIR == 0b10101010);

    p11.setAsOutputPin(PIN::ALL);
    assert(P11DIR == 0xFF);

    p11.setAsInputPin(PIN::ALL);
    assert(P11DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORTJ_R__) || defined(__MSP430_HAS_PORTJ__)
    PortJ pj{};
    pj.setAsOutputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    pj.setAsInputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(PJDIR == 0b01010101);

    pj.setAsInputPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    pj.setAsOutputPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(PJDIR == 0b10101010);

    pj.setAsOutputPin(PIN::ALL);
    assert(PJDIR == 0xFF);

    pj.setAsInputPin(PIN::ALL);
    assert(PJDIR == 0x00);
#endif
}

void runPortPullUpDown() noexcept {

#if defined(__MSP430_HAS_PORT1_R__) || defined(__MSP430_HAS_PORT1__)
    Port1 p1{};
    p1.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1DIR == 0x00);
    assert(P1REN == 0xFF);
    assert(P1OUT == 0b10101010);

    p1.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1DIR == 0x00);
    assert(P1REN == 0xFF);
    assert(P1OUT == 0b01010101);

    p1.setAsInputPinWithPullUp(PIN::ALL);
    assert(P1DIR == 0x00);
    assert(P1REN == 0xFF);
    assert(P1OUT == 0xFF);

    p1.setAsInputPinWithPullDown(PIN::ALL);
    assert(P1DIR == 0x00);
    assert(P1REN == 0xFF);
    assert(P1OUT == 0x00);

    p1.setAsInputPin(PIN::ALL);
    assert(P1REN == 0x00);
    assert(P1DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT2_R__) || defined(__MSP430_HAS_PORT2__)
    Port2 p2{};
    p2.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2DIR == 0x00);
    assert(P2REN == 0xFF);
    assert(P2OUT == 0b10101010);

    p2.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2DIR == 0x00);
    assert(P2REN == 0xFF);
    assert(P2OUT == 0b01010101);

    p2.setAsInputPinWithPullUp(PIN::ALL);
    assert(P2DIR == 0x00);
    assert(P2REN == 0xFF);
    assert(P2OUT == 0xFF);

    p2.setAsInputPinWithPullDown(PIN::ALL);
    assert(P2DIR == 0x00);
    assert(P2REN == 0xFF);
    assert(P2OUT == 0x00);

    p2.setAsInputPin(PIN::ALL);
    assert(P2REN == 0x00);
    assert(P2DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT3_R__) || defined(__MSP430_HAS_PORT3__)
    Port3 p3{};
    p3.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3DIR == 0x00);
    assert(P3REN == 0xFF);
    assert(P3OUT == 0b10101010);

    p3.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3DIR == 0x00);
    assert(P3REN == 0xFF);
    assert(P3OUT == 0b01010101);

    p3.setAsInputPinWithPullUp(PIN::ALL);
    assert(P3DIR == 0x00);
    assert(P3REN == 0xFF);
    assert(P3OUT == 0xFF);

    p3.setAsInputPinWithPullDown(PIN::ALL);
    assert(P3DIR == 0x00);
    assert(P3REN == 0xFF);
    assert(P3OUT == 0x00);

    p3.setAsInputPin(PIN::ALL);
    assert(P3REN == 0x00);
    assert(P3DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT4_R__) || defined(__MSP430_HAS_PORT4__)
    Port4 p4{};
    p4.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4DIR == 0x00);
    assert(P4REN == 0xFF);
    assert(P4OUT == 0b10101010);

    p4.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4DIR == 0x00);
    assert(P4REN == 0xFF);
    assert(P4OUT == 0b01010101);

    p4.setAsInputPinWithPullUp(PIN::ALL);
    assert(P4DIR == 0x00);
    assert(P4REN == 0xFF);
    assert(P4OUT == 0xFF);

    p4.setAsInputPinWithPullDown(PIN::ALL);
    assert(P4DIR == 0x00);
    assert(P4REN == 0xFF);
    assert(P4OUT == 0x00);

    p4.setAsInputPin(PIN::ALL);
    assert(P4REN == 0x00);
    assert(P4DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT5_R__) || defined(__MSP430_HAS_PORT5__)
    Port5 p5{};
    p5.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p5.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P5DIR == 0x00);
    assert(P5REN == 0xFF);
    assert(P5OUT == 0b10101010);

    p5.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p5.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P5DIR == 0x00);
    assert(P5REN == 0xFF);
    assert(P5OUT == 0b01010101);

    p5.setAsInputPinWithPullUp(PIN::ALL);
    assert(P5DIR == 0x00);
    assert(P5REN == 0xFF);
    assert(P5OUT == 0xFF);

    p5.setAsInputPinWithPullDown(PIN::ALL);
    assert(P5DIR == 0x00);
    assert(P5REN == 0xFF);
    assert(P5OUT == 0x00);

    p5.setAsInputPin(PIN::ALL);
    assert(P5REN == 0x00);
    assert(P5DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT6_R__) || defined(__MSP430_HAS_PORT6__)
    Port6 p6{};
    p6.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p6.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P6DIR == 0x00);
    assert(P6REN == 0xFF);
    assert(P6OUT == 0b10101010);

    p6.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p6.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P6DIR == 0x00);
    assert(P6REN == 0xFF);
    assert(P6OUT == 0b01010101);

    p6.setAsInputPinWithPullUp(PIN::ALL);
    assert(P6DIR == 0x00);
    assert(P6REN == 0xFF);
    assert(P6OUT == 0xFF);

    p6.setAsInputPinWithPullDown(PIN::ALL);
    assert(P6DIR == 0x00);
    assert(P6REN == 0xFF);
    assert(P6OUT == 0x00);

    p6.setAsInputPin(PIN::ALL);
    assert(P6REN == 0x00);
    assert(P6DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT7_R__) || defined(__MSP430_HAS_PORT7__)
    Port7 p7{};
    p7.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p7.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P7DIR == 0x00);
    assert(P7REN == 0xFF);
    assert(P7OUT == 0b10101010);

    p7.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p7.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P7DIR == 0x00);
    assert(P7REN == 0xFF);
    assert(P7OUT == 0b01010101);

    p7.setAsInputPinWithPullUp(PIN::ALL);
    assert(P7DIR == 0x00);
    assert(P7REN == 0xFF);
    assert(P7OUT == 0xFF);

    p7.setAsInputPinWithPullDown(PIN::ALL);
    assert(P7DIR == 0x00);
    assert(P7REN == 0xFF);
    assert(P7OUT == 0x00);

    p7.setAsInputPin(PIN::ALL);
    assert(P7REN == 0x00);
    assert(P7DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT8_R__) || defined(__MSP430_HAS_PORT8__)
    Port8 p8{};
    p8.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p8.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P8DIR == 0x00);
    assert(P8REN == 0xFF);
    assert(P8OUT == 0b10101010);

    p8.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p8.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P8DIR == 0x00);
    assert(P8REN == 0xFF);
    assert(P8OUT == 0b01010101);

    p8.setAsInputPinWithPullUp(PIN::ALL);
    assert(P8DIR == 0x00);
    assert(P8REN == 0xFF);
    assert(P8OUT == 0xFF);

    p8.setAsInputPinWithPullDown(PIN::ALL);
    assert(P8DIR == 0x00);
    assert(P8REN == 0xFF);
    assert(P8OUT == 0x00);

    p8.setAsInputPin(PIN::ALL);
    assert(P8REN == 0x00);
    assert(P8DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT9_R__) || defined(__MSP430_HAS_PORT9__)
    Port9 p9{};
    p9.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p9.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P9DIR == 0x00);
    assert(P9REN == 0xFF);
    assert(P9OUT == 0b10101010);

    p9.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p9.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P9DIR == 0x00);
    assert(P9REN == 0xFF);
    assert(P9OUT == 0b01010101);

    p9.setAsInputPinWithPullUp(PIN::ALL);
    assert(P9DIR == 0x00);
    assert(P9REN == 0xFF);
    assert(P9OUT == 0xFF);

    p9.setAsInputPinWithPullDown(PIN::ALL);
    assert(P9DIR == 0x00);
    assert(P9REN == 0xFF);
    assert(P9OUT == 0x00);

    p9.setAsInputPin(PIN::ALL);
    assert(P9REN == 0x00);
    assert(P9DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT10_R__) || defined(__MSP430_HAS_PORT10__)
    Port10 p10{};
    p10.setAsInputPinWithPullDown(PIN::P0 | PIN::P2);
    p10.setAsInputPinWithPullUp(PIN::P1);
    assert(P10DIR == 0x00);
    assert(P10REN == 0b00000111);
    assert(P10OUT == 0b00000010);

    p10.setAsInputPinWithPullUp(PIN::P0 | PIN::P2);
    p10.setAsInputPinWithPullDown(PIN::P1);
    assert(P10DIR == 0x00);
    assert(P10REN == 0b00000111);
    assert(P10OUT == 0b00000101);

    p10.setAsInputPinWithPullUp(PIN::ALL);
    assert(P10DIR == 0x00);
    assert(P10REN == 0b00000111);
    assert(P10OUT == 0b00000111);

    p10.setAsInputPinWithPullDown(PIN::ALL);
    assert(P10DIR == 0x00);
    assert(P10REN == 0b00000111);
    assert(P10OUT == 0x00);

    p10.setAsInputPin(PIN::ALL);
    assert(P10REN == 0x00);
    assert(P10DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT11_R__) || defined(__MSP430_HAS_PORT11__)
    Port11 p11{};
    p11.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p11.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P11DIR == 0x00);
    assert(P11REN == 0xFF);
    assert(P11OUT == 0b10101010);

    p11.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p11.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P11DIR == 0x00);
    assert(P11REN == 0xFF);
    assert(P11OUT == 0b01010101);

    p11.setAsInputPinWithPullUp(PIN::ALL);
    assert(P11DIR == 0x00);
    assert(P11REN == 0xFF);
    assert(P11OUT == 0xFF);

    p11.setAsInputPinWithPullDown(PIN::ALL);
    assert(P11DIR == 0x00);
    assert(P11REN == 0xFF);
    assert(P11OUT == 0x00);

    p11.setAsInputPin(PIN::ALL);
    assert(P11REN == 0x00);
    assert(P11DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORTJ_R__) || defined(__MSP430_HAS_PORTJ__)
    PortJ pj{};
    pj.setAsInputPinWithPullDown(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    pj.setAsInputPinWithPullUp(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(PJDIR == 0x00);
    assert(PJREN == 0xFF);
    assert(PJOUT == 0b10101010);

    pj.setAsInputPinWithPullUp(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    pj.setAsInputPinWithPullDown(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(PJDIR == 0x00);
    assert(PJREN == 0xFF);
    assert(PJOUT == 0b01010101);

    pj.setAsInputPinWithPullUp(PIN::ALL);
    assert(PJDIR == 0x00);
    assert(PJREN == 0xFF);
    assert(PJOUT == 0xFF);

    pj.setAsInputPinWithPullDown(PIN::ALL);
    assert(PJDIR == 0x00);
    assert(PJREN == 0xFF);
    assert(PJOUT == 0x00);

    pj.setAsInputPin(PIN::ALL);
    assert(PJREN == 0x00);
    assert(PJDIR == 0x00);
#endif
}

void runPortSelection() noexcept {

#if defined(__MSP430_HAS_PORT1_R__) || defined(__MSP430_HAS_PORT1__)
    Port1 p1{};
    p1.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1DIR == 0x00);
    assert(P1SEL0 == 0b01010101);
    assert(P1SEL1 == 0b10101010);

    p1.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P1SEL0 == 0xFF);
    assert(P1SEL1 == 0xFF);

    p1.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1DIR == 0xFF);
    assert(P1SEL0 == 0b01010101);
    assert(P1SEL1 == 0b10101010);

    p1.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P1SEL0 == 0xFF);
    assert(P1SEL1 == 0xFF);

    p1.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P1DIR == 0x00);
    assert(P1SEL0 == 0x00);
    assert(P1SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT2_R__) || defined(__MSP430_HAS_PORT2__)
    Port2 p2{};
    p2.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2DIR == 0x00);
    assert(P2SEL0 == 0b01010101);
    assert(P2SEL1 == 0b10101010);

    p2.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P2SEL0 == 0xFF);
    assert(P2SEL1 == 0xFF);

    p2.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2DIR == 0xFF);
    assert(P2SEL0 == 0b01010101);
    assert(P2SEL1 == 0b10101010);

    p2.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P2SEL0 == 0xFF);
    assert(P2SEL1 == 0xFF);

    p2.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P2DIR == 0x00);
    assert(P2SEL0 == 0x00);
    assert(P2SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT3_R__) || defined(__MSP430_HAS_PORT3__)
    Port3 p3{};
    p3.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3DIR == 0x00);
    assert(P3SEL0 == 0b01010101);
    assert(P3SEL1 == 0b10101010);

    p3.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P3SEL0 == 0xFF);
    assert(P3SEL1 == 0xFF);

    p3.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3DIR == 0xFF);
    assert(P3SEL0 == 0b01010101);
    assert(P3SEL1 == 0b10101010);

    p3.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P3SEL0 == 0xFF);
    assert(P3SEL1 == 0xFF);

    p3.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P3DIR == 0x00);
    assert(P3SEL0 == 0x00);
    assert(P3SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT4_R__) || defined(__MSP430_HAS_PORT4__)
    Port4 p4{};
    p4.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4DIR == 0x00);
    assert(P4SEL0 == 0b01010101);
    assert(P4SEL1 == 0b10101010);

    p4.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P4SEL0 == 0xFF);
    assert(P4SEL1 == 0xFF);

    p4.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4DIR == 0xFF);
    assert(P4SEL0 == 0b01010101);
    assert(P4SEL1 == 0b10101010);

    p4.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P4SEL0 == 0xFF);
    assert(P4SEL1 == 0xFF);

    p4.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P4DIR == 0x00);
    assert(P4SEL0 == 0x00);
    assert(P4SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT5_R__) || defined(__MSP430_HAS_PORT5__)
    Port5 p5{};
    p5.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p5.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P5DIR == 0x00);
    assert(P5SEL0 == 0b01010101);
    assert(P5SEL1 == 0b10101010);

    p5.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P5SEL0 == 0xFF);
    assert(P5SEL1 == 0xFF);

    p5.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p5.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P5DIR == 0xFF);
    assert(P5SEL0 == 0b01010101);
    assert(P5SEL1 == 0b10101010);

    p5.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P5SEL0 == 0xFF);
    assert(P5SEL1 == 0xFF);

    p5.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P5DIR == 0x00);
    assert(P5SEL0 == 0x00);
    assert(P5SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT6_R__) || defined(__MSP430_HAS_PORT6__)
    Port6 p6{};
    p6.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p6.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P6DIR == 0x00);
    assert(P6SEL0 == 0b01010101);
    assert(P6SEL1 == 0b10101010);

    p6.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P6SEL0 == 0xFF);
    assert(P6SEL1 == 0xFF);

    p6.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p6.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P6DIR == 0xFF);
    assert(P6SEL0 == 0b01010101);
    assert(P6SEL1 == 0b10101010);

    p6.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P6SEL0 == 0xFF);
    assert(P6SEL1 == 0xFF);

    p6.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P6DIR == 0x00);
    assert(P6SEL0 == 0x00);
    assert(P6SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT7_R__) || defined(__MSP430_HAS_PORT7__)
    Port7 p7{};
    p7.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p7.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P7DIR == 0x00);
    assert(P7SEL0 == 0b01010101);
    assert(P7SEL1 == 0b10101010);

    p7.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P7SEL0 == 0xFF);
    assert(P7SEL1 == 0xFF);

    p7.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p7.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P7DIR == 0xFF);
    assert(P7SEL0 == 0b01010101);
    assert(P7SEL1 == 0b10101010);

    p7.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P7SEL0 == 0xFF);
    assert(P7SEL1 == 0xFF);

    p7.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P7DIR == 0x00);
    assert(P7SEL0 == 0x00);
    assert(P7SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT8_R__) || defined(__MSP430_HAS_PORT8__)
    Port8 p8{};
    p8.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p8.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P8DIR == 0x00);
    assert(P8SEL0 == 0b01010101);
    assert(P8SEL1 == 0b10101010);

    p8.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P8SEL0 == 0xFF);
    assert(P8SEL1 == 0xFF);

    p8.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p8.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P8DIR == 0xFF);
    assert(P8SEL0 == 0b01010101);
    assert(P8SEL1 == 0b10101010);

    p8.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P8SEL0 == 0xFF);
    assert(P8SEL1 == 0xFF);

    p8.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P8DIR == 0x00);
    assert(P8SEL0 == 0x00);
    assert(P8SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT9_R__) || defined(__MSP430_HAS_PORT9__)
    Port9 p9{};
    p9.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p9.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P9DIR == 0x00);
    assert(P9SEL0 == 0b01010101);
    assert(P9SEL1 == 0b10101010);

    p9.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P9SEL0 == 0xFF);
    assert(P9SEL1 == 0xFF);

    p9.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p9.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P9DIR == 0xFF);
    assert(P9SEL0 == 0b01010101);
    assert(P9SEL1 == 0b10101010);

    p9.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P9SEL0 == 0xFF);
    assert(P9SEL1 == 0xFF);

    p9.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P9DIR == 0x00);
    assert(P9SEL0 == 0x00);
    assert(P9SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT10_R__) || defined(__MSP430_HAS_PORT10__)
    Port10 p10{};
    p10.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2);
    p10.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1);
    assert(P10DIR == 0x00);
    assert(P10SEL0 == 0b00000101);
    assert(P10SEL1 == 0b00000010);

    p10.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P10SEL0 == 0b00000111);
    assert(P10SEL1 == 0b00000111);

    p10.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2);
    p10.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1);
    assert(P10DIR == 0b00000111);
    assert(P10SEL0 == 0b00000101);
    assert(P10SEL1 == 0b00000010);

    p10.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P10SEL0 == 0b00000111);
    assert(P10SEL1 == 0b00000111);

    p10.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P10DIR == 0x00);
    assert(P10SEL0 == 0x00);
    assert(P10SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORT11_R__) || defined(__MSP430_HAS_PORT11__)
    Port11 p11{};
    p11.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p11.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P11DIR == 0x00);
    assert(P11SEL0 == 0b01010101);
    assert(P11SEL1 == 0b10101010);

    p11.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P11SEL0 == 0xFF);
    assert(P11SEL1 == 0xFF);

    p11.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p11.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P11DIR == 0xFF);
    assert(P11SEL0 == 0b01010101);
    assert(P11SEL1 == 0b10101010);

    p11.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(P11SEL0 == 0xFF);
    assert(P11SEL1 == 0xFF);

    p11.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(P11DIR == 0x00);
    assert(P11SEL0 == 0x00);
    assert(P11SEL1 == 0x00);
#endif

#if defined(__MSP430_HAS_PORTJ_R__) || defined(__MSP430_HAS_PORTJ__)
    PortJ pj{};
    pj.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    pj.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(PJDIR == 0x00);
    assert(PJSEL0 == 0b01010101);
    assert(PJSEL1 == 0b10101010);

    pj.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(PJSEL0 == 0xFF);
    assert(PJSEL1 == 0xFF);

    pj.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::PRIMARY, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    pj.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::SECONDARY, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(PJDIR == 0xFF);
    assert(PJSEL0 == 0b01010101);
    assert(PJSEL1 == 0b10101010);

    pj.setAsPeripheralModuleFunctionOutputPin(MODULE_FUNC::TERNARY, PIN::ALL);
    assert(PJSEL0 == 0xFF);
    assert(PJSEL1 == 0xFF);

    pj.setAsPeripheralModuleFunctionInputPin(MODULE_FUNC::GPIO, PIN::ALL);
    assert(PJDIR == 0x00);
    assert(PJSEL0 == 0x00);
    assert(PJSEL1 == 0x00);
#endif
}


void runPortInterrupt() noexcept {

#if defined(__MSP430_HAS_PORT1_R__) || defined(__MSP430_HAS_PORT1__)
    Port1 p1{};
    p1.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1IES == 0b01010101);

    p1.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1IES == 0b10101010);

    p1.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::ALL);
    assert(P1IES == 0xFF);

    p1.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::ALL);
    assert(P1IES == 0x00);

    p1.enableInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.disableInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1IE == 0b01010101);

    p1.disableInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.enableInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1IE == 0b10101010);

    p1.enableInterrupt(PIN::ALL);
    assert(P1IE == 0xFF);

    p1.disableInterrupt(PIN::ALL);
    assert(P1IE == 0x00);

    P1IFG |= 0xFF;
    assert(p1.getInterruptStatus(PIN::ALL) == MT::MSP430::INT_MASK_MATCH::TRUE);

    p1.clearInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    assert(p1.getInterruptStatus(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7) == MT::MSP430::INT_MASK_MATCH::TRUE);

    p1.clearInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1IFG == 0x00);
    assert(p1.getInterruptStatus(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6) == MT::MSP430::INT_MASK_MATCH::FALSE);
#endif

#if defined(__MSP430_HAS_PORT2_R__) || defined(__MSP430_HAS_PORT2__)
    Port2 p2{};
    p2.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2IES == 0b01010101);

    p2.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2IES == 0b10101010);

    p2.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::ALL);
    assert(P2IES == 0xFF);

    p2.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::ALL);
    assert(P2IES == 0x00);

    p2.enableInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.disableInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2IE == 0b01010101);

    p2.disableInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.enableInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2IE == 0b10101010);

    p2.enableInterrupt(PIN::ALL);
    assert(P2IE == 0xFF);

    p2.disableInterrupt(PIN::ALL);
    assert(P2IE == 0x00);

    P2IFG |= 0xFF;
    assert(p2.getInterruptStatus(PIN::ALL) == MT::MSP430::INT_MASK_MATCH::TRUE);

    p2.clearInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    assert(p2.getInterruptStatus(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7) == MT::MSP430::INT_MASK_MATCH::TRUE);

    p2.clearInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2IFG == 0x00);
    assert(p2.getInterruptStatus(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6) == MT::MSP430::INT_MASK_MATCH::FALSE);
#endif

#if defined(__MSP430_HAS_PORT3_R__) || defined(__MSP430_HAS_PORT3__)
    Port3 p3{};
    p3.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3IES == 0b01010101);

    p3.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3IES == 0b10101010);

    p3.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::ALL);
    assert(P3IES == 0xFF);

    p3.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::ALL);
    assert(P3IES == 0x00);

    p3.enableInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.disableInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3IE == 0b01010101);

    p3.disableInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.enableInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3IE == 0b10101010);

    p3.enableInterrupt(PIN::ALL);
    assert(P3IE == 0xFF);

    p3.disableInterrupt(PIN::ALL);
    assert(P3IE == 0x00);

    P3IFG |= 0xFF;
    assert(p3.getInterruptStatus(PIN::ALL) == MT::MSP430::INT_MASK_MATCH::TRUE);

    p3.clearInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    assert(p3.getInterruptStatus(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7) == MT::MSP430::INT_MASK_MATCH::TRUE);

    p3.clearInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3IFG == 0x00);
    assert(p3.getInterruptStatus(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6) == MT::MSP430::INT_MASK_MATCH::FALSE);
#endif

#if defined(__MSP430_HAS_PORT4_R__) || defined(__MSP430_HAS_PORT4__)
    Port4 p4{};
    p4.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4IES == 0b01010101);

    p4.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4IES == 0b10101010);

    p4.selectInterruptEdge(INT_EDGE::HIGH_TO_LOW, PIN::ALL);
    assert(P4IES == 0xFF);

    p4.selectInterruptEdge(INT_EDGE::LOW_TO_HIGH, PIN::ALL);
    assert(P4IES == 0x00);

    p4.enableInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.disableInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4IE == 0b01010101);

    p4.disableInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.enableInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4IE == 0b10101010);

    p4.enableInterrupt(PIN::ALL);
    assert(P4IE == 0xFF);

    p4.disableInterrupt(PIN::ALL);
    assert(P4IE == 0x00);

    P4IFG |= 0xFF;
    assert(p4.getInterruptStatus(PIN::ALL) == MT::MSP430::INT_MASK_MATCH::TRUE);

    p4.clearInterrupt(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    assert(p4.getInterruptStatus(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7) == MT::MSP430::INT_MASK_MATCH::TRUE);

    p4.clearInterrupt(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4IFG == 0x00);
    assert(p4.getInterruptStatus(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6) == MT::MSP430::INT_MASK_MATCH::FALSE);
#endif
}

void runPortOut() noexcept {

#if defined(__MSP430_HAS_PORT1_R__) || defined(__MSP430_HAS_PORT1__)
    Port1 p1{};
    p1.setAsOutputPin(PIN::ALL);
    assert(P1DIR == 0xFF);

    p1.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1OUT == 0b01010101);

    p1.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p1.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P1OUT == 0b10101010);

    p1.setOutputHighOnPin(PIN::ALL);
    assert(P1OUT == 0xFF);

    p1.toggleOutputOnPin(PIN::ALL);
    assert(P1OUT == 0x00);

    p1.setAsInputPin(PIN::ALL);
    assert(P1DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT2_R__) || defined(__MSP430_HAS_PORT2__)
    Port2 p2{};
    p2.setAsOutputPin(PIN::ALL);
    assert(P2DIR == 0xFF);

    p2.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2OUT == 0b01010101);

    p2.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p2.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P2OUT == 0b10101010);

    p2.setOutputHighOnPin(PIN::ALL);
    assert(P2OUT == 0xFF);

    p2.toggleOutputOnPin(PIN::ALL);
    assert(P2OUT == 0x00);

    p2.setAsInputPin(PIN::ALL);
    assert(P2DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT3_R__) || defined(__MSP430_HAS_PORT3__)
    Port3 p3{};
    p3.setAsOutputPin(PIN::ALL);
    assert(P3DIR == 0xFF);

    p3.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3OUT == 0b01010101);

    p3.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p3.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P3OUT == 0b10101010);

    p3.setOutputHighOnPin(PIN::ALL);
    assert(P3OUT == 0xFF);

    p3.toggleOutputOnPin(PIN::ALL);
    assert(P3OUT == 0x00);

    p3.setAsInputPin(PIN::ALL);
    assert(P3DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT4_R__) || defined(__MSP430_HAS_PORT4__)
    Port4 p4{};
    p4.setAsOutputPin(PIN::ALL);
    assert(P4DIR == 0xFF);

    p4.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4OUT == 0b01010101);

    p4.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p4.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P4OUT == 0b10101010);

    p4.setOutputHighOnPin(PIN::ALL);
    assert(P4OUT == 0xFF);

    p4.toggleOutputOnPin(PIN::ALL);
    assert(P4OUT == 0x00);

    p4.setAsInputPin(PIN::ALL);
    assert(P4DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT5_R__) || defined(__MSP430_HAS_PORT5__)
    Port5 p5{};
    p5.setAsOutputPin(PIN::ALL);
    assert(P5DIR == 0xFF);

    p5.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p5.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P5OUT == 0b01010101);

    p5.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p5.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P5OUT == 0b10101010);

    p5.setOutputHighOnPin(PIN::ALL);
    assert(P5OUT == 0xFF);

    p5.toggleOutputOnPin(PIN::ALL);
    assert(P5OUT == 0x00);

    p5.setAsInputPin(PIN::ALL);
    assert(P5DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT6_R__) || defined(__MSP430_HAS_PORT6__)
    Port6 p6{};
    p6.setAsOutputPin(PIN::ALL);
    assert(P6DIR == 0xFF);

    p6.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p6.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P6OUT == 0b01010101);

    p6.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p6.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P6OUT == 0b10101010);

    p6.setOutputHighOnPin(PIN::ALL);
    assert(P6OUT == 0xFF);

    p6.toggleOutputOnPin(PIN::ALL);
    assert(P6OUT == 0x00);

    p6.setAsInputPin(PIN::ALL);
    assert(P6DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT7_R__) || defined(__MSP430_HAS_PORT7__)
    Port7 p7{};
    p7.setAsOutputPin(PIN::ALL);
    assert(P7DIR == 0xFF);

    p7.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p7.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P7OUT == 0b01010101);

    p7.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p7.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P7OUT == 0b10101010);

    p7.setOutputHighOnPin(PIN::ALL);
    assert(P7OUT == 0xFF);

    p7.toggleOutputOnPin(PIN::ALL);
    assert(P7OUT == 0x00);

    p7.setAsInputPin(PIN::ALL);
    assert(P7DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT8_R__) || defined(__MSP430_HAS_PORT8__)
    Port8 p8{};
    p8.setAsOutputPin(PIN::ALL);
    assert(P8DIR == 0xFF);

    p8.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p8.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P8OUT == 0b01010101);

    p8.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p8.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P8OUT == 0b10101010);

    p8.setOutputHighOnPin(PIN::ALL);
    assert(P8OUT == 0xFF);

    p8.toggleOutputOnPin(PIN::ALL);
    assert(P8OUT == 0x00);

    p8.setAsInputPin(PIN::ALL);
    assert(P8DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT9_R__) || defined(__MSP430_HAS_PORT9__)
    Port9 p9{};
    p9.setAsOutputPin(PIN::ALL);
    assert(P9DIR == 0xFF);

    p9.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p9.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P9OUT == 0b01010101);

    p9.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p9.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P9OUT == 0b10101010);

    p9.setOutputHighOnPin(PIN::ALL);
    assert(P9OUT == 0xFF);

    p9.toggleOutputOnPin(PIN::ALL);
    assert(P9OUT == 0x00);

    p9.setAsInputPin(PIN::ALL);
    assert(P9DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT10_R__) || defined(__MSP430_HAS_PORT10__)
    Port10 p10{};
    p10.setAsOutputPin(PIN::ALL);
    assert(P10DIR == 0b00000111);

    p10.setOutputHighOnPin(PIN::P0 | PIN::P2);
    p10.setOutputLowOnPin(PIN::P1);
    assert(P10OUT == 0b00000101);

    p10.setOutputLowOnPin(PIN::P0 | PIN::P2);
    p10.setOutputHighOnPin(PIN::P1);
    assert(P10OUT == 0b00000010);

    p10.setOutputHighOnPin(PIN::ALL);
    assert(P10OUT == 0b00000111);

    p10.toggleOutputOnPin(PIN::ALL);
    assert(P10OUT == 0x00);

    p10.setAsInputPin(PIN::ALL);
    assert(P10DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORT11_R__) || defined(__MSP430_HAS_PORT11__)
    Port11 p11{};
    p11.setAsOutputPin(PIN::ALL);
    assert(P11DIR == 0xFF);

    p11.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p11.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P11OUT == 0b01010101);

    p11.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    p11.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(P11OUT == 0b10101010);

    p11.setOutputHighOnPin(PIN::ALL);
    assert(P11OUT == 0xFF);

    p11.toggleOutputOnPin(PIN::ALL);
    assert(P11OUT == 0x00);

    p11.setAsInputPin(PIN::ALL);
    assert(P11DIR == 0x00);
#endif

#if defined(__MSP430_HAS_PORTJ_R__) || defined(__MSP430_HAS_PORTJ__)
    PortJ pj{};
    pj.setAsOutputPin(PIN::ALL);
    assert(PJDIR == 0xFF);

    pj.setOutputHighOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    pj.setOutputLowOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(PJOUT == 0b01010101);

    pj.setOutputLowOnPin(PIN::P0 | PIN::P2 | PIN::P4 | PIN::P6);
    pj.setOutputHighOnPin(PIN::P1 | PIN::P3 | PIN::P5 | PIN::P7);
    assert(PJOUT == 0b10101010);

    pj.setOutputHighOnPin(PIN::ALL);
    assert(PJOUT == 0xFF);

    pj.toggleOutputOnPin(PIN::ALL);
    assert(PJOUT == 0x00);

    pj.setAsInputPin(PIN::ALL);
    assert(PJDIR == 0x00);
#endif
}

}// namespace MT::Tests::MSP430::GPIO::Internal

namespace MT::Tests::MSP430::GPIO {
void run() noexcept {
    Internal::runPortDirection();
    Internal::runPortPullUpDown();
    Internal::runPortSelection();
    Internal::runPortInterrupt();
    Internal::runPortOut();
}
}// namespace MT::Tests::MSP430::GPIO


#endif /* MICROTRAIT_TESTS_MSP430_TESTGPIO_HPP_ */

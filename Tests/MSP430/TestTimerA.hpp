
#ifndef MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_

#include "MicroTrait/MSP430/TIMERA/TimerA.hpp"
#include <assert.h>

namespace MT::Tests::MSP430::TIMERA::Internal {

using namespace MT::MSP430::TIMERA;

void runContMode() noexcept {

    TA0 ta0;

    initContinuous param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        GLOBAL_INT::DISABLE,
        CLEAR_COUNT_DIR::ENABLE,
        true
    };

#if defined(__MSP430_HAS_MSP430I_CPU__)
    param.div = CLOCK_DIV::DIV8;
#endif

    ta0.initContinuousMode(param);

    assert(TA0CTL & TASSEL_2);
    assert(TA0CTL & ID_3);
    assert(TA0CTL & MC_2);
    assert((TA0CTL & TAIE) == 0);
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    assert(TA0EX0 & TAIDEX_7);
#endif

    param.div = CLOCK_DIV::DIV1;
    ta0.initContinuousMode(param);

    assert(TA0CTL & TASSEL_2);
    assert((TA0CTL & ID_3) == 0);
    assert(TA0CTL & MC_2);
    assert((TA0CTL & TAIE) == 0);
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    assert(TA0EX0 == TAIDEX_0);
#endif

#if not defined(__MSP430_HAS_MSP430I_CPU__)
    param.div = CLOCK_DIV::DIV12;
    ta0.initContinuousMode(param);
    assert(TA0CTL & TASSEL_2);
    assert((TA0CTL & ID_2) == 0);
    assert(TA0CTL & MC_2);
    assert((TA0CTL & TAIE) == 0);
    assert(TA0EX0 == TAIDEX_5);
#endif

    param.global_int_en = GLOBAL_INT::ENABLE;
    ta0.initContinuousMode(param);
    assert(TA0CTL & TAIE);
}


void runUpMode() noexcept {

    TA0 ta0;

    initUp param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        32767,
        GLOBAL_INT::DISABLE,
        CAPTURE_COMPARE_INT::DISABLE,
        CLEAR_COUNT_DIR::ENABLE,
        true
    };


#if defined(__MSP430_HAS_MSP430I_CPU__)
    param.div = CLOCK_DIV::DIV8;
#endif

    ta0.initUpMode(param);

    assert(TA0CTL & TASSEL_2);
    assert(TA0CTL & ID_3);
    assert(TA0CTL & MC_1);
    assert((TA0CTL & TAIE) == 0);
    assert(TA0CCR0 == 32767);
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    assert(TA0EX0 & TAIDEX_7);
#endif


    param.div = CLOCK_DIV::DIV1;
    ta0.initUpMode(param);

    assert(TA0CTL & TASSEL_2);
    assert((TA0CTL & ID_3) == 0);
    assert(TA0CTL & MC_1);
    assert((TA0CTL & TAIE) == 0);
    assert(TA0CCR0 == 32767);
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    assert(TA0EX0 == TAIDEX_0);
#endif

#if not defined(__MSP430_HAS_MSP430I_CPU__)
    param.div = CLOCK_DIV::DIV12;
    ta0.initUpMode(param);
    assert(TA0CTL & TASSEL_2);
    assert((TA0CTL & ID_2) == 0);
    assert(TA0CTL & MC_1);
    assert((TA0CTL & TAIE) == 0);
    assert(TA0EX0 == TAIDEX_5);
    assert(TA0CCR0 == 32767);
#endif

    param.global_int_en = GLOBAL_INT::ENABLE;
    ta0.initUpMode(param);
    assert(TA0CTL & TAIE);

    param.ccr_in_en = CAPTURE_COMPARE_INT::ENABLE;
    ta0.initUpMode(param);
    assert(TA0CCTL0 & CCIE);
}


}// namespace MT::Tests::MSP430::TIMERA::Internal


namespace MT::Tests::MSP430::TIMERA {
void run() noexcept {
    Internal::runContMode();
    Internal::runUpMode();
}
}// namespace MT::Tests::MSP430::TIMERA


#endif /* MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_ */

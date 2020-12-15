
#ifndef MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_

#include "MicroTrait/MSP430/TIMERA/TimerA.hpp"
#include <MicroTrait/MSP430/Types.hpp>
#include <assert.h>

namespace MT::Tests::MSP430::TIMERA::Internal {

using namespace MT::MSP430::TIMERA;
using namespace MT::MSP430;

void resetRegisters() {
    TA0CTL   = 0;
    TA0R     = 0;
    TA0CCTL0 = 0;
    TA0CCTL1 = 0;
    TA0CCTL2 = 0;
    TA0CCR0  = 0;
    TA0CCR1  = 0;
    TA0CCR2  = 0;
    TA0IV    = 0;

#if not defined(__MSP430_HAS_MSP430I_CPU__)
    TA0EX0 = 0;
#endif
}


void runContMode() noexcept {

    resetRegisters();

    TA0 ta0;

    initContinuous param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        TAIE_INT::DISABLE,
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

    param.global_int_en = TAIE_INT::ENABLE;
    ta0.initContinuousMode(param);
    assert(TA0CTL & TAIE);
}


void runUpMode() noexcept {

    resetRegisters();

    TA0 ta0;

    initUp param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        32767,
        TAIE_INT::DISABLE,
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

    param.global_int_en = TAIE_INT::ENABLE;
    ta0.initUpMode(param);
    assert(TA0CTL & TAIE);

    param.ccr_in_en = CAPTURE_COMPARE_INT::ENABLE;
    ta0.initUpMode(param);
    assert(TA0CCTL0 & CCIE);
}


void runUpDownMode() noexcept {

    resetRegisters();

    TA0 ta0;

    initUpDown param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        32767,
        TAIE_INT::DISABLE,
        CAPTURE_COMPARE_INT::DISABLE,
        CLEAR_COUNT_DIR::ENABLE,
        true
    };


#if defined(__MSP430_HAS_MSP430I_CPU__)
    param.div = CLOCK_DIV::DIV8;
#endif

    ta0.initUpDownMode(param);

    assert(TA0CTL & TASSEL_2);
    assert(TA0CTL & ID_3);
    assert(TA0CTL & MC_3);
    assert((TA0CTL & TAIE) == 0);
    assert(TA0CCR0 == 32767);
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    assert(TA0EX0 & TAIDEX_7);
#endif


    param.div = CLOCK_DIV::DIV1;
    ta0.initUpDownMode(param);

    assert(TA0CTL & TASSEL_2);
    assert((TA0CTL & ID_3) == 0);
    assert(TA0CTL & MC_3);
    assert((TA0CTL & TAIE) == 0);
    assert(TA0CCR0 == 32767);
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    assert(TA0EX0 == TAIDEX_0);
#endif

#if not defined(__MSP430_HAS_MSP430I_CPU__)
    param.div = CLOCK_DIV::DIV12;
    ta0.initUpDownMode(param);
    assert(TA0CTL & TASSEL_2);
    assert((TA0CTL & ID_2) == 0);
    assert(TA0CTL & MC_3);
    assert((TA0CTL & TAIE) == 0);
    assert(TA0EX0 == TAIDEX_5);
    assert(TA0CCR0 == 32767);
#endif

    param.global_int_en = TAIE_INT::ENABLE;
    ta0.initUpDownMode(param);
    assert(TA0CTL & TAIE);

    param.ccr_in_en = CAPTURE_COMPARE_INT::ENABLE;
    ta0.initUpDownMode(param);
    assert(TA0CCTL0 & CCIE);
}

void runCaptureMode() noexcept {
    resetRegisters();

    TA0 ta0;

    initCapture param{
        CAPTURE_COMPARE::REGISTER0,
        CAPTURE_MODE::RISING_AND_FALLING_EDGE,
        CAPTURE_INPUT::VCC,
        CAPTURE::SYNCHRONOUS,
        CAPTURE_COMPARE_INT::ENABLE,
        COMPARE_OUTPUT::RESET_SET
    };

    ta0.initCaptureMode(param);

    assert(TA0CCTL0 & CM_3);
    assert(TA0CCTL0 & CCIS_3);
    assert(TA0CCTL0 & SCS);
    assert(TA0CCTL0 & CCIE);
    assert(TA0CCTL0 & OUTMOD_7);
    assert(TA0CCTL0 & CAP);

    param.mode = CAPTURE_MODE::OFF;
    ta0.initCaptureMode(param);
    assert((TA0CCTL0 & CM_3) == 0);
    assert(TA0CCTL0 & CCIS_3);
    assert(TA0CCTL0 & SCS);
    assert(TA0CCTL0 & CCIE);
    assert(TA0CCTL0 & OUTMOD_7);
    assert(TA0CCTL0 & CAP);

    param.input = CAPTURE_INPUT::CCIXA;
    ta0.initCaptureMode(param);
    assert((TA0CCTL0 & CM_3) == 0);
    assert((TA0CCTL0 & CCIS_3) == 0);
    assert(TA0CCTL0 & SCS);
    assert(TA0CCTL0 & CCIE);
    assert(TA0CCTL0 & OUTMOD_7);
    assert(TA0CCTL0 & CAP);

    param.sync = CAPTURE::ASYNCHRONOUS;
    ta0.initCaptureMode(param);
    assert((TA0CCTL0 & CM_3) == 0);
    assert((TA0CCTL0 & CCIS_3) == 0);
    assert((TA0CCTL0 & SCS) == 0);
    assert(TA0CCTL0 & CCIE);
    assert(TA0CCTL0 & OUTMOD_7);
    assert(TA0CCTL0 & CAP);

    param.int_en = CAPTURE_COMPARE_INT::DISABLE;
    ta0.initCaptureMode(param);
    assert((TA0CCTL0 & CM_3) == 0);
    assert((TA0CCTL0 & CCIS_3) == 0);
    assert((TA0CCTL0 & SCS) == 0);
    assert((TA0CCTL0 & CCIE) == 0);
    assert(TA0CCTL0 & OUTMOD_7);
    assert(TA0CCTL0 & CAP);

    param.out = COMPARE_OUTPUT::BITVALUE;
    ta0.initCaptureMode(param);
    assert((TA0CCTL0 & CM_3) == 0);
    assert((TA0CCTL0 & CCIS_3) == 0);
    assert((TA0CCTL0 & SCS) == 0);
    assert((TA0CCTL0 & CCIE) == 0);
    assert((TA0CCTL0 & OUTMOD_7) == 0);
    assert(TA0CCTL0 & CAP);
}

void runCompareMode() noexcept {

    resetRegisters();

    TA0 ta0;

    initCompare param{
        CAPTURE_COMPARE::REGISTER0,
        CAPTURE_COMPARE_INT::ENABLE,
        COMPARE_OUTPUT::RESET_SET,
        5000
    };


    ta0.initCompareMode(param);

    assert(TA0CCTL0 & CCIE);
    assert(TA0CCTL0 & OUTMOD_7);
    assert(TA0CCR0 == 5000);
    assert((TA0CCTL0 & CAP) == 0);

    param.int_en = CAPTURE_COMPARE_INT::DISABLE;
    ta0.initCompareMode(param);
    assert((TA0CCTL0 & CCIE) == 0);
    assert(TA0CCTL0 & OUTMOD_7);
    assert(TA0CCR0 == 5000);
    assert((TA0CCTL0 & CAP) == 0);

    param.out = COMPARE_OUTPUT::BITVALUE;
    ta0.initCompareMode(param);
    assert((TA0CCTL0 & OUTMOD_7) == 0);
    assert(TA0CCR0 == 5000);
    assert((TA0CCTL0 & CAP) == 0);

    param.compareValue = 123;
    ta0.initCompareMode(param);
    assert((TA0CCTL0 & CCIE) == 0);
    assert((TA0CCTL0 & OUTMOD_7) == 0);
    assert(TA0CCR0 == 123);
    assert((TA0CCTL0 & CAP) == 0);
}

void runInterrupts() noexcept {

    resetRegisters();

    TA0 ta0;
    ta0.enableInterrupt();
    assert(TA0CTL & TAIE);

    ta0.disableInterrupt();
    assert((TA0CTL & TAIE) == 0);

    TA0CTL |= TAIFG;
    assert(ta0.getInterruptStatus() == INT_MASK_MATCH::TRUE);

    ta0.clearTimerInterrupt();
    assert(ta0.getInterruptStatus() == INT_MASK_MATCH::FALSE);
}

void runCCInterrupts() noexcept {

    resetRegisters();

    TA0 ta0;
    ta0.enableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER0);
    assert(TA0CCTL0 & CCIE);

    ta0.enableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER1);
    assert(TA0CCTL1 & CCIE);

    ta0.enableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER2);
    assert(TA0CCTL2 & CCIE);


    ta0.disableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER0);
    assert((TA0CCTL0 & CCIE) == 0);

    ta0.disableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER1);
    assert((TA0CCTL1 & CCIE) == 0);

    ta0.disableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER2);
    assert((TA0CCTL2 & CCIE) == 0);


    TA0CCTL0 |= CCIFG;
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::TRUE);

    TA0CCTL0 |= COV;
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::TRUE);


    TA0CCTL1 |= CCIFG;
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::TRUE);

    TA0CCTL1 |= COV;
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::TRUE);


    TA0CCTL2 |= CCIFG;
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::TRUE);

    TA0CCTL2 |= COV;
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::TRUE);


    ta0.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER0);
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::FALSE);

    ta0.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_OVERFLOW);
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::FALSE);


    ta0.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER1);
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::FALSE);

    ta0.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_OVERFLOW);
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::FALSE);


    ta0.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER2);
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::FALSE);

    ta0.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_OVERFLOW);
    assert(ta0.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::FALSE);
}


void runMisc() noexcept {

    resetRegisters();
    TA0 ta0;

    TA0CTL |= MC_3;
    ta0.stop();
    assert((TA0CTL & MC_3) == 0);

    TA0R = 123;
    assert(ta0.getCounterValue() == 123);
}

void runCCMisc() noexcept {

    resetRegisters();
    TA0 ta0;

    assert(ta0.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER0, CAPTURE_COMPARE_READ_INPUT::SYNCED) == CAPTURE_COMPARE_INPUT::LOW);
    assert(ta0.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER0, CAPTURE_COMPARE_READ_INPUT::NOT_SYNCED) == CAPTURE_COMPARE_INPUT::LOW);

    assert(ta0.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER1, CAPTURE_COMPARE_READ_INPUT::SYNCED) == CAPTURE_COMPARE_INPUT::LOW);
    assert(ta0.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER1, CAPTURE_COMPARE_READ_INPUT::NOT_SYNCED) == CAPTURE_COMPARE_INPUT::LOW);

    assert(ta0.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER2, CAPTURE_COMPARE_READ_INPUT::SYNCED) == CAPTURE_COMPARE_INPUT::LOW);
    assert(ta0.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER2, CAPTURE_COMPARE_READ_INPUT::NOT_SYNCED) == CAPTURE_COMPARE_INPUT::LOW);


    TA0CCTL0 |= OUT;
    assert(ta0.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER0) == COMPARE_OUT_BIT::HIGH);
    TA0CCTL0 &= ~OUT;
    assert(ta0.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER0) == COMPARE_OUT_BIT::LOW);

    TA0CCTL1 |= OUT;
    assert(ta0.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER1) == COMPARE_OUT_BIT::HIGH);
    TA0CCTL1 &= ~OUT;
    assert(ta0.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER1) == COMPARE_OUT_BIT::LOW);

    TA0CCTL2 |= OUT;
    assert(ta0.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER2) == COMPARE_OUT_BIT::HIGH);
    TA0CCTL2 &= ~OUT;
    assert(ta0.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER2) == COMPARE_OUT_BIT::LOW);


    TA0CCR0 = 123;
    assert(ta0.getCaptureCompareCount(CAPTURE_COMPARE::REGISTER0) == 123);

    TA0CCR1 = 123;
    assert(ta0.getCaptureCompareCount(CAPTURE_COMPARE::REGISTER1) == 123);

    TA0CCR2 = 123;
    assert(ta0.getCaptureCompareCount(CAPTURE_COMPARE::REGISTER2) == 123);


    ta0.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER0, COMPARE_OUT_BIT::HIGH);
    assert(TA0CCTL0 & OUT);

    ta0.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER0, COMPARE_OUT_BIT::LOW);
    assert((TA0CCTL0 & OUT) == 0);

    ta0.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER1, COMPARE_OUT_BIT::HIGH);
    assert(TA0CCTL1 & OUT);

    ta0.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER1, COMPARE_OUT_BIT::LOW);
    assert((TA0CCTL1 & OUT) == 0);

    ta0.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER2, COMPARE_OUT_BIT::HIGH);
    assert(TA0CCTL2 & OUT);

    ta0.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER2, COMPARE_OUT_BIT::LOW);
    assert((TA0CCTL2 & OUT) == 0);


    ta0.setCompareValue(CAPTURE_COMPARE::REGISTER0, 123);
    assert(TA0CCR0 == 123);

    ta0.setCompareValue(CAPTURE_COMPARE::REGISTER1, 123);
    assert(TA0CCR1 == 123);

    ta0.setCompareValue(CAPTURE_COMPARE::REGISTER2, 123);
    assert(TA0CCR2 == 123);


    TA0CCTL0 = 0;
    ta0.setOutputMode(CAPTURE_COMPARE::REGISTER0, COMPARE_OUTPUT::TOGGLE);
    assert(TA0CCTL0 == OUTMOD_4);

    TA0CCTL1 = 0;
    ta0.setOutputMode(CAPTURE_COMPARE::REGISTER1, COMPARE_OUTPUT::TOGGLE);
    assert(TA0CCTL1 == OUTMOD_4);

    TA0CCTL2 = 0;
    ta0.setOutputMode(CAPTURE_COMPARE::REGISTER2, COMPARE_OUTPUT::TOGGLE);
    assert(TA0CCTL2 == OUTMOD_4);
}


}// namespace MT::Tests::MSP430::TIMERA::Internal


namespace MT::Tests::MSP430::TIMERA {
void run() noexcept {
    Internal::runContMode();
    Internal::runUpMode();
    Internal::runUpDownMode();
    Internal::runCaptureMode();
    Internal::runCompareMode();

    Internal::runInterrupts();
    Internal::runCCInterrupts();
    Internal::runMisc();
    Internal::runCCMisc();
}
}// namespace MT::Tests::MSP430::TIMERA


#endif /* MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_ */

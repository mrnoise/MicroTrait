
#ifndef MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_

#include "MicroTrait/MSP430/TIMERA/TimerA.hpp"
#include <MicroTrait/MSP430/Types.hpp>
#include <assert.h>

namespace MT::Tests::MSP430::TIMERA::Internal {

using namespace MT::MSP430::TIMERA;
using namespace MT::MSP430;


#if defined(__MSP430_HAS_T3A5__)

void resetRegisters() {
    TA3CTL   = 0;
    TA3R     = 0;
    TA3CCTL0 = 0;
    TA3CCTL1 = 0;
    TA3CCTL2 = 0;
    TA3CCTL3 = 0;
    TA3CCTL4 = 0;
    TA3CCR0  = 0;
    TA3CCR1  = 0;
    TA3CCR2  = 0;
    TA3CCR3  = 0;
    TA3CCR4  = 0;
    TA3IV    = 0;
    TA3EX0   = 0;
}


void runContMode() noexcept {

    resetRegisters();

    TA3 ta3;

    initContinuous param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        TAIE_INT::DISABLE,
        CLEAR_COUNT_DIR::ENABLE,
        true
    };

    ta3.initContinuousMode(param);
    assert(TA3CTL & TASSEL_2);
    assert(TA3CTL & ID_3);
    assert(TA3CTL & MC_2);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3EX0 & TAIDEX_7);

    param.div = CLOCK_DIV::DIV1;
    ta3.initContinuousMode(param);

    assert(TA3CTL & TASSEL_2);
    assert((TA3CTL & ID_3) == 0);
    assert(TA3CTL & MC_2);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3EX0 == TAIDEX_0);


    param.div = CLOCK_DIV::DIV12;
    ta3.initContinuousMode(param);
    assert(TA3CTL & TASSEL_2);
    assert((TA3CTL & ID_2) == 0);
    assert(TA3CTL & MC_2);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3EX0 == TAIDEX_5);

    param.global_int_en = TAIE_INT::ENABLE;
    ta3.initContinuousMode(param);
    assert(TA3CTL & TAIE);
}


void runUpMode() noexcept {

    resetRegisters();

    TA3 ta3;

    initUp param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        32767,
        TAIE_INT::DISABLE,
        CAPTURE_COMPARE_INT::DISABLE,
        CLEAR_COUNT_DIR::ENABLE,
        true
    };


    ta3.initUpMode(param);

    assert(TA3CTL & TASSEL_2);
    assert(TA3CTL & ID_3);
    assert(TA3CTL & MC_1);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3CCR0 == 32767);
    assert(TA3EX0 & TAIDEX_7);

    param.div = CLOCK_DIV::DIV1;
    ta3.initUpMode(param);

    assert(TA3CTL & TASSEL_2);
    assert((TA3CTL & ID_3) == 0);
    assert(TA3CTL & MC_1);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3CCR0 == 32767);
    assert(TA3EX0 == TAIDEX_0);

    param.div = CLOCK_DIV::DIV12;
    ta3.initUpMode(param);
    assert(TA3CTL & TASSEL_2);
    assert((TA3CTL & ID_2) == 0);
    assert(TA3CTL & MC_1);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3EX0 == TAIDEX_5);
    assert(TA3CCR0 == 32767);

    param.global_int_en = TAIE_INT::ENABLE;
    ta3.initUpMode(param);
    assert(TA3CTL & TAIE);

    param.ccr_in_en = CAPTURE_COMPARE_INT::ENABLE;
    ta3.initUpMode(param);
    assert(TA3CCTL0 & CCIE);
}


void runUpDownMode() noexcept {

    resetRegisters();

    TA3 ta3;

    initUpDown param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        32767,
        TAIE_INT::DISABLE,
        CAPTURE_COMPARE_INT::DISABLE,
        CLEAR_COUNT_DIR::ENABLE,
        true
    };


    ta3.initUpDownMode(param);
    assert(TA3CTL & TASSEL_2);
    assert(TA3CTL & ID_3);
    assert(TA3CTL & MC_3);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3CCR0 == 32767);
    assert(TA3EX0 & TAIDEX_7);


    param.div = CLOCK_DIV::DIV1;
    ta3.initUpDownMode(param);
    assert(TA3CTL & TASSEL_2);
    assert((TA3CTL & ID_3) == 0);
    assert(TA3CTL & MC_3);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3CCR0 == 32767);
    assert(TA3EX0 == TAIDEX_0);

    param.div = CLOCK_DIV::DIV12;
    ta3.initUpDownMode(param);
    assert(TA3CTL & TASSEL_2);
    assert((TA3CTL & ID_2) == 0);
    assert(TA3CTL & MC_3);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3EX0 == TAIDEX_5);
    assert(TA3CCR0 == 32767);

    param.global_int_en = TAIE_INT::ENABLE;
    ta3.initUpDownMode(param);
    assert(TA3CTL & TAIE);

    param.ccr_in_en = CAPTURE_COMPARE_INT::ENABLE;
    ta3.initUpDownMode(param);
    assert(TA3CCTL0 & CCIE);
}

void runCaptureMode() noexcept {
    resetRegisters();

    TA3 ta3;

    initCapture param{
        CAPTURE_COMPARE::REGISTER0,
        CAPTURE_MODE::RISING_AND_FALLING_EDGE,
        CAPTURE_INPUT::VCC,
        CAPTURE::SYNCHRONOUS,
        CAPTURE_COMPARE_INT::ENABLE,
        COMPARE_OUTPUT::RESET_SET
    };

    ta3.initCaptureMode(param);

    assert(TA3CCTL0 & CM_3);
    assert(TA3CCTL0 & CCIS_3);
    assert(TA3CCTL0 & SCS);
    assert(TA3CCTL0 & CCIE);
    assert(TA3CCTL0 & OUTMOD_7);
    assert(TA3CCTL0 & CAP);

    param.mode = CAPTURE_MODE::OFF;
    ta3.initCaptureMode(param);
    assert((TA3CCTL0 & CM_3) == 0);
    assert(TA3CCTL0 & CCIS_3);
    assert(TA3CCTL0 & SCS);
    assert(TA3CCTL0 & CCIE);
    assert(TA3CCTL0 & OUTMOD_7);
    assert(TA3CCTL0 & CAP);

    param.input = CAPTURE_INPUT::CCIXA;
    ta3.initCaptureMode(param);
    assert((TA3CCTL0 & CM_3) == 0);
    assert((TA3CCTL0 & CCIS_3) == 0);
    assert(TA3CCTL0 & SCS);
    assert(TA3CCTL0 & CCIE);
    assert(TA3CCTL0 & OUTMOD_7);
    assert(TA3CCTL0 & CAP);

    param.sync = CAPTURE::ASYNCHRONOUS;
    ta3.initCaptureMode(param);
    assert((TA3CCTL0 & CM_3) == 0);
    assert((TA3CCTL0 & CCIS_3) == 0);
    assert((TA3CCTL0 & SCS) == 0);
    assert(TA3CCTL0 & CCIE);
    assert(TA3CCTL0 & OUTMOD_7);
    assert(TA3CCTL0 & CAP);

    param.int_en = CAPTURE_COMPARE_INT::DISABLE;
    ta3.initCaptureMode(param);
    assert((TA3CCTL0 & CM_3) == 0);
    assert((TA3CCTL0 & CCIS_3) == 0);
    assert((TA3CCTL0 & SCS) == 0);
    assert((TA3CCTL0 & CCIE) == 0);
    assert(TA3CCTL0 & OUTMOD_7);
    assert(TA3CCTL0 & CAP);

    param.out = COMPARE_OUTPUT::BITVALUE;
    ta3.initCaptureMode(param);
    assert((TA3CCTL0 & CM_3) == 0);
    assert((TA3CCTL0 & CCIS_3) == 0);
    assert((TA3CCTL0 & SCS) == 0);
    assert((TA3CCTL0 & CCIE) == 0);
    assert((TA3CCTL0 & OUTMOD_7) == 0);
    assert(TA3CCTL0 & CAP);
}

void runCompareMode() noexcept {

    resetRegisters();

    TA3 ta3;

    initCompare param{
        CAPTURE_COMPARE::REGISTER0,
        CAPTURE_COMPARE_INT::ENABLE,
        COMPARE_OUTPUT::RESET_SET,
        5000
    };


    ta3.initCompareMode(param);

    assert(TA3CCTL0 & CCIE);
    assert(TA3CCTL0 & OUTMOD_7);
    assert(TA3CCR0 == 5000);
    assert((TA3CCTL0 & CAP) == 0);

    param.int_en = CAPTURE_COMPARE_INT::DISABLE;
    ta3.initCompareMode(param);
    assert((TA3CCTL0 & CCIE) == 0);
    assert(TA3CCTL0 & OUTMOD_7);
    assert(TA3CCR0 == 5000);
    assert((TA3CCTL0 & CAP) == 0);

    param.out = COMPARE_OUTPUT::BITVALUE;
    ta3.initCompareMode(param);
    assert((TA3CCTL0 & OUTMOD_7) == 0);
    assert(TA3CCR0 == 5000);
    assert((TA3CCTL0 & CAP) == 0);

    param.compareValue = 123;
    ta3.initCompareMode(param);
    assert((TA3CCTL0 & CCIE) == 0);
    assert((TA3CCTL0 & OUTMOD_7) == 0);
    assert(TA3CCR0 == 123);
    assert((TA3CCTL0 & CAP) == 0);
}


void runPWMMode() noexcept {

    resetRegisters();

    TA3 ta3;

    initPWM param{
        CLOCKSOURCE::SMCLK,
        CLOCK_DIV::DIV64,
        32767,
        CAPTURE_COMPARE::REGISTER3,
        COMPARE_OUTPUT::RESET_SET,
        1600
    };

    ta3.outputPWM(param);

    assert(TA3CTL & TASSEL_2);
    assert(TA3CTL & ID_3);
    assert(TA3CTL & MC_1);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3CCR0 == 32767);
    assert(TA3EX0 & TAIDEX_7);
    assert(TA3CCR3 == 1600);
    assert(TA3CCTL3 == OUTMOD_7);

    param.div = CLOCK_DIV::DIV1;
    ta3.outputPWM(param);

    assert(TA3CTL & TASSEL_2);
    assert((TA3CTL & ID_3) == 0);
    assert(TA3CTL & MC_1);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3CCR0 == 32767);
    assert(TA3EX0 == TAIDEX_0);
    assert(TA3CCR3 == 1600);
    assert(TA3CCTL3 == OUTMOD_7);

    param.div = CLOCK_DIV::DIV12;
    ta3.outputPWM(param);
    assert(TA3CTL & TASSEL_2);
    assert((TA3CTL & ID_2) == 0);
    assert(TA3CTL & MC_1);
    assert((TA3CTL & TAIE) == 0);
    assert(TA3EX0 == TAIDEX_5);
    assert(TA3CCR0 == 32767);
    assert(TA3CCR3 == 1600);
    assert(TA3CCTL3 == OUTMOD_7);

    param.dutyCycle = 800;
    ta3.outputPWM(param);
    assert(TA3CCR3 == 800);
    assert(TA3CCTL3 == OUTMOD_7);

    param.reg = CAPTURE_COMPARE::REGISTER1;
    ta3.outputPWM(param);
    assert(TA3CCR1 == 800);
    assert(TA3CCTL1 == OUTMOD_7);

    param.out = COMPARE_OUTPUT::SET;
    ta3.outputPWM(param);
    assert(TA3CCR1 == 800);
    assert(TA3CCTL1 == OUTMOD_1);
}


void runInterrupts() noexcept {

    resetRegisters();

    TA3 ta3;
    ta3.enableInterrupt();
    assert(TA3CTL & TAIE);

    ta3.disableInterrupt();
    assert((TA3CTL & TAIE) == 0);

    TA3CTL |= TAIFG;
    assert(ta3.getInterruptStatus() == INT_MASK_MATCH::TRUE);

    ta3.clearTimerInterrupt();
    assert(ta3.getInterruptStatus() == INT_MASK_MATCH::FALSE);
}

void runCCInterrupts() noexcept {

    resetRegisters();

    TA3 ta3;
    ta3.enableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER0);
    assert(TA3CCTL0 & CCIE);

    ta3.enableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER1);
    assert(TA3CCTL1 & CCIE);

    ta3.enableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER2);
    assert(TA3CCTL2 & CCIE);

    ta3.enableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER3);
    assert(TA3CCTL3 & CCIE);

    ta3.enableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER4);
    assert(TA3CCTL4 & CCIE);


    ta3.disableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER0);
    assert((TA3CCTL0 & CCIE) == 0);

    ta3.disableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER1);
    assert((TA3CCTL1 & CCIE) == 0);

    ta3.disableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER2);
    assert((TA3CCTL2 & CCIE) == 0);

    ta3.disableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER3);
    assert((TA3CCTL3 & CCIE) == 0);

    ta3.disableCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER4);
    assert((TA3CCTL4 & CCIE) == 0);


    TA3CCTL0 |= CCIFG;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::TRUE);

    TA3CCTL0 |= COV;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::TRUE);

    TA3CCTL1 |= CCIFG;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::TRUE);

    TA3CCTL1 |= COV;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::TRUE);

    TA3CCTL2 |= CCIFG;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::TRUE);

    TA3CCTL2 |= COV;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::TRUE);

    TA3CCTL3 |= CCIFG;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER3, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::TRUE);

    TA3CCTL3 |= COV;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER3, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::TRUE);

    TA3CCTL4 |= CCIFG;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER4, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::TRUE);

    TA3CCTL4 |= COV;
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER4, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::TRUE);


    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER0);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_OVERFLOW);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER0, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER1);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_OVERFLOW);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER1, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER2);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_OVERFLOW);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER2, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER3);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER3, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER3, INT::CAPTURE_OVERFLOW);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER3, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER4);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER4, INT::CAPTURE_INTERRUPT) == INT_MASK_MATCH::FALSE);

    ta3.clearCaptureCompareInterrupt(CAPTURE_COMPARE::REGISTER4, INT::CAPTURE_OVERFLOW);
    assert(ta3.getCaptureCompareInterruptStatus(CAPTURE_COMPARE::REGISTER4, INT::CAPTURE_INTERRUPT | INT::CAPTURE_OVERFLOW) == INT_MASK_MATCH::FALSE);
}


void runMisc() noexcept {

    resetRegisters();
    TA3 ta3;

    TA3CTL |= MC_3;
    ta3.stop();
    assert((TA3CTL & MC_3) == 0);

    TA3R = 123;
    assert(ta3.getCounterValue() == 123);
}

void runCCMisc() noexcept {

    resetRegisters();
    TA3 ta3;

    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER0, CAPTURE_COMPARE_READ_INPUT::SYNCED) == CAPTURE_COMPARE_INPUT::LOW);
    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER0, CAPTURE_COMPARE_READ_INPUT::NOT_SYNCED) == CAPTURE_COMPARE_INPUT::LOW);

    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER1, CAPTURE_COMPARE_READ_INPUT::SYNCED) == CAPTURE_COMPARE_INPUT::LOW);
    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER1, CAPTURE_COMPARE_READ_INPUT::NOT_SYNCED) == CAPTURE_COMPARE_INPUT::LOW);

    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER2, CAPTURE_COMPARE_READ_INPUT::SYNCED) == CAPTURE_COMPARE_INPUT::LOW);
    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER2, CAPTURE_COMPARE_READ_INPUT::NOT_SYNCED) == CAPTURE_COMPARE_INPUT::LOW);

    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER3, CAPTURE_COMPARE_READ_INPUT::SYNCED) == CAPTURE_COMPARE_INPUT::LOW);
    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER3, CAPTURE_COMPARE_READ_INPUT::NOT_SYNCED) == CAPTURE_COMPARE_INPUT::LOW);

    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER4, CAPTURE_COMPARE_READ_INPUT::SYNCED) == CAPTURE_COMPARE_INPUT::LOW);
    assert(ta3.getSynchronizedCaptureCompareInput(CAPTURE_COMPARE::REGISTER4, CAPTURE_COMPARE_READ_INPUT::NOT_SYNCED) == CAPTURE_COMPARE_INPUT::LOW);


    TA3CCTL0 |= OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER0) == COMPARE_OUT_BIT::HIGH);
    TA3CCTL0 &= ~OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER0) == COMPARE_OUT_BIT::LOW);

    TA3CCTL1 |= OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER1) == COMPARE_OUT_BIT::HIGH);
    TA3CCTL1 &= ~OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER1) == COMPARE_OUT_BIT::LOW);

    TA3CCTL2 |= OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER2) == COMPARE_OUT_BIT::HIGH);
    TA3CCTL2 &= ~OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER2) == COMPARE_OUT_BIT::LOW);

    TA3CCTL3 |= OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER3) == COMPARE_OUT_BIT::HIGH);
    TA3CCTL3 &= ~OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER3) == COMPARE_OUT_BIT::LOW);

    TA3CCTL4 |= OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER4) == COMPARE_OUT_BIT::HIGH);
    TA3CCTL4 &= ~OUT;
    assert(ta3.getOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER4) == COMPARE_OUT_BIT::LOW);


    TA3CCR0 = 123;
    assert(ta3.getCaptureCompareCount(CAPTURE_COMPARE::REGISTER0) == 123);

    TA3CCR1 = 123;
    assert(ta3.getCaptureCompareCount(CAPTURE_COMPARE::REGISTER1) == 123);

    TA3CCR2 = 123;
    assert(ta3.getCaptureCompareCount(CAPTURE_COMPARE::REGISTER2) == 123);

    TA3CCR3 = 123;
    assert(ta3.getCaptureCompareCount(CAPTURE_COMPARE::REGISTER3) == 123);

    TA3CCR4 = 123;
    assert(ta3.getCaptureCompareCount(CAPTURE_COMPARE::REGISTER4) == 123);


    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER0, COMPARE_OUT_BIT::HIGH);
    assert(TA3CCTL0 & OUT);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER0, COMPARE_OUT_BIT::LOW);
    assert((TA3CCTL0 & OUT) == 0);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER1, COMPARE_OUT_BIT::HIGH);
    assert(TA3CCTL1 & OUT);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER1, COMPARE_OUT_BIT::LOW);
    assert((TA3CCTL1 & OUT) == 0);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER2, COMPARE_OUT_BIT::HIGH);
    assert(TA3CCTL2 & OUT);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER2, COMPARE_OUT_BIT::LOW);
    assert((TA3CCTL2 & OUT) == 0);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER3, COMPARE_OUT_BIT::HIGH);
    assert(TA3CCTL3 & OUT);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER3, COMPARE_OUT_BIT::LOW);
    assert((TA3CCTL3 & OUT) == 0);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER4, COMPARE_OUT_BIT::HIGH);
    assert(TA3CCTL4 & OUT);

    ta3.setOutputForOutputModeOutBitValue(CAPTURE_COMPARE::REGISTER4, COMPARE_OUT_BIT::LOW);
    assert((TA3CCTL4 & OUT) == 0);


    ta3.setCompareValue(CAPTURE_COMPARE::REGISTER0, 123);
    assert(TA3CCR0 == 123);

    ta3.setCompareValue(CAPTURE_COMPARE::REGISTER1, 123);
    assert(TA3CCR1 == 123);

    ta3.setCompareValue(CAPTURE_COMPARE::REGISTER2, 123);
    assert(TA3CCR2 == 123);

    ta3.setCompareValue(CAPTURE_COMPARE::REGISTER3, 123);
    assert(TA3CCR3 == 123);

    ta3.setCompareValue(CAPTURE_COMPARE::REGISTER4, 123);
    assert(TA3CCR4 == 123);

    ta3.setOutputMode(CAPTURE_COMPARE::REGISTER0, COMPARE_OUTPUT::TOGGLE);
    assert(TA3CCTL0 == OUTMOD_4);

    ta3.setOutputMode(CAPTURE_COMPARE::REGISTER1, COMPARE_OUTPUT::TOGGLE);
    assert(TA3CCTL1 == OUTMOD_4);

    ta3.setOutputMode(CAPTURE_COMPARE::REGISTER2, COMPARE_OUTPUT::TOGGLE);
    assert(TA3CCTL2 == OUTMOD_4);

    ta3.setOutputMode(CAPTURE_COMPARE::REGISTER3, COMPARE_OUTPUT::TOGGLE);
    assert(TA3CCTL3 == OUTMOD_4);

    ta3.setOutputMode(CAPTURE_COMPARE::REGISTER4, COMPARE_OUTPUT::TOGGLE);
    assert(TA3CCTL4 == OUTMOD_4);
}

#endif

}// namespace MT::Tests::MSP430::TIMERA::Internal


namespace MT::Tests::MSP430::TIMERA {
void run() noexcept {
#if defined(__MSP430_HAS_T3A5__)
    Internal::runContMode();
    Internal::runUpMode();
    Internal::runUpDownMode();
    Internal::runCaptureMode();
    Internal::runCompareMode();
    Internal::runPWMMode();

    Internal::runInterrupts();
    Internal::runCCInterrupts();
    Internal::runMisc();
    Internal::runCCMisc();
#else
    assert(1 == 2);// Test not executed!!
#endif
}
}// namespace MT::Tests::MSP430::TIMERA


#endif /* MICROTRAIT_TESTS_MSP430_TESTTIMERA_HPP_ */

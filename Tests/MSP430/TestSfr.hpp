#ifndef MICROTRAIT_TESTS_MSP430_TESTSFR_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTSFR_HPP_

#include "MicroTrait/MSP430/SFR/Sfr.hpp"
#include <assert.h>

namespace MT::Tests::MSP430::SFR::Internal {

using namespace MT::MSP430::SFR;


void runInt() noexcept {
    MT::MSP430::Sfr sfr{};

    sfr.enableInterrupt(INT::WATCHDOG_INTERVAL_TIMER);
    assert(SFRIE1_L == WDTIE);

    sfr.disableInterrupt(INT::WATCHDOG_INTERVAL_TIMER);
    assert(SFRIE1_L == 0x00);

    sfr.enableInterrupt(INT::NMI_PIN);
    assert(SFRIE1_L == NMIIE);

    sfr.disableInterrupt(INT::NMI_PIN);
    assert(SFRIE1_L == 0x00);

    SFRIFG1_L |= WDTIFG;
    assert(sfr.getInterruptStatus(INT::WATCHDOG_INTERVAL_TIMER) == MT::MSP430::MASK_MATCH::TRUE);

    sfr.clearInterruptStatus(INT::WATCHDOG_INTERVAL_TIMER);
    assert(sfr.getInterruptStatus(INT::WATCHDOG_INTERVAL_TIMER) == MT::MSP430::MASK_MATCH::FALSE);
    assert(!(SFRIFG1_L & WDTIFG));

    SFRIFG1_L |= NMIIE;
    assert(sfr.getInterruptStatus(INT::NMI_PIN) == MT::MSP430::MASK_MATCH::TRUE);

    sfr.clearInterruptStatus(INT::NMI_PIN);
    assert(sfr.getInterruptStatus(INT::NMI_PIN) == MT::MSP430::MASK_MATCH::FALSE);
    assert(!(SFRIFG1_L & NMIIE));
}

void runReset() noexcept {
    MT::MSP430::Sfr sfr{};

    sfr.setResetPinPullResistor(RST_RESISTOR::PULLDOWN);
    assert(SFRRPCR & SYSRSTRE);

    sfr.setResetPinPullResistor(RST_RESISTOR::PULLUP);
    assert(SFRRPCR & (SYSRSTRE | SYSRSTUP));

    sfr.setNMIEdge(NMI_EDGE::FALLING);
    assert(SFRRPCR & SYSNMIIES);

    sfr.setNMIEdge(NMI_EDGE::RISING);

    sfr.setResetNMIPinFunction(RST_FUNC::NMI);
    assert(SFRRPCR & SYSNMI);

    sfr.setResetNMIPinFunction(RST_FUNC::RESET);
}


void runMeta() noexcept {
    MT::MSP430::Sfr sfr{};

    volatile INT vint = INT::WATCHDOG_INTERVAL_TIMER;
    sfr.clearInterruptStatus(vint);

    const INT cint = INT::WATCHDOG_INTERVAL_TIMER;
    sfr.clearInterruptStatus(cint);

    const volatile INT cvint = INT::WATCHDOG_INTERVAL_TIMER;
    sfr.clearInterruptStatus(cvint);
}


}// namespace MT::Tests::MSP430::SFR::Internal


namespace MT::Tests::MSP430::SFR {
void run() noexcept {
    Internal::runInt();
#if not defined(__MSP430_HAS_MSP430I_CPU__)
    Internal::runReset();
#endif
    Internal::runMeta();
}
}// namespace MT::Tests::MSP430::SFR


#endif /* MICROTRAIT_TESTS_MSP430_TESTSFR_HPP_ */

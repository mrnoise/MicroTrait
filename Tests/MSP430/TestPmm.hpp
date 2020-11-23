
#ifndef MICROTRAIT_TESTS_MSP430_TESTPMM_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTPMM_HPP_

#include "MicroTrait/MSP430/PMM/Pmm.hpp"
#include <assert.h>

namespace MT::Tests::MSP430::PMM::Internal {

using namespace MT::MSP430;

void runSVS() noexcept {

    Pmm pmm;

#if defined(__MSP430_HAS_PMM_FRAM__) || defined(__MSP430_HAS_PMM_FR5xx__)
    pmm.disableSVSH();
    assert((PMMCTL0 & SVSHE) == 0);

    pmm.enableSVSH();
    assert(PMMCTL0 & SVSHE);
#endif
}

void runMisc() noexcept {
    Pmm pmm;

#if defined(__MSP430_HAS_PMM_FRAM__) || defined(__MSP430_HAS_PMM_FR5xx__)
    pmm.turnOnRegulator();
    assert((PMMCTL0 & PMMREGOFF) == 0);

    pmm.turnOffRegulator();
    assert(PMMCTL0 & PMMREGOFF);

    //pmm.trigPOR();//can`t be tested because reset will occur
    //pmm.trigBOR(); //can`t be tested because reset will occur
    //pmm.unlockLPM5(); //can`t be tested because depends on startup state
#endif
}

void runInterrupt() noexcept {
    Pmm pmm;

#if defined(__MSP430_HAS_PMM_FRAM__) || defined(__MSP430_HAS_PMM_FR5xx__)

    //Not all Flags can be tested because dependency on system start up
    assert(pmm.getInterruptStatus(MT::MSP430::PMM::INT::RST) == INT_MASK_MATCH::TRUE);
    pmm.clearInterrupt(MT::MSP430::PMM::INT::RST);
    assert((PMMIFG & PMMRSTIFG) == 0);

    assert(pmm.getInterruptStatus(MT::MSP430::PMM::INT::SVSH) == INT_MASK_MATCH::FALSE);
    assert(pmm.getInterruptStatus(MT::MSP430::PMM::INT::BOR) == INT_MASK_MATCH::FALSE);
    assert(pmm.getInterruptStatus(MT::MSP430::PMM::INT::POR) == INT_MASK_MATCH::FALSE);

#endif
}


void runMeta() noexcept {
    Pmm pmm;
#if defined(__MSP430_HAS_PMM_FRAM__) || defined(__MSP430_HAS_PMM_FR5xx__)

    volatile MT::MSP430::PMM::INT vint = MT::MSP430::PMM::INT::RST;
    pmm.clearInterrupt(vint);

    const MT::MSP430::PMM::INT cint = MT::MSP430::PMM::INT::RST;
    pmm.clearInterrupt(cint);

    const volatile MT::MSP430::PMM::INT cvint = MT::MSP430::PMM::INT::RST;
    pmm.clearInterrupt(cvint);
#endif
}


}// namespace MT::Tests::MSP430::PMM::Internal


namespace MT::Tests::MSP430::PMM {
void run() noexcept {
    Internal::runSVS();
    Internal::runMisc();
    Internal::runInterrupt();
    Internal::runMeta();
}
}// namespace MT::Tests::MSP430::PMM

#endif /* MICROTRAIT_TESTS_MSP430_TESTPMM_HPP_ */

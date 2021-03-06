
#ifndef MICROTRAIT_TESTS_TESTRUNNER_HPP_
#define MICROTRAIT_TESTS_TESTRUNNER_HPP_

#include "MicroTrait/Tests/TestUniversal.hpp"
#include "MicroTrait/Tests/MSP430/TestGpio.hpp"
#include "MicroTrait/Tests/MSP430/TestSfr.hpp"
#include "MicroTrait/Tests/MSP430/TestWdtA.hpp"
#include "MicroTrait/Tests/MSP430/TestPmm.hpp"
#include "MicroTrait/Tests/MSP430/TestTimerA.hpp"
#include "MicroTrait/Tests/MSP430/TestEusciA.hpp"
#include "MicroTrait/Tests/MSP430/TestEusciB.hpp"

namespace MT::Tests {
void run() noexcept {
    MT::Tests::Universal::run();
    MT::Tests::MSP430::GPIO::run();
    MT::Tests::MSP430::SFR::run();
    MT::Tests::MSP430::WDTA::run();
    MT::Tests::MSP430::PMM::run();
    MT::Tests::MSP430::TIMERA::run();
    MT::Tests::MSP430::EUSCIA::run();
    MT::Tests::MSP430::EUSCIB::run();
}
}// namespace MT::Tests

#endif /* MICROTRAIT_TESTS_TESTRUNNER_HPP_ */

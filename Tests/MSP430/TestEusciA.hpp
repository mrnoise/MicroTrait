#ifndef MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_
#define MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_

#include <MicroTrait/MSP430/Types.hpp>
#include <MicroTrait/MSP430/EUSCI/EusciA.hpp>
#include <assert.h>

namespace MT::Tests::MSP430::EUSCIA::Internal {

using namespace MT::MSP430::EUSCIA;
using namespace MT::MSP430;


}// namespace MT::Tests::MSP430::EUSCI::Internal


namespace MT::Tests::MSP430::EUSCIA {
void run() noexcept {
#if defined(__MSP430_HAS_EUSCI_A0__)


#else
    assert(1 == 2);// Test not executed!!
#endif
}
}// namespace MT::Tests::MSP430::EUSCIA

#endif /* MICROTRAIT_TESTS_MSP430_TESTEUSCIA_HPP_ */

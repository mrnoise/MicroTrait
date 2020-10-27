#include <MicroTrait/MSP430/WDTA/WdtAInterrupt.hpp>

#ifdef MT_USE_MSP430_LIB
#ifdef __MSP430_HAS_WDT_A__
#ifndef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

namespace MT::MSP430::WDTA::Interrupt {

std::array<void (*)(), 1>
    WdtVectors{};

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = WDT_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(WDT_VECTOR)))
#endif
    void
    WDT_A_ISR(void) {
    if (WdtVectors[WDTA::VEC1] != nullptr) WdtVectors[WDTA::VEC1]();
}

}// namespace MT::MSP430::WDTA::Interrupt

#endif
#endif
#endif

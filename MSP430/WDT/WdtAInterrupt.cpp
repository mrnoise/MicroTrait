#include <MicroTrait/MSP430/WDT/WdtAInterrupt.hpp>

#ifdef MT_USE_MSP430_LIB
#ifdef __MSP430_HAS_WDT_A__
#ifndef MT_MSP430_USE_WDT_COMPILE_TIME_CALLBACKS

namespace MT::MSP430::WDTA::Interrupt {

std::array<void (*)(), 1> WdtVectors{};

}// namespace MT::MSP430::WDTA::Interrupt

#endif
#endif
#endif

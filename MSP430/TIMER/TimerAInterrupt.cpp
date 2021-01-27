#include <MicroTrait/MSP430/TIMER/TimerAInterrupt.hpp>

#ifdef MT_USE_MSP430_LIB

#ifndef MT_MSP430_USE_TIMERA_COMPILE_TIME_CALLBACKS

namespace MT::MSP430::TIMERA::Interrupt {

std::array<void (*)(const TIMERA::Interrupt::SOURCE), 4> Vectors{};

}// namespace MT::MSP430::TIMERA::Interrupt
#endif
#endif

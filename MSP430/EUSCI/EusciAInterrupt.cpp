#include <MicroTrait/MSP430/EUSCI/EusciAInterrupt.hpp>

#ifdef MT_USE_MSP430_LIB

#ifndef MT_MSP430_USE_EUSCIA_UART_COMPILE_TIME_CALLBACKS

namespace MT::MSP430::EUSCIA::UART::Interrupt {

std::array<void (*)(const EUSCIA::UART::INT), 4> Vectors{};
std::array<volatile INTRINSICS, 4>                        Intrinsics{ INTRINSICS::NONE };

}// namespace MT::MSP430::EUSCIA::UART::Interrupt
#endif
#endif

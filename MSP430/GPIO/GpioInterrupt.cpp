#include <MicroTrait/MSP430/GPIO/GpioInterrupt.hpp>

#ifdef MT_USE_MSP430_LIB

#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

namespace MT::MSP430::GPIO::Interrupt {

std::array<void (*)(), 2> PortVectors{};

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
{
    if (PortVectors[PORTS::PORT1] != nullptr) PortVectors[PORTS::PORT1]();
}

// Port 2 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT2_VECTOR
__interrupt void
    Port_2(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT2_VECTOR))) Port_2(void)
#else
#error Compiler not supported!
#endif
{
    if (PortVectors[PORTS::PORT2] != nullptr) PortVectors[PORTS::PORT2]();
}

}// namespace MT::MSP430::GPIO::Interrupt
#endif
#endif

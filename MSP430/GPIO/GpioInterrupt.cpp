#include <MicroTrait/MSP430/GPIO/GpioInterrupt.hpp>

#ifdef MT_USE_MSP430_LIB

#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

namespace MT::MSP430::GPIO::Interrupt {

std::array<void (*)(const MT::MSP430::GPIO::PIN), PORTS::NONE> PortVectors{};

}// namespace MT::MSP430::GPIO::Interrupt
#endif
#endif

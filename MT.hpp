#ifndef MICROTRAIT_MT_HPP_
#define MICROTRAIT_MT_HPP_

#include "MicroTrait/Version.hpp"

#include "MicroTrait/Universal/Register.hpp"
#include "MicroTrait/Universal/Interrupt.hpp"

#include "MicroTrait/MSP430/Settings.hpp"
#include "MicroTrait/MSP430/GPIO/PortRegister.hpp"
#include "MicroTrait/MSP430/GPIO/PortInterrupt.hpp"

#if defined(__GNUC__)
#else
#error Compiler not supported!
#endif

#endif /* MICROTRAIT_MT_HPP_ */

#ifndef MICROTRAIT_MT_HPP_
#define MICROTRAIT_MT_HPP_


#include "MicroTrait/Version.hpp"
#include "MicroTrait/Settings.hpp"

#include "MicroTrait/Universal/Register.hpp"
#include "MicroTrait/Universal/Interrupt.hpp"

#include "MicroTrait/MSP430/Settings.hpp"
#include "MicroTrait/MSP430/Types.hpp"
#include "MicroTrait/MSP430/GPIO/Gpio.hpp"
#include "MicroTrait/MSP430/GPIO/GpioInterrupt.hpp"
#include "MicroTrait/MSP430/SFR/Sfr.hpp"
#include "MicroTrait/MSP430/PMM/Pmm.hpp"
#include <MicroTrait/MSP430/TIMER/TimerA.hpp>
#include <MicroTrait/MSP430/TIMER/TimerAInterrupt.hpp>
#include <MicroTrait/MSP430/WDT/WdtA.hpp>
#include <MicroTrait/MSP430/WDT/WdtAInterrupt.hpp>
#include <MicroTrait/MSP430/EUSCI/EusciA.hpp>
#include <MicroTrait/MSP430/EUSCI/EusciAInterrupt.hpp>

#if defined(__GNUC__)
#else
#error Compiler not supported!
#endif

#endif /* MICROTRAIT_MT_HPP_ */

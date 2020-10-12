
#include "MicroTrait/MSP430/GPIO/PortInterrupt.hpp"

namespace MT {
namespace MSP430 {
    namespace GPIO {
        namespace Interrupt {

            std::array<void (*)(), 2> PortVectors{};

#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

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
                if (PortVectors[PORT1] != nullptr) PortVectors[PORT1]();
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
                if (PortVectors[PORT2] != nullptr) PortVectors[PORT2]();
            }

#endif

        }// namespace Interrupt
    }    // namespace GPIO
}// namespace MSP430
}// namespace MT

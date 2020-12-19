#include <MicroTrait/MSP430/GPIO/GpioInterrupt.hpp>

#ifdef MT_USE_MSP430_LIB

#ifndef MT_MSP430_USE_GPIO_COMPILE_TIME_CALLBACKS

namespace MT::MSP430::GPIO::Interrupt {

std::array<void (*)(MT::MSP430::GPIO::PIN), PORTS::NONE> PortVectors{};

#if defined(P1IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT1_VECTOR))) Port_1(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P1IV, P1IV_P1IFG7)) {
        case P1IV_NONE: break;
        case P1IV_P1IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P1IV_P1IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P1IV_P1IFG2:
            pin = MT::MSP430::GPIO::PIN::P2;
            break;
        case P1IV_P1IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P1IV_P1IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P1IV_P1IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P1IV_P1IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P1IV_P1IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P1] != nullptr) PortVectors[PORTS::P1](pin);
}
#endif


#if defined(P2IFG)
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
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P2IV, P2IV_P2IFG7)) {
        case P2IV_NONE: break;
        case P2IV_P2IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P2IV_P2IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P2IV_P2IFG2:
            pin = MT::MSP430::GPIO::PIN::P2;
            break;
        case P2IV_P2IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P2IV_P2IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P2IV_P2IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P2IV_P2IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P2IV_P2IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P2] != nullptr) PortVectors[PORTS::P2](pin);
}
#endif


#if defined(P3IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT3_VECTOR
__interrupt void
    Port_3(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT3_VECTOR))) Port_3(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P3IV, P3IV_P3IFG7)) {
        case P3IV_NONE: break;
        case P3IV_P3IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P3IV_P3IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P3IV_P3IFG2:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P3IV_P3IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P3IV_P3IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P3IV_P3IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P3IV_P3IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P3IV_P3IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P3] != nullptr) PortVectors[PORTS::P3](pin);
}
#endif

#if defined(P4IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT4_VECTOR
__interrupt void
    Port_4(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT4_VECTOR))) Port_4(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P4IV, P4IV_P4IFG7)) {
        case P4IV_NONE: break;
        case P4IV_P4IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P4IV_P4IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P4IV_P4IFG2:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P4IV_P4IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P4IV_P4IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P4IV_P4IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P4IV_P4IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P4IV_P4IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P4] != nullptr) PortVectors[PORTS::P4](pin);
}
#endif

#if defined(P5IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT5_VECTOR
__interrupt void
    Port_5(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT5_VECTOR))) Port_5(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P5IV, P5IV_P5IFG7)) {
        case P5IV_NONE: break;
        case P5IV_P5IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P5IV_P5IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P5IV_P5IFG2:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P5IV_P5IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P5IV_P5IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P5IV_P5IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P5IV_P5IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P5IV_P5IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P5] != nullptr) PortVectors[PORTS::P5](pin);
}
#endif


#if defined(P6IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT6_VECTOR
__interrupt void
    Port_6(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT6_VECTOR))) Port_6(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P6IV, P6IV_P6IFG7)) {
        case P6IV_NONE: break;
        case P6IV_P6IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P6IV_P6IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P6IV_P6IFG2:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P6IV_P6IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P6IV_P6IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P6IV_P6IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P6IV_P6IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P6IV_P6IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P6] != nullptr) PortVectors[PORTS::P6](pin);
}
#endif


#if defined(P7IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT7_VECTOR
__interrupt void
    Port_7(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT7_VECTOR))) Port_7(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P7IV, P7IV_P7IFG7)) {
        case P7IV_NONE: break;
        case P7IV_P7IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P7IV_P7IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P7IV_P7IFG2:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
        case P7IV_P7IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P7IV_P7IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P7IV_P7IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P7IV_P7IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P7IV_P7IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P7] != nullptr) PortVectors[PORTS::P7](pin);
}
#endif


#if defined(P8IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT8_VECTOR
__interrupt void
    Port_8(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT8_VECTOR))) Port_8(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P8IV, P8IV_P8IFG7)) {
        case P8IV_NONE: break;
        case P8IV_P8IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P8IV_P8IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P8IV_P8IFG2:
            pin = MT::MSP430::GPIO::PIN::P8;
            break;
        case P8IV_P8IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P8IV_P8IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P8IV_P8IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P8IV_P8IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P8IV_P8IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P8] != nullptr) PortVectors[PORTS::P8](pin);
}
#endif

#if defined(P9IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT9_VECTOR
__interrupt void
    Port_9(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT9_VECTOR))) Port_9(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P9IV, P9IV_P9IFG7)) {
        case P9IV_NONE: break;
        case P9IV_P9IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P9IV_P9IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P9IV_P9IFG2:
            pin = MT::MSP430::GPIO::PIN::P9;
            break;
        case P9IV_P9IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P9IV_P9IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P9IV_P9IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P9IV_P9IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P9IV_P9IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P9] != nullptr) PortVectors[PORTS::P9](pin);
}
#endif

#if defined(P10IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT10_VECTOR
__interrupt void
    Port_10(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT10_VECTOR))) Port_10(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P10IV, P10IV_P10IFG7)) {
        case P10IV_NONE: break;
        case P10IV_P10IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P10IV_P10IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P10IV_P10IFG2:
            pin = MT::MSP430::GPIO::PIN::P10;
            break;
        case P10IV_P10IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P10IV_P10IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P10IV_P10IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P10IV_P10IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P10IV_P10IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P10] != nullptr) PortVectors[PORTS::P10](pin);
}
#endif

#if defined(P11IFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORT11_VECTOR
__interrupt void
    Port_11(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORT11_VECTOR))) Port_11(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(P11IV, P11IV_P11IFG7)) {
        case P11IV_NONE: break;
        case P11IV_P11IFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case P11IV_P11IFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case P11IV_P11IFG2:
            pin = MT::MSP430::GPIO::PIN::P11;
            break;
        case P11IV_P11IFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case P11IV_P11IFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case P11IV_P11IFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case P11IV_P11IFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case P11IV_P11IFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::P11] != nullptr) PortVectors[PORTS::P11](pin);
}
#endif

#if defined(PJIFG)
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = PORTJ_VECTOR
__interrupt void
    Port_J(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(PORTJ_VECTOR))) Port_J(void)
#else
#error Compiler not supported!
#endif
{
    MT::MSP430::GPIO::PIN pin = MT::MSP430::GPIO::PIN::NONE;

    switch (__even_in_range(PJIV, PJIV_PJIFG7)) {
        case PJIV_NONE: break;
        case PJIV_PJIFG0:
            pin = MT::MSP430::GPIO::PIN::P0;
            break;
        case PJIV_PJIFG1:
            pin = MT::MSP430::GPIO::PIN::P1;
            break;
        case PJIV_PJIFG2:
            pin = MT::MSP430::GPIO::PIN::PJ;
            break;
        case PJIV_PJIFG3:
            pin = MT::MSP430::GPIO::PIN::P3;
            break;
        case PJIV_PJIFG4:
            pin = MT::MSP430::GPIO::PIN::P4;
            break;
        case PJIV_PJIFG5:
            pin = MT::MSP430::GPIO::PIN::P5;
            break;
        case PJIV_PJIFG6:
            pin = MT::MSP430::GPIO::PIN::P6;
            break;
        case PJIV_PJIFG7:
            pin = MT::MSP430::GPIO::PIN::P7;
            break;
    }

    if (PortVectors[PORTS::PJ] != nullptr) PortVectors[PORTS::PJ](pin);
}
#endif


}// namespace MT::MSP430::GPIO::Interrupt
#endif
#endif

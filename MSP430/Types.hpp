/** @defgroup groupMSP430 MSP430
* MSP430 specific code
*/

/** @defgroup groupMSP430Types Types
 *  @ingroup groupMSP430
* @brief Generic Type definitions
*
* @author Steffen Fuchs
*<br> Email: admin@definefalsetrue.com
*<br> Web: https://definefalsetrue.com
*
****************************************************************
*/


/** @defgroup groupEnumsMSP430Types Enums
*  @ingroup groupMSP430Types
*  Enums in this module
*/

#ifndef MICROTRAIT_MSP430_TYPES_HPP_
#define MICROTRAIT_MSP430_TYPES_HPP_

#include <stdint.h>

namespace MT::MSP430 {

/**
* @ingroup groupEnumsMSP430Types
****************************************************************
* @brief generic Status
****************************************************************
*/
enum class STATUS : uint_fast8_t {
    FAIL = 0,
    SUCCESS
};

/**
* @ingroup groupEnumsMSP430Types
****************************************************************
* @brief Indicates that a mask match occurred or not
****************************************************************
*/
enum class MASK_MATCH : uint_fast8_t {
    FALSE = 0,
    TRUE
};


/**
* @ingroup groupEnumsMSP430Types
****************************************************************
* @brief Interrupt pending or not
****************************************************************
*/
enum class INT_PENDING_STATUS : uint_fast8_t {
    NOT_PENDING = 0,
    PENDING
};

/**
* @ingroup groupEnumsMSP430Types
****************************************************************
* @brief Intrinsics which can be invoked before leaving ISR
****************************************************************
*/
enum class ISR_INTRINSICS {
    NONE            = 0,
    LEAVE_LOW_POWER = 1,
};

/**
* @ingroup groupEnumsMSP430Types
****************************************************************
* @brief if the Register is in the reset state (after startup) or not
****************************************************************
*/
enum class REGISTER_STATE : uint_fast8_t {
    RESET = 0,
    MODIFIED
};


/**
* @ingroup groupEnumsMSP430Types
****************************************************************
* @brief context usage of a function or class -> in ISR context or polling
****************************************************************
*/
enum class USAGE_CONTEXT : uint_fast8_t {
    IN_INTERRUPT = 0,
    POLLING
};

}// namespace MT::MSP430

#endif /* MICROTRAIT_MSP430_TYPES_HPP_ */

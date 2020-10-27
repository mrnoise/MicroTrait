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
* @brief Interrupt Flag match
****************************************************************
*/
enum class INT_MASK_MATCH : uint_fast8_t {
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

}// namespace MT::MSP430

#endif /* MICROTRAIT_MSP430_TYPES_HPP_ */

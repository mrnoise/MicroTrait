/*
 * TestRunner.hpp
 *
 *  Created on: 02.10.2020
 *      Author: steff
 */

#ifndef MICROTRAIT_TESTS_TESTRUNNER_HPP_
#define MICROTRAIT_TESTS_TESTRUNNER_HPP_

#include "MicroTrait/Tests/TestUniversal.hpp"

namespace MT {
namespace Tests {
    void run() noexcept {

        MT::Tests::Universal::run();
    }

}// namespace Tests
}// namespace MT


#endif /* MICROTRAIT_TESTS_TESTRUNNER_HPP_ */

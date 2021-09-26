//
// Created by loghin on 05.04.2021.
//

#include "FloatTest.h"

#include <CDS/Float>
#include <iostream>

auto FloatTest::execute() noexcept -> bool {
    bool allOk = true;

    auto value = Float::parse("-.5");

    std::cout << value << '\n';

    return allOk;
}
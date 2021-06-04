//
// Created by loghin on 05.04.2021.
//

#include "BooleanTest.h"
#include <Boolean.hpp>

auto BooleanTest::execute() noexcept -> bool{
    bool allOk = true;
    this->logBold("Start of test Boolean...");

    this->executeSubtest("Constructor Test", [this, &allOk]{
        Boolean empty;
        this->log("Empty Boolean constructed: ");
    });
    return allOk;
}

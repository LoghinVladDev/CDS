//
// Created by loghin on 05.04.2021.
//

#include "IntegerTest.h"

#include "primitive/Integer.hpp"
#include <CDS/Range>

auto IntegerTest::execute() noexcept -> bool{

    bool allOk = true;

    this->logBold("Starting of test Integer...");

    //TODO: create constructor tests
    this->executeSubtest("Constructor Tests", [this, &allOk]{
        Integer empty;
        this->log("Empty Integer Constructed: ");
    });

    this->executeSubtest("Random Tests", [this, &allOk]{

        std::vector<int> values;

        for(auto i : Range(5)) {
            Integer random_value = Integer::random();
            values.push_back((int) random_value);
            this->log("Random value assigned: %d", random_value.get());
        }

        Integer random_value_from_interval = Integer::random(-239252, 23509);
        this->log("Random value from %d to %d assigned: %d", -239252, 23509, random_value_from_interval.get());

    });

    this->executeSubtest("Assignment Operators Tests", [this, &allOk]{

        int test_int = 23492;
        Integer A = test_int;

        if((int) A == test_int) {
            this->log("Value %d has been successfully assigned to Integer obj A", test_int);
            A = 0;
        }
        else
            this->logError("Error at assigning value %d to Integer obj", test_int);

        Integer B;
        B = A;
        if(A.get() == B.get() && (int)A == (int)B)
            this->log("Integer obj A with value %d has been successfully assigned to Integer object B", test_int);
        else
            this->logError("Error at assigning Integer obj A to Integer obj B");
    });

    this->executeSubtest("Algebraic Operators Test", [this, &allOk]{
        Integer A, B, C;
        int test_int = 2350;

#define _ALGEBRAIC_OP_TEST(_op)                                                                     \
        A = Integer::random();                                                                      \
        B = Integer::random();                                                                      \
        C = A _op B;                                                                                \
        if(C == A _op B && C.get() == A.get() _op B.get() && (int)C == (int)A _op (int)B) {         \
            this->log("#_op between two Integer obj done successfully.");                           \
        }                                                                                           \
        else                                                                                        \
            this->logError("Error at #_op between two Integer Obj");                                \
        C = A _op test_int;                                                                         \
        if(C == A _op test_int && C.get() == A.get() _op test_int && (int)C == (int)A _op test_int) \
            this->log("Int value successfully #_op to an Integer obj");                             \
        else                                                                                        \
            this->logError("Error at #_op between an Integer Obj and an int value");                \

        _ALGEBRAIC_OP_TEST(+)
        _ALGEBRAIC_OP_TEST(-)
        _ALGEBRAIC_OP_TEST(*)
        _ALGEBRAIC_OP_TEST(/)
        _ALGEBRAIC_OP_TEST(%)

#undef _ALGEBRAIC_OP_TEST

//        C = A + B;
//        if(C == A + B && C.get() == A.get() + B.get() && (int)C == (int)A + (int)B)
//            this->log("Sum between two Integer obj done successfully.");
//        else
//            this->logError("Error at operator+ between two Integer Obj");
//
//        C = A + test_int;
//        if(C== A + test_int && C.get() == A.get() + test_int && (int)C == (int)A + test_int)
//            this->log("Int value successfully added to an Integer obj");
//        else
//            this->logError("Error at operator+ between an Integer Obj and an int value");

    });

    this->executeSubtest("Relational Operators Tests", [this, &allOk]{

    });
    return false;
}


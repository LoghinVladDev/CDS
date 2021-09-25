//
// Created by loghin on 05.04.2021.
//

#include "LongTest.h"

#include "primitive/Long.hpp"
#include <CDS/Range>
#include <CDS/Thread>

auto LongTest::execute() noexcept -> bool{

    bool allOk = true;

    this->logBold("Starting of test Long...");

    //TODO: create constructor tests
    this->executeSubtest("Constructor Tests", [this, &allOk]{
        Long empty;
        this->log("Empty Long Constructed: %d", empty.get());

        if ( empty.get() != 0 ) {
            this->logWarning("Empty Constructor Error");
            allOk = false;
        }

        Long fromInt (5);
        this->log("From Int Long : %d", fromInt.get());
        if ( fromInt.get() != 5 ) {
            this->logWarning("From Literal Error : %d", fromInt.get());
            allOk = false;
        }

        Long copy(fromInt);
        this->log("Copied : %d", copy.get());
        if ( copy.get() != 5 ) {
            this->logWarning("Copy Error : %d", copy.get());
            allOk = false;
        }

        copy = 7;
        this->log("Int Assigned : %d", copy.get());
        if ( copy.get() != 7 ) {
            this->logWarning("Assign sint64 error");
            allOk = false;
        }

        copy = fromInt;
        this->log("Long Assigned: %d", copy.get());
        if ( copy != fromInt ) {
            this->logWarning("Assign Long error");
            allOk = false;
        }
    });

    this->executeSubtest("Random Tests", [this, &allOk]{

        std::vector<sint64> values;

        Long random_value = Long::random();
        for(auto i : Range(25)) {
            values.push_back((sint64) random_value);
            this->log("Random value assigned: %d", random_value.get());
            random_value = Long::random();
        }

        Random::Int entropyTest1, entropyTest2;

        auto v1 = entropyTest1.get(), v2 = entropyTest2.get();

        if ( v1 == v2 ) {
            this->logWarning("Long Random Entropy Error : value1 = %d, value2 = %d", v1, v2);
            allOk = false;
        } else {
            this->log("Long Random Entropy Success : value1 = %d, value2 = %d", v1, v2);
        }

        Long random_value_from_sint64erval = Long::random(-239252, 23509);
        this->log("Random value from %d to %d assigned: %d", -239252, 23509, random_value_from_sint64erval.get());

        Long random_value_from_sint64erval_recreated = Long::random(10, 15);
        this->log("Random value from %d to %d assigned: %d", 10, 15, random_value_from_sint64erval_recreated.get());

        if ( random_value_from_sint64erval_recreated.get() < 10 || random_value_from_sint64erval_recreated.get() > 15 ) {
            this->logWarning("Random from Re-Created Interval Error : %d", random_value_from_sint64erval_recreated.get());

            allOk = false;
        }

        HashMap < sint64, sint64 > valueDistribution;

        for ( auto _ : Range(0, 100000) ) {
            auto rValue = Long::random(10, 15);
            if ( rValue.get() < 10 || rValue.get() > 15 ) {
                this->logWarning("Random from 100000 calls Error");
                allOk = false;
                break;
            }

            valueDistribution[rValue] ++;
        }

        for ( auto i : valueDistribution ) {
            this->log("Distribution of %d among 100000 randoms in [10, 15] : %f %%", i.first(), static_cast < float > (i.second()) * 100.0f);
            if ( i.second() > 30000 ) {
                this->logWarning("Distribution invalid, consider reporting this error");
                allOk = false;
            }
        }
    });

    this->executeSubtest("Assignment Operators Tests", [this, &allOk]{

        sint64 test_sint64 = 23492;
        Long A = test_sint64;

        if((sint64) A == test_sint64) {
            this->log("Value %d has been successfully assigned to Long obj A", test_sint64);
            A = 0;
        }
        else
            this->logError("Error at assigning value %d to Long obj", test_sint64);

        Long B;
        B = A;
        if(A.get() == B.get() && (sint64)A == (sint64)B)
            this->log("Long obj A with value %d has been successfully assigned to Long object B", test_sint64);
        else
            this->logError("Error at assigning Long obj A to Long obj B");
    });

    this->executeSubtest("Algebraic Operators Test", [this, &allOk]{
        Long A, B, C;
        sint64 test_sint64 = 2350;

#define ALGEBRAIC_OP_TEST(_op)                                                                     \
        A = Long::random(-1000, 1000);                                                                      \
        B = Long::random(-1000, 1000);                                                                      \
        C = A _op B;                                                                                \
        if(C == A _op B && C.get() == A.get() _op B.get() && (sint64)C == (sint64)A _op (sint64)B) {         \
            this->log(#_op " between two Long obj done successfully.");                           \
        }                                                                                           \
        else                                                                                        \
            this->logError("Error at " #_op " between two Long Obj");                                \
        C = A _op test_sint64;                                                                         \
        if(C == A _op test_sint64 && C.get() == A.get() _op test_sint64 && (sint64)C == (sint64)A _op test_sint64) \
            this->log("Int value successfully " #_op " to an Long obj");                             \
        else                                                                                        \
            this->logError("Error at " #_op " between an Long Obj and an sint64 value");                \

        ALGEBRAIC_OP_TEST(+)
        ALGEBRAIC_OP_TEST(-)
        ALGEBRAIC_OP_TEST(*)
        ALGEBRAIC_OP_TEST(/)
        ALGEBRAIC_OP_TEST(%)

#undef ALGEBRAIC_OP_TEST
        sint64 c;
#define ALGEBRAIC_OP_TEST(_op) \
        A = Long::random(-1000, 1000); \
        B = Long::random(-1000, 1000); \
        c = A.get();                       \
                               \
        c _op B.get();     \
                               \
        A _op B;               \
                               \
        if ( c == A )          \
            this->log("Int Value successfully " # _op " to an Long Obj"); \
        else                   \
            this->logError("Error at " # _op " between Long and sint64 value");\

        ALGEBRAIC_OP_TEST(+=)
        ALGEBRAIC_OP_TEST(-=)
        ALGEBRAIC_OP_TEST(*=)
        ALGEBRAIC_OP_TEST(/=)
        ALGEBRAIC_OP_TEST(%=)

#undef ALGEBRAIC_OP_TEST

        try {
            sint64 x = 5;
            Long y;

            x / y;
        } catch ( Exception const & e ) {
            this->log("Caught %s, sint64ended", e.toString().cStr());
        }

    });

    this->executeSubtest("Relational Operators Tests", [this, &allOk]{
        Array < Long > values;
        Random::Int rValues(-10, 10);

        for ( auto i : Range(0, Long::random(10, 200)) )
            values.pushBack(rValues.get());

        for ( auto i : Range(0, values.size()) )
            for ( auto j : Range(0, values.size()) ) {
                if ( ( values[i] == values[j] ) != ( values[i].get() == values[j].get() ) ) {
                    this->logWarning("Operator == Error");
                    allOk = false;
                }
                if ( ( values[i] != values[j] ) != ( values[i].get() != values[j].get() ) ) {
                    this->logWarning("Operator != Error");
                    allOk = false;
                }
                if ( ( values[i] >= values[j] ) != ( values[i].get() >= values[j].get() ) ) {
                    this->logWarning("Operator >= Error");
                    allOk = false;
                }
                if ( ( values[i] <= values[j] ) != ( values[i].get() <= values[j].get() ) ) {
                    this->logWarning("Operator <= Error");
                    allOk = false;
                }
                if ( ( values[i] > values[j] ) != ( values[i].get() > values[j].get() ) ) {
                    this->logWarning("Operator > Error");
                    allOk = false;
                }
                if ( ( values[i] < values[j] ) != ( values[i].get() < values[j].get() ) ) {
                    this->logWarning("Operator < Error");
                    allOk = false;
                }
                if ( ( values[i] & values[j] ) != ( values[i].get() & values[j].get() ) ) {
                    this->logWarning("Operator & Error");
                    allOk = false;
                }
                if ( ( values[i] | values[j] ) != ( values[i].get() | values[j].get() ) ) {
                    this->logWarning("Operator | Error");
                    allOk = false;
                }
                if ( ( values[i] ^ values[j] ) != ( values[i].get() ^ values[j].get() ) ) {
                    this->logWarning("Operator ^ Error");
                    allOk = false;
                }
                if ( ( values[i] << values[j] ) != ( values[i].get() << values[j].get() ) ) {
                    this->logWarning("Operator << Error");
                    allOk = false;
                }
                if ( ( values[i] >> values[j] ) != ( values[i].get() >> values[j].get() ) ) {
                    this->logWarning("Operator >> Error");
                    allOk = false;
                }

                if ( ~ values[i] != ~values[i].get() ) {
                    this->logWarning("Operator ~ Error");
                    allOk = false;
                }

                sint64 rA = Long::random(10, 20);
                sint64 rB = Long::random(10, 20);

                Long cA = rA;
                Long cB = rB;

                if ( ( cA &= cB ) != ( rA &= rB ) ) {
                    this->logWarning("Operator &= Error");
                    allOk = false;
                }

                if ( ( cA |= cB ) != ( rA |= rB ) ) {
                    this->logWarning("Operator |= Error");
                    allOk = false;
                }

                if ( ( cA ^= cB ) != ( rA ^= rB ) ) {
                    this->logWarning("Operator ^= Error");
                    allOk = false;
                }

                if ( ( cA <<= cB ) != ( rA <<= rB ) ) {
                    this->logWarning("Operator <<= Error");
                    allOk = false;
                }

                if ( ( cA >>= cB ) != ( rA >>= rB ) ) {
                    this->logWarning("Operator >>= Error");
                    allOk = false;
                }

                if ( cA ++ != rA ++ ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( cA ++ != rA ++ ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( cA ++ != rA ++ ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( cA -- != rA -- ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( cA -- != rA -- ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( cA -- != rA -- ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( -- cA != -- rA ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( -- cA != -- rA ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( -- cA != -- rA ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( ++ cA != ++ rA ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( ++ cA != ++ rA ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                if ( ++ cA != ++ rA ) {
                    this->logWarning("Operator ++ Error");
                    allOk = false;
                }

                this->log("Operands between %d and %d successful", values[i].get(), values[j].get());
            }

        this->executeSubtest("Utilities", [& allOk, this]{
            Long ip = 14;
            Long in = -14;

            this->log("Pos toString : '%s', Neg toString : '%s'", ip.toString().cStr(), in.toString().cStr());

            if ( ip.toString() != "14" || in.toString() != "-14" ) {
                this->logWarning("toString error");
                allOk = false;
            }

            ip = Long::parse("14");
            in = Long::parse("-14");

            this->log("Parse pos : '%s', Parse neg : '%s'", ip.toString().cStr(), in.toString().cStr());
            if ( ip.get() != 14 || in.get() != -14 ) {
                this->logWarning("parse Error");
                allOk = false;
            }
        });

        this->executeSubtest("Long::Atomic Tests", [& allOk, this] {
            Long::Atomic index = 0;

            Array < Long::Atomic > syncNumbers;
            syncNumbers.resize(10);

            auto syncTestThread = [&] {
                sint64 th = index++;
                this->log("Thread 'syncTestThread', ID: %d started", th);

                Index limit = Thread::hardwareConcurrency() <= 4 ? 10000 : 100000;
                for ( Index j = 0; j < limit; ++ j ) {
                    Index i = 0;
                    for (auto &e: syncNumbers) {
                        if ((i + th) % 2 == 0)
                            e++;
                        else
                            e--;
                        i++;
                    }
                }
                this->log("Thread 'syncTestThread', ID: %d ended", th);
            };

            Array < SharedPointer < Thread > > threads {
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),

                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),

                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),

                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),

                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),

                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
                    new Runnable < decltype (syncTestThread) > ( syncTestThread ),
            };

            threads.forEach([](PointerBase < Thread > & thread ){
                thread->start();
            });
            threads.forEach([](PointerBase < Thread > & thread ){
                thread->join();
            });

            if ( syncNumbers.any([](Long::Atomic & e){ return e.get().get() != 0; }) ) {
                this->logWarning("Thread Sync Error");
                allOk = false;
            }

            index = 0;

            auto numbers = Array < Long :: Atomic >();
            numbers.resize( Long::random(30, 100) );

            Mutex distLock;
            HashMap < Boolean, Long > dist;

            auto opFunction = [&] {
                Long::RandomGenerator generator(10, 50);
                Long::RandomGenerator rIn(0, (sint64)numbers.size() - 1);
                sint64 threadIndex = index ++;

                for ( auto & e : numbers )
                    for (auto _ : Range(generator.get()))
                        e = generator.get();

                for ( auto & e : numbers ) {
                    for (auto _: Range(generator.get()))
                        e = numbers[(sint64)rIn];

                    for (auto _: Range(generator.get()))
                        e = numbers[(sint64)rIn];
                }

                for (auto _: Range(generator.get()))
                    numbers[(sint64)rIn] ++;
                for (auto _: Range(generator.get()))
                    -- numbers[(sint64)rIn];
                for (auto _: Range(generator.get()))
                    numbers[(sint64)rIn] --;
                for (auto _: Range(generator.get()))
                    ++ numbers[(sint64)rIn];

                for (auto _: Range(generator.get()))
                    if ( numbers[(sint64)rIn] == numbers[(sint64)rIn] ) {
                        distLock.lock();
                        dist[true]++;
                        distLock.unlock();
                    } else if ( numbers[(sint64)rIn] == numbers[(sint64)rIn].get() ){
                        distLock.lock();
                        dist[true] ++;
                        distLock.unlock();
                    } else if ( numbers[(sint64)rIn].get() == numbers[(sint64)rIn] ){
                        distLock.lock();
                        dist[true] ++;
                        distLock.unlock();
                    } else if ( numbers[(sint64)rIn] != numbers[(sint64)rIn] ) {
                        distLock.lock();
                        dist[false]++;
                        distLock.unlock();
                    } else if ( numbers[(sint64)rIn] != numbers[(sint64)rIn].get() ){
                        distLock.lock();
                        dist[false] ++;
                        distLock.unlock();
                    } else if ( numbers[(sint64)rIn].get() != numbers[(sint64)rIn] ){
                        distLock.lock();
                        dist[false] ++;
                        distLock.unlock();
                    }

                for ( auto _ : Range( (sint64)generator ) ) {
                    numbers[(sint64)rIn] = numbers[(sint64)rIn] + numbers[(sint64)rIn];
                    numbers[(sint64)rIn] = numbers[(sint64)rIn] - numbers[(sint64)rIn];
                    numbers[(sint64)rIn] = numbers[(sint64)rIn] * numbers[(sint64)rIn];

                    try {
                        numbers[(sint64) rIn] = numbers[(sint64) rIn] / numbers[(sint64) rIn];
                    } catch ( ArithmeticException const & e ) {
                        this->log("Caught %s, sint64ended", e.toString().cStr());
                    }

                    try {
                        numbers[(sint64) rIn] = numbers[(sint64) rIn] % numbers[(sint64) rIn];
                    } catch ( std :: exception const & t ) {
                        this->log("Caught %s, sint64ended", t.what());
                    }

                    numbers[(sint64)rIn] = numbers[(sint64)rIn] & numbers[(sint64)rIn];
                    numbers[(sint64)rIn] = numbers[(sint64)rIn] | numbers[(sint64)rIn];
                    numbers[(sint64)rIn] = numbers[(sint64)rIn] ^ numbers[(sint64)rIn];
                    numbers[(sint64)rIn] = numbers[(sint64)rIn] >> numbers[(sint64)rIn];
                    numbers[(sint64)rIn] = numbers[(sint64)rIn] << numbers[(sint64)rIn];

                    numbers[(sint64)rIn] += numbers[(sint64)rIn];
                    numbers[(sint64)rIn] -= numbers[(sint64)rIn];
                    numbers[(sint64)rIn] *= numbers[(sint64)rIn];

                    try {
                        numbers[(sint64) rIn] /= numbers[(sint64) rIn];
                    } catch ( ArithmeticException const & ) {

                    }

                    try {
                        numbers[(sint64) rIn] %= numbers[(sint64) rIn];
                    } catch ( Exception const & ) {

                    }

                    numbers[(sint64)rIn] &= numbers[(sint64)rIn];
                    numbers[(sint64)rIn] >>= numbers[(sint64)rIn];
                    numbers[(sint64)rIn] <<= numbers[(sint64)rIn];

                    bool v1 = numbers[(sint64)rIn] <= numbers[(sint64)rIn];
                    v1 = numbers[(sint64)rIn] >= numbers[(sint64)rIn];
                    v1 = numbers[(sint64)rIn] > numbers[(sint64)rIn];
                    v1 = numbers[(sint64)rIn] < numbers[(sint64)rIn];
                    v1 = numbers[(sint64)rIn] == numbers[(sint64)rIn];
                    v1 = numbers[(sint64)rIn] != numbers[(sint64)rIn];
                }
            };

            Array < SharedPointer < Thread > > opThreads;
            for ( auto _ : Range((Index)Thread::hardwareConcurrency() * 8) )
                opThreads.add( new Runnable < decltype (opFunction) > (opFunction) );

            opThreads.forEach([](PointerBase < Thread > & thread ){
                thread->start();
            });
            opThreads.forEach([](PointerBase < Thread > & thread ){
                thread->join();
            });

            this->log("Equality Distribution : %s", dist.toString().cStr());
            this->log("Numbers : %s", numbers.sequence()
                    .map([](Long o){return (Long)o;})
                    .toLinkedList().toString().cStr()
            );
        });

        Exception e;
    });

    return allOk;
}


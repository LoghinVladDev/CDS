//
// Created by loghin on 05.04.2021.
//

#include "IntegerTest.h"

#include "primitive/Integer.hpp"
#include <CDS/Range>
#include <CDS/Thread>

auto IntegerTest::execute() noexcept -> bool{

    bool allOk = true;

    this->logBold("Starting of test Integer...");

    //TODO: create constructor tests
    this->executeSubtest("Constructor Tests", [this, &allOk]{
        Integer empty;
        this->log("Empty Integer Constructed: %d", empty.get());

        if ( empty.get() != 0 ) {
            this->logWarning("Empty Constructor Error");
            allOk = false;
        }

        Integer fromInt (5);
        this->log("From Int Integer : %d", fromInt.get());
        if ( fromInt.get() != 5 ) {
            this->logWarning("From Literal Error : %d", fromInt.get());
            allOk = false;
        }

        Integer copy(fromInt);
        this->log("Copied : %d", copy.get());
        if ( copy.get() != 5 ) {
            this->logWarning("Copy Error : %d", copy.get());
            allOk = false;
        }

        copy = 7;
        this->log("Int Assigned : %d", copy.get());
        if ( copy != 7 ) {
            this->logWarning("Assign int error");
            allOk = false;
        }

        copy = fromInt;
        this->log("Integer Assigned: %d", copy.get());
        if ( copy != fromInt ) {
            this->logWarning("Assign Integer error");
            allOk = false;
        }
    });

    this->executeSubtest("Random Tests", [this, &allOk]{

        std::vector<int> values;

        Integer random_value = Integer::random();
        for(auto i : Range(25)) {
            values.push_back((int) random_value);
            this->log("Random value assigned: %d", random_value.get());
            random_value = Integer::random();
        }

        Random::Int entropyTest1, entropyTest2;

        auto v1 = entropyTest1.get(), v2 = entropyTest2.get();

        if ( v1 == v2 ) {
            this->logWarning("Integer Random Entropy Error : value1 = %d, value2 = %d", v1, v2);
            allOk = false;
        } else {
            this->log("Integer Random Entropy Success : value1 = %d, value2 = %d", v1, v2);
        }

        Integer random_value_from_interval = Integer::random(-239252, 23509);
        this->log("Random value from %d to %d assigned: %d", -239252, 23509, random_value_from_interval.get());

        Integer random_value_from_interval_recreated = Integer::random(10, 15);
        this->log("Random value from %d to %d assigned: %d", 10, 15, random_value_from_interval_recreated.get());

        if ( random_value_from_interval_recreated < 10 || random_value_from_interval_recreated > 15 ) {
            this->logWarning("Random from Re-Created Interval Error : %d", random_value_from_interval_recreated.get());

            allOk = false;
        }

        HashMap < int, int > valueDistribution;

        for ( auto _ : Range(0, 100000) ) {
            auto rValue = Integer::random(10, 15);
            if ( rValue < 10 || rValue > 15 ) {
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

#define ALGEBRAIC_OP_TEST(_op)                                                                     \
        A = Integer::random(-1000, 1000);                                                                      \
        B = Integer::random(-1000, 1000);                                                                      \
        C = A _op B;                                                                                \
        if(C == A _op B && C.get() == A.get() _op B.get() && (int)C == (int)A _op (int)B) {         \
            this->log(#_op " between two Integer obj done successfully.");                           \
        }                                                                                           \
        else                                                                                        \
            this->logError("Error at " #_op " between two Integer Obj");                                \
        C = A _op test_int;                                                                         \
        if(C == A _op test_int && C.get() == A.get() _op test_int && (int)C == (int)A _op test_int) \
            this->log("Int value successfully " #_op " to an Integer obj");                             \
        else                                                                                        \
            this->logError("Error at " #_op " between an Integer Obj and an int value");                \

        ALGEBRAIC_OP_TEST(+)
        ALGEBRAIC_OP_TEST(-)
        ALGEBRAIC_OP_TEST(*)
        ALGEBRAIC_OP_TEST(/)
        ALGEBRAIC_OP_TEST(%)

#undef ALGEBRAIC_OP_TEST
        int c;
#define ALGEBRAIC_OP_TEST(_op) \
        A = Integer::random(-1000, 1000); \
        B = Integer::random(-1000, 1000); \
        c = A.get();                       \
                               \
        c _op B.get();     \
                               \
        A _op B;               \
                               \
        if ( c == A )          \
            this->log("Int Value successfully " # _op " to an Integer Obj"); \
        else                   \
            this->logError("Error at " # _op " between Integer and int value");\

        ALGEBRAIC_OP_TEST(+=)
        ALGEBRAIC_OP_TEST(-=)
        ALGEBRAIC_OP_TEST(*=)
        ALGEBRAIC_OP_TEST(/=)
        ALGEBRAIC_OP_TEST(%=)

#undef ALGEBRAIC_OP_TEST

        try {
            int x = 5;
            Integer y;

            x / y;
        } catch ( Exception const & e ) {
            this->log("Caught %s, intended", e.toString().cStr());
        }

    });

    this->executeSubtest("Relational Operators Tests", [this, &allOk]{
        Array < Integer > values;
        Random::Int rValues(-10, 10);

        for ( auto i : Range(0, Integer::random(10, 200)) )
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

                int rA = Integer::random(10, 20);
                int rB = Integer::random(10, 20);

                Integer cA = rA;
                Integer cB = rB;

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
            Integer ip = 14;
            Integer in = -14;

            this->log("Pos toString : '%s', Neg toString : '%s'", ip.toString().cStr(), in.toString().cStr());

            if ( ip.toString() != "14" || in.toString() != "-14" ) {
                this->logWarning("toString error");
                allOk = false;
            }

            ip = Integer::parse("14");
            in = Integer::parse("-14");

            this->log("Parse pos : '%s', Parse neg : '%s'", ip.toString().cStr(), in.toString().cStr());
            if ( ip != 14 || in != -14 ) {
                this->logWarning("parse Error");
                allOk = false;
            }
        });

        this->executeSubtest("Integer::Atomic Tests", [& allOk, this] {
            Integer::Atomic index = 0;

            Array < Integer::Atomic > syncNumbers;
            syncNumbers.resize(10);

            auto syncTestThread = [&] {
                int th = index++;
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

            if ( syncNumbers.any([](Integer::Atomic & e){ return e != 0; }) ) {
                this->logWarning("Thread Sync Error");
                allOk = false;
            }

            index = 0;

            auto numbers = Array < Integer :: Atomic >();
            numbers.resize( Integer::random(30, 100) );

            Mutex distLock;
            HashMap < Boolean, Integer > dist;

            auto opFunction = [&] {
                Integer::RandomGenerator generator(10, 50);
                Integer::RandomGenerator rIn(0, (int)numbers.size() - 1);
                int threadIndex = index ++;

                for ( auto & e : numbers )
                    for (auto _ : Range(generator.get()))
                        e = generator.get();

                for ( auto & e : numbers ) {
                    for (auto _: Range(generator.get()))
                        e = numbers[(int)rIn];

                    for (auto _: Range(generator.get()))
                        e = numbers[(int)rIn];
                }

                for (auto _: Range(generator.get()))
                    numbers[(int)rIn] ++;
                for (auto _: Range(generator.get()))
                    -- numbers[(int)rIn];
                for (auto _: Range(generator.get()))
                    numbers[(int)rIn] --;
                for (auto _: Range(generator.get()))
                    ++ numbers[(int)rIn];

                for (auto _: Range(generator.get()))
                    if ( numbers[(int)rIn] == numbers[(int)rIn] ) {
                        distLock.lock();
                        dist[true]++;
                        distLock.unlock();
                    } else if ( numbers[(int)rIn] == numbers[(int)rIn].get() ){
                        distLock.lock();
                        dist[true] ++;
                        distLock.unlock();
                    } else if ( numbers[(int)rIn].get() == numbers[(int)rIn] ){
                        distLock.lock();
                        dist[true] ++;
                        distLock.unlock();
                    } else if ( numbers[(int)rIn] != numbers[(int)rIn] ) {
                        distLock.lock();
                        dist[false]++;
                        distLock.unlock();
                    } else if ( numbers[(int)rIn] != numbers[(int)rIn].get() ){
                        distLock.lock();
                        dist[false] ++;
                        distLock.unlock();
                    } else if ( numbers[(int)rIn].get() != numbers[(int)rIn] ){
                        distLock.lock();
                        dist[false] ++;
                        distLock.unlock();
                    }

                for ( auto _ : Range( (int)generator ) ) {
                    numbers[(int)rIn] = numbers[(int)rIn] + numbers[(int)rIn];
                    numbers[(int)rIn] = numbers[(int)rIn] - numbers[(int)rIn];
                    numbers[(int)rIn] = numbers[(int)rIn] * numbers[(int)rIn];

                    try {
                        numbers[(int) rIn] = numbers[(int) rIn] / numbers[(int) rIn];
                    } catch ( ArithmeticException const & e ) {
                        this->log("Caught %s, intended", e.toString().cStr());
                    }

                    try {
                        numbers[(int) rIn] = numbers[(int) rIn] % numbers[(int) rIn];
                    } catch ( std :: exception const & t ) {
                        this->log("Caught %s, intended", t.what());
                    }

                    numbers[(int)rIn] = numbers[(int)rIn] & numbers[(int)rIn];
                    numbers[(int)rIn] = numbers[(int)rIn] | numbers[(int)rIn];
                    numbers[(int)rIn] = numbers[(int)rIn] ^ numbers[(int)rIn];
                    numbers[(int)rIn] = numbers[(int)rIn] >> numbers[(int)rIn];
                    numbers[(int)rIn] = numbers[(int)rIn] << numbers[(int)rIn];

                    numbers[(int)rIn] += numbers[(int)rIn];
                    numbers[(int)rIn] -= numbers[(int)rIn];
                    numbers[(int)rIn] *= numbers[(int)rIn];

                    try {
                        numbers[(int) rIn] /= numbers[(int) rIn];
                    } catch ( ArithmeticException const & ) {

                    }

                    try {
                        numbers[(int) rIn] %= numbers[(int) rIn];
                    } catch ( Exception const & ) {

                    }

                    numbers[(int)rIn] &= numbers[(int)rIn];
                    numbers[(int)rIn] >>= numbers[(int)rIn];
                    numbers[(int)rIn] <<= numbers[(int)rIn];

                    bool v1 = numbers[(int)rIn] <= numbers[(int)rIn];
                    v1 = numbers[(int)rIn] >= numbers[(int)rIn];
                    v1 = numbers[(int)rIn] > numbers[(int)rIn];
                    v1 = numbers[(int)rIn] < numbers[(int)rIn];
                    v1 = numbers[(int)rIn] == numbers[(int)rIn];
                    v1 = numbers[(int)rIn] != numbers[(int)rIn];
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
                    .map([](Integer o){return o;})
                    .toLinkedList().toString().cStr()
            );
        });

        Exception e;
    });

    return allOk;
}


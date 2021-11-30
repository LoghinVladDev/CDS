//
// Created by loghin on 30.11.2021.
//

#include "CollectionTest.h"
#include <CDS/Array>

using namespace cds;

auto CollectionTest :: execute() noexcept -> bool {
    bool allOk = true;

    Array < int > arrayTestObject = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    this->executeSubtest( "Contains/Additions", [&]{

        auto arrayIntContains = []( Collection < int > & array, int value ) {
            return array.contains( value );
        };
        auto constArrayIntContains = []( Collection < int > const & array, int value ) {
            return array.contains( value );
        };

        if (
                ! arrayIntContains ( arrayTestObject, 3 ) ||
                ! constArrayIntContains ( arrayTestObject, 3 )
        ) {
            this->logWarning("Array Contains Error");
            allOk = false;
        }

        if (
                arrayIntContains ( arrayTestObject, 200 ) ||
                constArrayIntContains ( arrayTestObject, 200 )
        ) {
            this->logWarning("Array Contains Error");
            allOk = false;
        }

    });

    this->executeSubtest( "Iterative Functionals", [&]{

        auto arrayIntSum = []( cds :: Collection < int > const & array ) -> int {
            int sum = 0;
            for ( auto const & v : array )
                sum += v;
            return sum;
        };

        auto arrayIntSumForEach_paramCopy = [] ( cds :: Collection < int > & array ) -> int {
            int sum = 0;
            array.forEach([&sum](auto v){sum += v;});
            return sum;
        };

        auto arrayIntSumForEach_paramRef = [] ( cds :: Collection < int > & array ) -> int {
            int sum = 0;
            array.forEach([&sum](auto & v){sum += v;});
            return sum;
        };

        auto arrayIntSumForEach_paramCRef = [] ( cds :: Collection < int > & array ) -> int {
            int sum = 0;
            array.forEach([&sum](auto const & v){sum += v;});
            return sum;
        };

        auto compareResults = [&]{

            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramCopy (arrayTestObject)) {
                this->logWarning("Array forEach error");
                allOk = false;
            }

            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramRef (arrayTestObject)) {
                this->logWarning("Array forEach error");
                allOk = false;
            }

            if ( arrayIntSum(arrayTestObject) != arrayIntSumForEach_paramCRef (arrayTestObject)) {
                this->logWarning("Array forEach error");
                allOk = false;
            }

        };

        compareResults();

        auto intArrayModify = [] ( Collection < int > & collection ) {
            collection.forEach([](auto & e){e = e * 2;});
        };

        intArrayModify ( arrayTestObject );

        compareResults();

    });

    return allOk;
}
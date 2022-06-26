#include <iostream>

//#include "src/experimental/new_iterable_model/Array.hpp"

#include <CDS/Object>

#include <CDS/experimental/Iterator>
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/DelegateIteratorRequestType.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/AbstractDelegateIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/impl/AbstractDelegateIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/AbstractDelegateWrapperIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/impl/AbstractDelegateWrapperIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/ForwardDelegateWrapperIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/BidirectionalDelegateWrapperIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/impl/ForwardDelegateWrapperIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/impl/BidirectionalDelegateWrapperIterator.hpp"


enum class E1 {
    f1 = 0x01,
    f2 = 0x02
};

class I {};
class D : public I {

};


using namespace cds :: experimental;

int main () {
    D d;

//    Array < int > a;
//
//    a.pushBack (3);
//    a.pushBack (2);
//    a.pushBack (1);
//    a.pushBack (2);
//    a.pushBack (3);
//
//    for ( auto & e : a ) {
//        std :: cout << e << ' ';
//    }
//    std :: cout << '\n';
//    for ( auto & e : ( Collection < int > const & ) a ) {
//        std :: cout << e << ' ';
//    }
//
//    std :: cout << sizeof ( Array < int >  ) - 64 * 4;

    return 0;
}
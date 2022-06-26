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
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/client/DelegateForwardIterableClient.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/client/DelegateForwardConstIterableClient.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/client/DelegateBackwardIterableClient.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/client/DelegateBackwardConstIterableClient.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/channel/DelegateIterableChannel.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/channel/DelegateConstIterableChannel.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/client/impl/DelegateForwardIterableClient.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/client/impl/DelegateForwardConstIterableClient.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/client/impl/DelegateBackwardIterableClient.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/client/impl/DelegateBackwardConstIterableClient.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/channel/impl/DelegateIterableChannel.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/channel/impl/DelegateConstIterableChannel.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/DelegateIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterator/impl/DelegateIterator.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/positive/DelegateConstIterableForwardPositiveResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/positive/DelegateConstIterableBackwardPositiveResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/positive/impl/DelegateConstIterableForwardPositiveResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/positive/impl/DelegateConstIterableBackwardPositiveResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/negative/DelegateConstIterableForwardNegativeResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/negative/DelegateConstIterableBackwardNegativeResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/negative/impl/DelegateConstIterableForwardNegativeResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/negative/impl/DelegateConstIterableBackwardNegativeResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/positive/DelegateIterableForwardPositiveResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/positive/DelegateIterableBackwardPositiveResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/positive/impl/DelegateIterableForwardPositiveResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/positive/impl/DelegateIterableBackwardPositiveResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/negative/DelegateIterableForwardNegativeResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/negative/DelegateIterableBackwardNegativeResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/negative/impl/DelegateIterableForwardNegativeResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/response/negative/impl/DelegateIterableBackwardNegativeResponse.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/DelegateIterableServer.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/DelegateConstIterableServer.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/impl/DelegateIterableServer.hpp"
#include "src/experimental/collection_new_iterable_model/shared/delegateIterableCommunication/server/impl/DelegateConstIterableServer.hpp"


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
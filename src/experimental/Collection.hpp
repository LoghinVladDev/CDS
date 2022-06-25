//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_EX_COLLECTION_HPP__
#define __CDS_EX_COLLECTION_HPP__

#include <CDS/Object>
#include "../collection/collection/DelegateIteratorRequestType.hpp"
#include "iterable/DelegateConstIterable.hpp"

namespace cds {

    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Collection :
                public Object,
                public __hidden :: __impl :: __DelegateConstIterable <
                        Collection < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __DelegateForwardConstIterable <
                        Collection < __ElementType >,
                        __ElementType,
                        false
                > {

        protected:
            using DelegateForwardConstIterable =
                    __hidden :: __impl ::__DelegateForwardConstIterable <
                            Collection < __ElementType >,
                            __ElementType,
                            false
                    >;

        public:
            using DelegateForwardConstIterable :: begin;
            using DelegateForwardConstIterable :: end;
            using DelegateForwardConstIterable :: cbegin;
            using DelegateForwardConstIterable :: cend;
        };

    }

}

#endif // __CDS_EX_COLLECTION_HPP__

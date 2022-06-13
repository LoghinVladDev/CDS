//
// Created by loghin on 6/13/22.
//

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace __impl {

                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                struct __UnidirectionalNode { // NOLINT(bugprone-reserved-identifier)
                    __ElementType        * _pData;
                    __UnidirectionalNode * _pNext;
                };

                template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
                struct __BidirectionalNode { // NOLINT(bugprone-reserved-identifier)
                    __ElementType         * _pData;
                    __BidirectionalNode   * _pNext;
                    __BidirectionalNode   * _pPrevious;
                };

            }
        }

    }
}

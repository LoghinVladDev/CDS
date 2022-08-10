//
// Created by loghin on 09/07/22.
//

#ifndef __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__
#define __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ServerType,                                                                                                                  // NOLINT(bugprone-reserved-identifier)
                        typename __ServiceType,                                                                                                                 // NOLINT(bugprone-reserved-identifier)
                        typename __ElementType,                                                                                                                 // NOLINT(bugprone-reserved-identifier)
                        typename __IteratorType,                                                                                                                // NOLINT(bugprone-reserved-identifier)
                        typename __ConstIteratorType,                                                                                                           // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            // NOLINT(bugprone-reserved-identifier)
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             // NOLINT(bugprone-reserved-identifier)
                > class __ListServerDispatcher :                                                                                                                // NOLINT(bugprone-reserved-identifier)
                        public __MutableCollectionServerDispatcher <
                                __ServerType,
                                __ServiceType,
                                __ElementType,
                                __IteratorType,
                                __ConstIteratorType,
                                __newAddressFunction,
                                __removeFunction,
                                __removeConstFunction
                        > {

                protected:
                    auto __newFront () noexcept -> __ElementType *; // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __newBack () noexcept -> __ElementType *; // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __newFrontArray ( // NOLINT(bugprone-reserved-identifier)
                            Size             count,
                            __ElementType ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __newBackArray ( // NOLINT(bugprone-reserved-identifier)
                            Size             count,
                            __ElementType ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __newBefore ( // NOLINT(bugprone-reserved-identifier)
                            __IteratorType const * pIterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __newBeforeConst ( // NOLINT(bugprone-reserved-identifier)
                            __ConstIteratorType const * pIterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __newAfter ( // NOLINT(bugprone-reserved-identifier)
                            __IteratorType const * pIterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __newAfterConst ( // NOLINT(bugprone-reserved-identifier)
                            __ConstIteratorType const * pIterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __newBeforeArray ( // NOLINT(bugprone-reserved-identifier)
                            __IteratorType  const * pIterator,
                            Size                    count,
                            __ElementType        ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __newBeforeArrayConst ( // NOLINT(bugprone-reserved-identifier)
                            __ConstIteratorType const * pIterator,
                            Size                        count,
                            __ElementType            ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __newAfterArray ( // NOLINT(bugprone-reserved-identifier)
                            __IteratorType const * pIterator,
                            Size                   count,
                            __ElementType       ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __newAfterArrayConst ( // NOLINT(bugprone-reserved-identifier)
                            __ConstIteratorType const * pIterator,
                            Size                        count,
                            __ElementType            ** ppElements
                    ) noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_SHARED_LIST_SERVER_DISPATCHER_HPP__

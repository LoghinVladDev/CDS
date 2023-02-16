/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __AbstractIteratorRemovePrimitiveClient <
                    __ReceiverType,
                    __ElementType
            > :: remove (
                    AbstractIterator const & iterator
            ) noexcept -> bool {

                using __ReceiverRemoveIteratorHandlerType   = cds :: functional :: PredicateFunction < __ReceiverType *, cds :: meta :: Iterator const * >;
                auto pReceiver                              = reinterpret_cast < __ReceiverType * > ( this );

                /* Since iterator is abstract, it is compatible with Collection Ownership -> has 'of' function. Check for ownership. If not owned, removal unsuccessful */
                if ( ! iterator.of ( pReceiver ) ) {
                    return false;
                }

                /* Acquire the member function to call from client and call it with extracted delegate as parameter, return value received from the call */
                return reinterpret_cast < __ReceiverRemoveIteratorHandlerType > ( pReceiver->__iicch_obtainGenericHandler ( __IterableInternalRequestType :: __iirt_remove ) ) (
                        pReceiver,
                        iterator._pDelegate->iterator()
                );
            }


            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __AbstractIteratorRemovePrimitiveClient <
                    __ReceiverType,
                    __ElementType
            > :: removeAll (
                    AbstractIterator const * pIterators,
                    Size                     iteratorCount
            ) noexcept -> Size {

                using __ReceiverRemoveIteratorArrayHandlerType  = cds :: functional :: MapperFunction < Size, __ReceiverType *, cds :: meta :: Iterator const * const *, Size >;
                using __ReceiverRemoveIteratorHandlerType       = cds :: functional :: PredicateFunction < __ReceiverType *, cds :: meta :: Iterator const * >;

                auto pReceiver                  = reinterpret_cast < __ReceiverType * > ( this );
                auto genericIteratorArray       = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < cds :: meta :: Iterator const * > ( iteratorCount );
                Size genericIteratorArraySize   = 0ULL;
                Size removedIteratorCount       = 0ULL;

                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                    if ( ! pIterators [ index ].of ( pReceiver ) ) {
                        continue;
                    }

                    genericIteratorArray [ genericIteratorArraySize ++ ] = pIterators [ index ]._pDelegate->iterator();
                }

                if ( genericIteratorArraySize >= 2ULL ) {

                    removedIteratorCount = reinterpret_cast < __ReceiverRemoveIteratorArrayHandlerType > ( pReceiver->__iicch_obtainGenericHandler ( __IterableInternalRequestType :: __iirt_removeArray ) ) (
                            pReceiver,
                            & genericIteratorArray [0ULL],
                            genericIteratorArraySize
                    );
                } else if ( genericIteratorArraySize == 1ULL ) {

                    removedIteratorCount = reinterpret_cast < __ReceiverRemoveIteratorHandlerType > ( pReceiver->__iicch_obtainGenericHandler ( __IterableInternalRequestType :: __iirt_remove ) ) (
                            pReceiver,
                            genericIteratorArray [0ULL]
                    ) ? 1ULL : 0ULL;
                }

                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( genericIteratorArray );
                return removedIteratorCount;
            }


            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalIteratorRemovePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __IteratorType
            > :: remove (
                    Iterator const & iterator
            ) noexcept -> bool {

                /* local client, directly call the dispatcher-generated function for const removal */
                return __ReceiverType :: __remove (
                        reinterpret_cast < __ReceiverType * > ( this ),
                        & iterator
                );
            }


            template <
                    typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __LocalIteratorRemovePrimitiveClient <
                    __ReceiverType,
                    __ElementType,
                    __IteratorType
            > :: removeAll (
                    Iterator const * pIterators,
                    Size             iteratorCount
            ) noexcept -> Size {

                auto pReceiver = reinterpret_cast < __ReceiverType * > ( this );
                if ( iteratorCount >= 2ULL ) {

                    auto pIteratorBuffer    = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < Iterator const * > ( iteratorCount );
                    for ( Size index = 0U; index < iteratorCount; ++ index ) {
                        pIteratorBuffer[ index ] = & pIterators [ index ];
                    }

                    Size removedCount = __ReceiverType :: __removeArray (
                            pReceiver,
                            & pIteratorBuffer [0ULL],
                            iteratorCount
                    );

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pIteratorBuffer );
                    return removedCount;

                } else if ( iteratorCount == 1ULL ) {

                    return __ReceiverType :: __remove (
                            pReceiver,
                            & pIterators [0ULL]
                    ) ? 1ULL : 0ULL;
                }

                return 0ULL;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ */

/*
 * Created by loghin on 09/08/22.
 */

#ifndef __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        bool     __bidirectional                /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindUniqueImmutablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __KeyType,
                        __bidirectional
                > :: find (
                        __KeyType const & key
                ) const noexcept -> ConstIterator {

                    /* explicit type of the handler received from the client */
                    using __ReceiverFindConstHandlerType    = __AbstractDelegateIterator < __ElementType const > * ( __ReceiverType :: * ) ( __KeyType const & ) const;
                    /* object as the receiver type */
                    auto const pReceiver                    = reinterpret_cast < __ReceiverType const * > ( this );

                    /* create a wrapper const iterator with the received delegate iterator from __cirt_findConst */
                    return ConstIterator (
                            pReceiver, (
                                    pReceiver ->* reinterpret_cast < __ReceiverFindConstHandlerType > (
                                            pReceiver->__cicch_obtainGenericConstHandler (
                                                    __CollectionInternalRequestType :: __cirt_findConst
                                            )
                                    )
                            ) ( key )
                    );
                }


                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __LocalFindUniqueImmutablePrimitiveClient <
                        __ReceiverType,
                        __KeyType,
                        __IteratorType
                > :: find (
                        __KeyType const & key
                ) const noexcept -> ConstIterator {

                    /* directly call the __findConstLocal function */
                    return reinterpret_cast < __ReceiverType const * > ( this )->__findConstLocal ( key );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__*/

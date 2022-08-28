/*
 * Created by loghin on 09/08/22.
 */

#ifndef __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__
#define __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        bool     __bidirectional                /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __FindUniqueMutablePrimitiveClient <
                        __ReceiverType,
                        __ElementType,
                        __KeyType,
                        __bidirectional
                > :: find (
                        __KeyType const & key
                ) noexcept -> Iterator {

                    using __ReceiverFindHandlerType = __AbstractDelegateIterator < __ElementType > * ( __ReceiverType :: * ) ();
                    auto const pReceiver            = reinterpret_cast < __ReceiverType * > ( this );

                    return Iterator (
                            pReceiver, (
                                    pReceiver ->* reinterpret_cast < __ReceiverFindHandlerType > (
                                            pReceiver->__cicch_obtainGenericHandler (
                                                    __CollectionInternalRequestType :: __cirt_find
                                            )
                                    )
                            ) ( key )
                    );
                }


                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __LocalFindUniqueMutablePrimitiveClient <
                        __ReceiverType,
                        __KeyType,
                        __IteratorType
                > :: find (
                        __KeyType const & key
                ) noexcept -> Iterator {

                    return reinterpret_cast < __ReceiverType * > ( this )->__find ( key );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__ */

/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ServerType,                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )           -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )     -> bool                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __CollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __AbstractConstIteratorType,
                        __ConstIteratorType,
                        __cbeginFunction,
                        __cendFunction,
                        __newAddressFunction,
                        __removeConstFunction
                > :: __cbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                    /* call the template received member function and wrap iterator in a new delegate */
                    return Memory :: instance().create < __DelegateIterator < __ElementType const, __ConstIteratorType > > (
                            ( reinterpret_cast < __ServerType const * > ( this ) ->* __cbeginFunction ) ()
                    );
                }


                template <
                        typename __ServerType,                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )           -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )     -> bool                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __CollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __AbstractConstIteratorType,
                        __ConstIteratorType,
                        __cbeginFunction,
                        __cendFunction,
                        __newAddressFunction,
                        __removeConstFunction
                > :: __cend () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                    /* call the template received member function and wrap iterator in a new delegate */
                    return Memory :: instance ().create < __DelegateIterator < __ElementType const, __ConstIteratorType > > (
                            ( reinterpret_cast < __ServerType const * > ( this ) ->* __cendFunction ) ()
                    );
                }


                template <
                        typename __ServerType,                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )           -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )     -> bool                 /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __CollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __AbstractConstIteratorType,
                        __ConstIteratorType,
                        __cbeginFunction,
                        __cendFunction,
                        __newAddressFunction,
                        __removeConstFunction
                > :: __cbeginLocal () const noexcept -> __ConstIteratorType {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType const * > ( this ) ->* __cbeginFunction ) ();
                }


                template <
                        typename __ServerType,                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )           -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )     -> bool                 /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __CollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __AbstractConstIteratorType,
                        __ConstIteratorType,
                        __cbeginFunction,
                        __cendFunction,
                        __newAddressFunction,
                        __removeConstFunction
                > :: __cendLocal () const noexcept -> __ConstIteratorType {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType const * > ( this ) ->* __cendFunction ) ();
                }


                template <
                        typename __ServerType,                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )           -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )     -> bool                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __CollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __AbstractConstIteratorType,
                        __ConstIteratorType,
                        __cbeginFunction,
                        __cendFunction,
                        __newAddressFunction,
                        __removeConstFunction
                > :: __newAddress (
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> __ElementType * {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAddressFunction ) (
                            pReferenceElement,
                            pNewElementCreated
                    );
                }


                template <
                        typename __ServerType,                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __AbstractConstIteratorType,                                                                                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cbeginFunction )        ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __cendFunction )          ()                                  const   -> __ConstIteratorType, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )    ( __ElementType const *, bool * )           -> __ElementType *,     /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )   ( __AbstractConstIteratorType const & )     -> bool                 /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __CollectionServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __AbstractConstIteratorType,
                        __ConstIteratorType,
                        __cbeginFunction,
                        __cendFunction,
                        __newAddressFunction,
                        __removeConstFunction
                > :: __removeConst (
                        __AbstractConstIteratorType const * pIterator
                ) noexcept -> bool {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __removeConstFunction ) (
                            * pIterator
                    );
                }

            }
        }
    }
}

#endif /* __CDS_SHARED_COLLECTION_SERVER_DISPATCHER_IMPL_HPP__ */

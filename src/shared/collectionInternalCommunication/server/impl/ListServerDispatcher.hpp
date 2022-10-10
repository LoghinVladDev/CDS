/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_LIST_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_LIST_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __rbegin () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType, __ReverseIteratorType > > (
                        ( reinterpret_cast < __ServerType * > ( this ) ->* __rbeginFunction ) ()
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __rend () noexcept -> __AbstractDelegateIterator < __ElementType > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType, __ReverseIteratorType > > (
                        ( reinterpret_cast < __ServerType * > ( this ) ->* __rendFunction ) ()
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __crbegin () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType const, __ConstReverseIteratorType > > (
                        ( reinterpret_cast < __ServerType const * > ( this ) ->* __crbeginFunction ) ()
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __crend () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {

                /* call the template received member function and wrap iterator in a new delegate */
                return Memory :: instance().create < __DelegateIterator < __ElementType const, __ConstReverseIteratorType > > (
                        ( reinterpret_cast < __ServerType const * > ( this ) ->* __crendFunction ) ()
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __rbeginLocal () noexcept -> __ReverseIteratorType {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __rbeginFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __rendLocal () noexcept -> __ReverseIteratorType {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __rendFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __crbeginLocal () const noexcept -> __ConstReverseIteratorType {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType const * > ( this ) ->* __crbeginFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > constexpr auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __crendLocal () const noexcept -> __ConstReverseIteratorType {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType const * > ( this ) ->* __crendFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newFront () noexcept -> __ElementType * {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newFrontFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newBack () noexcept -> __ElementType * {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBackFunction ) ();
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newFrontArray (
                    Size                count,
                    __ElementType    ** ppElements
            ) noexcept -> void {

                /* call the template received member function */
                ( reinterpret_cast < __ServerType * > ( this ) ->* __newFrontArrayFunction ) (
                        count,
                        ppElements
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newBackArray (
                    Size                count,
                    __ElementType    ** ppElements
            ) noexcept -> void {

                /* call the template received member function */
                ( reinterpret_cast < __ServerType * > ( this ) ->* __newBackArrayFunction ) (
                        count,
                        ppElements
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newBefore (
                    __AbstractIteratorType const * pIterator
            ) noexcept -> __ElementType * {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBeforeFunction ) (
                        * pIterator
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newBeforeConst (
                    __AbstractConstIteratorType const * pIterator
            ) noexcept -> __ElementType * {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBeforeConstFunction ) (
                        * pIterator
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newAfter (
                    __AbstractIteratorType const * pIterator
            ) noexcept -> __ElementType * {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAfterFunction ) (
                        * pIterator
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newAfterConst (
                    __AbstractConstIteratorType const * pIterator
            ) noexcept -> __ElementType * {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAfterConstFunction ) (
                        * pIterator
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newBeforeArray (
                    __AbstractIteratorType  const * pIterator,
                    Size                            count,
                    __ElementType                ** ppElements
            ) noexcept -> bool {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBeforeArrayFunction ) (
                        * pIterator,
                        count,
                        ppElements
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newBeforeArrayConst (
                    __AbstractConstIteratorType const * pIterator,
                    Size                                count,
                    __ElementType                    ** ppElements
            ) noexcept -> bool {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBeforeArrayConstFunction ) (
                        * pIterator,
                        count,
                        ppElements
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newAfterArray (
                    __AbstractIteratorType  const * pIterator,
                    Size                            count,
                    __ElementType                ** ppElements
            ) noexcept -> bool {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAfterArrayFunction ) (
                        * pIterator,
                        count,
                        ppElements
                );
            }


            template <
                    typename __ServerType,                                                                                                                                              /* NOLINT(bugprone-reserved-identifier) */
                    typename __ServiceType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __ElementType,                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractIteratorType,                                                                                                                                    /* NOLINT(bugprone-reserved-identifier) */
                    typename __AbstractConstIteratorType,                                                                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    typename __IteratorType,                                                                                                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstIteratorType,                                                                                                                                       /* NOLINT(bugprone-reserved-identifier) */
                    typename __ReverseIteratorType,                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __ConstReverseIteratorType,                                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __beginFunction )                 ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __endFunction )                   ()                                                                      -> __IteratorType,              /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cbeginFunction )                ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __cendFunction )                  ()                                                              const   -> __ConstIteratorType,         /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rbeginFunction )                ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __rendFunction )                  ()                                                                      -> __ReverseIteratorType,       /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crbeginFunction )               ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __crendFunction )                 ()                                                              const   -> __ConstReverseIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                                       -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontFunction )              ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackFunction )               ()                                                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                                              -> void,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeFunction )             ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeConstFunction )        ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterFunction )              ( __AbstractIteratorType const & )                                      -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterConstFunction )         ( __AbstractConstIteratorType const & )                                 -> __ElementType *,             /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayFunction )         ( __AbstractIteratorType const &, Size, __ElementType ** )              -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __AbstractConstIteratorType const &, Size, __ElementType ** )         -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeFunction )                ( __AbstractIteratorType const & )                                      -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstFunction )           ( __AbstractConstIteratorType const & )                                 -> bool,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeArrayFunction )           ( __AbstractIteratorType const * const *, Size )                        -> Size,                        /* NOLINT(bugprone-reserved-identifier) */
                    auto ( __ServiceType :: * __removeConstArrayFunction )      ( __AbstractConstIteratorType const * const *, Size )                   -> Size                         /* NOLINT(bugprone-reserved-identifier) */
            > __CDS_OptimalInline auto __ListServerDispatcher <
                    __ServerType,
                    __ServiceType,
                    __ElementType,
                    __AbstractIteratorType,
                    __AbstractConstIteratorType,
                    __IteratorType,
                    __ConstIteratorType,
                    __ReverseIteratorType,
                    __ConstReverseIteratorType,
                    __beginFunction,
                    __endFunction,
                    __cbeginFunction,
                    __cendFunction,
                    __rbeginFunction,
                    __rendFunction,
                    __crbeginFunction,
                    __crendFunction,
                    __newAddressFunction,
                    __newFrontFunction,
                    __newBackFunction,
                    __newFrontArrayFunction,
                    __newBackArrayFunction,
                    __newBeforeFunction,
                    __newBeforeConstFunction,
                    __newAfterFunction,
                    __newAfterConstFunction,
                    __newBeforeArrayFunction,
                    __newBeforeArrayConstFunction,
                    __newAfterArrayFunction,
                    __newAfterArrayConstFunction,
                    __removeFunction,
                    __removeConstFunction,
                    __removeArrayFunction,
                    __removeConstArrayFunction
            > :: __newAfterArrayConst (
                    __AbstractConstIteratorType const * pIterator,
                    Size                                count,
                    __ElementType                    ** ppElements
            ) noexcept -> bool {

                /* call the template received member function */
                return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAfterArrayConstFunction ) (
                        * pIterator,
                        count,
                        ppElements
                );
            }

        }
    }
}

#endif /* __CDS_SHARED_LIST_SERVER_DISPATCHER_IMPL_HPP__ */

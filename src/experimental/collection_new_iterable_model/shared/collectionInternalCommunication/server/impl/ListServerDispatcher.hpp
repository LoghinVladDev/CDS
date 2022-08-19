/*
 * Created by loghin on 09/07/22.
 */

#ifndef __CDS_SHARED_LIST_SERVER_DISPATCHER_IMPL_HPP__
#define __CDS_SHARED_LIST_SERVER_DISPATCHER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "MutableCollectionServerDispatcher.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newFront () noexcept -> __ElementType * {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newFrontFunction ) ();
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newBack () noexcept -> __ElementType * {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBackFunction ) ();
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
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
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
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
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newBefore (
                        __IteratorType const * pIterator
                ) noexcept -> __ElementType * {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBeforeFunction ) (
                            * pIterator
                    );
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newBeforeConst (
                        __ConstIteratorType const * pIterator
                ) noexcept -> __ElementType * {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBeforeConstFunction ) (
                            * pIterator
                    );
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newAfter (
                        __IteratorType const * pIterator
                ) noexcept -> __ElementType * {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAfterFunction ) (
                            * pIterator
                    );
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newAfterConst (
                        __ConstIteratorType const * pIterator
                ) noexcept -> __ElementType * {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAfterConstFunction ) (
                            * pIterator
                    );
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newBeforeArray (
                        __IteratorType  const * pIterator,
                        Size                    count,
                        __ElementType        ** ppElements
                ) noexcept -> bool {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBeforeArrayFunction ) (
                            * pIterator,
                            count,
                            ppElements
                    );
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newBeforeArrayConst (
                        __ConstIteratorType const * pIterator,
                        Size                        count,
                        __ElementType            ** ppElements
                ) noexcept -> bool {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newBeforeArrayConstFunction ) (
                            * pIterator,
                            count,
                            ppElements
                    );
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newAfterArray (
                        __IteratorType  const * pIterator,
                        Size                    count,
                        __ElementType        ** ppElements
                ) noexcept -> bool {

                    /* call the template received member function */
                    return ( reinterpret_cast < __ServerType * > ( this ) ->* __newAfterArrayFunction ) (
                            * pIterator,
                            count,
                            ppElements
                    );
                }


                template <
                        typename __ServerType,                                                                                                                  /* NOLINT(bugprone-reserved-identifier) */
                        typename __ServiceType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType,                                                                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ConstIteratorType,                                                                                                           /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAddressFunction )            ( __ElementType const *, bool * )                       -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontFunction )              ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackFunction )               ()                                                      -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newFrontArrayFunction )         ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBackArrayFunction )          ( Size, __ElementType ** )                              -> void,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeFunction )             ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeConstFunction )        ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterFunction )              ( __IteratorType const & )                              -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterConstFunction )         ( __ConstIteratorType const & )                         -> __ElementType *, /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayFunction )        ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newBeforeArrayConstFunction )   ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayFunction )         ( __IteratorType const &, Size, __ElementType ** )      -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __newAfterArrayConstFunction )    ( __ConstIteratorType const &, Size, __ElementType ** ) -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeFunction )                ( __IteratorType const & )                              -> bool,            /* NOLINT(bugprone-reserved-identifier) */
                        auto ( __ServiceType :: * __removeConstFunction )           ( __ConstIteratorType const & )                         -> bool             /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __ListServerDispatcher <
                        __ServerType,
                        __ServiceType,
                        __ElementType,
                        __IteratorType,
                        __ConstIteratorType,
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
                        __removeConstFunction
                > :: __newAfterArrayConst (
                        __ConstIteratorType const * pIterator,
                        Size                        count,
                        __ElementType            ** ppElements
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
}

#endif /* __CDS_SHARED_LIST_SERVER_DISPATCHER_IMPL_HPP__ */

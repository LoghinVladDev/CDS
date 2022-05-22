//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_COLLECTION_HPP__
#define __CDS_EX_COLLECTION_HPP__

#include <CDS/std-types>
#include <CDS/experimental/Object>
#include <CDS/experimental/meta/TypeTraits>
#include <CDS/Concepts>
#include <CDS/Function>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/smartPointers/ForeignPointer>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    namespace experimental {

        template < typename T >
        class Collection : public Object {
        public:
            using ElementType = T;

        protected:
            using InitializerList = std :: initializer_list < T >;

        protected:
            class AbstractDelegateIterator;
        protected:
            class DelegateConstIterator;
        protected:
            class AbstractIterator;
        protected:
            enum class DelegateIteratorRequestType;

        public:
            class ConstIterator;
        public:
            class ConstReverseIterator;

        protected:
            constexpr static auto acquireDelegate ( AbstractIterator const & ) noexcept -> AbstractDelegateIterator const *;
        protected:
            constexpr static auto acquireDelegate ( ConstIterator const & ) noexcept -> DelegateConstIterator const *;
        protected:
            constexpr static auto acquireDelegate ( ConstReverseIterator const & ) noexcept -> DelegateConstIterator const *;
        protected:
            virtual auto delegateConstIterator ( DelegateIteratorRequestType ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > = 0;

        public:
            __CDS_OptimalInline auto begin () const noexcept -> ConstIterator;
        public:
            __CDS_OptimalInline auto end () const noexcept -> ConstIterator;
        public:
            __CDS_OptimalInline auto cbegin () const noexcept -> ConstIterator;
        public:
            __CDS_OptimalInline auto cend () const noexcept -> ConstIterator;
        public:
            __CDS_OptimalInline auto rbegin () const noexcept -> ConstReverseIterator;
        public:
            __CDS_OptimalInline auto rend () const noexcept -> ConstReverseIterator;
        public:
            __CDS_OptimalInline auto crbegin () const noexcept -> ConstReverseIterator;
        public:
            __CDS_OptimalInline auto crend () const noexcept -> ConstReverseIterator;

        public:
            virtual auto remove ( ConstIterator const & ) noexcept -> bool = 0;
        public:
            virtual auto remove ( ConstReverseIterator const & ) noexcept -> bool = 0;

        protected:
            virtual auto remove ( ConstIterator const *, Size ) noexcept -> Size = 0;
        protected:
            virtual auto remove ( ConstReverseIterator const *, Size ) noexcept -> Size = 0;

        public:
            template < typename Predicate >
            auto remove ( Predicate const &, Size ) noexcept -> Size;
        public:
            template < typename Predicate >
            auto removeFirst ( Predicate const & ) noexcept -> bool;
        public:
            template < typename Predicate >
            auto removeLast ( Predicate const & ) noexcept -> bool;
        public:
            template < typename Predicate >
            auto removeAll ( Predicate const & ) noexcept -> Size;

        public:
            auto remove ( ElementType const &, Size ) noexcept -> Size;
        public:
            auto removeFirst ( ElementType const & ) noexcept -> bool;
        public:
            auto removeLast ( ElementType const & ) noexcept -> bool;
        public:
            auto removeAll ( ElementType const & ) noexcept -> Size;

        public:
            auto removeOf ( Collection < T > const &, Size ) noexcept -> Size;
        public:
            auto removeFirstOf ( Collection < T > const & ) noexcept -> bool;
        public:
            auto removeLastOf ( Collection < T > const & ) noexcept -> bool;
        public:
            auto removeAllOf ( Collection < T > const & ) noexcept -> Size;

        public:
            auto removeNotOf ( Collection < T > const &, Size ) noexcept -> Size;
        public:
            auto removeFirstNotOf ( Collection < T > const & ) noexcept -> bool;
        public:
            auto removeLastNotOf ( Collection < T > const & ) noexcept -> bool;
        public:
            auto removeAllNotOf ( Collection < T > const & ) noexcept -> Size;

        public:
            auto removeOf ( InitializerList const &, Size ) noexcept -> Size;
        public:
            auto removeFirstOf ( InitializerList const & ) noexcept -> bool;
        public:
            auto removeLastOf ( InitializerList const & ) noexcept -> bool;
        public:
            auto removeAllOf ( InitializerList const & ) noexcept -> Size;

        public:
            auto removeNotOf ( InitializerList const &, Size ) noexcept -> Size;
        public:
            auto removeFirstNotOf ( InitializerList const & ) noexcept -> bool;
        public:
            auto removeLastNotOf ( InitializerList const & ) noexcept -> bool;
        public:
            auto removeAllNotOf ( InitializerList const & ) noexcept -> Size;

        public:
            template < typename Action >
            auto forEach ( Action const & ) noexcept ( noexcept ( ( * ( ( Action * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> void __CDS_Requires (
                    ActionOver < Action, ElementType >
            );
        public:
            template < typename Action >
            auto forEach ( Action const & ) const noexcept ( noexcept ( ( * ( ( Action * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> void __CDS_Requires (
                    ActionOver < Action, ElementType >
            );

        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto some (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto some (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );

        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atLeast (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atLeast (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );

        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atMost (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atMost (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );

        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto moreThan (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto moreThan (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );

        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto lessThan (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto lessThan (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );

        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto count (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> Size __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto count (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> Size __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );

        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto any (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto any (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );

        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto all (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto all (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> bool __CDS_Requires (
                    PredicateOver < Predicate, ElementType >
            );

        public:
            __CDS_cpplang_ConstexprPureAbstract operator bool () const noexcept;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override = 0;
        public:
            __CDS_NoDiscard auto hash () const noexcept -> Index override;
        public:
            __CDS_NoDiscard auto equals ( Object const & ) const noexcept -> bool override;

        protected:
            constexpr Collection () noexcept = default;
        public:
            ~Collection() noexcept override = default;

        public:
            virtual auto clear () noexcept -> void = 0;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto size () const noexcept -> Size = 0;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto empty () const noexcept -> bool;
        public:
            virtual auto contains ( ElementType const & ) const noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            __CDS_OptimalInline auto add ( ElementType const & ) noexcept -> void;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            __CDS_OptimalInline auto add ( ElementType && ) noexcept -> void;

        protected:
            virtual auto pNewInsert () noexcept -> ElementType * & = 0;
        protected:
            __CDS_OptimalInline virtual auto pNewInsertPost () noexcept -> void;
        };

    }
}

#include "collection/DelegateIteratorRequestType.hpp"
#include "collection/AbstractDelegateIterator.hpp"
#include "collection/DelegateConstIterator.hpp"
#include "collection/AbstractIterator.hpp"
#include "collection/ConstIterator.hpp"
#include "collection/ConstReverseIterator.hpp"

#include "collection/impl/AbstractDelegateIterator.hpp"
#include "collection/impl/DelegateConstIterator.hpp"
#include "collection/impl/AbstractIterator.hpp"
#include "collection/impl/ConstIterator.hpp"
#include "collection/impl/ConstReverseIterator.hpp"

#include "collection/impl/Collection.hpp"

#include "collection/impl/CollectionDerivedRequired.hpp"

#endif // __CDS_EX_COLLECTION_HPP__

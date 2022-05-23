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
            auto forEach ( Action const & ) const noexcept ( noexcept ( meta :: valueOf < Action > () ( meta :: referenceOf < ElementType const > () ) ) ) -> void;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto some (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atLeast (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atMost (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto moreThan (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto lessThan (
                    Size                count,
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto count (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> Size;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto any (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto all (
                    Predicate   const & predicate   = [] ( ElementType const & ) noexcept -> bool { return true; }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            template < template < typename ... > typename CollectionType >
            auto find ( ElementType const &, CollectionType < ConstIterator > &, Size ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto find ( ElementType const &, Size ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirst ( ElementType const & ) const noexcept -> ConstIterator;
        public:
            auto findLast ( ElementType const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAll ( ElementType const &, CollectionType < ConstIterator > & ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAll ( ElementType const & ) const noexcept -> CollectionType < ConstIterator >;
        public:
            template < template < typename ... > typename CollectionType >
            auto findOf ( Collection < T > const &, CollectionType < ConstIterator > &, Size ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findOf ( Collection < T > const &, Size ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirstOf ( Collection < T > const & ) const noexcept -> ConstIterator;
        public:
            auto findLastOf ( Collection < T > const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllOf ( Collection < T > const &, CollectionType < ConstIterator > & ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllOf ( Collection < T > const & ) const noexcept -> CollectionType < ConstIterator >;
        public:
            template < template < typename ... > typename CollectionType >
            auto findNotOf ( Collection < T > const &, CollectionType < ConstIterator > &, Size ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findNotOf ( Collection < T > const &, Size ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirstNotOf ( Collection < T > const & ) const noexcept -> ConstIterator;
        public:
            auto findLastNotOf ( Collection < T > const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllNotOf ( Collection < T > const &, CollectionType < ConstIterator > & ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllNotOf ( Collection < T > const & ) const noexcept -> CollectionType < ConstIterator >;
        public:
            template < template < typename ... > typename CollectionType >
            auto findOf ( InitializerList const &, CollectionType < ConstIterator > &, Size ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findOf ( InitializerList const &, Size ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirstOf ( InitializerList const & ) const noexcept -> ConstIterator;
        public:
            auto findLastOf ( InitializerList const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllOf ( InitializerList const &, CollectionType < ConstIterator > & ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllOf ( InitializerList const & ) const noexcept -> CollectionType < ConstIterator >;
        public:
            template < template < typename ... > typename CollectionType >
            auto findNotOf ( InitializerList const &, Size, CollectionType < ConstIterator > & ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findNotOf ( InitializerList const &, Size ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirstNotOf ( InitializerList const & ) const noexcept -> ConstIterator;
        public:
            auto findLastNotOf ( InitializerList const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllNotOf ( InitializerList const &, CollectionType < ConstIterator > & ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllNotOf ( InitializerList const & ) const noexcept -> CollectionType < ConstIterator >;
        public:
            template < template < typename ... > typename CollectionType, typename Predicate >
            auto find ( Predicate const &, CollectionType < ConstIterator > &, Size ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType, typename Predicate >
            auto find ( Predicate const &, Size ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator >;
        public:
            template < typename Predicate >
            auto findFirst ( Predicate const & ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator;
        public:
            template < typename Predicate >
            auto findLast ( Predicate const & ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType, typename Predicate >
            auto findAll ( Predicate const &, CollectionType < ConstIterator > & ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType, typename Predicate >
            auto findAll ( Predicate const & ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator >;

        public:
            __CDS_cpplang_ConstexprPureAbstract __CDS_explicit(false) operator bool () const noexcept;

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
            auto containsAnyOf ( Collection < ElementType > const & ) const noexcept -> bool;
        public:
            auto containsAnyNotOf ( Collection < ElementType > const & ) const noexcept -> bool;
        public:
            auto containsAllOf ( Collection < ElementType > const & ) const noexcept -> bool;
        public:
            auto containsAllNotOf ( Collection < ElementType > const & ) const noexcept -> bool;

        public:
            auto containsAnyOf ( InitializerList const & ) const noexcept -> bool;
        public:
            auto containsAnyNotOf ( InitializerList const & ) const noexcept -> bool;
        public:
            auto containsAllOf ( InitializerList const & ) const noexcept -> bool;
        public:
            auto containsAllNotOf ( InitializerList const & ) const noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            __CDS_OptimalInline auto add ( ElementType const & ) noexcept -> void;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            __CDS_OptimalInline auto add ( ElementType && ) noexcept -> void;

        public:
            template < typename ... ArgumentTypes >
            auto addAll ( ArgumentTypes && ... ) noexcept -> void;

        public:
            template < typename R, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () || meta :: isConvertible < R, V > () > = 0 >
            auto addAllOf ( Collection < R > const & ) noexcept -> void;

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

#endif // __CDS_EX_COLLECTION_HPP__

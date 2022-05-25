//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_LIST_HPP__
#define __CDS_EX_LIST_HPP__

#include <CDS/experimental/Collection>
#include <CDS/experimental/View>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class List : public Collection < T > {
        public:
            using typename Collection < T > :: ElementType;

        protected:
            using typename Collection < T > :: InitializerList;

        public:
            class Iterator;
        public:
            using typename Collection < T > :: ConstIterator;
        public:
            class ReverseIterator;
        public:
            using typename Collection < T > :: ConstReverseIterator;

        protected:
            using typename Collection < T > :: AbstractIterator;
        protected:
            using typename Collection < T > :: AbstractDelegateIterator;
        protected:
            class DelegateIterator;
        protected:
            using typename Collection < T > :: DelegateConstIterator;

        protected:
            Size _size { 0U };

        protected:
            using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;
        protected:
            constexpr static auto acquireDelegate (
                    Iterator const &
            ) noexcept -> DelegateIterator const *;
        protected:
            constexpr static auto acquireDelegate (
                    ReverseIterator const &
            ) noexcept -> DelegateIterator const *;
        protected:
            virtual auto delegateIterator (
                    DelegateIteratorRequestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > = 0;

        public:
            auto begin () noexcept -> Iterator;
        public:
            auto end () noexcept -> Iterator;
        public:
            auto rbegin () noexcept -> ReverseIterator;
        public:
            auto rend () noexcept -> ReverseIterator;

        public:
            using Collection < T > :: begin;
        public:
            using Collection < T > :: end;
        public:
            using Collection < T > :: cbegin;
        public:
            using Collection < T > :: cend;
        public:
            using Collection < T > :: rbegin;
        public:
            using Collection < T > :: rend;
        public:
            using Collection < T > :: crbegin;
        public:
            using Collection < T > :: crend;

        protected:
            constexpr List () noexcept = default;
        protected:
            constexpr List (
                    List const &
            ) noexcept;
        protected:
            constexpr List (
                    List &&
            ) noexcept;
        protected:
            constexpr explicit List (
                    Size
            ) noexcept;

        public:
            ~List () noexcept override = default;

        public:
            virtual auto get (
                    Index
            ) noexcept (false) -> ElementType & = 0;
        public:
            virtual auto get (
                    Index
            ) const noexcept (false) -> ElementType const & = 0;

        public:
            __CDS_NoDiscard auto equals (
                    Object const &
            ) const noexcept -> bool override;

        protected:
            __CDS_OptimalInline auto pNewInsert () noexcept -> ElementType * & override;

        public:
            template < typename ListType, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType, Collection < T > > () > = 0 >
            auto sub (
                    Index,
                    Index,
                    ListType &
            ) const noexcept (false) -> ListType &;
        public:
            template < typename ListType, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType, Collection < T > > () > = 0 >
            auto sub (
                    Index,
                    Index
            ) const noexcept (false) -> ListType;
        public:
            template < template < typename ... > typename ListType, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType < T >, Collection < T > > () > = 0 >
            auto sub (
                    Index,
                    Index,
                    ListType < ElementType > &
            ) const noexcept (false) -> ListType < ElementType > &;
        public:
            template < template < typename ... > typename ListType, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType < T >, Collection < T > > () > = 0 >
             auto sub (
                     Index,
                     Index
             ) const noexcept (false) -> ListType < ElementType >;

        public:
            template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > = 0 >
            auto indices (
                    ElementType const &,
                    ListType &
            ) const noexcept -> ListType &;
        public:
            template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > = 0 >
            auto indices (
                    ElementType const &
            ) const noexcept -> ListType;
        public:
            template < template < typename ... > typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > = 0 >
            auto indices (
                    ElementType const &,
                    ListType < Index > &
            ) const noexcept -> ListType < Index > &;
        public:
            template < template < typename ... > typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > = 0 >
            auto indices (
                    ElementType const &
            ) const noexcept -> ListType < Index >;

        public:
            template < typename Predicate, typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > = 0 >
            auto indices (
                    Predicate   const &,
                    ListType &
            ) const noexcept -> ListType &;
        public:
            template < typename Predicate, typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > = 0 >
            auto indices (
                    Predicate const &
            ) const noexcept -> ListType;
        public:
            template < typename Predicate, template < typename ... > typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > = 0 >
            auto indices (
                    Predicate    const &,
                    ListType < Index > &
            ) const noexcept -> ListType < Index > &;
        public:
            template < typename Predicate, template < typename ... > typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > = 0 >
            auto indices (
                    Predicate const &
            ) const noexcept -> ListType < Index >;

        public:
            auto operator [] (
                    Index
            ) noexcept (false) -> ElementType &;
        public:
            auto operator [] (
                    Index
            ) const noexcept (false) -> ElementType const &;

        public:
            virtual auto popFront () noexcept -> void = 0;
        public:
            virtual auto popBack () noexcept -> void = 0;

        protected:
            virtual auto pNewFront () noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBack () noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBefore (
                    Iterator const &
            ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewAfter (
                    Iterator const &
            ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBefore (
                    ConstIterator const &
            ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewAfter (
                    ConstIterator const &
            ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBefore (
                    ReverseIterator const &
            ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewAfter (
                    ReverseIterator const &
            ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBefore (
                    ConstReverseIterator const &
            ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewAfter (
                    ConstReverseIterator const &
            ) noexcept -> ElementType * & = 0;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto pushFront (
                    ElementType const &
            ) noexcept -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto pushFront (
                    ElementType &&
            ) noexcept -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto pushBack (
                    ElementType const &
            ) noexcept -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto pushBack (
                    ElementType &&
            ) noexcept -> ElementType &;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertBefore (
                    Iterator    const &,
                    ElementType const &
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertBefore (
                    Iterator    const &,
                    ElementType      &&
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertAfter (
                    Iterator    const &,
                    ElementType const &
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertAfter (
                    Iterator   const &,
                    ElementType     &&
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertBefore (
                    ConstIterator   const &,
                    ElementType     const &
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertBefore (
                    ConstIterator  const &,
                    ElementType         &&
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertAfter (
                    ConstIterator   const &,
                    ElementType     const &
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertAfter (
                    ConstIterator  const &,
                    ElementType         &&
            ) noexcept (false) -> ElementType &;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertBefore (
                    ReverseIterator const &,
                    ElementType     const &
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertBefore (
                    ReverseIterator const &,
                    ElementType          &&
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertAfter (
                    ReverseIterator const &,
                    ElementType     const &
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertAfter (
                    ReverseIterator const &,
                    ElementType          &&
            ) noexcept (false) -> ElementType &;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertBefore (
                    ConstReverseIterator    const &,
                    ElementType             const &
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertBefore (
                    ConstReverseIterator const &,
                    ElementType               &&
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertAfter (
                    ConstReverseIterator    const &,
                    ElementType             const &
            ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertAfter (
                    ConstReverseIterator const &,
                    ElementType               &&
            ) noexcept (false) -> ElementType &;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto append (
                    ElementType const &
            ) noexcept -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto append (
                    ElementType &&
            ) noexcept -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto prepend (
                    ElementType const &
            ) noexcept -> ElementType &;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto prepend (
                    ElementType &&
            ) noexcept -> ElementType &;

        public:
            virtual auto removeAt (
                    Index
            ) noexcept -> bool = 0;
        public:
            virtual auto removeAt (
                    Collection < Index > const &
            ) noexcept -> Size = 0;

        public:
            virtual auto remove (
                    Iterator const &
            ) noexcept -> bool = 0;
        public:
            auto remove (
                    ConstIterator const &
            ) noexcept -> bool override = 0;
        public:
            virtual auto remove (
                    ReverseIterator const &
            ) noexcept -> bool = 0;
        public:
            auto remove (
                    ConstReverseIterator const &
            ) noexcept -> bool override = 0;


        protected:
            virtual auto remove (
                    Iterator const *,
                    Size
            ) noexcept -> Size = 0;
        protected:
            auto remove (
                    ConstIterator const *,
                    Size
            ) noexcept -> Size override = 0;
        protected:
            virtual auto remove (
                    ReverseIterator const *,
                    Size
            ) noexcept -> Size = 0;
        protected:
            auto remove (
                    ConstReverseIterator const *,
                    Size
            ) noexcept -> Size override = 0;

        protected:
            template < typename ComparatorFunction >
            auto static quickSort (
                    Iterator            const &,
                    Iterator            const &,
                    ComparatorFunction  const &
            ) noexcept -> void;
        protected:
            template < typename ComparatorFunction >
            auto static quickSortPartition (
                    Iterator            const &,
                    Iterator            const &,
                    ComparatorFunction  const &
            ) noexcept -> Iterator;
        public:
            template < typename ComparatorFunction = Function < bool ( ElementType const &, ElementType const & ) > >
            auto sort (
                    ComparatorFunction const & = [] ( ElementType const & a, ElementType const & b ) {
                        return a < b;
                    }
            ) noexcept -> void;

        public:
            __CDS_NoDiscard constexpr auto size () const noexcept -> Size override;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replace (
                    Size,
                    ElementType const &,
                    ElementType const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAll (
                    ElementType const &,
                    ElementType const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirst (
                    ElementType const &,
                    ElementType const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirst (
                    ElementType const &,
                    ElementType      &&
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLast (
                    ElementType const &,
                    ElementType const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLast (
                    ElementType const &,
                    ElementType      &&
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceOf (
                    Size,
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAllOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirstOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirstOf (
                    Collection < T >    const &,
                    ElementType              &&
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLastOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLastOf (
                    Collection < T >    const &,
                    ElementType              &&
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceNotOf (
                    Size,
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAllNotOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirstNotOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirstNotOf (
                    Collection < T >    const &,
                    ElementType              &&
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLastNotOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLastNotOf (
                    Collection < T >    const &,
                    ElementType              &&
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceOf (
                    Size,
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAllOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirstOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirstOf (
                    InitializerList     const &,
                    ElementType              &&
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLastOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLastOf (
                    InitializerList     const &,
                    ElementType              &&
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceNotOf (
                    Size,
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAllNotOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirstNotOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirstNotOf (
                    InitializerList     const &,
                    ElementType              &&
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLastNotOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLastNotOf (
                    InitializerList     const &,
                    ElementType              &&
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replace (
                    Iterator    const &,
                    ElementType const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replace (
                    Iterator    const &,
                    ElementType      &&
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replace (
                    ConstIterator   const &,
                    ElementType     const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replace (
                    ConstIterator   const &,
                    ElementType          &&
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replace (
                    ReverseIterator const &,
                    ElementType     const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replace (
                    ReverseIterator const &,
                    ElementType          &&
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replace (
                    ConstReverseIterator    const &,
                    ElementType             const &
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replace (
                    ConstReverseIterator    const &,
                    ElementType                  &&
            ) noexcept -> bool;

        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replace (
                    Size,
                    Predicate   const &,
                    ElementType const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> Size;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAll (
                    Size,
                    Predicate   const &,
                    ElementType const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> Size;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirst (
                    Predicate   const &,
                    ElementType const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirst (
                    Predicate   const &,
                    ElementType      &&
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLast (
                    Predicate   const &,
                    ElementType const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLast (
                    Predicate   const &,
                    ElementType      &&
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            template < typename Predicate, typename Supplier >
            auto replace (
                    Size,
                    Predicate   const &,
                    Supplier    const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) && noexcept ( meta :: valueOf < Supplier > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate, typename Supplier >
            auto replaceAll (
                    Predicate   const &,
                    Supplier    const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) && noexcept ( meta :: valueOf < Supplier > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate, typename Supplier >
            auto replaceFirst (
                    Predicate   const &,
                    Supplier    const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) && noexcept ( meta :: valueOf < Supplier > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
            template < typename Predicate, typename Supplier >
            auto replaceLast (
                    Predicate   const &,
                    Supplier    const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) && noexcept ( meta :: valueOf < Supplier > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            virtual auto front () noexcept (false) -> ElementType & = 0;
        public:
            virtual auto front () const noexcept (false) -> ElementType const & = 0;
        public:
            virtual auto back () noexcept (false) -> ElementType & = 0;
        public:
            virtual auto back () const noexcept (false) -> ElementType const & = 0;

        public:
            virtual auto makeUnique () noexcept -> void = 0;

        public:
            __CDS_NoDiscard constexpr auto empty () const noexcept -> bool override;
        public:
            __CDS_NoDiscard __CDS_OptimalInline auto toString () const noexcept -> String override;
        public:
            auto index (
                    ElementType const &
            ) const noexcept -> Index;

        public:
            template < template < typename ... > typename ListType >
            auto find (
                    Size,
                    ElementType             const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto find (
                    Size,
                    ElementType const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirst (
                    ElementType const &
            ) noexcept -> Iterator;
        public:
            auto findLast (
                    ElementType const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAll (
                    ElementType             const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAll (
                    ElementType const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > typename ListType >
            auto findOf (
                    Size,
                    Collection < T >        const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findOf (
                    Size,
                    Collection < T > const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirstOf (
                    Collection < T > const &
            ) noexcept -> Iterator;
        public:
            auto findLastOf (
                    Collection < T > const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf (
                    Collection < T >        const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf (
                    Collection < T > const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > typename ListType >
            auto findNotOf (
                    Size,
                    Collection < T >        const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findNotOf (
                    Size,
                    Collection < T > const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirstNotOf (
                    Collection < T > const &
            ) noexcept -> Iterator;
        public:
            auto findLastNotOf (
                    Collection < T > const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf (
                    Collection < T >        const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf (
                    Collection < T > const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > typename ListType >
            auto findOf (
                    Size,
                    InitializerList         const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findOf (
                    Size,
                    InitializerList const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirstOf (
                    InitializerList const &
            ) noexcept -> Iterator;
        public:
            auto findLastOf (
                    InitializerList const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf (
                    InitializerList         const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf (
                    InitializerList const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > typename ListType >
            auto findNotOf (
                    Size,
                    InitializerList         const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findNotOf (
                    Size,
                    InitializerList const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirstNotOf (
                    InitializerList const &
            ) noexcept -> Iterator;
        public:
            auto findLastNotOf (
                    InitializerList const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf (
                    InitializerList         const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf (
                    InitializerList const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto find (
                    Size,
                    Predicate               const &,
                    ListType < Iterator >         &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto find (
                    Size,
                    Predicate const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> ListType < Iterator >;
        public:
            template < typename Predicate >
            auto findFirst (
                    Predicate const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator;
        public:
            template < typename Predicate >
            auto findLast (
                    Predicate const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto findAll (
                    Predicate               const &,
                    ListType < Iterator >         &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto findAll (
                    Predicate const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> ListType < Iterator >;

        public:
            template < typename Action >
            auto forEach (
                    Action const &
            ) noexcept ( noexcept ( meta :: valueOf < Action > () ( meta :: referenceOf < ElementType > () ) ) ) -> void;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto some (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atLeast (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atMost (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto moreThan (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto lessThan (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto count (
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> Size;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto any (
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto all (
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            using Collection < T > :: forEach;
        public:
            using Collection < T > :: some;
        public:
            using Collection < T > :: atLeast;
        public:
            using Collection < T > :: atMost;
        public:
            using Collection < T > :: moreThan;
        public:
            using Collection < T > :: lessThan;
        public:
            using Collection < T > :: count;
        public:
            using Collection < T > :: any;
        public:
            using Collection < T > :: all;
        public:
            using Collection < T > :: find;
        public:
            using Collection < T > :: findFirst;
        public:
            using Collection < T > :: findLast;
        public:
            using Collection < T > :: findAll;
        public:
            using Collection < T > :: findOf;
        public:
            using Collection < T > :: findFirstOf;
        public:
            using Collection < T > :: findLastOf;
        public:
            using Collection < T > :: findAllOf;
        public:
            using Collection < T > :: findNotOf;
        public:
            using Collection < T > :: findFirstNotOf;
        public:
            using Collection < T > :: findLastNotOf;
        public:
            using Collection < T > :: findAllNotOf;
        };

    }
}

#include "list/DelegateIterator.hpp"
#include "list/Iterator.hpp"
#include "list/ReverseIterator.hpp"

#include "list/impl/DelegateIterator.hpp"
#include "list/impl/Iterator.hpp"
#include "list/impl/ReverseIterator.hpp"

#include "list/impl/List.hpp"

#endif // __CDS_EX_LIST_HPP__

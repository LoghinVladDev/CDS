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
            using typename Collection < T > :: Iterator;
        public:
            using typename Collection < T > :: ConstIterator;
        public:
            using typename Collection < T > :: ReverseIterator;
        public:
            using typename Collection < T > :: ConstReverseIterator;

        protected:
            using typename Collection < T > :: DelegateIterator;
        protected:
            using typename Collection < T > :: DelegateConstIterator;

        protected:
            Size _size { 0U };

        protected:
            constexpr List () noexcept = default;
        protected:
            constexpr List ( List const & ) noexcept;
        protected:
            constexpr List ( List && ) noexcept;
        protected:
            constexpr explicit List ( Size ) noexcept;

        public:
            ~List () noexcept override = default;

        public:
            virtual auto get ( Index ) noexcept (false) -> ElementType & = 0;
        public:
            virtual auto get ( Index ) const noexcept (false) -> ElementType const & = 0;

        public:
            __CDS_NoDiscard __CDS_OptimalInline auto equals ( Object const & ) const noexcept -> bool override;

        public:
            template < typename ListType, typename V = T, EnableIf < Type < V > :: copyConstructible && isDerivedFrom < ListType, Collection < T > > :: value > = 0 >
            auto sub ( Index, Index, ListType & ) const noexcept (false) -> ListType &;
        public:
            template < typename ListType, typename V = T, EnableIf < Type < V > :: copyConstructible && isDerivedFrom < ListType, Collection < T > > :: value > = 0 >
            auto sub ( Index, Index ) const noexcept (false) -> ListType;
        public:
            template < template < typename ... > typename ListType, typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto sub ( Index, Index, ListType < ElementType > & ) const noexcept (false) -> ListType < ElementType > &;
        public:
            template < template < typename ... > typename ListType, typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto sub ( Index, Index ) const noexcept (false) -> ListType < ElementType >;

        public:
            template < typename ListType, typename = EnableIf < isDerivedFrom < ListType, Collection < T > > :: value > >
            auto indices ( ElementType const &, ListType & ) const noexcept -> ListType &;
        public:
            template < typename ListType, typename = EnableIf < isDerivedFrom < ListType, Collection < T > > :: value > >
            auto indices ( ElementType const & ) const noexcept -> ListType;
        public:
            template < template < typename ... > typename ListType >
            auto indices ( ElementType const &, ListType < Index > & ) const noexcept -> ListType < Index > &;
        public:
            template < template < typename ... > typename ListType >
            auto indices ( ElementType const & ) const noexcept -> ListType < Index >;

        public:
            auto operator [] ( Index ) noexcept (false) -> ElementType &;
        public:
            auto operator [] ( Index ) const noexcept -> ElementType const &;

        public:
            virtual auto popFront () noexcept -> void = 0;
        public:
            virtual auto popBack () noexcept -> void = 0;

        protected:
            virtual auto pNewFront () noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBack () noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBefore ( Iterator const & ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewAfter ( Iterator const & ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBefore ( ConstIterator const & ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewAfter ( ConstIterator const & ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBefore ( ReverseIterator const & ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewAfter ( ReverseIterator const & ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewBefore ( ConstReverseIterator const & ) noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewAfter ( ConstReverseIterator const & ) noexcept -> ElementType * & = 0;

        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto pushFront ( ElementType const & ) noexcept -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto pushFront ( ElementType && ) noexcept -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto pushBack ( ElementType const & ) noexcept -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto pushBack ( ElementType && ) noexcept -> ElementType &;

        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto insertBefore ( Iterator const &, ElementType const & ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto insertBefore ( Iterator const &, ElementType && ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto insertAfter ( Iterator const &, ElementType const & ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto insertAfter ( Iterator const &, ElementType && ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto insertBefore ( ConstIterator const &, ElementType const & ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto insertBefore ( ConstIterator const &, ElementType && ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto insertAfter ( ConstIterator const &, ElementType const & ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto insertAfter ( ConstIterator const &, ElementType && ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto insertBefore ( ReverseIterator const &, ElementType const & ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto insertBefore ( ReverseIterator const &, ElementType && ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto insertAfter ( ReverseIterator const &, ElementType const & ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto insertAfter ( ReverseIterator const &, ElementType && ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto insertBefore ( ConstReverseIterator const &, ElementType const & ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto insertBefore ( ConstReverseIterator const &, ElementType && ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            auto insertAfter ( ConstReverseIterator const &, ElementType const & ) noexcept (false) -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            auto insertAfter ( ConstReverseIterator const &, ElementType && ) noexcept (false) -> ElementType &;

        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            __CDS_OptimalInline auto append ( ElementType const & ) noexcept -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            __CDS_OptimalInline auto append ( ElementType && ) noexcept -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
            __CDS_OptimalInline auto prepend ( ElementType const & ) noexcept -> ElementType &;
        public:
            template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
            __CDS_OptimalInline auto prepend ( ElementType && ) noexcept -> ElementType &;

        public:
            virtual auto remove ( Index ) noexcept -> bool = 0;

        public:
            auto remove ( Iterator const & ) noexcept -> bool override = 0;
        public:
            auto remove ( ConstIterator const & ) noexcept -> bool override = 0;
        public:
            auto remove ( ReverseIterator const & ) noexcept -> bool override = 0;
        public:
            auto remove ( ConstReverseIterator const & ) noexcept -> bool override = 0;

        public:
            auto remove ( Collection < Iterator > const & ) noexcept -> Size override = 0;
        public:
            auto remove ( Collection < ConstIterator > const & ) noexcept -> Size override = 0;
        public:
            auto remove ( Collection < ReverseIterator > const & ) noexcept -> Size override = 0;
        public:
            auto remove ( Collection < ConstReverseIterator > const & ) noexcept -> Size override = 0;

        protected:
            template < typename ComparatorFunction >
            auto static quickSort ( Iterator const &, Iterator const &, ComparatorFunction const & ) noexcept -> void;
        protected:
            template < typename ComparatorFunction >
            auto static quickSortPartition ( Iterator const &, Iterator const &, ComparatorFunction const & ) noexcept -> Iterator;
        public:
            template < typename ComparatorFunction = Function < bool ( ElementType const &, ElementType const & ) > >
            auto sort ( ComparatorFunction const & = [] ( ElementType const & a, ElementType const & b ) { return a < b; } ) noexcept -> void;

        public:
            __CDS_NoDiscard constexpr auto size () const noexcept -> Size override;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replace (
                    ElementType const &,
                    ElementType const &,
                    Size
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceAll (
                    ElementType const &,
                    ElementType const &
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceFirst (
                    ElementType const &,
                    ElementType const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceFirst (
                    ElementType const &,
                    ElementType      &&
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceLast (
                    ElementType const &,
                    ElementType const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceLast (
                    ElementType const &,
                    ElementType      &&
            ) noexcept -> bool;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceOf (
                    Collection < T >    const &,
                    ElementType         const &,
                    Size
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceAllOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceFirstOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceFirstOf (
                    Collection < T >    const &,
                    ElementType              &&
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceLastOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceLastOf (
                    Collection < T >    const &,
                    ElementType              &&
            ) noexcept -> bool;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceNotOf (
                    Collection < T >    const &,
                    ElementType         const &,
                    Size
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceAllNotOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceFirstNotOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceFirstNotOf (
                    Collection < T >    const &,
                    ElementType              &&
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceLastNotOf (
                    Collection < T >    const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceLastNotOf (
                    Collection < T >    const &,
                    ElementType              &&
            ) noexcept -> bool;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceOf (
                    InitializerList     const &,
                    ElementType         const &,
                    Size
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceAllOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceFirstOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceFirstOf (
                    InitializerList     const &,
                    ElementType              &&
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceLastOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceLastOf (
                    InitializerList     const &,
                    ElementType              &&
            ) noexcept -> bool;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceNotOf (
                    InitializerList     const &,
                    ElementType         const &,
                    Size
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceAllNotOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> Size;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceFirstNotOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceFirstNotOf (
                    InitializerList     const &,
                    ElementType              &&
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceLastNotOf (
                    InitializerList     const &,
                    ElementType         const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceLastNotOf (
                    InitializerList     const &,
                    ElementType              &&
            ) noexcept -> bool;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replace (
                    Iterator    const &,
                    ElementType const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replace (
                    Iterator    const &,
                    ElementType      &&
            ) noexcept -> bool;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replace (
                    ConstIterator   const &,
                    ElementType     const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replace (
                    ConstIterator   const &,
                    ElementType          &&
            ) noexcept -> bool;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replace (
                    ReverseIterator const &,
                    ElementType     const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replace (
                    ReverseIterator const &,
                    ElementType          &&
            ) noexcept -> bool;

        public:
            template < typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replace (
                    ConstReverseIterator    const &,
                    ElementType             const &
            ) noexcept -> bool;
        public:
            template < typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replace (
                    ConstReverseIterator    const &,
                    ElementType                  &&
            ) noexcept -> bool;

        public:
            template < typename Predicate, typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replace (
                    Predicate   const &,
                    ElementType const &,
                    Size
            ) noexcept -> Size;
        public:
            template < typename Predicate, typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceAll (
                    Predicate   const &,
                    ElementType const &,
                    Size
            ) noexcept -> Size;
        public:
            template < typename Predicate, typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceFirst (
                    Predicate   const &,
                    ElementType const &
            ) noexcept -> bool;
        public:
            template < typename Predicate, typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceFirst (
                    Predicate   const &,
                    ElementType      &&
            ) noexcept -> bool;
        public:
            template < typename Predicate, typename V = T, typename = EnableIf < Type < V > :: copyAssignable > >
            auto replaceLast (
                    Predicate   const &,
                    ElementType const &
            ) noexcept -> bool;
        public:
            template < typename Predicate, typename V = T, typename = EnableIf < Type < V > :: moveAssignable > >
            auto replaceLast (
                    Predicate   const &,
                    ElementType      &&
            ) noexcept -> bool;

        public:
            template < typename Predicate, typename Supplier >
            auto replace (
                    Predicate   const &,
                    Supplier    const &,
                    Size
            ) noexcept -> bool;
        public:
            template < typename Predicate, typename Supplier >
            auto replaceAll (
                    Predicate   const &,
                    Supplier    const &
            ) noexcept -> bool;
        public:
            template < typename Predicate, typename Supplier >
            auto replaceFirst (
                    Predicate   const &,
                    Supplier    const &
            ) noexcept -> bool;
            template < typename Predicate, typename Supplier >
            auto replaceLast (
                    Predicate   const &,
                    Supplier    const &
            ) noexcept -> bool;

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
            auto index ( ElementType const & ) const noexcept -> Index;

        public:
            template < template < typename ... > typename ListType >
            auto find ( ElementType const &, ListType < Iterator > &, Size ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto find ( ElementType const &, Size ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto find ( ElementType const &, ListType < ConstIterator > &, Size ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto find ( ElementType const &, Size ) const noexcept -> ListType < ConstIterator >;
        public:
            auto findFirst ( ElementType const & ) noexcept -> Iterator;
        public:
            auto findFirst ( ElementType const & ) const noexcept -> ConstIterator;
        public:
            auto findLast ( ElementType const & ) noexcept -> Iterator;
        public:
            auto findLast ( ElementType const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAll ( ElementType const &, ListType < Iterator > & ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAll ( ElementType const & ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findAll ( ElementType const &, ListType < ConstIterator > & ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAll ( ElementType const & ) const noexcept -> ListType < ConstIterator >;

        public:
            template < template < typename ... > typename ListType >
            auto findOf ( Collection < T > const &, ListType < Iterator > &, Size ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findOf ( Collection < T > const &, Size ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findOf ( Collection < T > const &, ListType < ConstIterator > &, Size ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findOf ( Collection < T > const &, Size ) const noexcept -> ListType < ConstIterator >;
        public:
            auto findFirstOf ( Collection < T > const & ) noexcept -> Iterator;
        public:
            auto findFirstOf ( Collection < T > const & ) const noexcept -> ConstIterator;
        public:
            auto findLastOf ( Collection < T > const & ) noexcept -> Iterator;
        public:
            auto findLastOf ( Collection < T > const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf ( Collection < T > const &, ListType < Iterator > & ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf ( Collection < T > const & ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf ( Collection < T > const &, ListType < ConstIterator > & ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf ( Collection < T > const & ) const noexcept -> ListType < ConstIterator >;

        public:
            template < template < typename ... > typename ListType >
            auto findNotOf ( Collection < T > const &, ListType < Iterator > &, Size ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findNotOf ( Collection < T > const &, Size ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findNotOf ( Collection < T > const &, ListType < ConstIterator > &, Size ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findNotOf ( Collection < T > const &, Size ) const noexcept -> ListType < ConstIterator >;
        public:
            auto findFirstNotOf ( Collection < T > const & ) noexcept -> Iterator;
        public:
            auto findFirstNotOf ( Collection < T > const & ) const noexcept -> ConstIterator;
        public:
            auto findLastNotOf ( Collection < T > const & ) noexcept -> Iterator;
        public:
            auto findLastNotOf ( Collection < T > const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf ( Collection < T > const &, ListType < Iterator > & ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf ( Collection < T > const & ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf ( Collection < T > const &, ListType < ConstIterator > & ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf ( Collection < T > const & ) const noexcept -> ListType < ConstIterator >;

        public:
            template < template < typename ... > typename ListType >
            auto findOf ( InitializerList const &, ListType < Iterator > &, Size ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findOf ( InitializerList const &, Size ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findOf ( InitializerList const &, ListType < ConstIterator > &, Size ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findOf ( InitializerList const &, Size ) const noexcept -> ListType < ConstIterator >;
        public:
            auto findFirstOf ( InitializerList const & ) noexcept -> Iterator;
        public:
            auto findFirstOf ( InitializerList const & ) const noexcept -> ConstIterator;
        public:
            auto findLastOf ( InitializerList const & ) noexcept -> Iterator;
        public:
            auto findLastOf ( InitializerList const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf ( InitializerList const &, ListType < Iterator > & ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf ( InitializerList const & ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf ( InitializerList const &, ListType < ConstIterator > & ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllOf ( InitializerList const & ) const noexcept -> ListType < ConstIterator >;

        public:
            template < template < typename ... > typename ListType >
            auto findNotOf ( InitializerList const &, Size, ListType < Iterator > & ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findNotOf ( InitializerList const &, Size ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findNotOf ( InitializerList const &, Size, ListType < ConstIterator > & ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findNotOf ( InitializerList const &, Size ) const noexcept -> ListType < ConstIterator >;
        public:
            auto findFirstNotOf ( InitializerList const & ) noexcept -> Iterator;
        public:
            auto findFirstNotOf ( InitializerList const & ) const noexcept -> ConstIterator;
        public:
            auto findLastNotOf ( InitializerList const & ) noexcept -> Iterator;
        public:
            auto findLastNotOf ( InitializerList const & ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf ( InitializerList const &, ListType < Iterator > & ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf ( InitializerList const & ) noexcept -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf ( InitializerList const &, ListType < ConstIterator > & ) const noexcept -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType >
            auto findAllNotOf ( InitializerList const & ) const noexcept -> ListType < ConstIterator >;

        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto find ( Predicate const &, ListType < Iterator > &, Size ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto find ( Predicate const &, Size ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto find ( Predicate const &, ListType < ConstIterator > &, Size ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto find ( Predicate const &, Size ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> ListType < ConstIterator >;
        public:
            template < typename Predicate >
            auto findFirst ( Predicate const & ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> Iterator;
        public:
            template < typename Predicate >
            auto findFirst ( Predicate const & ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> ConstIterator;
        public:
            template < typename Predicate >
            auto findLast ( Predicate const & ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> Iterator;
        public:
            template < typename Predicate >
            auto findLast ( Predicate const & ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> ConstIterator;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto findAll ( Predicate const &, ListType < Iterator > & ) noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> ListType < Iterator > &;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto findAll ( Predicate const & ) noexcept ( noexcept ( ( * ( ( Predicate ) nullptr ) ) ( * ( ( ElementType * ) nullptr ) ) ) ) -> ListType < Iterator >;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto findAll ( Predicate const &, ListType < ConstIterator > & ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> ListType < ConstIterator > &;
        public:
            template < template < typename ... > typename ListType, typename Predicate >
            auto findAll ( Predicate const & ) const noexcept ( noexcept ( ( * ( ( Predicate * ) nullptr ) ) ( * ( ( ElementType const * ) nullptr ) ) ) ) -> ListType < ConstIterator >;
        };

    }
}

#include "list/impl/List.hpp"

#endif // __CDS_EX_LIST_HPP__

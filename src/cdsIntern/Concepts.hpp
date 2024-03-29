//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_CONCEPTS_HPP
#define CDS_CONCEPTS_HPP

#include <CDS/Compiler>

#if __CDS_cpplang_Concepts_available

namespace cds {
    class Object;

    namespace __hidden { // NOLINT(bugprone-reserved-identifier,modernize-concat-nested-namespaces)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseString; // NOLINT(bugprone-reserved-identifier)

        }
    }

}

#include <CDS/meta/TypeTraits>
#include <type_traits>
#include <concepts>
#include <iostream>

namespace cds {

    template <typename T>
    concept Integral =
            std::is_integral<T>::value ||
            std::is_convertible<T, int>::value ||
            std::is_convertible<T, long long int>::value;

    template < typename T, typename R >
    concept ConvertibleTo = std :: is_convertible < T, R > :: value;

    template < typename T >
    concept Pointer =
            meta :: isPointer < T > ();

    template < typename T >
    concept Iterable = requires ( T obj ) {
        { obj.begin() } -> std::same_as < typename T::Iterator >;
        { obj.end() }   -> std::same_as < typename T::Iterator >;
    };

    template < typename T >
    concept ConstIterable = requires ( T obj ) {
        { obj.begin() } -> std::same_as < typename T::ConstIterator >;
        { obj.end() }   -> std::same_as < typename T::ConstIterator >;
    };

    template < typename T >
    concept ReverseIterable = requires ( T obj ) {
        { obj.rbegin() } -> std::same_as < typename T::ReverseIterator >;
        { obj.rend() }   -> std::same_as < typename T::ReverseIterator >;
    };

    template < typename T >
    concept ConstReverseIterable = requires ( T obj ) {
        { obj.rbegin() } -> std::same_as < typename T::ConstReverseIterator >;
        { obj.rend() }   -> std::same_as < typename T::ConstReverseIterator >;
    };

    template < typename T >
    concept ForwardIterable = Iterable < T > || ConstIterable < T >;

    template < typename T >
    concept BackwardIterable = ReverseIterable < T > || ConstReverseIterable < T >;

    template < typename T >
    concept AnyIterable = ForwardIterable < T > || BackwardIterable < T >;

    template < typename T >
    concept BidirectionalIterable = ForwardIterable < T > && BackwardIterable < T >;

    template < typename T >
    concept ObjectDerived =
        std::is_base_of < Object, T > ::value;

    template < typename T >
    concept HasToString =
            ObjectDerived < T >                                                             ||
            std::is_same < T, __hidden :: __impl :: __BaseString < char > >::value          ||
            std::is_same < T, __hidden :: __impl :: __BaseString < char > const >::value;

    template < typename T >
    concept Printable = requires (T object) {
        { std::cout << object } -> std::same_as < std::ostream & >;
    };

    template <class T>
    concept Callable = std::is_invocable<T>::value;

    template <typename T>
    concept UniqueIdentifiableByObject = requires {
        std::is_base_of < Object, T >::value;
    };

    template <typename T>
    concept UniqueIdentifiableByOperator = requires (T const & left, T const & right ) {
        left == right;
    };

    template < typename T >
    concept Summable = requires ( T const & left, T const & right ) {
        left + right;
    };

    template <typename T>
    concept UniqueIdentifiable = requires ( T const & left, T const & right ) {
        requires UniqueIdentifiableByObject<T> || UniqueIdentifiableByOperator<T>;
    };

}

#include <CDS/Types>

namespace cds {

    template < typename T >
    concept PairType =
            meta :: isPair < T > ();

    template < typename T, typename V >
    concept LessComparable =
            meta :: lessThanPossible < T, V > ();

    template < typename T, typename V >
    concept GreaterComparable =
            meta :: greaterThanPossible < T, V > ();

    template < typename T >
    concept TypeLessComparable =
            LessComparable < T, T >;

    template < typename T >
    concept TypeGreaterComparable =
            GreaterComparable < T, T >;

    template < typename T, typename V >
    concept EqualsComparable =
            meta :: equalToPossible < T, V > ();

    template < typename T >
    concept TypeEqualsComparable =
            EqualsComparable < T, T >;

    template < typename D, typename B >
    concept DerivedFrom =
            meta :: isDerivedFrom < D, B > ();


    template < typename FunctionType, typename ReturnType, typename ... ArgumentTypes >
    concept FunctionOver =
            std :: is_invocable_r < ReturnType, FunctionType, decltype ((meta :: referenceOf < ArgumentTypes > () )) ... > :: type :: value;

    template < typename Predicate, typename T >
    concept PredicateOver =
            FunctionOver < Predicate, bool, T >;

    template < typename Predicate, typename T >
    concept IndexedPredicateOver = FunctionOver < Predicate, bool, Index, T >;

    template < typename Predicate >
    concept EmptyPredicate = FunctionOver < Predicate, bool >;

    template < typename Action, typename T >
    concept ActionOver =
            FunctionOver < Action, void, T >;

    template < typename Action, typename T >
    concept IndexedActionOver = FunctionOver < Action, void, Index, T >;

    template < typename Action >
    concept EmptyAction =
            FunctionOver < Action, void >;


    template < typename Transformer, typename ... ArgumentTypes >
    concept TransformerOver =
            true;
//            FunctionOver < Transformer, ReturnOf < Transformer >, ArgumentTypes ... >;

    template < typename Mapper, typename ... ArgumentTypes >
    concept MapperFor =
            TransformerOver < Mapper, ArgumentTypes ... >;

    template < typename Comparator, typename ElementType >
    concept ComparatorFor =
            FunctionOver < Comparator, bool, ElementType, ElementType >;

    template < typename Selector, typename ElementType >
    concept AscendingSelectorFor =
            true;
//            FunctionOver < Selector, ReturnOf < Selector >, ElementType > &&
//            TypeLessComparable < ReturnOf < Selector > >;

    template < typename Selector, typename ElementType >
    concept DescendingSelectorFor =
            true;
//            FunctionOver < Selector, ReturnOf < Selector >, ElementType > &&
//            TypeGreaterComparable < ReturnOf < Selector > >;

    template < typename Selector, typename ElementType >
    concept SelectorFor =
            true;
//            FunctionOver < Selector, ReturnOf < Selector >, ElementType > && (
//                TypeLessComparable < ReturnOf < Selector > > ||
//                TypeGreaterComparable < ReturnOf < Selector > >
//            );

    template < typename Accumulator, typename R, typename T >
    concept AccumulatorFor =
            FunctionOver < Accumulator, meta :: RemoveConst < meta :: RemoveReference < R > >, R, T >;

    template < typename Accumulator, typename R, typename T >
    concept IndexedAccumulatorFor =
            FunctionOver < Accumulator, meta :: RemoveConst < meta :: RemoveReference < R > >, Index, R, T >;

}

namespace cds {

    template < typename T >
    concept Comparable = requires(T const & left, T const & right) {
        std::is_convertible<decltype(left < right), bool>::value;
    };

}

#endif

#endif //CDS_CONCEPTS_HPP

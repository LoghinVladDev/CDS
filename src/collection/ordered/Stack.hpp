//
// Created by loghin on 19.07.2021.
//

#ifndef CDS_STACK_HPP
#define CDS_STACK_HPP

#include <CDS/SingleLinkedList>

namespace cds {

    template < typename T >
    class Stack : public SingleLinkedList < T > {
    public:
        Stack () noexcept = default;
        Stack (Stack const &) noexcept = default;
        Stack (Stack &&) noexcept = default;

        ~Stack() noexcept override = default;

    private:
        inline auto remove (Index i) noexcept -> bool override { return this->SingleLinkedList < T > ::remove(i); }
        inline auto remove ( T const & e, Size c ) noexcept -> bool override { return this->SingleLinkedList < T > :: remove (e, c); }
        inline auto removeLast ( T const & e ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLast ( e ); }
        inline auto removeOf ( Collection<T> const & e , Size c ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeOf (e, c); }
        inline auto removeLastOf ( Collection<T> const & e ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLastOf (e); }
        inline auto removeNotOf ( Collection<T> const & e, Size c ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeNotOf (e, c); }
        inline auto removeLastNotOf ( Collection<T> const & e ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLastNotOf (e); }
        inline auto remove ( typename Collection<T>::Iterator const & w ) noexcept (false) -> T override { return this->SingleLinkedList < T > :: remove (w); }
        inline auto removeOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->SingleLinkedList < T > ::removeOf (list, count); }
        inline auto removeLastOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLastOf (list); }
        inline auto removeNotOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeNotOf (list, count); }
        inline auto removeLastNotOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->SingleLinkedList < T > ::removeLastNotOf( list ); }

        inline auto removeAll ( T const & o ) noexcept -> bool override { return this->Collection < T > :: removeAll ( o ); }
        inline auto removeFirst ( T const & o ) noexcept -> bool override { return this->Collection < T > :: removeFirst ( o ); }
        inline auto removeFirstOf ( Collection < T > const & o ) noexcept -> bool override { return this->removeOf( o, 1 ); }
        inline auto removeAllOf ( Collection < T > const & o ) noexcept -> bool override { return this->removeOf ( o, this->size() ); }
        inline auto removeFirstNotOf ( Collection < T > const & o ) noexcept -> bool override { return this->removeNotOf ( o, 1 ); }
        inline auto removeAllNotOf ( Collection < T > const & o ) noexcept -> bool override  { return this->removeNotOf( o, this->size() ); }
        inline auto removeFirstOf ( std::initializer_list<T> const & o ) noexcept -> bool override { return this->removeOf( o, 1 ); }
        inline auto removeAllOf ( std::initializer_list<T> const & o ) noexcept -> bool override { return this->removeOf ( o, this->size() ); }
        inline auto removeFirstNotOf ( std::initializer_list<T> const & o ) noexcept -> bool override { return this->removeNotOf ( o, 1 ); }
        inline auto removeAllNotOf ( std::initializer_list<T> const & o ) noexcept -> bool override  { return this->removeNotOf( o, this->size() ); }

        inline auto makeUnique () noexcept -> void override { return this->SingleLinkedList <T> :: makeUnique(); }

        inline auto index ( T const & e ) const noexcept -> Index override { return this->SingleLinkedList < T > :: index (e); }
        inline auto index ( T & e ) noexcept -> Index override { return this->SingleLinkedList < T > :: index (e); }

        inline auto popBack () noexcept (false) -> T override { return this->SingleLinkedList < T > :: popBack(); }
        inline auto popFront () noexcept (false) -> T override { return this->SingleLinkedList < T > :: popFront(); }

    public:
        inline auto push ( T const & e ) noexcept -> void { return this->SingleLinkedList < T > :: pushFront (e); }
        inline auto push ( T && e ) noexcept -> void { return this->SingleLinkedList < T > :: pushFront (e); }

        inline auto pop () noexcept (false) -> T { return this->popFront(); }
    };

}

__CDS_RegisterParseTypeTemplateT(Stack)

#endif //CDS_STACK_HPP

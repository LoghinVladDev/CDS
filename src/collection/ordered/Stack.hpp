//
// Created by loghin on 19.07.2021.
//

#ifndef CDS_STACK_HPP
#define CDS_STACK_HPP

#include <CDS/LinkedList>

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
        inline auto replace ( T const & e, T const & r, Size c ) noexcept -> void override { return this->SingleLinkedList < T > :: replace (e, r, c); }
        inline auto replaceLast ( T const & e, T const & r ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceLast (e, r); }
        inline auto replaceOf ( Collection<T> const & e, T const & r , Size c ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceOf (e, r, c); }
        inline auto replaceLastOf ( Collection<T> const & e, T const & r ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceLastOf ( e, r ); }
        inline auto replaceNotOf ( Collection<T> const & e, T const & r, Size c ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceNotOf (e, r, c); }
        inline auto replaceLastNotOf ( Collection<T> const & e, T const & r ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceLastNotOf ( e, r ); }
        inline auto remove ( typename Collection<T>::Iterator const & w ) noexcept (false) -> T override { return this->SingleLinkedList < T > :: remove (w); }
        inline auto replace( typename Collection<T>::Iterator const & w, T const & e ) noexcept -> void override { return this->SingleLinkedList < T > :: replace (w,e ); }
        inline auto insertBefore( typename Collection<T>::Iterator const & w, T const & e ) noexcept -> void override { return this->SingleLinkedList < T > :: insertBefore (w,e); }
        inline auto insertAfter( typename Collection<T>::Iterator const & w, T const & e ) noexcept -> void override { return this->SingleLinkedList < T > :: insertAfter (w, e); }
        inline auto removeOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->SingleLinkedList < T > ::removeOf (list, count); }
        inline auto removeLastOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLastOf (list); }
        inline auto removeNotOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeNotOf (list, count); }
        inline auto removeLastNotOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->SingleLinkedList < T > ::removeLastNotOf( list ); }
        inline auto replaceOf ( std::initializer_list<T> const & list, T const & with, Size count ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceOf ( list, with, count ); }
        inline auto replaceLastOf ( std::initializer_list<T> const & list, T const & with ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceLastOf ( list, with ); }
        inline auto replaceNotOf ( std::initializer_list<T> const & list, T const & with, Size count ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceNotOf ( list, with, count ); }
        inline auto replaceLastNotOf ( std::initializer_list<T> const & list, T const & with ) noexcept -> void override { return this->SingleLinkedList < T > :: replaceLastNotOf ( list, with ); }

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
        inline auto replaceFirst ( T const & what, T const & with ) noexcept -> void override { return this->replace(what, with, 1); }
        inline auto replaceAll ( T const & what, T const & with ) noexcept -> void override { return this->replace(what, with, this->size()); }
        inline auto replaceFirstOf ( Collection < T > const & what, T const & with ) noexcept -> void override { return this->replaceOf(what, with, 1); }
        inline auto replaceAllOf ( Collection < T > const & what, T const & with ) noexcept -> void override { return this->replaceOf(what, with, this->size()); }
        inline auto replaceFirstNotOf ( Collection < T > const & what, T const & with ) noexcept -> void override { return this->replaceNotOf(what, with, 1); }
        inline auto replaceAllNotOf ( Collection < T > const & what, T const & with ) noexcept -> void override { return this->replaceNotOf(what, with, this->size()); }
        inline auto replaceFirstOf ( std::initializer_list<T> const & what, T const & with ) noexcept -> void override { return this->replaceOf(what, with, 1); }
        inline auto replaceAllOf ( std::initializer_list<T> const & what, T const & with ) noexcept -> void override { return this->replaceOf(what, with, this->size()); }
        inline auto replaceFirstNotOf ( std::initializer_list<T> const & what, T const & with ) noexcept -> void override { return this->replaceNotOf(what, with, 1); }
        inline auto replaceAllNotOf ( std::initializer_list<T> const & what, T const & with ) noexcept -> void override { return this->replaceNotOf(what, with, this->size()); }

        inline auto makeUnique () noexcept -> void override { return this->SingleLinkedList <T> :: makeUnique(); }

        inline auto index ( T const & e ) const noexcept -> Index override { return this->SingleLinkedList < T > :: index (e); }
        inline auto index ( T & e ) noexcept -> Index override { return this->SingleLinkedList < T > :: index (e); }

        inline auto get ( Index i ) const noexcept(false) -> T const & override { return this->SingleLinkedList < T > :: get (i); }
        inline auto get ( Index i ) noexcept(false) -> T & override { return this->SingleLinkedList < T > :: get (i); }

        inline auto set ( T const & e, Index i ) noexcept(false) -> T & override { return this->SingleLinkedList < T > :: set (e, i); }

        inline auto sub ( Index from, Index to ) const noexcept (false) -> SingleLinkedList < T > override {
            return this->SingleLinkedList < T > :: sub (from, to);
        }

        inline auto sub ( List < T > & list, Index from, Index to ) const noexcept(false) -> void final {
            return this->SingleLinkedList < T > :: sub (list, from, to);
        }

        inline auto popBack () noexcept (false) -> T override { return this->SingleLinkedList < T > :: popBack(); }
        inline auto popFront () noexcept (false) -> T override { return this->SingleLinkedList < T > :: popFront(); }

        inline auto pushFront ( T const & e ) noexcept -> void override { return this->SingleLinkedList < T > :: pushFront (e); }
        inline auto pushFront ( T && e ) noexcept -> void override { return this->SingleLinkedList < T > :: pushFront (e); }
        inline auto pushBack ( T const & e ) noexcept -> void override { return this->SingleLinkedList < T > :: pushBack (e); }
        inline auto pushBack ( T && e ) noexcept -> void override { return this->SingleLinkedList < T > :: pushBack (e); }

        inline auto prepend ( T const & e ) noexcept -> void override { return this->SingleLinkedList < T > :: prepend (e); }
        inline auto prepend ( T && e ) noexcept -> void override { return this->SingleLinkedList < T > :: prepend (e); }

    public:
        inline auto push ( T const & e ) noexcept -> void { return this->SingleLinkedList < T > :: pushFront (e); }
        inline auto push ( T && e ) noexcept -> void { return this->SingleLinkedList < T > :: pushFront (e); }

        inline auto pop () noexcept (false) -> T { return this->popFront(); }
    };

}

__CDS_RegisterParseTypeTemplateT(Stack)

#endif //CDS_STACK_HPP

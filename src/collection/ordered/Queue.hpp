//
// Created by loghin on 19.07.2021.
//


#ifndef CDS_QUEUE_HPP
#define CDS_QUEUE_HPP

#include <CDS/SingleLinkedList>

namespace cds {

    template < typename T >
    class Queue : public SingleLinkedList < T > { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    public:
        Queue () noexcept = default;
        Queue (Queue const &) noexcept = default;
        Queue (Queue &&) noexcept = default;

        ~Queue() noexcept override = default;

    private:
        inline auto remove (Index index) noexcept -> bool override { return this->SingleLinkedList < T > ::remove(index); }
        inline auto remove (T const & element, Size count ) noexcept -> bool override { return this->SingleLinkedList < T > :: remove (element, count); }
        inline auto removeLast ( T const & element ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLast (element ); }
        inline auto removeOf (Collection<T> const & element , Size count ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeOf (element, count); }
        inline auto removeLastOf ( Collection<T> const & element ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLastOf (element); }
        inline auto removeNotOf (Collection<T> const & element, Size count ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeNotOf (element, count); }
        inline auto removeLastNotOf ( Collection<T> const & element ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLastNotOf (element); }
        inline auto remove ( typename Collection<T>::Iterator const & elements ) noexcept (false) -> T override { return this->SingleLinkedList < T > :: remove (elements); }
        inline auto removeOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->SingleLinkedList < T > ::removeOf (list, count); }
        inline auto removeLastOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeLastOf (list); }
        inline auto removeNotOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->SingleLinkedList < T > :: removeNotOf (list, count); }
        inline auto removeLastNotOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->SingleLinkedList < T > ::removeLastNotOf( list ); }

        inline auto removeAll ( T const & element ) noexcept -> bool override { return this->Collection < T > :: removeAll (element ); }
        inline auto removeFirst ( T const & element ) noexcept -> bool override { return this->Collection < T > :: removeFirst (element ); }
        inline auto removeFirstOf ( Collection < T > const & elements ) noexcept -> bool override { return this->removeOf(elements, 1 ); }
        inline auto removeAllOf ( Collection < T > const & elements ) noexcept -> bool override { return this->removeOf (elements, this->size() ); }
        inline auto removeFirstNotOf ( Collection < T > const & elements ) noexcept -> bool override { return this->removeNotOf (elements, 1 ); }
        inline auto removeAllNotOf ( Collection < T > const & elements ) noexcept -> bool override  { return this->removeNotOf(elements, this->size() ); }
        inline auto removeFirstOf ( std::initializer_list<T> const & elements ) noexcept -> bool override { return this->removeOf(elements, 1 ); }
        inline auto removeAllOf ( std::initializer_list<T> const & elements ) noexcept -> bool override { return this->removeOf (elements, this->size() ); }
        inline auto removeFirstNotOf ( std::initializer_list<T> const & elements ) noexcept -> bool override { return this->removeNotOf (elements, 1 ); }
        inline auto removeAllNotOf ( std::initializer_list<T> const & elements ) noexcept -> bool override  { return this->removeNotOf(elements, this->size() ); }

        inline auto makeUnique () noexcept -> void override {
            return this->SingleLinkedList <T> :: makeUnique();
        }

        inline auto popBack () noexcept (false) -> T override {
            return this->SingleLinkedList < T > :: popBack();
        }

        inline auto popFront () noexcept (false) -> T override {
            return this->SingleLinkedList < T > :: popFront();
        }

    public:

        template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
        inline auto push ( T const & element ) noexcept -> T& {
            return this->SingleLinkedList < T > :: pushBack (element);
        }

        template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
        __CDS_MaybeUnused inline auto push ( T && element ) noexcept -> T& {
            return this->SingleLinkedList < T > :: pushBack (element);
        }

        inline auto pop () noexcept (false) -> T {
            return this->popFront();
        }
    };

}

__CDS_RegisterParseTypeTemplateT(Queue) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_QUEUE_HPP

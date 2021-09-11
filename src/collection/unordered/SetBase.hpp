//
// Created by loghin on 26.01.2021.
//

#ifndef CDS_SETBASE_HPP
#define CDS_SETBASE_HPP

#include <CDS/Collection>

template <class T>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
    requires UniqueIdentifiable <T>
#endif
class Set : public Collection<T> {
public:
    typedef T & Reference;
    typedef T const & ConstReference;
    typedef T * Pointer;
    typedef T const * ConstPointer;

    using Node = dataTypes::SingleListNode<T>;
    typedef Node * NodePointer;
    typedef Node const * ConstNodePointer;

    class Iterator final : public Collection<T>::Iterator {
    private:
        mutable NodePointer _pNode { nullptr };

    public:
        Iterator () noexcept = default;
        Iterator ( Iterator const & ) noexcept = default;
        Iterator ( Iterator && ) noexcept = default;
        explicit Iterator ( NodePointer pNode ) : Collection<T>::Iterator(), _pNode(pNode) {  }
        ~Iterator () noexcept final = default;

        constexpr inline auto equals ( typename Collection<T>::Iterator const & it ) const noexcept -> bool final { return dynamic_cast < Iterator const & > (it)._pNode == this->_pNode; }
        constexpr inline auto value () const noexcept -> Reference final { return this->_pNode->data; }
        constexpr inline auto next () noexcept -> Iterator & final { this->_pNode = this->_pNode->pNext; return * this; }

        constexpr inline auto operator ++ () noexcept -> Iterator & final { return this->next(); }
        constexpr inline auto operator ++ (int) noexcept -> Iterator { auto copy = *this; this->_pNode = this->_pNode->pNext; return copy; }

        __CDS_NoDiscard inline auto copy () const noexcept -> Iterator * override { return new Iterator (* this); }
    };

    class ConstIterator final : public Collection<T>::ConstIterator {
    private:
        ConstNodePointer _pNode { nullptr };

    public:
        ConstIterator () noexcept = default;
        ConstIterator ( ConstIterator const & ) noexcept = default;
        ConstIterator ( ConstIterator && ) noexcept = default;
        explicit ConstIterator ( ConstNodePointer pNode ) : Collection<T>::ConstIterator(), _pNode(pNode) {  }
        ~ConstIterator () noexcept final = default;

        constexpr inline auto equals ( typename Collection<T>::ConstIterator const & it ) const noexcept -> bool final { return dynamic_cast < ConstIterator const & > (it)._pNode == this->_pNode; }
        constexpr inline auto value () const noexcept -> ConstReference final { return this->_pNode->data; }
        constexpr inline auto next () noexcept -> ConstIterator & final { this->_pNode = this->_pNode->pNext; return * this; }

        constexpr inline auto operator ++ () noexcept -> ConstIterator & final { return this->next(); }
        constexpr inline auto operator ++ (int) noexcept -> ConstIterator { auto copy = *this; this->_pNode = this->_pNode->pNext; return copy; }

        __CDS_NoDiscard inline auto copy () const noexcept -> ConstIterator * override { return new ConstIterator (* this); }
    };

protected:
    NodePointer _pFront {nullptr};
    Size        _size   {0ull};

    inline auto beginPtr () noexcept -> Iterator * final { return new Iterator ( this->_pFront ); }
    inline auto endPtr () noexcept -> Iterator * final { return new Iterator ( nullptr ); }
    inline auto beginPtr () const noexcept -> ConstIterator * final { return new ConstIterator ( this->_pFront ); }
    inline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator ( nullptr ); }

    Set() noexcept = default;
    Set(Set const &) noexcept {}
    Set(Set && o) noexcept(false):
            _pFront(exchange(o._pFront, nullptr)),
            _size(exchange(o._size, 0ull)){

    }

public:

    ~Set() noexcept override { this->clear(); }

    __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator { return Iterator(this->_pFront); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator { return Iterator(nullptr); }
    constexpr inline auto begin () const noexcept -> ConstIterator { return ConstIterator (this->_pFront); }
    constexpr auto end () const noexcept -> ConstIterator { return ConstIterator (nullptr); }
    constexpr inline auto cbegin () const noexcept -> ConstIterator { return ConstIterator (this->_pFront); }
    constexpr inline auto cend () const noexcept -> ConstIterator { return ConstIterator (nullptr); }

protected:
    auto inline remove ( const T & e, Size ) noexcept -> bool final { return this->remove(e); }
    auto inline removeAll ( const T & o ) noexcept -> bool final { return false; }
    auto inline removeFirst ( const T & o ) noexcept -> bool final { return false; }
    auto inline removeLast ( const T & o ) noexcept -> bool final { return false; }
    auto inline removeOf ( const Collection<T> &, Size ) noexcept -> bool final { return false; }
    auto inline removeFirstOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
    auto inline removeAllOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
    auto inline removeLastOf ( const Collection<T> & ) noexcept -> bool final { return false; }
    auto inline removeNotOf ( const Collection<T> &, Size ) noexcept -> bool final { return false; }
    auto inline removeFirstNotOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
    auto inline removeAllNotOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
    auto inline removeLastNotOf ( const Collection<T> & ) noexcept -> bool final { return false; }
    auto inline removeOf ( const std::initializer_list<T> &, Size ) noexcept -> bool final { return false; }
    auto inline removeFirstOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
    auto inline removeAllOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
    auto inline removeLastOf ( const std::initializer_list<T> & ) noexcept -> bool final { return false; }
    auto inline removeNotOf ( const std::initializer_list<T> &, Size ) noexcept -> bool final { return false; }
    auto inline removeFirstNotOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
    auto inline removeAllNotOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
    auto inline removeLastNotOf ( const std::initializer_list<T> & ) noexcept -> bool final { return false; }
    auto inline replace ( const T &, const T &, Size ) noexcept -> void final { }
    auto inline replaceFirst ( const T & what, const T & with ) noexcept -> void final { }
    auto inline replaceAll ( const T & what, const T & with ) noexcept -> void final { }
    auto inline replaceLast ( const T &, const T & ) noexcept -> void final { }
    auto inline replaceOf ( const Collection <T> &, const T &, Size ) noexcept -> void final { }
    auto inline replaceFirstOf ( const Collection <T> & what, const T & with ) noexcept -> void final { }
    auto inline replaceAllOf ( const Collection <T> & what, const T & with ) noexcept -> void final { }
    auto inline replaceLastOf ( const Collection <T> &, const T & ) noexcept -> void final { }
    auto inline replaceNotOf ( const Collection <T> &, const T &, Size ) noexcept -> void final { }
    auto inline replaceFirstNotOf ( const Collection <T> & what, const T & with ) noexcept -> void final { }
    auto inline replaceAllNotOf ( const Collection <T> & what, const T & with ) noexcept -> void final { }
    auto inline replaceLastNotOf ( const Collection <T> &, const T & ) noexcept -> void final { }
    auto inline replaceOf ( const std::initializer_list<T> &, const T &, Size ) noexcept -> void final { }
    auto inline replaceFirstOf ( const std::initializer_list<T> & what, const T & with ) noexcept -> void final { }
    auto inline replaceAllOf ( const std::initializer_list<T> & what, const T & with ) noexcept -> void final { }
    auto inline replaceLastOf ( const std::initializer_list<T> &, const T & ) noexcept -> void final { }
    auto inline replaceNotOf ( const std::initializer_list<T> &, const T &, Size ) noexcept -> void final { }
    auto inline replaceFirstNotOf ( const std::initializer_list<T> & what, const T & with ) noexcept -> void final { }
    auto inline replaceAllNotOf ( const std::initializer_list<T> & what, const T & with ) noexcept -> void final { }
    auto inline replaceLastNotOf ( const std::initializer_list<T> &, const T & ) noexcept -> void final { }

    auto makeUnique () noexcept -> void final { }

public:
    auto remove ( ConstReference ) noexcept -> bool;
    virtual auto insert ( ConstReference ) noexcept -> bool = 0;
    virtual auto insert ( T && ) noexcept -> bool = 0;

    inline auto add ( ConstReference v ) noexcept -> void override {
        this->insert( v );
    }

    inline auto add ( T && v ) noexcept -> void override {
        this->insert( v );
    }

    auto clear () noexcept -> void final {
        while (this->_pFront != nullptr) {
            auto current = this->_pFront;
            this->_pFront = this->_pFront->pNext;
            delete current;
        }

        this->_size = 0;
    }

    auto back () noexcept (false) -> Reference final {
        if ( this->empty() )
            throw typename Collection<T>::CollectionOutOfBounds();

        auto head = this->_pFront;
        while ( head->pNext != nullptr )
            head = head->pNext;

        return head->data;
    }

    auto back () const noexcept(false) -> ConstReference final {
        if ( this->empty() )
            throw typename Collection<T>::CollectionOutOfBounds();

        auto head = this->_pFront;
        while ( head->pNext != nullptr )
            head = head->pNext;

        return head->data;
    }

    auto front() noexcept (false) -> Reference final {
        if ( this->empty() )
            throw typename Collection<T>::CollectionOutOfBounds();

        return this->_pFront->data;
    }

    auto front() const noexcept(false) -> ConstReference final {
        if ( this->empty() )
            throw typename Collection<T>::CollectionOutOfBounds();

        return this->_pFront->data;
    }

    __CDS_NoDiscard constexpr inline auto empty () const noexcept -> bool final { return this->size() == 0; }
    __CDS_NoDiscard constexpr inline auto size () const noexcept -> Size final { return this->_size; }

    inline auto contains ( ConstReference e ) const noexcept -> bool final {
        return this->any([&e](ConstReference x) noexcept -> bool {return Type < T > :: compare ( x, e );});
    }

    auto inline operator != (Set const & o) const noexcept -> bool { return ! this->operator==(o); }

    auto operator == (Set const & o) const noexcept -> bool {
        if ( this == & o ) return true;

        for ( auto itThis = this->begin(), itObj = o.begin(); itThis != this->end() && itObj != o.end(); itThis ++, itObj ++ )
            if ( ! ( Type < T > :: compare ( itThis.value(), itObj.value() ) ) )
                return false;
        return true;
    }

    __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < Set < T > const * > ( & o );
        if ( p == nullptr ) return false;

        return this->operator == (*p);
    }

    __CDS_NoDiscard auto toString () const noexcept -> String final;
};

#include <sstream>
template <class T>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires UniqueIdentifiable <T>
#endif
auto Set<T>::toString() const noexcept -> String {
    if ( this->empty() )
        return {"{ }"};

    std::stringstream out;
    out << "{ ";

    for ( ConstReference e : (*this) )
        Type < T > ::streamPrint( out, e ) << ", ";

    auto s = out.str();
    return {s.substr(0, s.length() - 2).append(" }")};
}

template <class T>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
    requires UniqueIdentifiable <T>
#endif
auto Set<T>::remove( ConstReference e) noexcept -> bool {
    if ( this->empty() )
        return false;

    if ( Type < T > :: compare ( e, this->_pFront->data ) ) {
        auto p = this->_pFront;
        this->_pFront = this->_pFront->pNext;
        this->_size --;

        delete p;
        return true;
    } else if ( this->size() == 1 )
        return false;

    auto head = this->_pFront;
    while ( head->pNext != nullptr ) {
        if ( Type < T > :: compare ( e, head->pNext->data ) ) {
            auto node = head->pNext;
            head->pNext = head->pNext->pNext;
            delete node;
            this->_size --;
            return true;
        }

        head = head->pNext;
    }

    return false;
}

#endif //CDS_SETBASE_HPP

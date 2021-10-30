//
// Created by loghin on 26.01.2021.
//

#ifndef CDS_SETBASE_HPP
#define CDS_SETBASE_HPP

#include <CDS/Collection>

template < typename T> __CDS_Requires ( UniqueIdentifiable <T> )
class Set : public Collection < T > {
public:
    using ElementType   = typename Collection < T > :: ElementType;

protected:
    using ElementRef                = typename Collection < T > :: ElementRef;
    using ElementCRef               = typename Collection < T > :: ElementCRef;
    using ElementMRef               = typename Collection < T > :: ElementMRef;
    using ElementPtr                = typename Collection < T > :: ElementPtr;
    using ElementPtrRef             = typename Collection < T > :: ElementPtrRef;
    using ElementCPtr               = typename Collection < T > :: ElementCPtr;

protected:
    using CollectionIterator        = typename Collection < T > :: Iterator;
    using ConstCollectionIterator   = typename Collection < T > :: ConstIterator;
    using InitializerList           = typename Collection < T > :: InitializerList;

    struct Node {
        T       * data;
        Node    * pNext {nullptr};
    };

    using NodePointer       = Node *;
    using ConstNodePointer  = Node const *;

public:

    class Iterator : public Collection < T > :: Iterator {
    private:
        NodePointer mutable _pNode { nullptr };

    public:
        constexpr Iterator () noexcept = delete;
        constexpr Iterator ( Iterator const & ) noexcept = default;
        constexpr Iterator ( Iterator && ) noexcept = default;

        constexpr explicit Iterator ( NodePointer pNode, Set < T > * pSet ) noexcept :
                Collection<T>::Iterator(pSet),
                _pNode(pNode) {

        }

        __CDS_cpplang_ConstexprDestructor ~Iterator () noexcept override = default;

        __CDS_cpplang_ConstexprOverride auto equals ( CollectionIterator const & it ) const noexcept -> bool final {
            return dynamic_cast < Iterator const & > (it)._pNode == this->_pNode;
        }

        __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef final {
            return * this->_pNode->data;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> Iterator & final {
            this->_pNode = this->_pNode->pNext; return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Iterator & final {
            return this->next();
        }

        __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Iterator {
            auto copy = *this;
            this->_pNode = this->_pNode->pNext;
            return copy;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> Iterator * override {
            return new Iterator (* this);
        }
    };

    class ConstIterator : public Collection<T>::ConstIterator {
    private:
        ConstNodePointer _pNode { nullptr };

    public:
        constexpr ConstIterator () noexcept = default;
        constexpr ConstIterator ( ConstIterator const & ) noexcept = default;
        constexpr ConstIterator ( ConstIterator && ) noexcept = default;

        constexpr explicit ConstIterator ( ConstNodePointer pNode, Set < T > const * pSet ) noexcept :
                Collection<T>::ConstIterator(pSet),
                _pNode(pNode) {

        }

        __CDS_cpplang_ConstexprDestructor ~ConstIterator () noexcept override = default;

        __CDS_cpplang_ConstexprOverride auto equals ( ConstCollectionIterator const & it ) const noexcept -> bool final {
            return dynamic_cast < ConstIterator const & > (it)._pNode == this->_pNode;
        }

        __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef final {
            return * this->_pNode->data;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ConstIterator & final {
            this->_pNode = this->_pNode->pNext;
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstIterator & final {
            return this->next();
        }

        __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ConstIterator {
            auto copy = *this;
            this->_pNode = this->_pNode->pNext;
            return copy;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> ConstIterator * override {
            return new ConstIterator (* this);
        }
    };

protected:
    NodePointer _pFront {nullptr};
    Size        _size   {0ull};

    __CDS_OptimalInline auto beginPtr () noexcept -> Iterator * final { return new Iterator ( this->_pFront, this ); }
    __CDS_OptimalInline auto endPtr () noexcept -> Iterator * final { return new Iterator ( nullptr, this ); }
    __CDS_OptimalInline auto beginPtr () const noexcept -> ConstIterator * final { return new ConstIterator ( this->_pFront, this ); }
    __CDS_OptimalInline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator ( nullptr, this ); }

    constexpr Set() noexcept = default;
    constexpr Set(Set const &) noexcept {}

    constexpr Set(Set && o) noexcept:
            _pFront(Utility::exchange(o._pFront, nullptr)),
            _size(Utility::exchange(o._size, 0ull)){

    }

public:

    ~Set() noexcept override { this->clear(); }

    __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator { return Iterator(this->_pFront, this); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator { return Iterator(nullptr, this); }
    __CDS_OptimalInline auto begin () const noexcept -> ConstIterator { return ConstIterator (this->_pFront, this); }
    __CDS_OptimalInline auto end () const noexcept -> ConstIterator { return ConstIterator (nullptr, this); }
    __CDS_OptimalInline auto cbegin () const noexcept -> ConstIterator { return ConstIterator (this->_pFront, this); }
    __CDS_OptimalInline auto cend () const noexcept -> ConstIterator { return ConstIterator (nullptr, this); }

protected:
    auto __CDS_OptimalInline remove ( const T & e, Size ) noexcept -> bool final { return this->remove(e); }
    auto __CDS_OptimalInline removeAll ( const T & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeFirst ( const T & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeLast ( const T & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeOf ( const Collection<T> &, Size ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeFirstOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeAllOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeLastOf ( const Collection<T> & ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeNotOf ( const Collection<T> &, Size ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeFirstNotOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeAllNotOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeLastNotOf ( const Collection<T> & ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeOf ( const std::initializer_list<T> &, Size ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeFirstOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeAllOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeLastOf ( const std::initializer_list<T> & ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeNotOf ( const std::initializer_list<T> &, Size ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeFirstNotOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeAllNotOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
    auto __CDS_OptimalInline removeLastNotOf ( const std::initializer_list<T> & ) noexcept -> bool final { return false; }

    auto makeUnique () noexcept -> void final { }

public:
    auto remove ( ElementCRef ) noexcept -> bool;
    __CDS_OptimalInline auto insert ( ElementCRef e ) noexcept -> void {
        return this->add(e);
    }

    __CDS_OptimalInline auto insert ( ElementMRef e ) noexcept -> void {
        return this->add(e);
    }

    auto clear () noexcept -> void final {
        while (this->_pFront != nullptr) {
            auto current = this->_pFront;
            this->_pFront = this->_pFront->pNext;

            delete current->data;
            delete current;
        }

        this->_size = 0;
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto empty () const noexcept -> bool final {
        return this->size() == 0;
    }

    __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size final {
        return this->_size;
    }

    auto __CDS_OptimalInline operator != (Set const & o) const noexcept -> bool { return ! this->operator==(o); }

    auto operator == (Set const & o) const noexcept -> bool {
        if ( this == & o ) return true;

        for ( auto itThis = this->begin(), itObj = o.begin(); itThis != this->end() && itObj != o.end(); itThis ++, itObj ++ )
            if ( ! ( Type < T > :: compare ( itThis.value(), itObj.value() ) ) )
                return false;
        return true;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto equals (Object const & o) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < Set < T > const * > ( & o );
        if ( p == nullptr ) return false;

        return this->operator == (*p);
    }

    __CDS_NoDiscard auto toString () const noexcept -> String final;
};

#include <sstream>
template < typename T > __CDS_Requires( UniqueIdentifiable <T> )
auto Set<T>::toString() const noexcept -> String {
    if ( this->empty() )
        return {"{ }"};

    std::stringstream out;
    out << "{ ";

    for ( ElementCRef e : (*this) )
        Type < T > ::streamPrint( out, e ) << ", ";

    auto s = out.str();
    return {s.substr(0, s.length() - 2).append(" }")};
}

template < typename T > __CDS_Requires( UniqueIdentifiable <T> )
auto Set<T>::remove( ElementCRef e ) noexcept -> bool {
    if ( this->empty() )
        return false;

    if ( Type < T > :: compare ( e, * this->_pFront->data ) ) {
        auto p = this->_pFront;
        this->_pFront = this->_pFront->pNext;
        -- this->_size;

        delete p->data;
        delete p;
        return true;
    } else if ( this->size() == 1 )
        return false;

    auto head = this->_pFront;
    while ( head->pNext != nullptr ) {
        if ( Type < T > :: compare ( e, * head->pNext->data ) ) {
            auto node = head->pNext;
            head->pNext = head->pNext->pNext;

            delete node->data;
            delete node;

            -- this->_size;
            return true;
        }

        head = head->pNext;
    }

    return false;
}

__CDS_RegisterParseTypeTemplateT(Set)

#endif //CDS_SETBASE_HPP

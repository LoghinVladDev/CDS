//
// Created by loghin on 26.01.2021.
//

#ifndef CDS_SETBASE_HPP
#define CDS_SETBASE_HPP

#include <CDS/Collection>
#include <CDS/Memory>

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
    using InitializerList           = typename Collection < T > :: InitializerList;

    using Iterator                  = typename Collection < T > :: Iterator;
    using ConstIterator             = typename Collection < T > :: ConstIterator;

    using ReverseIterator           = typename Collection < T > :: ReverseIterator;
    using ConstReverseIterator      = typename Collection < T > :: ConstReverseIterator;

    using DelegateIterator          = typename Collection < T > :: DelegateIterator;
    using DelegateConstIterator     = typename Collection < T > :: DelegateConstIterator;



    struct Node {
        T       * data;
        Node    * pNext {nullptr};
    };

    using NodePointer       = Node *;
    using ConstNodePointer  = Node const *;

    NodePointer _pFront {nullptr};
    Size        _size   {0ull};

    constexpr Set() noexcept = default;
    constexpr Set(Set const &) noexcept {}

    constexpr Set(Set && o) noexcept:
            _pFront(Utility::exchange(o._pFront, nullptr)),
            _size(Utility::exchange(o._size, 0ull)){

    }

    class SetDelegateIterator : public DelegateIterator {
    private:
        ForeignPointer < Set :: Node >  _pNode;

    public:
        explicit SetDelegateIterator ( Set :: Node * pNode ) noexcept :
                DelegateIterator (),
                _pNode ( pNode ) {

        }

        SetDelegateIterator ( SetDelegateIterator const & ) noexcept = default;
        SetDelegateIterator ( SetDelegateIterator && ) noexcept = default;

        ~SetDelegateIterator() noexcept override = default;

        auto next () noexcept -> SetDelegateIterator & override {
            this->_pNode = this->_pNode->pNext;
            return * this;
        }

        auto value () const noexcept -> ElementRef override {
            return * this->_pNode->data;
        }

        auto equals ( DelegateIterator const & it ) const noexcept -> bool override {
            if ( this == & it ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & it );
            if ( p == nullptr ) return false;

            return this->_pNode == p->_pNode;
        }

        auto copy () const noexcept -> SetDelegateIterator * override {
            return Memory :: instance ().create < SetDelegateIterator > ( * this );
        }
    };

    class SetDelegateConstIterator : public DelegateConstIterator {
    private:
        ForeignPointer < Set :: Node const >  _pNode;

    public:
        explicit SetDelegateConstIterator ( Set :: Node const * pNode ) noexcept :
                DelegateConstIterator (),
                _pNode ( pNode ) {

        }

        SetDelegateConstIterator ( SetDelegateConstIterator const & ) noexcept = default;
        SetDelegateConstIterator ( SetDelegateConstIterator && ) noexcept = default;

        ~SetDelegateConstIterator() noexcept override = default;

        auto next () noexcept -> SetDelegateConstIterator & override {
            this->_pNode = this->_pNode->pNext;
            return * this;
        }

        auto value () const noexcept -> ElementCRef override {
            return * this->_pNode->data;
        }

        auto equals ( DelegateConstIterator const & it ) const noexcept -> bool override {
            if ( this == & it ) return true;
            auto p = dynamic_cast < decltype ( this ) > ( & it );
            if ( p == nullptr ) return false;

            return this->_pNode == this->_pNode;
        }

        auto copy () const noexcept -> SetDelegateConstIterator * override {
            return Memory :: instance ().create < SetDelegateConstIterator > ( * this );
        }
    };


    using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

    auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
        switch ( requestType ) {
            case DelegateIteratorRequestType :: FORWARD_BEGIN:
                return Memory :: instance () . create < SetDelegateIterator > ( this->_pFront );
            case DelegateIteratorRequestType :: FORWARD_END:
                return Memory :: instance () . create < SetDelegateIterator > ( nullptr );
            case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                return Memory :: instance () . create < SetDelegateIterator > ( this->_pFront );
            case DelegateIteratorRequestType :: BACKWARD_END:
                return Memory :: instance () . create < SetDelegateIterator > ( nullptr );
        }
    }

    auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
        switch ( requestType ) {
            case DelegateIteratorRequestType :: FORWARD_BEGIN:
                return Memory :: instance () . create < SetDelegateConstIterator > ( this->_pFront );
            case DelegateIteratorRequestType :: FORWARD_END:
                return Memory :: instance () . create < SetDelegateConstIterator > ( nullptr );
            case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                return Memory :: instance () . create < SetDelegateConstIterator > ( this->_pFront );
            case DelegateIteratorRequestType :: BACKWARD_END:
                return Memory :: instance () . create < SetDelegateConstIterator > ( nullptr );
        }
    }

public:

    ~Set() noexcept override { this->clear(); }

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

            Memory :: instance().destroy ( current->data );
            Memory :: instance().destroy ( current );
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
            if ( ! ( Type < T > :: compare ( * itThis, * itObj ) ) )
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

        Memory::instance().destroy ( p->data );
        Memory::instance().destroy ( p );
        return true;
    } else if ( this->size() == 1 )
        return false;

    auto head = this->_pFront;
    while ( head->pNext != nullptr ) {
        if ( Type < T > :: compare ( e, * head->pNext->data ) ) {
            auto node = head->pNext;
            head->pNext = head->pNext->pNext;

            Memory::instance().destroy ( node->data );
            Memory::instance().destroy ( node );

            -- this->_size;
            return true;
        }

        head = head->pNext;
    }

    return false;
}

__CDS_RegisterParseTypeTemplateT(Set)

#endif //CDS_SETBASE_HPP

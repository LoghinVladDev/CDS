//
// Created by loghin on 26.01.2021.
//

#ifndef CDS_LISTSET_HPP
#define CDS_LISTSET_HPP

#include <CDS/Set>

namespace cds {

    template < typename T> __CDS_Requires ( UniqueIdentifiable <T> )
    class ListSet : public Set < T > { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    public:
        using ElementType               = typename Set < T > :: ElementType;

    protected:
        using ElementRef                = typename Set < T > :: ElementRef;
        using ElementCRef               = typename Set < T > :: ElementCRef;
        using ElementMRef               = typename Set < T > :: ElementMRef;
        using ElementPtr                = typename Set < T > :: ElementPtr;
        using ElementPtrRef             = typename Set < T > :: ElementPtrRef;
        using ElementCPtr               = typename Set < T > :: ElementCPtr;

    protected:
        using InitializerList           = typename Set < T > :: InitializerList;

        using Iterator                  = typename Set < T > :: Iterator;
        using ConstIterator             = typename Set < T > :: ConstIterator;

        using ReverseIterator           = typename Set < T > :: ReverseIterator;
        using ConstReverseIterator      = typename Set < T > :: ConstReverseIterator;

        using DelegateIterator          = typename Set < T > :: DelegateIterator;
        using DelegateConstIterator     = typename Set < T > :: DelegateConstIterator;


        struct Node {
            T       * data;
            Node    * pNext;
        };

        using NodePointer       = Node *;
        using ConstNodePointer  = Node const *;

        NodePointer _pFront {nullptr}; // NOLINT(clion-misra-cpp2008-11-0-1)
        Size        _size   {0ull}; // NOLINT(clion-misra-cpp2008-11-0-1)

        constexpr ListSet() noexcept = default;
        __CDS_OptimalInline ListSet(ListSet const & set) noexcept {}

        constexpr ListSet(ListSet && set) noexcept :
                _pFront(exchange(set._pFront, nullptr)),
                _size(exchange(set._size, 0ull)){

        }

        class SetDelegateIterator : public DelegateIterator {
        private:
            ForeignPointer < ListSet :: Node >  _pNode;

        public:
            constexpr explicit SetDelegateIterator ( ListSet :: Node * pNode ) noexcept :
                    DelegateIterator (),
                    _pNode ( pNode ) {

            }

            constexpr SetDelegateIterator ( SetDelegateIterator const & ) noexcept = default;
            constexpr SetDelegateIterator ( SetDelegateIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~SetDelegateIterator() noexcept override = default;

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> SetDelegateIterator & override {
                this->_pNode = this->_pNode->pNext;
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef override {
                return * this->_pNode->data;
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pObject = reinterpret_cast < decltype ( this ) > ( & iterator );

                return this->_pNode == pObject->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> SetDelegateIterator * override {
                return Memory :: instance ().create < SetDelegateIterator > ( * this );
            }
        };

        class SetDelegateConstIterator : public DelegateConstIterator {
        private:
            ForeignPointer < ListSet :: Node const >  _pNode;

        public:
            constexpr explicit SetDelegateConstIterator ( ListSet :: Node const * pNode ) noexcept :
                    DelegateConstIterator (),
                    _pNode ( pNode ) {

            }

            constexpr SetDelegateConstIterator ( SetDelegateConstIterator const & ) noexcept = default;
            constexpr SetDelegateConstIterator ( SetDelegateConstIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~SetDelegateConstIterator() noexcept override = default;

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> SetDelegateConstIterator & override {
                this->_pNode = this->_pNode->pNext;
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef override {
                return * this->_pNode->data;
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pObject = reinterpret_cast < decltype ( this ) > ( & iterator );

                return this->_pNode == pObject->_pNode;
            }

            __CDS_OptimalInline auto copy () const noexcept -> SetDelegateConstIterator * override {
                return Memory :: instance ().create < SetDelegateConstIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SetDelegateIterator > ( this->_pFront );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SetDelegateIterator > ( nullptr );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SetDelegateIterator > ( this->_pFront );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SetDelegateIterator > ( nullptr );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SetDelegateConstIterator > ( this->_pFront );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SetDelegateConstIterator > ( nullptr );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SetDelegateConstIterator > ( this->_pFront );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < SetDelegateConstIterator > ( nullptr );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

    public:

        ~ListSet() noexcept override { this->clear(); }

    public:
        auto remove ( ElementCRef ) noexcept -> bool override;

        auto clear () noexcept -> void final {
            while (this->_pFront != nullptr) {
                auto current = this->_pFront;
                this->_pFront = this->_pFront->pNext;

                Memory :: instance().destroy ( current->data );
                Memory :: instance().destroy ( current );
            }

            this->_size = 0;
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size final {
            return this->_size;
        }

        __CDS_OptimalInline auto operator != (ListSet const & set) const noexcept -> bool {
            return ! this->operator==(set); // NOLINT(clion-misra-cpp2008-5-3-1)
        }

        auto operator == (ListSet const & set) const noexcept -> bool {
            if ( this == & set ) {
                return true;
            }

            for ( // NOLINT(clion-misra-cpp2008-6-5-1)
                    auto // NOLINT(clion-misra-cpp2008-8-0-1)
                        aIt = this->begin(), aEnd = this->end(),
                        bIt = set.begin(), bEnd = set.end();
                    aIt != aEnd && bIt != bEnd;
                    ++ aIt, ++ bIt // NOLINT(clion-misra-cpp2008-5-18-1)
            ) {
                if ( ! ( Type < T > :: compare (* aIt, * bIt ) ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return false;
                }
            }

            return true;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto equals (Object const & object) const noexcept -> bool final {
            if (& object == this ) {
                return true;
            }

            auto pObject = dynamic_cast < ListSet < T > const * > ( & object );
            if (pObject == nullptr ) {
                return false;
            }

            return this->operator == (*pObject);
        }
    };

}

#include <sstream>

namespace cds {

    template < typename T > __CDS_Requires( UniqueIdentifiable <T> )
    auto ListSet<T>::remove( ElementCRef element ) noexcept -> bool {
        if ( this->empty() ) {
            return false;
        }

        if ( Type < T > :: compare (element, * this->_pFront->data ) ) {
            auto pFront = this->_pFront;
            this->_pFront = this->_pFront->pNext;
            -- this->_size;

            Memory::instance().destroy (pFront->data );
            Memory::instance().destroy (pFront );
            return true;
        } else if ( this->size() == 1 ) {
            return false;
        } else {
            /// do nothing
        }

        auto head = this->_pFront;
        while ( head->pNext != nullptr ) {
            if ( Type < T > :: compare (element, * head->pNext->data ) ) {
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

}

__CDS_RegisterParseTypeTemplateT(ListSet) // NOLINT(clion-misra-cpp2008-8-0-1)

#if !defined(__CDS_LISTSET_DOUBLEGUARD)
#define __CDS_LISTSET_DOUBLEGUARD // NOLINT(bugprone-reserved-identifier)

#include <CDS/OrderedSet>
#include <CDS/UnorderedSet>

#endif

#endif //CDS_LISTSET_HPP

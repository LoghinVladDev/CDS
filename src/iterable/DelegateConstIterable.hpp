//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_DELEGATE_CONST_ITERABLE_HPP__
#define __CDS_DELEGATE_CONST_ITERABLE_HPP__

#include "../collection/collection/DelegateIteratorRequestType.hpp"

namespace cds {

    namespace __hidden {
        namespace __impl {

            enum class __IteratorAdvanceDirection {
                __forward,
                __backward
            };

            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __AbstractDelegateIterator { // NOLINT(bugprone-reserved-identifier)
            protected: __AbstractDelegateIterator() = default;
            protected: virtual ~__AbstractDelegateIterator() noexcept = default;
            public: virtual auto advance ( __IteratorAdvanceDirection ) noexcept -> __AbstractDelegateIterator & = 0;
            public: virtual auto equals ( __AbstractDelegateIterator const & ) const noexcept -> bool = 0;
            public: virtual auto valid () const noexcept -> bool = 0;
            public: virtual auto copy () const noexcept -> __AbstractDelegateIterator * = 0;
            public: virtual auto value () const noexcept -> __ElementType & = 0;
            };

            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __AbstractIterator { // NOLINT(bugprone-reserved-identifier)
            private: Object const *                                 _pOwner     { nullptr };
            private: __AbstractDelegateIterator < __ElementType > * _pDelegate  { nullptr };
            protected: __AbstractIterator () noexcept = default;
            protected: __AbstractIterator ( __AbstractIterator const & ) noexcept;
            protected: __AbstractIterator ( __AbstractIterator && ) noexcept;
            protected: virtual ~__AbstractIterator () noexcept;

            protected:
                __AbstractIterator (
                        Object const *,
                        __AbstractDelegateIterator < __ElementType > *
                ) noexcept;

            public: auto of ( Object const * ) const noexcept -> bool;
            public: auto advance ( __IteratorAdvanceDirection ) noexcept -> __AbstractIterator &;
            public: auto valid () const noexcept -> bool;
            public: auto equals ( __AbstractIterator const & ) const noexcept -> bool;
            };

            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __DelegateOwnerUnidirectionalIterator : public __AbstractIterator < __ElementType > {
            public: __DelegateOwnerUnidirectionalIterator () noexcept;
            public: __DelegateOwnerUnidirectionalIterator (__DelegateOwnerUnidirectionalIterator const &) noexcept;
            public: __DelegateOwnerUnidirectionalIterator (__DelegateOwnerUnidirectionalIterator &&) noexcept;
            public: __DelegateOwnerUnidirectionalIterator (Object const *, __AbstractDelegateIterator < __ElementType > *) noexcept;
            public: ~__DelegateOwnerUnidirectionalIterator() noexcept override;
            public: auto operator = (__DelegateOwnerUnidirectionalIterator const &) noexcept -> __DelegateOwnerUnidirectionalIterator &;
            public: auto operator = (__DelegateOwnerUnidirectionalIterator &&) noexcept -> __DelegateOwnerUnidirectionalIterator &;
            public: auto operator ++ () noexcept -> __DelegateOwnerUnidirectionalIterator &;
            public: auto operator * () noexcept -> __ElementType &;
            public: auto operator -> () noexcept -> __ElementType *;
            };

            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __DelegateOwnerBidirectionalIterator : public __AbstractIterator < __ElementType > {
            public: __DelegateOwnerBidirectionalIterator () noexcept;
            public: __DelegateOwnerBidirectionalIterator (__DelegateOwnerBidirectionalIterator const &) noexcept;
            public: __DelegateOwnerBidirectionalIterator (__DelegateOwnerBidirectionalIterator &&) noexcept;
            public: __DelegateOwnerBidirectionalIterator (Object const *, __AbstractDelegateIterator < __ElementType > *) noexcept;
            public: ~__DelegateOwnerBidirectionalIterator() noexcept override;
            public: auto operator = (__DelegateOwnerBidirectionalIterator const &) noexcept -> __DelegateOwnerBidirectionalIterator &;
            public: auto operator = (__DelegateOwnerBidirectionalIterator &&) noexcept -> __DelegateOwnerBidirectionalIterator &;
            public: auto operator ++ () noexcept -> __DelegateOwnerBidirectionalIterator &;
            public: auto operator -- () noexcept -> __DelegateOwnerBidirectionalIterator &;
            public: auto operator * () noexcept -> __ElementType &;
            public: auto operator -> () noexcept -> __ElementType *;
            };

            template < typename __DerivedType, typename __ElementType, bool __bidirectional > // NOLINT(bugprone-reserved-identifier)
            class __DelegateForwardConstIterable {
            protected: using __dfci_ElementType = __ElementType const;
            protected: using __dfci_Iterator =
                    cds :: meta :: Conditional <
                            __bidirectional,
                            __DelegateOwnerUnidirectionalIterator < __dfci_ElementType >,
                            __DelegateOwnerBidirectionalIterator < __dfci_ElementType >
                    >;
            protected: auto begin () const noexcept -> __dfci_Iterator;
            protected: auto end () const noexcept -> __dfci_Iterator;
            protected: auto cbegin () const noexcept -> __dfci_Iterator;
            protected: auto cend () const noexcept -> __dfci_Iterator;
            };

            template < typename __DerivedType, typename __ElementType, bool __bidirectional > // NOLINT(bugprone-reserved-identifier)
            class __DelegateBackwardConstIterable {
            protected: using __dbci_ElementType = __ElementType const;
            protected: using __dbci_Iterator =
                        cds :: meta :: Conditional <
                                __bidirectional,
                                __DelegateOwnerUnidirectionalIterator < __dbci_ElementType >,
                                __DelegateOwnerBidirectionalIterator < __dbci_ElementType >
                        >;
            protected: auto rbegin () const noexcept -> __dbci_Iterator;
            protected: auto rend () const noexcept -> __dbci_Iterator;
            protected: auto crbegin () const noexcept -> __dbci_Iterator;
            protected: auto crend () const noexcept -> __dbci_Iterator;
            };

            template < typename __DerivedType, typename __ElementType, bool __bidirectional > // NOLINT(bugprone-reserved-identifier)
            class __DelegateForwardIterable {
            protected: using __dfi_ElementType = __ElementType;
            protected: using __dfi_Iterator =
                    cds :: meta :: Conditional <
                            __bidirectional,
                            __DelegateOwnerUnidirectionalIterator < __dfi_ElementType >,
                            __DelegateOwnerBidirectionalIterator < __dfi_ElementType >
                    >;
            protected: auto begin () noexcept -> __dfi_Iterator;
            protected: auto end () noexcept -> __dfi_Iterator;
            };

            template < typename __DerivedType, typename __ElementType, bool __bidirectional > // NOLINT(bugprone-reserved-identifier)
            class __DelegateBackwardIterable {
            protected: using __dbi_ElementType = __ElementType;
            protected: using __dbi_Iterator =
                        cds :: meta :: Conditional <
                                __bidirectional,
                                __DelegateOwnerUnidirectionalIterator < __dbi_ElementType >,
                                __DelegateOwnerBidirectionalIterator < __dbi_ElementType >
                        >;
            protected: auto begin () const noexcept -> __dbi_Iterator;
            protected: auto end () const noexcept -> __dbi_Iterator;
            };

            template < typename __DerivedType, typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __DelegateConstIterable {
            protected: using DelegateIteratorRequestType = __hidden :: __impl :: DelegateIteratorRequestType;
            protected: auto __dci_delegate ( DelegateIteratorRequestType )
                       const noexcept -> __AbstractDelegateIterator < __ElementType const >;
            };

            template < typename __DerivedType, typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __DelegateIterable {
            protected: using DelegateIteratorRequestType = __hidden :: __impl :: DelegateIteratorRequestType;
            protected: auto __di_delegate ( DelegateIteratorRequestType )
                       const noexcept -> __AbstractDelegateIterator < __ElementType >;
            };

        }
    }


}

#endif // __CDS_DELEGATE_CONST_ITERABLE_HPP__

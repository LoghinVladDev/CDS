//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_DELEGATE_CONST_ITERABLE_HPP__
#define __CDS_DELEGATE_CONST_ITERABLE_HPP__

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
            public: virtual ~__AbstractDelegateIterator() noexcept = default;
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
            protected: __AbstractIterator ( __AbstractIterator const & it ) noexcept : _pOwner ( it._pOwner ), _pDelegate ( it._pDelegate->copy() ) {}
            protected: __AbstractIterator ( __AbstractIterator && it ) noexcept : _pOwner ( it._pOwner ), _pDelegate ( cds :: exchange ( it._pDelegate, nullptr ) ) {}
            public: virtual ~__AbstractIterator () noexcept {
                delete this->_pDelegate;
            }

            protected:
                __AbstractIterator (
                        Object const * pObject,
                        __AbstractDelegateIterator < __ElementType > * pDelegate
                ) noexcept :
                        _pOwner ( pObject ),
                        _pDelegate ( pDelegate ) {

                }

            public: auto of ( Object const * ) const noexcept -> bool;
            public: auto advance ( __IteratorAdvanceDirection direction ) noexcept -> __AbstractIterator & {
                this->_pDelegate->advance( direction );
                return * this;
            }

            public: auto valid () const noexcept -> bool {
                return this->_pDelegate != nullptr && this->_pDelegate->valid();
            }

            public: auto value () const noexcept ->__ElementType & {
                return this->_pDelegate->value();
            }
            public: auto equals ( __AbstractIterator const & it ) const noexcept -> bool {
                return this->_pOwner == it._pOwner && this->_pDelegate->equals( * it._pDelegate );
            }
            public:
                auto copy ( __AbstractIterator const & it ) noexcept -> __AbstractIterator & {
                    if ( this == & it ) {
                        return * this;
                    }

                    delete this->_pDelegate;
                    this->_pDelegate = it._pDelegate->copy();
                    this->_pOwner = it._pOwner;

                    return * this;
                }
            public:
                auto move ( __AbstractIterator && it ) noexcept -> __AbstractIterator & {
                    if ( this == & it ) {
                        return * this;
                    }

                    delete this->_pDelegate;
                    this->_pDelegate = cds ::exchange(it._pDelegate, nullptr);
                    this->_pOwner = it._pOwner;

                    return * this;
                }
            };

            template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __DelegateOwnerUnidirectionalIterator : public __AbstractIterator < __ElementType > {
            public: __DelegateOwnerUnidirectionalIterator () noexcept {}
            public: __DelegateOwnerUnidirectionalIterator (__DelegateOwnerUnidirectionalIterator const & it) noexcept : __AbstractIterator<__ElementType>(it) {}
            public: __DelegateOwnerUnidirectionalIterator (__DelegateOwnerUnidirectionalIterator && it) noexcept : __AbstractIterator<__ElementType>(std::move(it)) {}
            public: __DelegateOwnerUnidirectionalIterator (Object const * pO, __AbstractDelegateIterator < __ElementType > * pD) noexcept : __AbstractIterator<__ElementType>(pO, pD) {}
            public: ~__DelegateOwnerUnidirectionalIterator() noexcept override = default;
            public: auto operator = (__DelegateOwnerUnidirectionalIterator const & it) noexcept -> __DelegateOwnerUnidirectionalIterator & {
                return reinterpret_cast < __DelegateOwnerUnidirectionalIterator<__ElementType> & >( this->copy ( it ) );
            }
            public: auto operator = (__DelegateOwnerUnidirectionalIterator &&it) noexcept -> __DelegateOwnerUnidirectionalIterator & {
                    return reinterpret_cast < __DelegateOwnerUnidirectionalIterator<__ElementType> & >( this->move (std::move( it ) ) );
                }
            public: auto operator == (__DelegateOwnerUnidirectionalIterator const & it) const noexcept -> bool {
                return this->equals ( it );
            }
            public: auto operator != (__DelegateOwnerUnidirectionalIterator const & it) const noexcept -> bool {
                return ! this->equals(it);
            }
            public: auto operator ++ () noexcept -> __DelegateOwnerUnidirectionalIterator & {
                return reinterpret_cast < __DelegateOwnerUnidirectionalIterator<__ElementType> & > ( this->advance(__IteratorAdvanceDirection::__forward) );
            }
            public: auto operator * () const noexcept -> __ElementType & {
                return this->value();
            }
            public: auto operator -> () const noexcept -> __ElementType * {
                return & ( this->value() );
            }
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
            public: auto operator == (__DelegateOwnerBidirectionalIterator const &) const noexcept -> bool;
            public: auto operator != (__DelegateOwnerBidirectionalIterator const &) const noexcept -> bool;
            public: auto operator ++ () noexcept -> __DelegateOwnerBidirectionalIterator &;
            public: auto operator -- () noexcept -> __DelegateOwnerBidirectionalIterator &;
            public: auto operator * () const noexcept -> __ElementType &;
            public: auto operator -> () const noexcept -> __ElementType *;
            };

            template < typename __DerivedType, typename __ElementType, bool __bidirectional > // NOLINT(bugprone-reserved-identifier)
            class __DelegateForwardConstIterable {
            protected: using __dfci_ElementType = __ElementType const;
            protected: using __dfci_Iterator =
                    cds :: meta :: Conditional <
                            __bidirectional,
                            __DelegateOwnerBidirectionalIterator < __dfci_ElementType >,
                            __DelegateOwnerUnidirectionalIterator < __dfci_ElementType >
                    >;
            protected: auto begin () const noexcept -> __dfci_Iterator {
                return this->cbegin();
            }
            protected: auto end () const noexcept -> __dfci_Iterator {
                return this->cend();
            }
            protected: auto cbegin () const noexcept -> __dfci_Iterator {
                    return __dfci_Iterator (
                            static_cast < __DerivedType const * > ( this ),
                            static_cast < __DerivedType const * > ( this )->__dci_delegate ( DelegateIteratorRequestType::ForwardBegin )
                    );
                }
            protected: auto cend () const noexcept -> __dfci_Iterator {
                    return __dfci_Iterator (
                            static_cast < __DerivedType const * > ( this ),
                            static_cast < __DerivedType const * > ( this )->__dci_delegate ( DelegateIteratorRequestType::ForwardEnd )
                    );
                }
            };

            template < typename __DerivedType, typename __ElementType, bool __bidirectional > // NOLINT(bugprone-reserved-identifier)
            class __DelegateBackwardConstIterable {
            protected: using __dbci_ElementType = __ElementType const;
            protected: using __dbci_Iterator =
                        cds :: meta :: Conditional <
                                __bidirectional,
                                __DelegateOwnerBidirectionalIterator < __dbci_ElementType >,
                                __DelegateOwnerUnidirectionalIterator < __dbci_ElementType >
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
                            __DelegateOwnerBidirectionalIterator < __dfi_ElementType >,
                            __DelegateOwnerUnidirectionalIterator < __dfi_ElementType >
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
                                __DelegateOwnerBidirectionalIterator < __dbi_ElementType >,
                                __DelegateOwnerUnidirectionalIterator < __dbi_ElementType >
                        >;
            protected: auto begin () const noexcept -> __dbi_Iterator;
            protected: auto end () const noexcept -> __dbi_Iterator;
            };

            template < typename __DerivedType, typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __DelegateConstIterable {
            private:
                friend class __DelegateForwardConstIterable < __DerivedType, __ElementType, false >;
                friend class __DelegateForwardConstIterable < __DerivedType, __ElementType, true >;
            protected: using DelegateIteratorRequestType = __hidden :: __impl :: DelegateIteratorRequestType;
            protected: virtual auto __dci_delegate ( DelegateIteratorRequestType )
                       const noexcept -> __AbstractDelegateIterator < __ElementType const > * = 0;
            };

            template < typename __DerivedType, typename __ElementType > // NOLINT(bugprone-reserved-identifier)
            class __DelegateIterable {
            protected: using DelegateIteratorRequestType = __hidden :: __impl :: DelegateIteratorRequestType;
            protected: auto __di_delegate ( DelegateIteratorRequestType )
                       noexcept -> __AbstractDelegateIterator < __ElementType > *;
            };

            template <
                    typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                    typename __IteratorType // NOLINT(bugprone-reserved-identifier)
            > class __DelegateIterableIterator : public __AbstractDelegateIterator < __ElementType > {
            private: __IteratorType it;
            public: __DelegateIterableIterator () noexcept = default;
            public: __DelegateIterableIterator (__DelegateIterableIterator const&) noexcept = default;
            public: ~__DelegateIterableIterator () noexcept override = default;
            public: __DelegateIterableIterator ( __IteratorType it ) noexcept : it (it) {}
            public: auto advance ( __IteratorAdvanceDirection direction ) noexcept -> __DelegateIterableIterator & override {
                ++ it;
                return * this;
            }
            public: auto equals ( __AbstractDelegateIterator < __ElementType > const & it ) const noexcept -> bool override {
                return this->it == reinterpret_cast < decltype ( this ) > ( & it )->it;
            }
            public: auto valid () const noexcept -> bool override {
                return it.valid();
            }
            public: auto copy () const noexcept -> __DelegateIterableIterator * override {
                return new __DelegateIterableIterator(* this);
            }
            public: auto value () const noexcept -> __ElementType & override {
                return * it;
            }
            };

            template <
                    typename __DerivedType,
                    typename __ElementType,
                    typename __IteratorType
            > class __DelegateConstIterableImplForward {
            protected:
                using __dci_DelegateIterator = __DelegateIterableIterator < __ElementType const, __IteratorType >;
            protected:
                auto __dci_begin () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {
                    return new __dci_DelegateIterator ( static_cast < __DerivedType const * > ( this )->begin() );
                }
                auto __dci_end () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {
                    return new __dci_DelegateIterator ( static_cast < __DerivedType const * > ( this )->end() );
                }
            };

            template <
                    typename __ElementType
            > class __DelegateConstIterableImplNoForward {
                auto __dci_begin () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {
                    return nullptr;
                }
                auto __dci_end () const noexcept -> __AbstractDelegateIterator < __ElementType const > * {
                    return nullptr;
                }
            };

            template <
                    typename __DerivedType, // NOLINT(bugprone-reserved-identifier)
                    typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                    typename __IteratorType, // NOLINT(bugprone-reserved-identifier)
                    bool __forward, // NOLINT(bugprone-reserved-identifier)
                    bool __backward // NOLINT(bugprone-reserved-identifier)
            > class __DelegateConstIterableImpl:
                    public cds :: meta :: Conditional <
                            __forward,
                            __DelegateConstIterableImplForward < __DerivedType, __ElementType, __IteratorType >,
                            __DelegateConstIterableImplNoForward < __ElementType >
                    > {

            protected:
                auto __dci_delegateAcquisition ( DelegateIteratorRequestType requestType ) const noexcept ->
                        __AbstractDelegateIterator < __ElementType const > * {

                    switch ( requestType ) {
                        case DelegateIteratorRequestType::ForwardBegin : return this->__dci_begin();
                        case DelegateIteratorRequestType::ForwardEnd : return this->__dci_end();
                        default: return nullptr;
                    }
                }
            };

        }
    }


}

#endif // __CDS_DELEGATE_CONST_ITERABLE_HPP__

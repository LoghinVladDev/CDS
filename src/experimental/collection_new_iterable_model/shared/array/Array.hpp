//
// Created by loghin on 7/5/22.
//

#ifndef __CDS_SHARED_ARRAY_HPP__
#define __CDS_SHARED_ARRAY_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                        __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        utility :: ComparisonFunction < __ElementType > __equals        // NOLINT(bugprone-reserved-identifier)
                > class __Array {                                                       // NOLINT(bugprone-reserved-identifier)

                protected:
                    using ElementType = __ElementType;

                private:
                    static Size const __a_minCapacity = 32ULL; // NOLINT(bugprone-reserved-identifier)

                public:
                    using __a_Iterator                      = AddressIterator < __ElementType, false >; // NOLINT(bugprone-reserved-identifier)

                public:
                    using __a_ConstIterator                 = AddressIterator < __ElementType const, false >; // NOLINT(bugprone-reserved-identifier)

                public:
                    using __a_ReverseIterator               = AddressIterator < __ElementType, true >; // NOLINT(bugprone-reserved-identifier)

                public:
                    using __a_ConstReverseIterator          = AddressIterator < __ElementType const, true >; // NOLINT(bugprone-reserved-identifier)

                public:
                    class __Dispatcher; // NOLINT(bugprone-reserved-identifier)

                private:
                    struct __ArrayImplDataContainer { // NOLINT(bugprone-reserved-identifier)
                        __ElementType * _pBuffer;
                        __ElementType * _pFront;
                        __ElementType * _pBack;
                        Size            _frontCapacity;
                        Size            _backCapacity;
                        Size            _frontNextCapacity;
                        Size            _backNextCapacity;
                    };

                private:
                    __ArrayImplDataContainer * _pData { nullptr };

                protected:
                    auto __a_clear ( // NOLINT(bugprone-reserved-identifier)
                            bool destroyBuffer
                    ) noexcept -> void;

                protected:
                    __CDS_NoDiscard constexpr auto __a_size () const noexcept -> Size; // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __a_remove ( // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) noexcept -> void;

                protected:
                    auto __a_remove ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __a_remove ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType const > const & iterator
                    ) noexcept -> bool;

                protected:
                    __CDS_NoDiscard constexpr auto __a_get ( // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) noexcept -> ElementType *;

                protected:
                    __CDS_NoDiscard constexpr auto __a_get ( // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) const noexcept -> ElementType const *;

                protected:
                    __CDS_NoDiscard auto __a_newFront () noexcept -> ElementType *; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard auto __a_newBack () noexcept -> ElementType *; // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __a_newFrontArray ( // NOLINT(bugprone-reserved-identifier)
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __a_newBackArray ( // NOLINT(bugprone-reserved-identifier)
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __a_newAddress ( // NOLINT(bugprone-reserved-identifier)
                            __ElementType const * pReferenceElement,
                            bool                * pNewElementCreated
                    ) noexcept -> ElementType *;

                protected:
                    auto __a_newAt ( // NOLINT(bugprone-reserved-identifier)
                            Index index
                    ) noexcept -> ElementType *;

                protected:
                    auto __a_newArrayAt ( // NOLINT(bugprone-reserved-identifier)
                            Index               index,
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    auto __a_newBefore ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __a_newBeforeConst ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType const > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __a_newAfter ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __a_newAfterConst ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType const > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    auto __a_newBeforeArray ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType >   const & iterator,
                            Size                                                count,
                            __ElementType                                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __a_newBeforeArrayConst ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType const > const & iterator,
                            Size                                                    count,
                            __ElementType                                        ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __a_newAfterArray ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType >   const & iterator,
                            Size                                                count,
                            __ElementType                                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    auto __a_newAfterArrayConst ( // NOLINT(bugprone-reserved-identifier)
                            AbstractAddressIterator < __ElementType const > const & iterator,
                            Size                                                    count,
                            __ElementType                                        ** ppElements
                    ) noexcept -> bool;

                private:
                    auto __a_init () noexcept -> void; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_begin () noexcept -> __a_Iterator; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_end () noexcept -> __a_Iterator; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_cbegin () const noexcept -> __a_ConstIterator; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_cend () const noexcept -> __a_ConstIterator; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_rbegin () noexcept -> __a_ReverseIterator; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_rend () noexcept -> __a_ReverseIterator; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_crbegin () const noexcept -> __a_ConstReverseIterator; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_crend () const noexcept -> __a_ConstReverseIterator; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __a_data () const noexcept -> __ElementType const *; // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __a_data () noexcept -> __ElementType *; // NOLINT(bugprone-reserved-identifier)
                };


                template <
                        typename __ElementType,                                         // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType > __equals // NOLINT(bugprone-reserved-identifier)
                > class __Array <
                        __ElementType,
                        __equals
                > :: __Dispatcher : public __ListServerDispatcher <
                        cds :: experimental :: Array < __ElementType >,
                        __Array < __ElementType, __equals >,
                        __ElementType,
                        AbstractAddressIterator < __ElementType >,
                        AbstractAddressIterator < __ElementType const >,
                        & __Array < __ElementType, __equals > :: __a_newAddress,
                        & __Array < __ElementType, __equals > :: __a_newFront,
                        & __Array < __ElementType, __equals > :: __a_newBack,
                        & __Array < __ElementType, __equals > :: __a_newFrontArray,
                        & __Array < __ElementType, __equals > :: __a_newBackArray,
                        & __Array < __ElementType, __equals > :: __a_newBefore,
                        & __Array < __ElementType, __equals > :: __a_newBeforeConst,
                        & __Array < __ElementType, __equals > :: __a_newAfter,
                        & __Array < __ElementType, __equals > :: __a_newAfterConst,
                        & __Array < __ElementType, __equals > :: __a_newBeforeArray,
                        & __Array < __ElementType, __equals > :: __a_newBeforeArrayConst,
                        & __Array < __ElementType, __equals > :: __a_newAfterArray,
                        & __Array < __ElementType, __equals > :: __a_newAfterArrayConst,
                        & __Array < __ElementType, __equals > :: __a_remove,
                        & __Array < __ElementType, __equals > :: __a_remove
                > {};

            }
        }
    }
}

#endif // __CDS_SHARED_ARRAY_HPP__

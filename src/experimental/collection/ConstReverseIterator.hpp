//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_CONST_REVERSE_ITERATOR_HPP__
#define __CDS_COLLECTION_CONST_REVERSE_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        /**
         * @class The Iterator type used for Backward Iteration over immutable values
         * @tparam T type of elements contained into the Collection class that nests the ConstIterator
         * @test tested in nester class test
         */
        template < typename T >
        class Collection < T > :: ConstReverseIterator : public Collection < T > :: AbstractIterator {
        public:
            /**
             * @brief Implicit Constructor
             * @exceptsafe
             * @test tested in nester class test
             */
            constexpr ConstReverseIterator () noexcept = default;

        public:
            /**
             * @brief Copy Constructor
             * @param iterator : ConstReverseIterator cref = Constant Reference to a ConstReverseIterator to copy properties from
             * @exceptsafe
             * @test tested in nester class test
             */
            ConstReverseIterator (
                    ConstReverseIterator const & iterator
            ) noexcept;

        public:
            /**
             * @brief Move Constructor
             * @param iterator : ConstReverseIterator mref = Move Reference to a ConstReverseIterator to move properties from
             * @exceptsafe
             * @test tested in nester class test
             */
            constexpr ConstReverseIterator (
                    ConstReverseIterator && iterator
            ) noexcept;

        public:
            /**
             * @brief Constructor Specialization
             * @param pCollection : Collection < T > cptr = Pointer to a Constant Collection this Iterator was created from
             * @param pIterator : UniquePointer < DelegateConstIterator > mref = Move Reference to an uniquely owned pointer to the Delegate Const Iterator implementing the iteration
             * @exceptsafe
             * @test tested in nester class test
             */
            constexpr ConstReverseIterator (
                    Collection < T >                                const * pCollection,
                    cds :: UniquePointer < DelegateConstIterator >       && pIterator
            ) noexcept;

        public:
            /**
             * @brief Implicit Destructor
             * @exceptsafe
             * @test tested in nester class test
             */
            ~ConstReverseIterator () noexcept override = default;

        public:
            /**
             * @brief Assignment/Copy Operator
             * @param iterator : ConstReverseIterator cref = Constant Reference to a ConstReverseIterator to copy properties from
             * @exceptsafe
             * @return ConstReverseIterator ref = Reference to the modified caller Iterator ( left operand )
             * @test tested in nester class test
             */
            auto operator = (
                    ConstReverseIterator const & iterator
            ) noexcept -> ConstReverseIterator &;

        public:
            /**
             * @brief Assignment/Move Operator
             * @param iterator : ConstReverseIterator mref = Move Reference to a ConstReverseIterator to move properties from
             * @exceptsafe
             * @return ConstReverseIterator ref = Reference to the modified caller Iterator ( left operand )
             * @test tested in nester class test
             */
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    ConstReverseIterator && iterator
            ) noexcept -> ConstReverseIterator &;

        public:
            /**
             * @brief Prefix Operator used to advance to the next iteration value via advancing the delegate
             * @exceptsafe
             * @return ConstReverseIterator ref = Reference to caller iterator object
             * @test tested in nester class test
             */
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> ConstReverseIterator &;

        public:
            /**
             * @brief Postfix Operator used to advance to the next iteration value via advancing the delegate
             * @exceptsafe
             * @return ConstReverseIterator = Copy of the original caller
             * @test tested in nester class test
             */
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ (int) noexcept -> ConstReverseIterator;

        public:
            /**
             * @brief Prefix Operator used to advance to the previous iteration value via advancing the delegate
             * @exceptsafe
             * @return ConstReverseIterator ref = Reference to caller iterator object
             * @test tested in nester class test
             */
            __CDS_cpplang_ConstexprPureAbstract auto operator -- () noexcept -> ConstReverseIterator &;

        public:
            /**
             * @brief Postfix Operator used to advance to the previous iteration value via advancing the delegate
             * @exceptsafe
             * @return ConstReverseIterator = Copy of the original caller
             * @test tested in nester class test
             */
            __CDS_cpplang_ConstexprPureAbstract auto operator -- (int) noexcept -> ConstReverseIterator;

        public:
            /**
             * @brief Dereference Operator, used to acquire the value the iterator is indicating to
             * @exceptsafe Even though iterator can be invalid, the behavior should be IllegalAccess / SegmentationFault for invalid case
             * @return ElementType cref = Constant Reference to a Collection Element
             * @test tested in nester class test
             */
            __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType const &;

        public:
            /**
             * @brief Member of Pointer Operator, used to acquire the address of the element the iterator is indicating to for member access
             * @exceptsafe Even though iterator can be invalid, the behavior should be IllegalAccess / SegmentationFault for invalid case
             * @return ElementType cptr = Pointer to a Constant element contained by the Collection, indicated by the Iterator
             * @test tested in nester class test
             */
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> ElementType const *;
        };

    }
}

#endif // __CDS_COLLECTION_CONST_REVERSE_ITERATOR_HPP__

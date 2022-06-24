//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_CONST_ITERATOR_HPP__
#define __CDS_COLLECTION_CONST_ITERATOR_HPP__

namespace cds {

    /**
     * @class The Iterator type used for Forward Iteration over immutable values
     * @tparam __ElementType type of elements contained into the Collection class that nests the ConstIterator
     * @test tested in nester class test
     */
    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class Collection < __ElementType > :: ConstIterator : public Collection < __ElementType > :: AbstractIterator {
    public:
        /**
         * @brief Implicit Constructor
         * @exceptsafe
         * @test tested in nester class test
         */
        constexpr ConstIterator () noexcept = default;

    public:
        /**
         * @brief Copy Constructor
         * @param iterator : ConstIterator cref = Constant Reference to a ConstIterator to copy properties from
         * @exceptsafe
         * @test tested in nester class test
         */
        ConstIterator (
                ConstIterator const & iterator
        ) noexcept;

    public:
        /**
         * @brief Move Constructor
         * @param iterator : ConstIterator mref = Move Reference to a ConstIterator to move properties from
         * @exceptsafe
         * @test tested in nester class test
         */
        constexpr ConstIterator (
                ConstIterator && iterator
        ) noexcept;

    public:
        /**
         * @brief Constructor Specialization
         * @param pCollection : Collection < T > cptr = Pointer to a Constant Collection this Iterator was created from
         * @param pIterator : UniquePointer < DelegateConstIterator > mref = Move Reference to an uniquely owned pointer to the Delegate Const Iterator implementing the iteration
         * @exceptsafe
         * @test tested in nester class test
         */
        constexpr ConstIterator (
                Collection < __ElementType >                    const * pCollection,
                cds :: UniquePointer < DelegateConstIterator >       && pIterator
        ) noexcept;

    public:
        /**
         * @brief Implicit Destructor
         * @exceptsafe
         * @test tested in nester class test
         */
        ~ConstIterator () noexcept override = default;

    public:
        /**
         * @brief Assignment/Copy Operator
         * @param iterator : ConstIterator cref = Constant Reference to a ConstIterator to copy properties from
         * @exceptsafe
         * @return ConstIterator ref = Reference to the modified caller Iterator ( left operand )
         * @test tested in nester class test
         */
        auto operator = (
                ConstIterator const & iterator
        ) noexcept -> ConstIterator &;

    public:
        /**
         * @brief Assignment/Move Operator
         * @param iterator : ConstIterator mref = Move Reference to a ConstIterator to move properties from
         * @exceptsafe
         * @return ConstIterator ref = Reference to the modified caller Iterator ( left operand )
         * @test tested in nester class test
         */
        auto operator = (
                ConstIterator && iterator
        ) noexcept -> ConstIterator &;

    public:
        /**
         * @brief Prefix Operator used to advance to the next iteration value via advancing the delegate
         * @exceptsafe
         * @return ConstIterator ref = Reference to caller iterator object
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprOverride auto operator ++ () noexcept -> ConstIterator &;

    public:
        /**
         * @brief Postfix Operator used to advance to the next iteration value via advancing the delegate
         * @exceptsafe
         * @return ConstIterator = Copy of the original caller
         * @test tested in nester class test
         */
        auto operator ++ (int) noexcept -> ConstIterator;

    public:
        /**
         * @brief Prefix Operator used to advance to the previous iteration value via advancing the delegate
         * @exceptsafe
         * @return ConstIterator ref = Reference to caller iterator object
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprOverride auto operator -- () noexcept -> ConstIterator &;

    public:
        /**
         * @brief Postfix Operator used to advance to the previous iteration value via advancing the delegate
         * @exceptsafe
         * @return ConstIterator = Copy of the original caller
         * @test tested in nester class test
         */
        auto operator -- (int) noexcept -> ConstIterator;

    public:
        /**
         * @brief Dereference Operator, used to acquire the value the iterator is indicating to
         * @exceptsafe Even though iterator can be invalid, the behavior should be IllegalAccess / SegmentationFault for invalid case
         * @return __ElementType cref = Constant Reference to a Collection Element
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprOverride auto operator * () const noexcept -> __ElementType const &;

    public:
        /**
         * @brief Member of Pointer Operator, used to acquire the address of the element the iterator is indicating to for member access
         * @exceptsafe Even though iterator can be invalid, the behavior should be IllegalAccess / SegmentationFault for invalid case
         * @return __ElementType cptr = Pointer to a Constant element contained by the Collection, indicated by the Iterator
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> __ElementType const *;
    };

}

#endif // __CDS_COLLECTION_CONST_ITERATOR_HPP__

//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_COLLECTION_DELEGATE_CONST_ITERATOR_HPP__

namespace cds {

    /**
     * @interface A more specific Abstract Delegate Iterator, used in implementing Delegate Iterators over immutable elements
     * @tparam __ElementType type of elements contained into the Collection class that nests the DelegateConstIterator
     * @test tested in nester class test
     */
    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class Collection < __ElementType > :: DelegateConstIterator : public Collection < __ElementType > :: AbstractDelegateIterator {
    protected:
        /**
         * @brief Implicit Constructor
         * @exceptsafe
         * @test tested in nester class test
         */
        constexpr DelegateConstIterator () noexcept = default;

    public:
        /**
         * @brief Implicit Destructor
         * @exceptsafe
         * @test tested in nester class test
         */
        ~DelegateConstIterator () noexcept override = default;

    public:
        /**
         * @brief Function used to advance to the next iteration value
         * @exceptsafe
         * @return DelegateConstIterator ref = Reference to caller iterator object
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprPureAbstract auto next () noexcept -> DelegateConstIterator & override = 0;

    public:
        /**
         * @brief Function used to advance to the previous iteration value
         * @exceptsafe
         * @return DelegateConstIterator ref = Reference to caller iterator object
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprPureAbstract auto previous () noexcept -> DelegateConstIterator & override = 0;

    public:
        /**
         * @brief Function used to acquire the value the iterator is indicating to
         * @exceptsafe Even though iterator can be invalid, the behavior should be IllegalAccess / SegmentationFault for invalid case
         * @return ElementType cref = Constant Reference to a Collection Element
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> __ElementType const & = 0;

    public:
        /**
         * @brief Comparison Function
         * @param iterator : AbstractDelegateIterator cref = Constant Reference to the iterator this is to be compared to
         * @exceptsafe
         * @return bool = equality status of the Iterators, true if equal, false otherwise
         * @test tested in nester class test
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool override = 0;

    public:
        /**
         * @brief Function used to check if iterator is not positioned validly in the owner collection ( i.e. end )
         * @exceptsafe
         * @return bool = true if iterator is validly positioned over an element, false otherwise
         * @test tested in nester class test
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto valid () const noexcept -> bool override = 0;

    public:
        /**
         * @brief Function used to acquire a new instance of this delegate iterator
         * @exceptsafe
         * @return DelegateConstIterator ptr = Address of the newly created delegate iterator
         * @test tested in nester class test
         */
        __CDS_NoDiscard auto copy () const noexcept -> DelegateConstIterator * override = 0;
    };

}

#endif // __CDS_COLLECTION_DELEGATE_CONST_ITERATOR_HPP__

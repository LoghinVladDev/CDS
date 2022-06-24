//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ABSTRACT_DELEGATE_ITERATOR_HPP__
#define __CDS_COLLECTION_ABSTRACT_DELEGATE_ITERATOR_HPP__

namespace cds {

    /**
     * @interface An Iterator Delegate represents the actual implementation of the iterator done by the derived classes. The Abstract Delegate Iterator is the base used by the Iterator bases
     * @tparam __ElementType type of elements contained into the Collection class that nests the AbstractDelegateIterator
     * @test tested in nester class test
     */
    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class Collection < __ElementType > :: AbstractDelegateIterator {
    protected:
        /**
         * @brief Implicit Constructor
         * @exceptsafe
         * @test tested in nester class test
         */
        constexpr AbstractDelegateIterator () noexcept = default;

    public:
        /**
         * @brief Implicit Destructor
         * @exceptsafe
         * @test tested in nester class test
         */
        virtual ~AbstractDelegateIterator () noexcept = default;

    public:
        /**
         * @brief Function used to advance to the next iteration value
         * @exceptsafe
         * @return AbstractDelegateIterator ref = Reference to caller iterator object
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprPureAbstract virtual auto next () noexcept -> AbstractDelegateIterator & = 0;

    public:
        /**
         * @brief Function used to advance to the previous iteration value
         * @exceptsafe
         * @return AbstractDelegateIterator ref = Reference to caller iterator object
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprPureAbstract virtual auto previous () noexcept -> AbstractDelegateIterator & = 0;
    public:

        /**
         * @brief Comparison Function
         * @param iterator : AbstractDelegateIterator cref = Constant Reference to the iterator this is to be compared to
         * @exceptsafe
         * @return bool = equality status of the Iterators, true if equal, false otherwise
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprPureAbstract virtual auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool = 0;

    public:
        /**
         * @brief Function used to check if iterator is not positioned validly in the owner collection ( i.e. end )
         * @exceptsafe
         * @return bool = true if iterator is validly positioned over an element, false otherwise
         * @test tested in nester class test
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valid () const noexcept -> bool = 0;

    public:
        /**
         * @brief Function used to acquire a new instance of this delegate iterator
         * @exceptsafe
         * @return AbstractDelegateIterator ptr = Address of the newly created delegate iterator
         * @test tested in nester class test
         */
        __CDS_NoDiscard virtual auto copy () const noexcept -> AbstractDelegateIterator * = 0;
    };

}

#endif // __CDS_COLLECTION_ABSTRACT_DELEGATE_ITERATOR_HPP__

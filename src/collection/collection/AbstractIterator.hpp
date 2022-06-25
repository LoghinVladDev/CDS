//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__
#define __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__

namespace cds {

    /**
     * @class The base class for Iterator types, mutable or immutable. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
     * @tparam __ElementType type of elements contained into the Collection class that nests the AbstractIterator
     * @test tested in nester class test
     */
    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class Collection < __ElementType > :: AbstractIterator {
    private:
        /// The base class is required to access the _pDelegate field
        friend class Collection < __ElementType >;

    protected:
        /// represents the collection this Iterator was created from. Not created or deleted by the Iterator
        Collection < __ElementType > const *                _pCollection { nullptr };

        /// represents the owned delegate that the Iterator is a wrapper for. Created by the collection, owned by the iterator, destroyed by the iterator.
        cds :: UniquePointer < AbstractDelegateIterator >   _pDelegate { nullptr };

    protected:
        /**
         * @brief Implicit Constructor
         * @exceptsafe
         * @test tested in nester class test
         */
        constexpr AbstractIterator () noexcept = default;

    protected:
        /**
         * @brief Copy Constructor
         * @param iterator : AbstractIterator cref = Constant Reference to an Abstract iterator to copy properties from
         * @exceptsafe
         * @test tested in nester class test
         */
        AbstractIterator (
                AbstractIterator const & iterator
        ) noexcept;

    protected:
        /**
         * @brief Move Constructor
         * @param iterator : AbstractIterator mref = Move Reference to an Abstract iterator to move properties from
         * @exceptsafe
         * @test tested in nester class test
         */
        constexpr AbstractIterator (
                AbstractIterator && iterator
        ) noexcept;

    public:
        /**
         * @brief Implicit Destructor
         * @exceptsafe
         * @test tested in nester class test
         */
        virtual ~AbstractIterator () noexcept = default;

    protected:
        /**
         * @brief Constructor Specialization
         * @param pCollection : Collection < T > cptr = Pointer to a Constant Collection this Iterator was created from
         * @param pIterator : UniquePointer < AbstractDelegateIterator > mref = Move Reference to an uniquely owned pointer to the Delegate Iterator implementing the iteration
         * @exceptsafe
         * @test tested in nester class test
         */
        constexpr AbstractIterator (
                Collection < __ElementType >                        const * pCollection,
                cds :: UniquePointer < AbstractDelegateIterator >        && pIterator
        ) noexcept;

    public:
        /**
         * @brief Function used to check if iterator belongs to a given collection
         * @param pCollection : Collection < T > cptr = Pointer to a Constant Collection object
         * @exceptsafe
         * @return bool = true if this iterator belongs / was created by the given collection, false otherwise
         * @test tested in nester class test
         */
        __CDS_NoDiscard constexpr auto of (
                Collection < __ElementType > const * pCollection
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to advance to the next iteration value via advancing the delegate
         * @exceptsafe
         * @return AbstractIterator ref = Reference to caller iterator object
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprPureAbstract auto next () noexcept -> AbstractIterator &;

    public:
        /**
         * @brief Function used to advance to the previous iteration value via advancing the delegate
         * @exceptsafe
         * @return AbstractIterator ref = Reference to caller iterator object
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprPureAbstract auto previous () noexcept -> AbstractIterator &;

    public:
        /**
         * @brief Function used to check if the contained iterator delegate is not positioned validly in the owner collection ( i.e. end )
         * @exceptsafe
         * @return bool = true if iterator delegate is validly positioned over an element, false otherwise
         * @test tested in nester class test
         */
        __CDS_NoDiscard __CDS_OptimalInline auto valid () const noexcept -> bool;

    public:
        /**
         * @brief Comparison Function
         * @param iterator : AbstractIterator cref = Constant Reference to the iterator this is to be compared to
         * @exceptsafe
         * @return bool = equality status of the Iterators, true if equal, false otherwise
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprOverride auto equals (
                AbstractIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Comparison Equality Function
         * @param iterator : AbstractIterator cref = Constant Reference to the iterator this is to be compared to
         * @exceptsafe
         * @return bool = equality status of the Iterators, true if equal, false otherwise
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprOverride auto operator == (
                AbstractIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Comparison Inequality Function
         * @param iterator : AbstractIterator cref = Constant Reference to the iterator this is to be compared to
         * @exceptsafe
         * @return bool = equality status of the Iterators, true if not equal, false otherwise
         * @test tested in nester class test
         */
        __CDS_cpplang_ConstexprOverride auto operator != (
                AbstractIterator const & iterator
        ) const noexcept -> bool;
    };

}

#endif // __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__

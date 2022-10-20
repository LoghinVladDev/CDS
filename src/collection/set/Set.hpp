/*
 * Created by loghin on 15.01.2021.
 */

#ifndef __CDS_SET_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SET_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Collection>

#include "../../shared/collectionInternalCommunication/client/primitive/FindUniqueImmutablePrimitiveClient.hpp"

#include "set/Constructs.hpp"

namespace cds {

    /**
     * @class Abstract Object representing a Set Container of elements, a Collection containing no duplicate elements.
     * As implied by its name, the class models the mathematical Set abstraction. The elements must provide a form
     * of equality, be it either by overriding an == operator, or by deriving them from cds :: Object and providing
     * an Object :: equals overridden function
     * @tparam __ElementType is the type of elements contained into the Set
     * @tparam __enabler is the enabler value generated by the EnableIf < isValidSetElement >, used only by definitions
     *
     * @extends     [public] Collection - Base Collection Class, inheriting properties - Immutable Iterable Container
     * @implements  [public] __SetFindUniqueClient < __ElementType, __enabler > - Find by Unique Element - compatible due to unique elements constraint
     *
     * @test Suite: STS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
     * @namespace cds
     * @public
     */
    template <
            typename                                                                            __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf < cds :: meta :: isValidSetElement < __ElementType > () >   __enabler       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class Set :
            public Collection < __ElementType >,
            public __hidden :: __impl :: __SetFindUniqueClient < __ElementType, __enabler > {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef public alias for __ElementType, the type of the contained elements,
         * publicly accessible, useful in sfinae statements - decltype ( Set ) :: ElementType
         * @public
         */
        using ElementType       = __ElementType;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for Collection \< __ElementType \> base extended class - providing immutable iterable properties
         * @protected
         */
        using CollectionBase    = Collection < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __SetFindUniqueClient base interface - Find by Unique Element - compatible due to unique elements constraint
         * @protected
         */
        using FindUniqueClient  = __hidden :: __impl :: __SetFindUniqueClient < __ElementType, __enabler >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef imported protected alias for __GenericHandler, representing a generic member function pointer, represents a function returned at a request made through the Collection Communication Channel
         * @protected
         */
        using typename CollectionBase :: __GenericHandler;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef imported protected alias for __GenericConstHandler, representing a generic member const-function pointer, represents a function returned at a request made through the Collection Communication Channel
         * @protected
         */
        using typename CollectionBase :: __GenericConstHandler; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor
         * @exceptsafe
         * @test Suite: STS-00001, Group: All, Test Cases: All
         * @protected
         */
        constexpr Set () noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor
         * @param [in] set : Set cref = Constant Reference to a Set to copy data from
         * @exceptsafe
         * @test Suite: STS-00001, Group: All, Test Cases: All
         * @protected
         */
        constexpr Set (
                Set const & set
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor
         * @param [in, out] set : Set mref = Move Reference to a Set to acquire and release the data from
         * @exceptsafe
         * @test Suite: STS-00001, Group: All, Test Cases: All
         * @protected
         */
        constexpr Set (
                Set && set
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Destructor
         * @exceptsafe
         * @test Suite: STS-00001, Group: All, Test Cases: All
         * @protected
         */
        __CDS_cpplang_ConstexprDestructor ~Set () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Deleted Copy Assignment Operator
         * @param [in] set : Set cref = Constant Reference to a set to copy data from
         * @exceptsafe
         * @return Set ref = Reference to the modified object
         *
         * @test N/A
         * @public
         */
        auto operator = (
                Set const &
        ) noexcept -> Set & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Deleted Move Assignment Operator
         * @param [in, out] set : Set mref = Move Reference to a set to move data from
         * @exceptsafe
         * @return Set ref = Reference to the modified object
         *
         * @test N/A
         * @public
         */
        auto operator = (
                Set &&
        ) noexcept -> Set & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit find function inherited from FindUniqueClient interface.
         * @test Suite: STS-00001, Group: STS-00050-FU, Test Cases: {
         *      STS-00051-FU-FindUniqueNotIn,
         *      STS-00052-FU-FindUniqueIn
         * }
         * @public
         */
        using FindUniqueClient :: find;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief String conversion function, used to obtain String representation of the Set
         * @exceptsafe
         * @return String = string representation
         * @test Suite: STS-00001, Group: STG-00101-MF, Test Cases: { STC-00101-MF-toString, STS-00102-MF-clear }
         * @public
         */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to clear the set, removing all elements from it
         * @exceptsafe
         * @test Suite: STS-00001, Group: STG-00100-MF, Test Cases: { STC-00102-MF-clear }
         * @public
         */
        auto clear () noexcept -> void override = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to remove an element from the Set by direct value reference
         * @param [in] element : __ElementType cref = Constant Reference to the element to remove
         * @return bool = true if element was removed, false otherwise
         * @test Suite: STS-00001, Group: STG-00100-MF, Test Cases: {
         *      STC-00103-MF-removeScen1,
         *      STC-00104-MF-removeScen2,
         *      STC-00105-MF-removeScen3,
         *      STC-00106-MF-removeScen4,
         *      STC-00107-MF-removeScen5
         * }
         * @public
         */
        virtual auto remove (
                __ElementType const & element
        ) noexcept -> bool = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to check if the collection contains the requested element.
         * Overridden by Set due to Set :: contains being faster than iteration, standard Collection :: contains implementation
         * @param [in] element : ElementType cref = Constant Reference to the element to be found in the collection
         * @return bool = true if the element exists in the collection, false otherwise
         * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00007-MF-containsTrue, CTC-00008-MF-containsFalse, CTC-00010-MF-clear }
         * @public
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto contains (
                __ElementType const & element
        ) const noexcept -> bool override = 0;
    };

} /* namespace cds */

#include "../../shared/collectionInternalCommunication/client/primitive/impl/FindUniqueImmutablePrimitiveClient.hpp"

#include "set/impl/Set.hpp"

#endif /* __CDS_SET_HPP__ */

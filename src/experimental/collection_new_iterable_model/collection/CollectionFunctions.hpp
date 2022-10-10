/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_COLLECTION_FUNCTIONS_HPP__
#define __CDS_EX_COLLECTION_FUNCTIONS_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @typedef Represents the type of function used by the Collection to check if an Iterable contains a given element
                 * @tparam __IterableType is the type of the iterable to check if the element is included in it
                 * @tparam __ElementType is the type of the element to be checked if it is included in the given collection
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template < typename __IterableType, typename __ElementType >                                /* NOLINT(bugprone-reserved-identifier) */
                using __ContainsFunction = auto ( __IterableType const &, __ElementType const & ) -> bool;  /* NOLINT(bugprone-reserved-identifier) */


                /**
                 * @class Represents the container for the function utility functions
                 * @tparam __ElementType is the type of the elements contained by the Collection
                 * @tparam __compare is an address to a comparison function, default cds :: meta :: equals
                 * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename                                                __ElementType,                                          /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >  __compare = & cds :: meta :: equals < __ElementType >   /* NOLINT(bugprone-reserved-identifier) */
                > class __CollectionFunctions {                                                                                         /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to check if two elements of the collection are equal
                     * @param left : __ElementType cref = Constant Reference to one of the elements involved in the comparison
                     * @param left : __ElementType cref = Constant Reference to another one of the elements involved in the comparison
                     * @exceptsafe
                     * @return bool = true if elements are equal, false otherwise
                     * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00010-MF-clear, CTC-00011-MF-equalsSelf,
                     *      CTC-00012-MF-equalsTrueSameType, CTC-00013-MF-equalsTrueDifferentType, CTC-00014-MF-equalsFalseSameType,
                     *      CTC-00015-MF-equalsFalseDifferentType, CTC-00016-MF-equalsFalseNotCollection }
                     * @protected
                     */
                    __CDS_NoDiscard constexpr static auto __cf_equals ( /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const & left,
                            __ElementType const & right
                    ) noexcept -> bool;
                };

            }
        }
    }
}

#endif /* __CDS_EX_COLLECTION_FUNCTIONS_HPP__ */

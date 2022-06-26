//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_COLLECTION_HPP__
#define __CDS_COLLECTION_HPP__

#include <CDS/std-types>
#include <CDS/Object>
#include <CDS/meta/TypeTraits>
#include <CDS/Concepts>
#include <CDS/smartPointers/UniquePointer>

#include "collection/DelegateIteratorRequestType.hpp"

namespace cds {

    /**
     * @class Abstract Object representing any Iterable Container of given elements of type
     * @tparam __ElementType is the type of elements contained into Collection
     * @test tested in collection/CollectionTest
     */
    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class Collection : public cds :: Object {

    public:
        /**
         * @typedef public alias for __ElementType, the type of the contained elements, publicly accessible, useful in sfinae statements - decltype ( Collection ) :: ElementType
         */
        using ElementType = __ElementType;

    protected:
        /**
         * @typedef Alias for std :: initializer_list < __ElementType > or std :: initializer_list < ElementType >
         */
        using InitializerList = std :: initializer_list < __ElementType >;

    public:
        /**
         * @brief Function used to remove a given number of elements that are contained in a given collection
         * @param count : Size = maximum number of elements to remove
         * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for contains check
         * @exceptsafe
         * @return Size = number of removed elements
         * @test tested in the class test
         */
        auto removeOf (
                Size                                count,
                Collection < ElementType >  const & collection
        ) noexcept -> Size;

    public:
        /**
         * @brief Function used to remove the first element that is contained in a given collection
         * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for contains check
         * @exceptsafe
         * @return bool = true if one element was removed, false otherwise
         * @test tested in the class test
         */
        auto removeFirstOf (
                Collection < ElementType > const & collection
        ) noexcept -> bool;

    public:
        /**
         * @brief Function used to remove the last element that is contained in a given collection
         * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for contains check
         * @exceptsafe
         * @return bool = true if one element was removed, false otherwise
         * @test tested in the class test
         */
        auto removeLastOf (
                Collection < ElementType > const & collection
        ) noexcept -> bool;

    public:
        /**
         * @brief Function used to remove all the elements that are contained in a given collection
         * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for contains check
         * @exceptsafe
         * @return Size = number of removed elements
         * @test tested in the class test
         */
        auto removeAllOf (
                Collection < ElementType > const & collection
        ) noexcept -> Size;

    public:
        /**
         * @brief Function used to remove a given number of elements that are not contained in a given collection
         * @param count : Size = maximum number of elements to remove
         * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for not contains check
         * @exceptsafe
         * @return Size = number of removed elements
         * @test tested in the class test
         */
        auto removeNotOf (
                Size                        count,
                Collection < ElementType >    const & collection
        ) noexcept -> Size;

    public:
        /**
         * @brief Function used to remove the first element that is not contained in a given collection
         * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for not contains check
         * @exceptsafe
         * @return bool = true if one element was removed, false otherwise
         * @test tested in the class test
         */
        auto removeFirstNotOf (
                Collection < ElementType > const & collection
        ) noexcept -> bool;

    public:
        /**
         * @brief Function used to remove the last element that is not contained in a given collection
         * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for not contains check
         * @exceptsafe
         * @return bool = true if one element was removed, false otherwise
         * @test tested in the class test
         */
        auto removeLastNotOf (
                Collection < ElementType > const & collection
        ) noexcept -> bool;

    public:
        /**
         * @brief Function used to remove a given number of elements that are not contained in a given collection
         * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for not contains check
         * @exceptsafe
         * @return Size = number of removed elements
         * @test tested in the class test
         */
        auto removeAllNotOf (
                Collection < ElementType > const & collection
        ) noexcept -> Size;

    public:
        /**
         * @brief Function used to remove a given number of elements that are contained in a given initializer list
         * @param count : Size = maximum number of elements to remove
         * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
         * @exceptsafe
         * @return Size = number of removed elements
         * @test tested in the class test
         */
        auto removeOf (
                Size                    count,
                InitializerList const & list
        ) noexcept -> Size;

    public:
        /**
         * @brief Function used to remove the first element that is contained in a given initializer list
         * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
         * @exceptsafe
         * @return bool = true if one element was removed, false otherwise
         * @test tested in the class test
         */
        auto removeFirstOf (
                InitializerList const & list
        ) noexcept -> bool;

    public:
        /**
         * @brief Function used to remove the last element that is contained in a given initializer list
         * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
         * @exceptsafe
         * @return bool = true if one element was removed, false otherwise
         * @test tested in the class test
         */
        auto removeLastOf (
                InitializerList const & list
        ) noexcept -> bool;

    public:
        /**
         * @brief Function used to remove all the elements that are contained in a given initializer list
         * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
         * @exceptsafe
         * @return Size = number of removed elements
         * @test tested in the class test
         */
        auto removeAllOf (
                InitializerList const & list
        ) noexcept -> Size;

    public:
        /**
         * @brief Function used to remove a given number of elements that are not contained in a given initializer list
         * @param count : Size = maximum number of elements to remove
         * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
         * @exceptsafe
         * @return Size = number of removed elements
         * @test tested in the class test
         */
        auto removeNotOf (
                Size                    count,
                InitializerList const & list
        ) noexcept -> Size;

    public:
        /**
         * @brief Function used to remove the first element that is not contained in a given initializer list
         * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
         * @exceptsafe
         * @return bool = true if one element was removed, false otherwise
         * @test tested in the class test
         */
        auto removeFirstNotOf (
                InitializerList const & list
        ) noexcept -> bool;

    public:
        /**
         * @brief Function used to remove the last element that is not contained in a given initializer list
         * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
         * @exceptsafe
         * @return bool = true if one element was removed, false otherwise
         * @test tested in the class test
         */
        auto removeLastNotOf (
                InitializerList const & list
        ) noexcept -> bool;

    public:
        /**
         * @brief Function used to remove a given number of elements that are not contained in a given initializer list
         * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
         * @exceptsafe
         * @return Size = number of removed elements
         * @test tested in the class test
         */
        auto removeAllNotOf (
                InitializerList const & list
        ) noexcept -> Size;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values matching the comparison to the given 'element' value
         * @tparam CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param maxCount : Size = maximum number of iterators to add to the storeIn object
         * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto find (
                Size                                        maxCount,
                ElementType                         const & element,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values matching the comparison to the given 'element' value
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param maxCount : Size = maximum number of iterators to add to the returned object
         * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto find (
                Size                maxCount,
                ElementType const & element
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the first value that is equal to the given 'element' value
         * @param element : ElementType cref = Constant Reference to an element to compare the collection's elements to
         * @exceptsafe
         * @return ConstIterator = iterator matching the first value equal to the given 'element' value, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findFirst (
                ElementType const & element
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the last value that is equal to the given 'element' value
         * @param element : ElementType cref = Constant Reference to an element to compare the collection's elements to
         * @exceptsafe
         * @return ConstIterator = iterator matching the last value equal to the given 'element' value, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findLast (
                ElementType const & element
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values matching the comparison to the given 'element' value
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAll (
                ElementType                         const & element,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values matching the comparison to the given 'element' value
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
         * @exceptsafe
         * @return __CollectionType < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAll (
                ElementType const & element
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' collection
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param maxCount : Size = maximum number of iterators to add to the storeIn object
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' collection
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param maxCount : Size = maximum number of iterators to add to the returned object
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findOf (
                Size                                maxCount,
                Collection < ElementType >  const & elements
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the first value that is also found in the 'elements' collection
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
         * @exceptsafe
         * @return ConstIterator = iterator matching the first value also found in the 'elements' collection, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findFirstOf (
                Collection < ElementType > const & elements
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the last value that is also found in the 'elements' collection
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
         * @exceptsafe
         * @return ConstIterator = iterator matching the last value also found in the 'elements' collection, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findLastOf (
                Collection < ElementType > const & elements
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are also found in the 'elements' collection
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAllOf (
                Collection < ElementType >          const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are also found in the 'elements' collection
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAllOf (
                Collection < ElementType > const & elements
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' collection
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param maxCount : Size = maximum number of iterators to add to the storeIn object
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' collection
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param maxCount : Size = maximum number of iterators to add to the returned object
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findNotOf (
                Size                                maxCount,
                Collection < ElementType >  const & elements
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the first value that is not found in the 'elements' collection
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
         * @exceptsafe
         * @return ConstIterator = iterator matching the first value not found in the 'elements' collection, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findFirstNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the last value that is not found in the 'elements' collection
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
         * @exceptsafe
         * @return ConstIterator = iterator matching the last value not found in the 'elements' collection, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findLastNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are not found in the 'elements' collection
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAllNotOf (
                Collection < ElementType >          const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are not found in the 'elements' collection
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAllNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' InitializerList
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param maxCount : Size = maximum number of iterators to add to the storeIn object
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' InitializerList
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param maxCount : Size = maximum number of iterators to add to the returned object
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findOf (
                Size                    maxCount,
                InitializerList const & elements
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the first value that is also found in the 'elements' InitializerList
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @exceptsafe
         * @return ConstIterator = iterator matching the first value also found in the 'elements' list, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findFirstOf (
                InitializerList const & elements
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the last value that is also found in the 'elements' InitializerList
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @exceptsafe
         * @return ConstIterator = iterator matching the last value also found in the 'elements' list, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findLastOf (
                InitializerList const & elements
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are also found in the 'elements' InitializerList
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAllOf (
                InitializerList                     const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are also found in the 'elements' InitializerList
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAllOf (
                InitializerList const & elements
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' InitializerList
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param maxCount : Size = maximum number of iterators to add to the storeIn object
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' InitializerList
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param maxCount : Size = maximum number of iterators to add to the returned object
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findNotOf (
                Size                    maxCount,
                InitializerList const & elements
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the first value that is not found in the 'elements' InitializerList
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @exceptsafe
         * @return ConstIterator = iterator matching the first value not found in the 'elements' list, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findFirstNotOf (
                InitializerList const & elements
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to return the ConstIterator matching the last value that is not found in the 'elements' InitializerList
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @exceptsafe
         * @return ConstIterator = iterator matching the last value not found in the 'elements' list, caller.end() if no value matches
         * @test tested in base class test
         */
        auto findLastNotOf (
                InitializerList const & elements
        ) const noexcept -> ConstIterator;

    public:
        /**
         * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are not found in the 'elements' InitializerList
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAllNotOf (
                InitializerList                     const & elements,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are not found in the 'elements' InitializerList
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
         * @exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto findAllNotOf (
                InitializerList const & elements
        ) const noexcept -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to populate a given Collection derived type of Iterators, with a maximum number of 'maxCount' iterators, pointing to the first or all the elements in the collection that are validated by a given predicate
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
         * @param maxCount : Size = maximum number of iterators to add to the storeIn object
         * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe if Predicate is exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto find (
                Size                                        maxCount,
                __Predicate                         const & predicate,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators, with a maximum number of 'maxCount' iterators, pointing to the first or all the elements in the collection that are validated by a given predicate
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
         * @param maxCount : Size = maximum number of iterators to add to the returned object
         * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
         * @exceptsafe if Predicate is exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto find (
                Size                maxCount,
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to return an iterator to the first element validated by the given predicate
         * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
         * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
         * @exceptsafe if Predicate is exceptsafe
         * @return Collection < ElementType > :: ConstIterator = Iterator to the first element validated by the given predicate, caller.end() if none exist
         * @test tested in base class test
         */
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto findFirst (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator;

    public:
        /**
         * @brief Function used to return an iterator to the last element validated by the given predicate
         * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
         * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
         * @exceptsafe if Predicate is exceptsafe
         * @return Collection < ElementType > :: ConstIterator = Iterator to the last element validated by the given predicate, caller.end() if none exist
         * @test tested in base class test
         */
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto findLast (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator;

    public:
        /**
         * @brief Function used to populate a given Collection derived type of Iterators with all iterators pointing to the first or all the elements in the collection that are validated by a given predicate
         * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
         * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
         * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
         * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
         * @exceptsafe if Predicate is exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto findAll (
                __Predicate                         const & predicate,
                __CollectionType < ConstIterator >        & storeIn
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator > &;

    public:
        /**
         * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the first or all the elements in the collection that are validated by a given predicate
         * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
         * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
         * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
         * @exceptsafe if Predicate is exceptsafe
         * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
         * @test tested in base class test
         */
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto findAll (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator >;

    public:
        /**
         * @brief Function used to check if the collection contains the requested element. Equivalent to collection.findFirst ( element ) != collection.end()
         * @param element : ElementType cref = Constant Reference to the element to be found in the collection
         * @return bool = true if the element exists in the collection, false otherwise
         * @test tested in base class test
         */
        virtual auto contains (
                ElementType const & element
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to check if the collection contains any of the requested elements.
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection of elements from which the caller collection's elements must have at least one match
         * @return bool = true if any element in the caller collection is found in the 'elements' collection, false otherwise
         * @test tested in base class test
         */
        auto containsAnyOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to check if the collection contains any element that is not of the requested elements.
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection of elements from which the caller collection's elements must have at least one non-match
         * @return bool = true if any element in the caller collection is not found in the 'elements' collection, false otherwise
         * @test tested in base class test
         */
        auto containsAnyNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to check if the collection contains all of the requested elements.
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection of elements from which the caller collection's elements must have every element matching
         * @return bool = true if all element in the caller collection are found in the 'elements' collection, false otherwise
         * @test tested in base class test
         */
        auto containsAllOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to check if the collection contains none of the requested elements.
         * @param elements : Collection < ElementType > cref = Constant Reference to the collection of elements from which the caller collection's elements must have every element non-matching
         * @return bool = true if no element in the caller collection are found in the 'elements' collection, false otherwise
         * @test tested in base class test
         */
        auto containsAllNotOf (
                Collection < ElementType > const & elements
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to check if the collection contains any of the requested elements.
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the list of elements from which the caller collection's elements must have at least one match
         * @return bool = true if any element in the caller collection is found in the 'elements' list, false otherwise
         * @test tested in base class test
         */
        auto containsAnyOf (
                InitializerList const & elements
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to check if the collection contains any element that is not of the requested elements.
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the list of elements from which the caller collection's elements must have at least one non-match
         * @return bool = true if any element in the caller collection is not found in the 'elements' list, false otherwise
         * @test tested in base class test
         */
        auto containsAnyNotOf (
                InitializerList const & elements
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to check if the collection contains all of the requested elements.
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the list of elements from which the caller collection's elements must have every element matching
         * @return bool = true if all element in the caller collection are found in the 'elements' list, false otherwise
         * @test tested in base class test
         */
        auto containsAllOf (
                InitializerList const & elements
        ) const noexcept -> bool;

    public:
        /**
         * @brief Function used to check if the collection contains none of the requested elements.
         * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the list of elements from which the caller collection's elements must have every element non-matching
         * @return bool = true if no element in the caller collection are found in the 'elements' list, false otherwise
         * @test tested in base class test
         */
        auto containsAllNotOf (
                InitializerList const & elements
        ) const noexcept -> bool;
    };

    template < template < typename ... > class __CollectionType, typename ... __ArgumentTypes, typename __Common = meta :: Common < __ArgumentTypes ... > > // NOLINT(bugprone-reserved-identifier)
    auto collectionOf (
            __ArgumentTypes && ... values
    ) noexcept -> __CollectionType < __Common >;

}

/// definition of Collection < T > :: DelegateIteratorRequestType
#include "collection/DelegateIteratorRequestType.hpp"

/// definition of Collection < T > :: AbstractDelegateIterator
#include "collection/AbstractDelegateIterator.hpp"

/// definition of Collection < T > :: DelegateConstIterator
#include "collection/DelegateConstIterator.hpp"

/// definition of Collection < T > :: AbstractIterator
#include "collection/AbstractIterator.hpp"

/// definition of Collection < T > :: ConstIterator
#include "collection/ConstIterator.hpp"

/// definition of Collection < T > :: ConstReverseIterator
#include "collection/ConstReverseIterator.hpp"


/// implementation of Collection < T > :: AbstractDelegateIterator functions
#include "collection/impl/AbstractDelegateIterator.hpp"

/// implementation of Collection < T > :: DelegateConstIterator functions
#include "collection/impl/DelegateConstIterator.hpp"

/// implementation of Collection < T > :: AbstractIterator functions
#include "collection/impl/AbstractIterator.hpp"

/// implementation of Collection < T > :: ConstIterator functions
#include "collection/impl/ConstIterator.hpp"

/// implementation of Collection < T > :: ConstReverseIterator functions
#include "collection/impl/ConstReverseIterator.hpp"


/// implementation of Collection < T > functions
#include "collection/impl/Collection.hpp"


#endif // __CDS_COLLECTION_HPP__

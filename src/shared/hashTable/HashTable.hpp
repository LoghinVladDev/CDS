// NOLINT(llvm-header-guard)
// Created by loghin on 27/07/22.
//

#ifndef __CDS_SHARED_HASH_TABLE_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_HASH_TABLE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

///
/// \class Base implementation class for hashtable-based objects
///
/// Works with a bucket buffer, each bucket being a single linked list.
/// Will allocate the bucket buffer based on a given template rehash policy
///
/// \tparam __ElementType is the element stored in each node located in the 'bucket' lists
/// \tparam __KeyType is the key extracted from the element stored in each node that will be hashed to determine the bucket location of the node
/// \tparam __KeyHasher is the type of the hasher object used to compute the hash of the key of each node. Used as type, to be declared and stored in
/// the class to facilitate initialization with key hasher
/// \tparam __RehashPolicy is the type of the rehash policy object used to determine when a rehash is required ( reallocation of buckets ). Used as type,
/// to be declared and stored in the class to facilitate initialization with key hasher
/// \tparam __keyExtractor is the function used to extract a __KeyType value from an __ElementType value.
/// Passed as function as it is not intended for copy. It is standard per interface type. ( set uses same value as key, map extracts )
/// \tparam __keyComparator is the function used to compare two __KeyType values, used when hashes are equal, to compare
/// keys in a given bucket.
/// \tparam __nodeDestructor is the function used to destroy an __ElementType value.
/// Called at destruction of a node, as an element can be composed of multiple objects ( i.e. MapEntry )
///
/// \test Suite: CTS-00001, Group: All, Test Cases: All
/// \test Suite: MCTS-00001, Group: All, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
///
template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __HashTable {                                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef Alias for forward mutable iterator
  /// \public
  using __ht_Iterator         = HashTableIterator <__ElementType>;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for forward immutable iterator
  /// \public
  using __ht_ConstIterator    = HashTableIterator <__ElementType const>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \class Dispatcher to this class' set-type implementation
  /// \implements __SetServerDispatcher
  /// \public
  template <typename __ServerType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  class __SetDispatcher;            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \class Dispatcher to this class' map-type implementation
  /// \implements __MapServerDispatcher
  /// \public
  template <typename __ServerType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  class __MapDispatcher;            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Copy Constructor, deleted
  /// \param [in] hashTable : __HashTable cref = Constant Reference to the hash table to copy data from
  /// \exceptsafe
  ///
  /// \test N/A
  /// \protected
  __HashTable (__HashTable const &) noexcept = delete;

  /// \brief Implicit Destructor
  /// \exceptsafe
  /// \test N/A
  /// \protected
  ~__HashTable() noexcept = default;

  /// \brief Copy Assignment Operator, deleted
  /// \param [in] hashTable : __HashTable cref = Constant Reference to the hash table to copy data from
  /// \exceptsafe
  /// \return __HashTable ref = Reference to the modified object
  /// \test N/A
  /// \protected
  auto operator = (
      __HashTable const&
  ) noexcept -> __HashTable& = delete;

  /// \brief Move Assignment Operator, deleted
  /// \param [in, out] hashTable : __HashTable mref = Move Reference to the hash table to acquire and release the data from
  /// \exceptsafe
  /// \return __HashTable ref = Reference to the modified object
  /// \test N/A
  /// \protected
  auto operator = (
      __HashTable&&
  ) noexcept -> __HashTable& = delete;
  
protected:
  /// \typedef Alias for template parameter __ElementType
  /// \protected
  using ElementType           = __ElementType;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for template parameter __KeyType
  /// \protected
  using KeyType               = __KeyType;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for template parameter __KeyHasher
  /// \protected
  using KeyHasher             = __KeyHasher;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for template parameter __RehashPolicy
  /// \protected
  using RehashPolicy          = __RehashPolicy;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Default Constructor, constexpr
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \protected
  constexpr __HashTable() noexcept;

  /// \brief Initialization constructor, using given key hasher
  /// \param [in] keyHasher : __KeyHasher cref = Constant Reference to key hasher to be used
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_Explicit constexpr __HashTable (__KeyHasher const &keyHasher) noexcept;

  /// \brief Initialization constructor, using given rehash policy
  /// \param [in] rehashPolicy : __RehashPolicy cref = Constant Reference to rehash policy to be used
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_Explicit constexpr __HashTable (__RehashPolicy const& rehashPolicy) noexcept;

  /// \brief Initialization constructor, using given key hasher and rehash policy
  /// \param [in] keyHasher : __KeyHasher cref = Constant Reference to key hasher to be used
  /// \param [in] rehashPolicy : __RehashPolicy cref = Constant Reference to rehash policy to be used
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  constexpr __HashTable (
      __KeyHasher const&    keyHasher,
      __RehashPolicy const& rehashPolicy
  ) noexcept;

  /// \brief Copy constructor, using given hash table and node copy function
  /// \tparam __CopyFunction is the type of the copy functor to be used
  /// \param [in] hashTable : __HashTable cref = Constant Reference to the hash table to copy data from
  /// \param [in] copyFunction : __CopyFunction cref = Constant Reference to the copy functor to initialize the new nodes with
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \protected
  template <
      typename __CopyFunction     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > __CDS_Implicit __HashTable (  // NOLINT(google-explicit-constructor)
      __HashTable const&    hashTable,
      __CopyFunction const& copyFunction
  ) noexcept(false);

  /// \brief Move constructor, using given hash table
  /// \param [in, out] hashTable : __HashTable mref = Move Reference to the hash table to acquire and release the data from
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \protected
  constexpr __HashTable (
      __HashTable&& hashTable
  ) noexcept;

  /// \brief Function used to purge the hash table data
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \protected
  auto __ht_clear() noexcept -> void;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire the number of elements in the hash table
  /// \exceptsafe
  /// \return Size = number of elements in the hash table
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr auto __ht_size () const noexcept -> Size;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to check if the hash table is empty
  /// \exceptsafe
  /// \return bool = true if hash table is empty, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr auto __ht_empty () const noexcept -> bool;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to acquire the number of buckets
  /// \exceptsafe
  /// \return Size = number of buckets
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_MaybeUnused constexpr auto __ht_bucketCount () const noexcept -> Size;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)

  /// \brief Function used to acquire a mutable forward iterator referencing the first element
  /// \excetpsafe
  /// \return __ht_Iterator = Hash Table Iterator to the first element
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ht_begin () noexcept -> __ht_Iterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)

  /// \brief Function used to acquire a mutable forward iterator referencing the space after the last element
  /// \excetpsafe
  /// \return __ht_Iterator = Hash Table Iterator to the space after the last element
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ht_end () noexcept -> __ht_Iterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire an immutable forward iterator referencing the first element
  /// \excetpsafe
  /// \return __ht_ConstIterator = Hash Table Const Iterator to the first element
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard constexpr auto __ht_cbegin () const noexcept -> __ht_ConstIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to acquire an immutable forward iterator referencing the space after the last element
  /// \excetpsafe
  /// \return __ht_ConstIterator = Hash Table Const Iterator to the space after the last element
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard constexpr auto __ht_cend () const noexcept -> __ht_ConstIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to allocate space for an element based on its key and return the memory address. Function is intended
  /// as an adapter to __ht_get, after the key has been extracted from pReferenceElement
  /// \param [in] pReferenceElement : __ElementType cptr = Address to an Immutable Reference comparison element. Used to extract the key of the new element
  /// \param [out] pNewElementCreated : bool ptr = Address of a boolean value to be set to true if newly created value was created. If key already exists, it will be set to false and the node address will be returned
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __ElementType ptr = Address to the newly created space for the element. If no element created, an address to the element containing the same key will be returned
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard auto __ht_new ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ElementType const*  pReferenceElement,
      bool*                 pNewElementCreated
  ) noexcept(false) -> __ElementType*;

  /// \brief Function used to allocate space for an element based on the given key
  /// \param [in] key : __KeyType cref = Constant Reference to a key to be used to check if a new element can be created
  /// \param [out] pNewElementCreated : bool ptr = Address of a boolean value to be set to true if newly created value was created. If key already exists, it will be set to false and the node address will be returned
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __ElementType ptr = Address to the newly created space for the element. If no element created, an address to the element containing the same key will be returned
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard auto __ht_get ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const&  key,
      bool*             pIsNew
  ) noexcept(false) -> __ElementType*;

  /// \brief Function used to acquire an immutable address of the node with the given key
  /// \param [in] key : __KeyType cref = Constant Reference to a key to be used to acquire the element with
  /// \exceptsafe
  /// \return __ElementType cptr = Address to an immutable node, if any found, nullptr otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __ht_getConst (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __KeyType const& key
  ) const noexcept -> __ElementType const*;

  /// \brief Function used to acquire a mutable address of the node with the given key. Unlike '__ht_get',
  /// '__ht_at' will not allocate new space, if key does not exist
  /// \param [in] key : __KeyType cref = Constant Reference to a key to be used to acquire the element with
  /// \exceptsafe
  /// \return __ElementType ptr = Address to an mutable node, if any found, nullptr otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_MaybeUnused auto __ht_at ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __KeyType const& key
  ) noexcept -> __ElementType*;

  /// \brief Function used to acquire an immutable address of the node with the given key
  /// \param [in] key : __KeyType cref = Constant Reference to a key to be used to acquire the element with
  /// \exceptsafe
  /// \return __ElementType cptr = Address to an immutable node, if any found, nullptr otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_MaybeUnused auto __ht_atConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __KeyType const& key
  ) const noexcept -> __ElementType const*;

  /// \brief Function used to remove a node based on a given key
  /// \param [in] key : __KeyType cref = Constant Reference to a key to be used to acquire the node with
  /// \exceptsafe
  /// \return bool = true if a node was removed, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ht_remove (                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const& key
  ) noexcept -> bool;

  auto __ht_removeGetPtr (                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const& key
  ) noexcept -> __ElementType*;

  /// \brief Function used to remove a node based on a given iterator. It will acquire the bucket index, the current and previous node and remove the node using these
  /// \param [in] iterator : __ht_Iterator cref = Constant Reference to a mutable forward iterator
  /// \exceptsafe
  /// \return bool = true if a node was removed, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ht_removeIterator (                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ht_Iterator const& iterator
  ) noexcept -> bool;

  /// \brief Function used to remove a node based on a given const iterator. It will acquire the bucket index, the current and previous node and remove the node using these
  /// \param [in] iterator : __ht_ConstIterator cref = Constant Reference to an immutable forward iterator
  /// \exceptsafe
  /// \return bool = true if a node was removed, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ht_removeIteratorConst (                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ht_ConstIterator const& iterator
  ) noexcept -> bool;

  /// \brief Function used to remove multiple nodes based on a given iterator array. It will acquire the bucket index, the current and previous node from each iterator and remove the nodes using these
  /// \param [in] ppIterators : __ht_Iterator cptr cptr = Address to an immutable array of addresses to immutable forward mutable iterators
  /// \param [in] iteratorCount : Size = number of elements in the iterator array
  /// \exceptsafe
  /// \return Size = number of removed nodes
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ht_removeIteratorArray (                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ht_Iterator const* const* ppIterators,
      Size                        iteratorCount
  ) noexcept -> Size;

  /// \brief Function used to remove multiple nodes based on a given const iterator array. It will acquire the bucket index, the current and previous node from each iterator and remove the nodes using these
  /// \param [in] ppIterators : __ht_ConstIterator cptr cptr = Address to an immutable array of addresses to immutable forward immutable iterators
  /// \param [in] iteratorCount : Size = number of elements in the iterator array
  /// \exceptsafe
  /// \return Size = number of removed nodes
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ht_removeConstIteratorArray (                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ht_ConstIterator const* const*  ppIterators,
      Size                              iteratorCount
  ) noexcept -> Size;

  /// \brief Function used to clear the current contents and copy the data from a received hash table.
  /// \tparam __CopyFunction is the type of the copy functor to be used
  /// \param [in] hashTable : __HashTable cref = Constant Reference to the hash table to copy data from
  /// \param [in] copyFunction : __CopyFunction cref = Constant Reference to the copy functor to initialize the new nodes with
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  template <
      typename __CopyFunction     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > auto __ht_copy (                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __HashTable const&    table,
      __CopyFunction const& copyFunction
  ) noexcept(false) -> void;

  /// \brief Function used to ONLY copy the data from a received hash table.
  /// \tparam __CopyFunction is the type of the copy functor to be used
  /// \param [in] hashTable : __HashTable cref = Constant Reference to the hash table to copy data from
  /// \param [in] copyFunction : __CopyFunction cref = Constant Reference to the copy functor to initialize the new nodes with
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  template <
      typename __CopyFunction     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > auto __ht_copyCleared (           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __HashTable const&    table,
      __CopyFunction const& copyFunction
  ) noexcept(false) -> void;

  /// \brief Function used to clear the current contents and move the data from a received hash table.
  /// \param [in, out] hashTable : __HashTable mref = Move Reference to the hash table to acquire and release the data from
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ht_move (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __HashTable&& table
  ) noexcept -> void;

  /// \brief Function used to ONLY move the data from a received hash table.
  /// \param [in, out] hashTable : __HashTable mref = Move Reference to the hash table to acquire and release the data from
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_cpplang_NonConstConstexprMemberFunction auto __ht_moveCleared (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __HashTable&& table
  ) noexcept -> void;

  /// \brief Function used to acquire an iterator to the node identified by given key. Will return end() if key does not exist in any node
  /// \param [in] key : __KeyType cref = Constant Reference to a key to be used to find the desired node
  /// \exceptsafe
  /// \return __ht_Iterator = Mutable Iterator to requested node with given key. end() if key does not exist
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard auto __ht_findIterator ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const& key
  ) noexcept -> __ht_Iterator;

  /// \brief Function used to acquire a const iterator to the node identified by given key. Will return cend() if key does not exist in any node
  /// \param [in] key : __KeyType cref = Constant Reference to a key to be used to find the desired node
  /// \exceptsafe
  /// \return __ht_ConstIterator = Immutable Iterator to requested node with given key. cend() if key does not exist
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard auto __ht_findIteratorConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const& key
  ) const noexcept -> __ht_ConstIterator;

  /// \brief Function used to compare the current hash table to a given hash table
  /// \param [in] table : __HashTable cref = Constant Reference to a hash table to compare the current one to
  /// \exceptsafe
  /// \return bool = true if tables contain equal content, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __ht_equals (                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __HashTable const& table
  ) const noexcept -> bool;

private:
  /// \typedef Alias for a bucket node type. Uses standard unidirectional node
  /// \private
  using __NodeType    = cds::__hidden::__impl::__UnidirectionalNode <__ElementType>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Number of allocated buckets
  Size                                  _bucketCount    {0u};

  /// \brief Number of total enclosed element count
  Size                                  _size           {0u};

  /// \brief Pointer to the bucket array.
  __NodeType**                          _pBucketArray   {nullptr};

  /// \brief The Key Hasher. Functor object, preferably, no address allocated.
  __CDS_NoUniqueAddress __KeyHasher     _hasher;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief The Rehash Policy. Functor object, preferably, no address allocated.
  __CDS_NoUniqueAddress __RehashPolicy  _rehash;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to rehash the hash table - increase the bucket buffer and relocate all newly misplaced nodes ( since remainder class value will increase )
  /// \param [in] bucketCount : Size = next number of buckets determined by the rehash policy
  /// \param [in] hashValueOfNewNode : Size = the hash value of the node that was inserted prior to rehash trigger.
  /// \param [in] pNewEmptyNode : __NodeType cptr = Address to the immutable new, uninitialized node. Used to identify said node, as it is not to be directly hashed.
  /// The hashValueOfNewNode value should be used
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __ht_rehash (                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      Size              bucketCount,
      Size              hashValueOfNewNode,
      __NodeType const* pNewEmptyNode
  ) noexcept(false) -> void;

  /// \brief Function used to relocate a node to a different given bucket. Used in rehashing
  /// \param [in, out] pBucket : __NodeType ptr ptr = Address to the head of the list ( therefore, address as well ) to emplace the node in
  /// \param [in] pNode : __NodeType ptr = Address to the node to be emplaced in the bucket
  /// \exceptsafe
  /// \static
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  static auto __ht_rehashEmplace (       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __NodeType**  pBucket,
      __NodeType*   pNode
  ) noexcept -> void;

  /// \brief Function used to acquire the mutable bucket at the given hash value. It will safely truncate the hash value to the current bucket count, which is also called the 'remainder class'
  /// \param [in] hash : Size = the hash used to identify intended bucket to be acquired
  /// \exceptsafe
  /// \return __NodeType ptr ref = Reference to the acquired bucket ( therefore address )
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ht_bucket (                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      Size hash
  ) noexcept -> __NodeType*&;

  /// \brief Function used to acquire the immutable bucket at the given hash value. It will safely truncate the hash value to the current bucket count, which is also called the 'remainder class'
  /// \param [in] hash : Size = the hash used to identify intended bucket to be acquired
  /// \exceptsafe
  /// \return __NodeType ptr cref = Constant Reference to the acquired bucket ( therefore address )
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_NoDiscard __CDS_MaybeUnused constexpr auto __ht_bucket (                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      Size hash
  ) const noexcept -> __NodeType*const&;

  /// \brief Function used to allocate a requested number of buckets. It will keep the current existing contents, but not rehash any elements
  /// \param [in] bucketCount : Size = the number of requested buckets
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __ht_allocateBuckets (                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      Size bucketCount
  ) noexcept(false) -> void;

  /// \brief Function used to free the bucket array. It will NOT clear the buckets before
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __ht_freeBuckets () noexcept -> void;                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to allocate memory for a new node. It will NOT initialize the __ElementType data
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __NodeType ptr = Address to the newly created node
  /// \static
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_NoDiscard static auto __ht_allocateNode () noexcept(false) -> __NodeType*;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to free the memory used by a node, including destroying the __ElementType data prior to free of memory
  /// \param [in] pNode : __NodeType ptr = Address to the node to be freed
  /// \exceptsafe
  /// \static
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  static auto __ht_freeNode (                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __NodeType* pNode
  ) noexcept -> void;

  /// \brief Function used to remove a node based on the bucket index, the node itself and the node before it, if applicable
  /// \param [in] pPreviousNode : __NodeType cptr = Address to the immutable node previous to the removed node
  /// \param [in] pCurrentNode : __NodeType cptr = Address to the immutable node to be removed
  /// \param [in] bucketIndex : Size = index of the bucket to remove the node from. Used if 'pPreviousNode' is null, to remove the head node
  /// \exceptsafe
  /// \return bool = true if a node was removed, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ht_removeNode (                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __NodeType const* pPreviousNode,
      __NodeType const* pCurrentNode,
      Size              bucketIndex
  ) noexcept -> bool;
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_HASH_TABLE_HPP__


namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// This is outside of the include guards, but with reasoning.
/// Special include guards apply to the dispatchers, as there is no reason to generate dispatchers that will not be used
/// ( i.e. including only HashSet should not require an inclusion of MapServerDispatcher )
/// Therefore, if both hash table AND set server dispatcher exist, generate set dispatcher
/// - same for map

#if defined (__CDS_SHARED_SET_SERVER_DISPATCHER_HPP__) && !defined (__CDS_SHARED_HASH_TABLE_SET_SERVER_DISPATCHER_HPP__) && defined (__CDS_SHARED_HASH_TABLE_HPP__)
#define __CDS_SHARED_HASH_TABLE_SET_SERVER_DISPATCHER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename                                                             __ServerType       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__SetDispatcher :
    public __SetServerDispatcher <
        __ServerType, __HashTable, __ElementType,
        HashTableIterator <__ElementType const>, HashTableIterator <__ElementType const>,
        &__HashTable::__ht_cbegin, &__HashTable::__ht_cend,
        &__HashTable::__ht_new,
        &__HashTable::__ht_removeIteratorConst, &__HashTable::__ht_removeConstIteratorArray,
        &__HashTable::__ht_findIteratorConst
    > {};

#endif


#if defined (__CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__) && !defined (__CDS_SHARED_HASH_TABLE_SERVER_DISPATCHER_HPP__) && defined (__CDS_SHARED_HASH_TABLE_HPP__)
#define __CDS_SHARED_HASH_TABLE_SERVER_DISPATCHER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename                                                            __ServerType        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __HashTable <
    __ElementType,
    __KeyType,
    __KeyHasher,
    __RehashPolicy,
    __keyExtractor,
    __keyComparator,
    __nodeDestructor
>::__MapDispatcher :
    public __MapServerDispatcher <
        __ServerType, __HashTable, __ElementType, __KeyType,
        HashTableIterator <__ElementType>, HashTableIterator <__ElementType const>,
        HashTableIterator <__ElementType>, HashTableIterator <__ElementType const>,
        &__HashTable::__ht_begin, &__HashTable::__ht_end,
        &__HashTable::__ht_cbegin, &__HashTable::__ht_cend,
        &__HashTable::__ht_new,
        &__HashTable::__ht_removeIterator, &__HashTable::__ht_removeIteratorConst,
        &__HashTable::__ht_removeIteratorArray, &__HashTable::__ht_removeConstIteratorArray,
        &__HashTable::__ht_findIterator, &__HashTable::__ht_findIteratorConst
    > {};

#endif

} // namespace __impl
} // namespace __hidden
} // namespace cds

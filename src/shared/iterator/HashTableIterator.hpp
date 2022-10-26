/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Partial pre-Declaration of __HashTable, as it requires private values
             * @tparam __ElementType is the type of the node data stored in the hash table
             * @tparam __KeyType is the key type of the hash table
             *
             * @test Suite: N/A, Group: N/A, Test Cases: N/A
             * @namespace cds :: __hidden :: __impl
             */
            template <
                    typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename,
                    typename,
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >,
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >,
                    functional :: ConsumerFunction < __ElementType & >
            > class __HashTable;            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        } /* namespace __impl */
    } /* namespace __hidden */

    /**
     * @brief Hash Table Iterator, similar to Unidirectional Node Iterator, with the addition of bucket concept.
     * Used by HashMap - begin/end
     * @tparam __ElementType is the type of the enclosed element.
     * @implements ForwardIterator
     *
     * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class HashTableIterator : public meta :: ForwardIterator {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Pre-Declaration of __HashTable, as it requires private values
         * @tparam __TElementType is the type of the node data stored in the hash table
         * @tparam __KeyType is the key type of the hash table
         * @tparam __KeyHasher is the type of the key Hasher
         * @tparam __RehashPolicy is the type of the Rehash Policy object
         * @tparam __keyExtractor is the function used to extract the key value from a node element type
         * @tparam __keyComparator is the function used to compare equality for two keys
         * @tparam __nodeDestructor is the function used to clear a node's element type
         * @test Not Applicable.
         * @namespace cds :: __hidden :: __impl
         */
        template <
                typename                                                                    __TElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > friend class cds :: __hidden :: __impl :: __HashTable;                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the BaseIterator Node Type. Buckets are composed of Nodes
         * @private
         */
        using DataNode = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Current Bucket Index in the Bucket Array
         * @private
         */
        Size        _bucketIndex    { 0ULL };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Current Bucket Count, size of the Bucket Array
         * @private
         */
        Size        _bucketCount    { 0ULL };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of current Node in the current bucket
         * @private
         */
        DataNode  * _pCurrentNode   { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of previous Node in the current bucket
         * @private
         */
        DataNode  * _pPreviousNode  { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of the Bucket List
         * @private
         */
        DataNode ** _pListArray     { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to advance to the next node. If next node is end of bucket list, advance to next bucket
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @private
         */
        __CDS_cpplang_ConstexprConditioned auto advanceBucket () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr HashTableIterator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pListArray : DataNode ptr ptr = address to a list of addresses of the buckets
         * @param [in] bucketCount : Size = the size of the address list of buckets
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @pulbic
         */
        __CDS_cpplang_ConstexprConditioned HashTableIterator (
                DataNode ** pListArray,
                Size        bucketCount
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pListArray : DataNode ptr ptr = address to a list of addresses of the buckets
         * @param [in] bucketCount : Size = the size of the address list of buckets
         * @param [in] pCurrentNode : DataNode ptr = the address of the initial current Node
         * @param [in] pPreviousNode : DataNode ptr = the address of the initial previous Node
         * @param [in] bucketIndex : Size = index of the initial bucket Index
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr HashTableIterator (
                DataNode ** pListArray,
                Size        bucketCount,
                DataNode  * pCurrentNode,
                DataNode  * pPreviousNode,
                Size        bucketIndex
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : HashTableIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr HashTableIterator (
                HashTableIterator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : HashTableIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr HashTableIterator (
                HashTableIterator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        ~HashTableIterator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : HashTableIterator cref = Constant Reference to an iterator to copy the values value from
         * @exceptsafe
         * @return HashTableIterator ref = Reference to the modified iterator
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(*-copy-assignment-signature, misc-unconventional-assign-operator) */
                HashTableIterator const & iterator
        ) noexcept -> HashTableIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : HashTableIterator mref = Move Reference to an iterator to move the values value from
         * @exceptsafe
         * @return HashTableIterator ref = Reference to the modified iterator
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(*-copy-assignment-signature, misc-unconventional-assign-operator) */
                HashTableIterator && iterator
        ) noexcept -> HashTableIterator &;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the bucket list of the iterator
         * @exceptsafe
         * @return DataNode ptr ptr = Address to the Address List
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto listArray () const noexcept -> DataNode **; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the bucket count of the bucket list
         * @exceptsafe
         * @return Size = the number of elements in the bucket list
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto bucketCount () const noexcept -> Size;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the bucket index in the bucket list
         * @exceptsafe
         * @return Size = the index of the currently used bucket
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto bucketIndex () const noexcept -> Size;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the address of the current node
         * @exceptsafe
         * @return DataNode ptr = Address of the current node
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto currentNode () const noexcept -> DataNode *;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the address of the previous node
         * @exceptsafe
         * @return DataNode ptr = Address of the previous node
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto previousNode () const noexcept -> DataNode *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Increment Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return HashTableIterator ref = Reference to the modified iterator
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> HashTableIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return HashTableIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> HashTableIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the current value the iterator is indicating to
         * @exceptsafe
         * @return __ElementType ref = Reference to the element the address is indicating to
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the address of the value the iterator is indicating to
         * @exceptsafe
         * @return __ElementType ptr = Pointer to the element the address is indicating to
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : HashTableIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                HashTableIterator const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : HashTableIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                HashTableIterator const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Validity function, bool cast.
         * @exceptsafe
         * @return bool = true if current node is not null, false otherwise
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, MTest Cases: All
         * @public
         */
        __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
    };


    /**
     * @brief Hash Table Const Iterator, similar to Unidirectional Node Const Iterator, with the addition of bucket concept.
     * Used by HashSet, HashMap - begin/end/cbegin/cend
     * @tparam __ElementType is the type of the enclosed element.
     * @implements ForwardIterator
     *
     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class HashTableConstIterator : public meta :: ForwardIterator {

    private:
        /**
         * @brief Pre-Declaration of __HashTable, as it requires private values
         * @tparam __TElementType is the type of the node data stored in the hash table
         * @tparam __KeyType is the key type of the hash table
         * @tparam __KeyHasher is the type of the key Hasher
         * @tparam __RehashPolicy is the type of the Rehash Policy object
         * @tparam __keyExtractor is the function used to extract the key value from a node element type
         * @tparam __keyComparator is the function used to compare equality for two keys
         * @tparam __nodeDestructor is the function used to clear a node's element type
         * @test Not Applicable.
         * @namespace cds :: __hidden :: __impl
         */
        template <
                typename                                                                    __TElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                functional :: MapperFunction < __KeyType const &, __TElementType const & >  __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                functional :: ConsumerFunction < __TElementType & >                         __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > friend class cds :: __hidden :: __impl :: __HashTable;                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the BaseIterator Node Type. Buckets are composed of Nodes
         * @private
         */
        using DataNode = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Current Bucket Index in the Bucket Array
         * @private
         */
        Size                        _bucketIndex    { 0ULL };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Current Bucket Count, size of the Bucket Array
         * @private
         */
        Size                        _bucketCount    { 0ULL };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of current Node in the current bucket
         * @private
         */
        DataNode            const * _pCurrentNode   { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of previous Node in the current bucket
         * @private
         */
        DataNode            const * _pPreviousNode  { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of the Bucket List
         * @private
         */
        DataNode    const * const * _pListArray     { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to advance to the next node. If next node is end of bucket list, advance to next bucket
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @private
         */
        __CDS_cpplang_ConstexprConditioned auto advanceBucket () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr HashTableConstIterator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pListArray : DataNode cptr cptr = address to an immutable list of addresses of the immutable buckets
         * @param [in] bucketCount : Size = the size of the address list of buckets
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @pulbic
         */
        __CDS_cpplang_ConstexprConditioned HashTableConstIterator (
                DataNode    const * const * pListArray,
                Size                        bucketCount
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pListArray : DataNode cptr cptr = address to an immutable list of addresses of the immutable buckets
         * @param [in] bucketCount : Size = the size of the address list of buckets
         * @param [in] pCurrentNode : DataNode cptr = the address of the initial immutable current Node
         * @param [in] pPreviousNode : DataNode cptr = the address of the initial immutable previous Node
         * @param [in] bucketIndex : Size = index of the initial bucket Index
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_ConstexprConditioned HashTableConstIterator (
                DataNode    const * const * pListArray,
                Size                        bucketCount,
                DataNode            const * pCurrentNode,
                DataNode            const * pPreviousNode,
                Size                        bucketIndex
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : HashTableConstIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr HashTableConstIterator (
                HashTableConstIterator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : HashTableConstIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr HashTableConstIterator (
                HashTableConstIterator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        ~HashTableConstIterator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : HashTableConstIterator cref = Constant Reference to an iterator to copy the values value from
         * @exceptsafe
         * @return HashTableConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(*-copy-assignment-signature, misc-unconventional-assign-operator) */
                HashTableConstIterator const & iterator
        ) noexcept -> HashTableConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : HashTableConstIterator mref = Move Reference to an iterator to move the values value from
         * @exceptsafe
         * @return HashTableConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(*-copy-assignment-signature, misc-unconventional-assign-operator) */
                HashTableConstIterator && iterator
        ) noexcept -> HashTableConstIterator &;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the bucket list of the iterator
         * @exceptsafe
         * @return DataNode cptr cptr = Address to the immutable List of immutable addresses to buckets
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto listArray () const noexcept -> DataNode const * const *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the bucket count of the bucket list
         * @exceptsafe
         * @return Size = the number of elements in the bucket list
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto bucketCount () const noexcept -> Size;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the bucket index in the bucket list
         * @exceptsafe
         * @return Size = the index of the currently used bucket
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto bucketIndex () const noexcept -> Size;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the address of the current node
         * @exceptsafe
         * @return DataNode ptr = Address of the immutable current node
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto currentNode () const noexcept -> DataNode const *;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the address of the previous node
         * @exceptsafe
         * @return DataNode cptr = Address of the immutable previous node
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @private
         */
        __CDS_NoDiscard __CDS_MaybeUnused constexpr auto previousNode () const noexcept -> DataNode const *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Increment Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return HashTableConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> HashTableConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return HashTableConstIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> HashTableConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the current value the iterator is indicating to
         * @exceptsafe
         * @return __ElementType cref = Constant Reference to the element the address is indicating to
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType const &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the address of the value the iterator is indicating to
         * @exceptsafe
         * @return __ElementType cptr = Pointer to the immutable element the address is indicating to
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType const *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : HashTableConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                HashTableConstIterator const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : HashTableConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                HashTableConstIterator const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Validity function, bool cast.
         * @exceptsafe
         * @return bool = true if current node is not null, false otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
    };

} /* namespace cds */

#endif /* __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__ */

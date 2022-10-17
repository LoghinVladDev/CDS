/*
 * Created by loghin on 17/07/22.
 */

#ifndef __CDS_SHARED_NODE_ITERATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_NODE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "IteratorModel.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Partial Pre-Declaration of __SingleLinkedList, as it requires private values
             * @tparam __ElementType is the type of the node data stored in the hash table
             *
             * @test Suite: N/A, Group: N/A, Test Cases: N/A
             * @namespace cds :: __hidden :: __impl
             */
            template <
                    typename __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: utility :: ComparisonFunction < __ElementType >
            > class __SingleLinkedList;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            /**
             * @brief Partial Pre-Declaration of __DoubleLinkedList, as it requires private values
             * @tparam __ElementType is the type of the node data stored in the hash table
             *
             * @test Suite: N/A, Group: N/A, Test Cases: N/A
             * @namespace cds :: __hidden :: __impl
             */
            template <
                    typename __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: utility :: ComparisonFunction < __ElementType >
            > class __DoubleLinkedList;      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        } /* namespace __impl */
    } /* namespace __hidden */


    /**
     * @brief Unidirectional Node Iterator. Parses nodes until a node is null
     * Used by LinkedHashMap - begin/end
     * @tparam __ElementType is the type of the enclosed element.
     * @implements ForwardIterator
     *
     * @test Suite: TBA, Group: TBA, Test Cases: TBA
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class UnidirectionalNodeIterator : public meta :: ForwardIterator {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Partial Pre-Declaration of __SingleLinkedList, as it requires private values
         * @tparam __ElementType is the type of the node data stored in the hash table
         *
         * @test Suite: N/A, Group: N/A, Test Cases: N/A
         * @namespace cds :: __hidden :: __impl
         */
        template <
                typename __TElementType,                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: utility :: ComparisonFunction < __TElementType >
        > friend class cds :: __hidden :: __impl :: __SingleLinkedList;     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @private
         */
        using ElementType = __ElementType;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the Node Type.
         * @private
         */
        using Node = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of current Node in the list
         * @private
         */
        Node * _pCurrentNode    { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of previous Node in the list
         * @private
         */
        Node * _pPreviousNode   { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr UnidirectionalNodeIterator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pPreviousNode : DataNode ptr = address to the node previous to the node containing the current element
         * @param [in] pCurrentNode : DataNode ptr = address of the node containing the current value
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @pulbic
         */
        __CDS_MaybeUnused constexpr UnidirectionalNodeIterator (
                Node * pPreviousNode,
                Node * pCurrentNode
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : UnidirectionalNodeIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr UnidirectionalNodeIterator (
                UnidirectionalNodeIterator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : UnidirectionalNodeIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr UnidirectionalNodeIterator (
                UnidirectionalNodeIterator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        ~UnidirectionalNodeIterator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : UnidirectionalNodeIterator cref = Constant Reference to an iterator to copy the values value from
         * @exceptsafe
         * @return UnidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                UnidirectionalNodeIterator const & iterator
        ) noexcept -> UnidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : UnidirectionalNodeIterator mref = Move Reference to an iterator to move the values value from
         * @exceptsafe
         * @return UnidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                UnidirectionalNodeIterator && iterator
        ) noexcept -> UnidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the current value the iterator is indicating to
         * @exceptsafe
         * @return __ElementType ref = Reference to the element the address is indicating to
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
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
         * @brief Equality Comparison Operator
         * @param [in] iterator : UnidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                UnidirectionalNodeIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : UnidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                UnidirectionalNodeIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Increment Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return UnidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> UnidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return UnidirectionalNodeIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> UnidirectionalNodeIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Validity function, bool cast.
         * @exceptsafe
         * @return bool = true if current node is not null, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
    };


    /**
     * @brief Unidirectional Node Const Iterator. Parses nodes until a node is null
     * Used by LinkedHashSet, LinkedHashMap - begin/end/cbegin/cend
     * @tparam __ElementType is the type of the enclosed element.
     * @implements ForwardIterator
     *
     * @test Suite: TBA, Group: TBA, Test Cases: TBA
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class UnidirectionalNodeConstIterator : public meta :: ForwardIterator {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Partial Pre-Declaration of __SingleLinkedList, as it requires private values
         * @tparam __ElementType is the type of the node data stored in the hash table
         *
         * @test Suite: N/A, Group: N/A, Test Cases: N/A
         * @namespace cds :: __hidden :: __impl
         */
        template <
                typename __TElementType,                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: utility :: ComparisonFunction < __TElementType >
        > friend class cds :: __hidden :: __impl :: __SingleLinkedList; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @private
         */
        using ElementType = __ElementType;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the Node Type.
         * @private
         */
        using Node = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of current Node in the list
         * @private
         */
        Node const * _pCurrentNode    { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of previous Node in the list
         * @private
         */
        Node const * _pPreviousNode   { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr UnidirectionalNodeConstIterator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pPreviousNode : DataNode cptr = address to the immutable node previous to the node containing the current element
         * @param [in] pCurrentNode : DataNode cptr = address of the immutable node containing the current value
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @pulbic
         */
        __CDS_MaybeUnused constexpr UnidirectionalNodeConstIterator (
                Node const * pPreviousNode,
                Node const * pCurrentNode
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : UnidirectionalNodeConstIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr UnidirectionalNodeConstIterator (
                UnidirectionalNodeConstIterator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : UnidirectionalNodeConstIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr UnidirectionalNodeConstIterator (
                UnidirectionalNodeConstIterator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        ~UnidirectionalNodeConstIterator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : UnidirectionalNodeConstIterator cref = Constant Reference to an iterator to copy the values value from
         * @exceptsafe
         * @return UnidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                UnidirectionalNodeConstIterator const & iterator
        ) noexcept -> UnidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : UnidirectionalNodeConstIterator mref = Move Reference to an iterator to move the values value from
         * @exceptsafe
         * @return UnidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                UnidirectionalNodeConstIterator && iterator
        ) noexcept -> UnidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the current value the iterator is indicating to
         * @exceptsafe
         * @return __ElementType cref = Constant Reference to the element the address is indicating to
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
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
         * @brief Equality Comparison Operator
         * @param [in] iterator : UnidirectionalNodeConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                UnidirectionalNodeConstIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : UnidirectionalNodeConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                UnidirectionalNodeConstIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Increment Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return UnidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> UnidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return UnidirectionalNodeConstIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> UnidirectionalNodeConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Validity function, bool cast.
         * @exceptsafe
         * @return bool = true if current node is not null, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
    };


    /**
     * @brief Abstract Bidirectional Node Iterator. Parses nodes until a node is null, direction-oblivious
     * @tparam __ElementType is the type of the enclosed element.
     * @implements BidirectionalIterator
     *
     * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class AbstractBidirectionalNodeIterator : public meta :: BidirectionalIterator {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Partial Pre-Declaration of __DoubleLinkedList, as it requires private values
         * @tparam __ElementType is the type of the node data stored in the hash table
         * @test Not Applicable.
         * @namespace cds :: __hidden :: __impl
         */
        template <
                typename __TElementType,                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: utility :: ComparisonFunction < __TElementType >
        > friend class cds :: __hidden :: __impl :: __DoubleLinkedList; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @public
         */
        using ElementType = __ElementType;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the Node Type.
         * @protected
         */
        using Node = cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of current Node in the list
         * @protected
         */
        Node * _pCurrentNode    { nullptr }; /* NOLINT(*-non-private-member-variables-in-classes) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of previous Node in the list
         * @protected
         */
        Node * _pPreviousNode   { nullptr }; /* NOLINT(*-non-private-member-variables-in-classes) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        constexpr AbstractBidirectionalNodeIterator () noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pPreviousNode : DataNode ptr = address to the node previous to the node containing the current element
         * @param [in] pCurrentNode : DataNode ptr = address of the node containing the current value
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        __CDS_Explicit constexpr AbstractBidirectionalNodeIterator (
                Node * pPreviousNode,
                Node * pCurrentNode
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : AbstractBidirectionalNodeIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        constexpr AbstractBidirectionalNodeIterator (
                AbstractBidirectionalNodeIterator const & iterator
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : AbstractBidirectionalNodeIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        constexpr AbstractBidirectionalNodeIterator (
                AbstractBidirectionalNodeIterator && iterator
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        ~AbstractBidirectionalNodeIterator () noexcept = default;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Assignment Copy Operator, constexpr
         * @param [in] iterator : AbstractBidirectionalNodeIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        auto operator = (
                AbstractBidirectionalNodeIterator const &
        ) noexcept -> AbstractBidirectionalNodeIterator & = default;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Assignment Move Operator, constexpr
         * @param [in, out] iterator : AbstractBidirectionalNodeIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        auto operator = (
                AbstractBidirectionalNodeIterator &&
        ) noexcept -> AbstractBidirectionalNodeIterator & = default;

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
         * @brief Equality Comparison Operator
         * @param [in] iterator : AbstractBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                AbstractBidirectionalNodeIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : AbstractBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                AbstractBidirectionalNodeIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Validity function, bool cast.
         * @exceptsafe
         * @return bool = true if current node is not null, false otherwise
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
    };


    /**
     * @brief Abstract Bidirectional Node Const Iterator. Parses nodes until a node is null, direction-oblivious
     * @tparam __ElementType is the type of the enclosed element.
     * @implements BidirectionalIterator
     *
     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class AbstractBidirectionalNodeConstIterator : public meta :: BidirectionalIterator {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Partial Pre-Declaration of __DoubleLinkedList, as it requires private values
         * @tparam __ElementType is the type of the node data stored in the hash table
         * @test Not Applicable.
         * @namespace cds :: __hidden :: __impl
         */
        template <
                typename __TElementType,                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: utility :: ComparisonFunction < __TElementType >
        > friend class cds :: __hidden :: __impl :: __DoubleLinkedList; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @public
         */
        using ElementType = __ElementType;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the Node Type.
         * @protected
         */
        using Node = cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of current Node in the list
         * @protected
         */
        Node const * _pCurrentNode    { nullptr }; /* NOLINT(*-non-private-member-variables-in-classes) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Address of previous Node in the list
         * @protected
         */
        Node const * _pPreviousNode   { nullptr }; /* NOLINT(*-non-private-member-variables-in-classes) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @protected
         */
        constexpr AbstractBidirectionalNodeConstIterator () noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pPreviousNode : DataNode cptr = address to the immutable node previous to the node containing the current element
         * @param [in] pCurrentNode : DataNode cptr = address of the immutable node containing the current value
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @protected
         */
        __CDS_Explicit constexpr AbstractBidirectionalNodeConstIterator (
                Node const * pPreviousNode,
                Node const * pCurrentNode
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : AbstractBidirectionalNodeConstIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @protected
         */
        constexpr AbstractBidirectionalNodeConstIterator (
                AbstractBidirectionalNodeConstIterator const & iterator
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : UnidirectionalNodeConstIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @protected
         */
        constexpr AbstractBidirectionalNodeConstIterator (
                AbstractBidirectionalNodeConstIterator && iterator
        ) noexcept;

    public:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @protected
         */
        ~AbstractBidirectionalNodeConstIterator () noexcept = default;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Assignment Copy Operator, constexpr
         * @param [in] iterator : AbstractBidirectionalNodeConstIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @protected
         */
        auto operator = (
                AbstractBidirectionalNodeConstIterator const &
        ) noexcept -> AbstractBidirectionalNodeConstIterator & = default;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Assignment Move Operator, constexpr
         * @param [in, out] iterator : AbstractBidirectionalNodeConstIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @protected
         */
        auto operator = (
                AbstractBidirectionalNodeConstIterator &&
        ) noexcept -> AbstractBidirectionalNodeConstIterator & = default;

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
         * @brief Equality Comparison Operator
         * @param [in] iterator : AbstractBidirectionalNodeConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : AbstractBidirectionalNodeConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
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


    /**
     * @brief Bidirectional Forward Node Iterator. Parses nodes until a node is null, front to back, by way of next
     * Used by LinkedList - begin/end
     * @tparam __ElementType is the type of the enclosed element.
     * @extends AbstractBidirectionalNodeIterator
     *
     * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class ForwardBidirectionalNodeIterator : public AbstractBidirectionalNodeIterator < __ElementType > {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @public
         */
        using ElementType = __ElementType;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @private
         */
        using typename AbstractBidirectionalNodeIterator < __ElementType > :: Node;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardBidirectionalNodeIterator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pPreviousNode : DataNode ptr = address to the node previous to the node containing the current element
         * @param [in] pCurrentNode : DataNode ptr = address of the node containing the current value
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @pulbic
         */
        __CDS_Explicit constexpr ForwardBidirectionalNodeIterator (
                Node * pPreviousNode,
                Node * pCurrentNode
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : ForwardBidirectionalNodeIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardBidirectionalNodeIterator (
                ForwardBidirectionalNodeIterator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : ForwardBidirectionalNodeIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardBidirectionalNodeIterator (
                ForwardBidirectionalNodeIterator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        ~ForwardBidirectionalNodeIterator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : ForwardBidirectionalNodeIterator cref = Constant Reference to an iterator to copy the values value from
         * @exceptsafe
         * @return ForwardBidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                ForwardBidirectionalNodeIterator const & iterator
        ) noexcept -> ForwardBidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : ForwardBidirectionalNodeIterator mref = Move Reference to an iterator to move the values value from
         * @exceptsafe
         * @return ForwardBidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                ForwardBidirectionalNodeIterator && iterator
        ) noexcept -> ForwardBidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : ForwardBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: MCTS-00001, MGroup: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                ForwardBidirectionalNodeIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : ForwardBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                ForwardBidirectionalNodeIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Increment Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return ForwardBidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardBidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return ForwardBidirectionalNodeIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardBidirectionalNodeIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Decrement Operator. Will advance backward one position and then return
         * @exceptsafe
         * @return ForwardBidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardBidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance backward the current one
         * @exceptsafe
         * @return ForwardBidirectionalNodeIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardBidirectionalNodeIterator;
    };


    /**
     * @brief Bidirectional Forward Node Const Iterator. Parses nodes until a node is null, front to back, by way of next
     * Used by LinkedList - begin/end/cbegin/cend
     * @tparam __ElementType is the type of the enclosed element.
     * @extends AbstractBidirectionalNodeConstIterator
     *
     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class ForwardBidirectionalNodeConstIterator : public AbstractBidirectionalNodeConstIterator < __ElementType > {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @public
         */
        using ElementType = __ElementType;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the Node Type.
         * @private
         */
        using typename AbstractBidirectionalNodeConstIterator < __ElementType > :: Node;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardBidirectionalNodeConstIterator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pPreviousNode : DataNode cptr = address to the immutable node previous to the node containing the current element
         * @param [in] pCurrentNode : DataNode cptr = address of the immutable node containing the current value
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @pulbic
         */
        __CDS_Explicit constexpr ForwardBidirectionalNodeConstIterator (
                Node const * pPreviousNode,
                Node const * pCurrentNode
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : ForwardBidirectionalNodeConstIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardBidirectionalNodeConstIterator (
                ForwardBidirectionalNodeConstIterator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : ForwardBidirectionalNodeConstIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardBidirectionalNodeConstIterator (
                ForwardBidirectionalNodeConstIterator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        ~ForwardBidirectionalNodeConstIterator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : ForwardBidirectionalNodeConstIterator cref = Constant Reference to an iterator to copy the values value from
         * @exceptsafe
         * @return ForwardBidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                ForwardBidirectionalNodeConstIterator const & iterator
        ) noexcept -> ForwardBidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : ForwardBidirectionalNodeConstIterator mref = Move Reference to an iterator to move the values value from
         * @exceptsafe
         * @return ForwardBidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                ForwardBidirectionalNodeConstIterator && iterator
        ) noexcept -> ForwardBidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : ForwardBidirectionalNodeConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                ForwardBidirectionalNodeConstIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : ForwardBidirectionalNodeConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                ForwardBidirectionalNodeConstIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Increment Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return ForwardBidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardBidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return ForwardBidirectionalNodeConstIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardBidirectionalNodeConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Decrement Operator. Will advance backward one position and then return
         * @exceptsafe
         * @return ForwardBidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardBidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance backward the current one
         * @exceptsafe
         * @return ForwardBidirectionalNodeConstIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardBidirectionalNodeConstIterator;
    };


    /**
     * @brief Bidirectional Forward Node Iterator. Parses nodes until a node is null, back to front, by way of previous
     * Used by LinkedList - rbegin/rend
     * @tparam __ElementType is the type of the enclosed element.
     * @extends AbstractBidirectionalNodeIterator
     *
     * @test Suite: TBA, Group: TBA, Test Cases: TBA
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class BackwardBidirectionalNodeIterator : public AbstractBidirectionalNodeIterator < __ElementType > {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @public
         */
        using ElementType = __ElementType;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @private
         */
        using typename AbstractBidirectionalNodeIterator < __ElementType > :: Node;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr BackwardBidirectionalNodeIterator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pPreviousNode : DataNode ptr = address to the node previous to the node containing the current element
         * @param [in] pCurrentNode : DataNode ptr = address of the node containing the current value
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @pulbic
         */
        __CDS_Explicit constexpr BackwardBidirectionalNodeIterator (
                Node * pPreviousNode,
                Node * pCurrentNode
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : BackwardBidirectionalNodeIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr BackwardBidirectionalNodeIterator (
                BackwardBidirectionalNodeIterator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : BackwardBidirectionalNodeIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr BackwardBidirectionalNodeIterator (
                BackwardBidirectionalNodeIterator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        ~BackwardBidirectionalNodeIterator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : BackwardBidirectionalNodeIterator cref = Constant Reference to an iterator to copy the values value from
         * @exceptsafe
         * @return BackwardBidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                BackwardBidirectionalNodeIterator const & iterator
        ) noexcept -> BackwardBidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : BackwardBidirectionalNodeIterator mref = Move Reference to an iterator to move the values value from
         * @exceptsafe
         * @return BackwardBidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                BackwardBidirectionalNodeIterator && iterator
        ) noexcept -> BackwardBidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : BackwardBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                BackwardBidirectionalNodeIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : BackwardBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                BackwardBidirectionalNodeIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Increment Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return BackwardBidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardBidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return BackwardBidirectionalNodeIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardBidirectionalNodeIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Decrement Operator. Will advance backward one position and then return
         * @exceptsafe
         * @return BackwardBidirectionalNodeIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardBidirectionalNodeIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance backward the current one
         * @exceptsafe
         * @return BackwardBidirectionalNodeIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardBidirectionalNodeIterator;
    };


    /**
     * @brief Bidirectional Backward Node Const Iterator. Parses nodes until a node is null, back to front, by way of previous
     * Used by LinkedList - rbegin/rend/crbegin/crend
     * @tparam __ElementType is the type of the enclosed element.
     * @extends AbstractBidirectionalNodeConstIterator
     *
     * @test Suite: TBA, Group: TBA, Test Cases: TBA
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class BackwardBidirectionalNodeConstIterator : public AbstractBidirectionalNodeConstIterator < __ElementType > {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the __ElementType template parameter
         * @public
         */
        using ElementType = __ElementType;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef Alias for the Node Type.
         * @private
         */
        using typename AbstractBidirectionalNodeConstIterator < __ElementType > :: Node;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr BackwardBidirectionalNodeConstIterator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pPreviousNode : DataNode cptr = address to the immutable node previous to the node containing the current element
         * @param [in] pCurrentNode : DataNode cptr = address of the immutable node containing the current value
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @pulbic
         */
        __CDS_Explicit constexpr BackwardBidirectionalNodeConstIterator (
                Node const * pPreviousNode,
                Node const * pCurrentNode
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : BackwardBidirectionalNodeConstIterator cref = Constant Reference to the iterator to acquire the values from
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr BackwardBidirectionalNodeConstIterator (
                BackwardBidirectionalNodeConstIterator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : BackwardBidirectionalNodeConstIterator mref = Move Reference to the iterator to move the values from
         * @exceptsafe
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        constexpr BackwardBidirectionalNodeConstIterator (
                BackwardBidirectionalNodeConstIterator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Implicit Destructor, constexpr
         * @exceptsafe
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        ~BackwardBidirectionalNodeConstIterator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : BackwardBidirectionalNodeConstIterator cref = Constant Reference to an iterator to copy the values value from
         * @exceptsafe
         * @return BackwardBidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                BackwardBidirectionalNodeConstIterator const & iterator
        ) noexcept -> BackwardBidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : BackwardBidirectionalNodeConstIterator mref = Move Reference to an iterator to move the values value from
         * @exceptsafe
         * @return BackwardBidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                BackwardBidirectionalNodeConstIterator && iterator
        ) noexcept -> BackwardBidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : BackwardBidirectionalNodeConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if iterators are indicating at the same node, with same previous, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                BackwardBidirectionalNodeConstIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : BackwardBidirectionalNodeConstIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = false if iterators are indicating at the same node, with same previous, true otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                BackwardBidirectionalNodeConstIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Increment Operator. Will advance backward one position and then return
         * @exceptsafe
         * @return BackwardBidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardBidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance backward the current one
         * @exceptsafe
         * @return BackwardBidirectionalNodeConstIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardBidirectionalNodeConstIterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Prefix Decrement Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return BackwardBidirectionalNodeConstIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardBidirectionalNodeConstIterator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return BackwardBidirectionalNodeConstIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardBidirectionalNodeConstIterator;
    };

} /* namespace cds */

#endif /* __CDS_SHARED_NODE_ITERATOR_HPP__ */

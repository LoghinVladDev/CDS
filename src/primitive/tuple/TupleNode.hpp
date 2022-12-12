/*
 * Created by loghin on 5/23/22.
 */

#ifndef __CDS_TUPLE_NODE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_TUPLE_NODE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Tuple;

    namespace __hidden { /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < uint32 __index, typename __CurrentType, typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __TypeAt { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                using Type = typename __TypeAt < __index - 1, __TypePack ... > :: Type;
            };

            template < typename __CurrentType, typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __TypeAt < 0, __CurrentType, __TypePack ... > {
                using Type = __CurrentType;
            };

            template < uint32 __index, typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __TupleNode { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            public:
                constexpr auto operator == (
                        __TupleNode const &
                ) const noexcept -> bool;

                __CDS_NoDiscard constexpr auto hash () const noexcept -> Index;
            };

            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __TupleNode < __index, __CurrentType, __RemainingTypes ... > : public __TupleNode < __index + 1, __RemainingTypes ... > {

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                __CurrentType data;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                __TupleNode () noexcept = default;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CurrentConstructorType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                explicit __TupleNode (
                        __CurrentConstructorType && currentArgument
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < typename __CurrentConstructorType, typename ... __RemainingConstructorTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                explicit __TupleNode (
                        __CurrentConstructorType      &&     currentArgument,
                        __RemainingConstructorTypes   && ... remainingArguments
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex == __index > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> __CurrentType &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex != __index > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> typename __hidden :: __impl :: __TypeAt < __requestedIndex - __index, __CurrentType, __RemainingTypes ... > :: Type &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex == __index > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr auto get () const noexcept -> __CurrentType const &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex != __index > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                constexpr auto get () const noexcept -> typename __hidden :: __impl :: __TypeAt < __requestedIndex - __index, __CurrentType, __RemainingTypes ... > :: Type const &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator == (
                        __TupleNode const & node
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto operator != (
                        __TupleNode const & node
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < uint32 __size = sizeof ... ( __RemainingTypes ), cds :: meta :: EnableIf < __size == 0 > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto toString (
                        std :: ostream & out
                ) const noexcept -> void;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                template < uint32 __size = sizeof ... ( __RemainingTypes ), cds :: meta :: EnableIf < __size != 0 > = 0 > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto toString (
                        std :: ostream & out
                ) const noexcept -> void;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                auto hash () const noexcept -> Index;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_TUPLE_NODE_HPP__ */

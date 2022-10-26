//
// Created by loghin on 5/23/22.
//

#ifndef __CDS_TUPLE_NODE_HPP__
#define __CDS_TUPLE_NODE_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
    class Tuple;

    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < uint32 __index, typename __CurrentType, typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
            struct __TypeAt { // NOLINT(bugprone-reserved-identifier)
                using Type = typename __TypeAt < __index - 1, __TypePack ... > :: Type;
            };

            template < typename __CurrentType, typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
            struct __TypeAt < 0, __CurrentType, __TypePack ... > {
                using Type = __CurrentType;
            };

            template < uint32 __index, typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
            class __TupleNode { // NOLINT(bugprone-reserved-identifier)
            public:
                constexpr auto operator == (
                        __TupleNode const &
                ) const noexcept -> bool;

                __CDS_NoDiscard constexpr auto hash () const noexcept -> Index;
            };

            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > // NOLINT(bugprone-reserved-identifier)
            class __TupleNode < __index, __CurrentType, __RemainingTypes ... > : public __TupleNode < __index + 1, __RemainingTypes ... > {
            private:
                __CurrentType data;

            public:
                __TupleNode () noexcept = default;

            public:
                template < typename __CurrentConstructorType > // NOLINT(bugprone-reserved-identifier)
                explicit __TupleNode (
                        __CurrentConstructorType && currentArgument
                ) noexcept;

            public:
                template < typename __CurrentConstructorType, typename ... __RemainingConstructorTypes > // NOLINT(bugprone-reserved-identifier)
                explicit __TupleNode (
                        __CurrentConstructorType      &&     currentArgument,
                        __RemainingConstructorTypes   && ... remainingArguments
                ) noexcept;

            public:
                template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex == __index > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> __CurrentType &;

            public:
                template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex != __index > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> typename __hidden :: __impl :: __TypeAt < __requestedIndex - __index, __CurrentType, __RemainingTypes ... > :: Type &;

            public:
                template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex == __index > = 0 > // NOLINT(bugprone-reserved-identifier)
                constexpr auto get () const noexcept -> __CurrentType const &;

            public:
                template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex != __index > = 0 > // NOLINT(bugprone-reserved-identifier)
                constexpr auto get () const noexcept -> typename __hidden :: __impl :: __TypeAt < __requestedIndex - __index, __CurrentType, __RemainingTypes ... > :: Type const &;

            public:
                auto operator == (
                        __TupleNode const & node
                ) const noexcept -> bool;

            public:
                auto operator != (
                        __TupleNode const & node
                ) const noexcept -> bool;

            public:
                template < uint32 __size = sizeof ... ( __RemainingTypes ), cds :: meta :: EnableIf < __size == 0 > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto toString (
                        std :: ostream & out
                ) const noexcept -> void;

            public:
                template < uint32 __size = sizeof ... ( __RemainingTypes ), cds :: meta :: EnableIf < __size != 0 > = 0 > // NOLINT(bugprone-reserved-identifier)
                auto toString (
                        std :: ostream & out
                ) const noexcept -> void;

            public:
                auto hash () const noexcept -> Index;
            };

        }
    }

}

#endif // __CDS_TUPLE_NODE_HPP__

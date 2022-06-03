//
// Created by loghin on 5/23/22.
//

#ifndef __CDS_EX_TUPLE_NODE_HPP__
#define __CDS_EX_TUPLE_NODE_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename ... TypePack >
        class Tuple;

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < uint32 index, typename CurrentType, typename ... TypePack >
                struct TypeAt {
                    using Type = typename TypeAt < index - 1, TypePack ... > :: Type;
                };

                template < typename CurrentType, typename ... TypePack >
                struct TypeAt < 0, CurrentType, TypePack ... > {
                    using Type = CurrentType;
                };

                template < uint32 index, typename ... TypePack >
                class TupleNode {
                public:
                    constexpr auto operator == ( TupleNode const & ) const noexcept -> bool;
                    __CDS_NoDiscard constexpr auto hash () const noexcept -> Index;
                };

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                class TupleNode < index, CurrentType, RemainingTypes ... > : public TupleNode < index + 1, RemainingTypes ... > {
                private:
                    CurrentType data;

                public:
                    TupleNode () noexcept = default;

                public:
                    template < typename CurrentConstructorType >
                    explicit TupleNode (
                            CurrentConstructorType &&
                    ) noexcept;

                public:
                    template < typename CurrentConstructorType, typename ... RemainingConstructorTypes >
                    explicit TupleNode (
                            CurrentConstructorType      &&,
                            RemainingConstructorTypes   && ...
                    ) noexcept;

                public:
                    template < uint32 requestedIndex, meta :: EnableIf < requestedIndex == index > = 0 >
                    __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> CurrentType &;

                public:
                    template < uint32 requestedIndex, meta :: EnableIf < requestedIndex != index > = 0 >
                    __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> typename hidden :: impl :: TypeAt < requestedIndex - index, CurrentType, RemainingTypes ... > :: Type &;

                public:
                    template < uint32 requestedIndex, meta :: EnableIf < requestedIndex == index > = 0 >
                    constexpr auto get () const noexcept -> CurrentType const &;

                public:
                    template < uint32 requestedIndex, meta :: EnableIf < requestedIndex != index > = 0 >
                    constexpr auto get () const noexcept -> typename hidden :: impl :: TypeAt < requestedIndex - index, CurrentType, RemainingTypes ... > :: Type const &;

                public:
                    auto operator == ( TupleNode const & ) const noexcept -> bool;

                public:
                    auto operator != ( TupleNode const & ) const noexcept -> bool;

                public:
                    template < uint32 size = sizeof ... (RemainingTypes), meta :: EnableIf < size == 0 > = 0 >
                    auto toString ( std :: ostream & ) const noexcept -> void;

                public:
                    template < uint32 size = sizeof ... (RemainingTypes), meta :: EnableIf < size != 0 > = 0 >
                    auto toString ( std :: ostream & ) const noexcept -> void;

                public:
                    auto hash () const noexcept -> Index;
                };

            }
        }

    }
}

#endif // __CDS_EX_TUPLE_NODE_HPP__

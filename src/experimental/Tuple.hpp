//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_EX_TUPLE_HPP__
#define __CDS_EX_TUPLE_HPP__

#include <CDS/experimental/Object>
#include <CDS/experimental/meta/Base>

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
                    constexpr auto operator == ( TupleNode const & ) const noexcept -> bool { return true; }
                    constexpr auto hash () const noexcept -> Index { return 0; }
                };

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                class TupleNode < index, CurrentType, RemainingTypes ... > : public TupleNode < index + 1, RemainingTypes ... > {
                private:
                    CurrentType data;

                public:
                    TupleNode () noexcept = default;

                public:
                    template < typename CurrentConstructorType >
                    explicit TupleNode ( CurrentConstructorType && currentArgument ) noexcept :
                            data ( std :: forward < CurrentConstructorType > ( currentArgument ) ) {

                    }

                public:
                    template < typename CurrentConstructorType, typename ... RemainingConstructorTypes >
                    explicit TupleNode ( CurrentConstructorType && currentArgument, RemainingConstructorTypes && ... remainingArguments ) noexcept :
                            TupleNode < index + 1, RemainingTypes ... > ( std :: forward < RemainingConstructorTypes > ( remainingArguments ) ... ),
                            data ( std :: forward < CurrentConstructorType > ( currentArgument ) ) {

                    }

                public:
                    template < uint32 requestedIndex, EnableIf < requestedIndex == index > = 0 >
                    auto get () noexcept -> CurrentType & {
                        return this->data;
                    }

                public:
                    template < uint32 requestedIndex, EnableIf < requestedIndex != index > = 0 >
                    auto get () noexcept -> typename hidden :: impl :: TypeAt < requestedIndex - index, CurrentType, RemainingTypes ... > :: Type & {
                        return this->TupleNode < index + 1, RemainingTypes ... > :: template get < requestedIndex > ();
                    }

                public:
                    template < uint32 requestedIndex, EnableIf < requestedIndex == index > = 0 >
                    auto get () const noexcept -> CurrentType const & {
                        return this->data;
                    }

                public:
                    template < uint32 requestedIndex, EnableIf < requestedIndex != index > = 0 >
                    auto get () const noexcept -> typename hidden :: impl :: TypeAt < requestedIndex - index, CurrentType, RemainingTypes ... > :: Type const & {
                        return this->TupleNode < index + 1, RemainingTypes ... > :: template get < requestedIndex > ();
                    }

                public:
                    auto operator == ( TupleNode const & node ) const noexcept -> bool {
                        return
                                this->data == node.data &&
                                this->TupleNode < index + 1, RemainingTypes ... > :: operator == ( node );
                    }

                public:
                    auto operator != ( TupleNode const & node ) const noexcept -> bool {
                        return
                                this->data != node.data ||
                                this->TupleNode < index + 1, RemainingTypes ... > :: operator != ( node );
                    }

                public:
                    template < uint32 size = sizeof ... (RemainingTypes), EnableIf < size == 0 > = 0 >
                    auto toString ( std :: ostream & str ) const noexcept -> void {
                        str << this->data;
                    }

                public:
                    template < uint32 size = sizeof ... (RemainingTypes), EnableIf < size != 0 > = 0 >
                    auto toString ( std :: ostream & str ) const noexcept -> void {
                        str << this->data << ", ";
                        this->TupleNode < index + 1, RemainingTypes ... > :: toString ( str );
                    }

                public:
                    auto hash () const noexcept -> Index {
                        return cds :: hash ( this->data ) + this->TupleNode < index + 1, RemainingTypes ... > :: hash ();
                    }
                };

            }
        }


        template < typename ... TypePack >
        class Tuple : public Object {

        private:
            hidden :: impl :: TupleNode < 0, TypePack ... > node;

        public:
            Tuple () noexcept = default;
        public:
            Tuple ( Tuple const & ) noexcept = default;
        public:
            Tuple ( Tuple && ) noexcept = default;
        public:
            auto operator = ( Tuple const & ) noexcept -> Tuple & = default;
        public:
            auto operator = ( Tuple && ) noexcept -> Tuple & = default;

        public:
            template <
                    typename ... ConstructorTypePack,
                    EnableIf < ( sizeof ... ( ConstructorTypePack ) == sizeof ... ( TypePack ) && sizeof ... ( ConstructorTypePack ) > 1 ) > = 0
            > Tuple ( ConstructorTypePack && ... argumentPack ) noexcept : // NOLINT(google-explicit-constructor)
                    node ( std :: forward < ConstructorTypePack > ( argumentPack ) ... ) {

            }

        public:
            template <
                    typename ... ConstructorTypePack,
                    EnableIf < (
                            sizeof ... ( ConstructorTypePack ) == sizeof ... ( TypePack ) && sizeof ... ( ConstructorTypePack ) == 1 &&
                            ! isSame < ConstructorTypePack ..., Tuple > ()
                    ) > = 0
            > Tuple ( ConstructorTypePack && ... argumentPack ) noexcept : // NOLINT(google-explicit-constructor)
                    node ( std :: forward < ConstructorTypePack > ( argumentPack ) ... ) {

            }

        public:
            template < uint32 index >
            auto get () noexcept -> typename hidden :: impl :: TypeAt < index, TypePack ... > :: Type & {
                return this->node.template get < index > ();
            }

        public:
            template < uint32 index >
            auto get () const noexcept -> typename hidden :: impl :: TypeAt < index, TypePack ... > :: Type const & {
                return this->node.template get < index > ();
            }

        public:
            auto operator == ( Tuple const & tuple ) const noexcept -> bool {
                return this->node == tuple.node;
            }

            inline auto operator != ( Tuple const & tuple ) const noexcept -> bool {
                return this->node != tuple.node;
            }

        public:
            template < uint32 index >
            using TypeOf = typename hidden :: impl :: TypeAt < index, TypePack ... > :: Type;

        public:
            auto toString () const noexcept -> String override {
                std :: stringstream output;
                this->node.toString ( output << "( " );
                output << " )";
                return output.str();
            }

        public:
            auto hash () const noexcept -> Index override {
                return this->node.hash();
            }
        };

    }
}

#endif // __CDS_EX_TUPLE_HPP__

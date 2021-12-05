//
// Created by loghin on 02.10.2021.
//

#ifndef CDS_SEQUENCEPRIVATE_H
#define CDS_SEQUENCEPRIVATE_H

#include <CDS/Traits>
#include <CDS/Double>
#include <CDS/Integer>
#include <CDS/Float>
#include <CDS/Long>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace sequenceImpl {

                template < typename V, typename = void >
                struct IsArithmetic {
                    static constexpr bool Value = false;
                };

                template < typename V >
                struct IsArithmetic < V > {
                    static constexpr bool Value =
                        std::is_arithmetic < V > :: type :: value ||
                        std::is_same < V, Integer > :: value ||
                        std::is_same < V, Long > :: value ||
                        std::is_same < V, Float > :: value ||
                        std::is_same < V, Double > :: value
                    ;
                };

                template < typename C >
                struct ContainedTypeImpl {
                    using Type = RemoveReference <
                        decltype (
                            * ( * Type <
                                    typename RemoveReference < C > :: Iterator
                            > :: unsafeAddress () )
                        )
                    >;
                };

                template < typename T >
                using ContainedType = typename ContainedTypeImpl < T > :: Type;

                template < typename C >
                __CDS_MaybeUnused constexpr auto isFlattable () noexcept -> bool {
                    return std :: is_same < C, Sequence < ContainedType < C > > > :: value;
                }

                template < typename C >
                struct __CDS_MaybeUnused FlattenType {
                    using Type = ContainedType < ContainedType < C > >;
                };

                template < typename MapperType, typename C >
                constexpr auto mapToSameType () noexcept -> bool {
                    return std :: is_same <
                        RemoveReference <
                            decltype (
                                * Type <
                                        typename RemoveReference < C > :: Iterator
                                > :: unsafeAddress ()
                            )
                        >,
                            ReturnOf < MapperType >
                    > :: type :: value;
                }

                template < typename TransformerType >
                struct FlatMapDeducted {
                    using Type = RemoveReference <
                        decltype (
                            * ( * Type <
                                typename ReturnOf < TransformerType > :: Iterator
                            > :: unsafeAddress () )
                        )
                    >;
                };

                template < typename TransformerType >
                using FlatMapDeducedType = typename FlatMapDeducted < TransformerType > :: Type;

                template < typename C >
                constexpr auto containedTypeIsPair () noexcept -> bool {
                    return isPair <
                        RemoveReference <
                            decltype (
                                * ( * Type <
                                    typename RemoveReference < C > :: Iterator
                                > :: unsafeAddress () )
                            )
                        >
                    > :: type :: value;
                }

                template < typename C >
                struct ContainedTypeAsPair : pairTrait <
                    RemoveReference <
                        decltype (
                            * ( * Type <
                                typename RemoveReference < C > :: Iterator
                            > :: unsafeAddress () )
                        )
                    >
                > {

                };

                struct Windowed {

                    template < typename Transformer >
                    constexpr static auto isAbstract () noexcept -> bool {
                        return std::is_abstract <
                            RemoveConst <
                                RemoveReference <
                                    decltype (
                                        std::get < 0 > (
                                            * Type <
                                                ArgumentsOf <
                                                    Transformer
                                                >
                                            > :: unsafeAddress ()
                                        )
                                    )
                                >
                            >
                        > :: type :: value;
                    }

                    template < typename Transformer >
                    using typeIfAbstract = LinkedList <
                        typename RemoveConst <
                            RemoveReference <
                                decltype (
                                    std::get < 0 > (
                                        * Type <
                                            ArgumentsOf <
                                                Transformer
                                            >
                                        > :: unsafeAddress ()
                                    )
                                )
                            >
                        > ::ElementType
                    >;

                    template < typename Transformer >
                    using typeIfNotAbstract = RemoveConst <
                        RemoveReference <
                            decltype(
                                std::get<0>(
                                    * Type <
                                        ArgumentsOf <
                                            Transformer
                                        >
                                    > :: unsafeAddress ()
                                )
                            )
                        >
                    >;

                    template < typename ListTransformer >
                    using type =
                        TypeIf <
                            isAbstract < ListTransformer > (),
                            typeIfAbstract < ListTransformer >,
                            typeIfNotAbstract < ListTransformer >
                        >;
                };

            }
        }
    }
}

#endif //CDS_SEQUENCEPRIVATE_H

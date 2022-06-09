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
#include <CDS/experimental/Tuple>

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
                    using Type = meta :: RemoveReference <
                        decltype (
                            * ( meta :: referenceOf <
                                    typename meta :: RemoveReference < C > :: Iterator
                            > () )
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
                        meta :: RemoveReference <
                            decltype (
                                meta :: referenceOf <
                                        typename meta :: RemoveReference < C > :: Iterator
                                > ()
                            )
                        >,
                        meta :: ReturnOf < MapperType >
                    > :: type :: value;
                }

                template < typename TransformerType >
                struct FlatMapDeducted {
                    using Type = meta :: RemoveReference <
                        decltype (
                            * ( meta :: referenceOf <
                                typename meta :: ReturnOf < TransformerType > :: Iterator
                            > () )
                        )
                    >;
                };

                template < typename TransformerType >
                using FlatMapDeducedType = typename FlatMapDeducted < TransformerType > :: Type;

                template < typename C >
                constexpr auto containedTypeIsPair () noexcept -> bool {
                    return meta :: isPair <
                        meta :: RemoveReference <
                            decltype (
                                * ( meta :: referenceOf <
                                    typename meta :: RemoveReference < C > :: Iterator
                                > () )
                            )
                        >
                    > ();
                }

                template < typename C >
                struct ContainedTypeAsPair : meta :: PairTraits <
                    meta :: RemoveReference <
                        decltype (
                            * ( meta :: referenceOf <
                                typename meta :: RemoveReference < C > :: Iterator
                            > () )
                        )
                    >
                > {

                };

                struct Windowed {

                    template < typename Transformer >
                    constexpr static auto isAbstract () noexcept -> bool {
                        return std::is_abstract <
                            meta :: RemoveConst <
                                meta :: RemoveReference <
                                    decltype (
                                        meta :: valueOf <
                                            meta :: ArgumentsOf <
                                                Transformer
                                            >
                                        > ().template get < 0 > ()
                                    )
                                >
                            >
                        > :: type :: value;
                    }

                    template < typename Transformer >
                    using typeIfAbstract = LinkedList <
                        typename meta :: RemoveConst <
                            meta :: RemoveReference <
                                decltype (
                                    meta :: valueOf <
                                        meta :: ArgumentsOf <
                                            Transformer
                                        >
                                    > ().template get < 0 > ()
                                )
                            >
                        > :: ElementType
                    >;

                    template < typename Transformer >
                    using typeIfNotAbstract = meta :: RemoveConst <
                        meta :: RemoveReference <
                            decltype(
                                meta :: valueOf <
                                    meta :: ArgumentsOf <
                                        Transformer
                                    >
                                > ().template get < 0 > ()
                            )
                        >
                    >;

                    template < typename ListTransformer >
                    using type =
                        meta :: Conditional <
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

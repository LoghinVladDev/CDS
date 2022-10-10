/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_EX_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_EX_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../../../shared/collectionInternalCommunication/client/primitive/RandomInsertionPrimitiveClient.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                namespace meta {

                    template < typename __IterableType >                                                                                /* NOLINT(bugprone-reserved-identifier) */
                    using __IterableSizeAvailable __CDS_DeprecatedHint("No longer an experimental feature.") = cds :: __hidden :: __impl :: meta :: __IterableSizeAvailable < __IterableType >;    /* NOLINT(bugprone-reserved-identifier) */

                }

                template < typename __ElementType, typename __FirstConstructedArgument >                    /* NOLINT(bugprone-reserved-identifier) */
                using __ConstructExceptSpecOne __CDS_DeprecatedHint("No longer an experimental feature.") = /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ConstructExceptSpecOne < __ElementType, __FirstConstructedArgument >;


                template < typename __ElementType, typename ... __Arguments >                                       /* NOLINT(bugprone-reserved-identifier) */
                using __ConstructExceptSpecMultiple __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __ConstructExceptSpecMultiple < __ElementType, __Arguments ... >;


                template <
                        typename     __AccumulatorType,                                                 /* NOLINT(bugprone-reserved-identifier) */
                        typename ... __Types                                                            /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_DeprecatedHint("No longer an experimental feature.") auto __expansiveInsert (   /* NOLINT(bugprone-reserved-identifier) */
                        __AccumulatorType      *     pAccumulator,
                        __Types               && ... values
                ) noexcept ( false ) -> void {

                    cds :: __hidden :: __impl :: __expansiveInsert ( pAccumulator, std :: forward < __Types > ( values ) ... );
                }


                template <
                        typename __ReceiverType,                                                                        /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                         /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType                                                                           /* NOLINT(bugprone-reserved-identifier) */
                > using __RandomInsertionPrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") =   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __RandomInsertionPrimitiveClient < __ReceiverType, __ElementType, __ReturnType >;


                template <
                        typename __ReceiverType,                                                                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                                                                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType                                                                               /* NOLINT(bugprone-reserved-identifier) */
                > using __LocalRandomInsertionPrimitiveClient __CDS_DeprecatedHint("No longer an experimental feature.") =  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: __hidden :: __impl :: __LocalRandomInsertionPrimitiveClient < __ReceiverType, __ElementType, __ReturnType >;

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__ */

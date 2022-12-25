/*
 * Created by loghin on 11/1/2022.
 */

#ifndef __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType, typename __Mapper, typename __MapperResult >
            using __LazySequenceTransitionPipelineIterableServer =
                    __IterableServer <
                            __LazySequenceTransitionPipeline < __ElementType, __Mapper, __MapperResult >,
                            __MapperResult
                    >;

        }
    }
}

#endif /* __CDS_LAZY_SEQUENCE_TRANSITION_PIPELINE_CONSTRUCTS_HPP__ */

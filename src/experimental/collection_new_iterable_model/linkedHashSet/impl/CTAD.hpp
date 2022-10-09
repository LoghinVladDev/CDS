/*
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_EX_LINKED_HASH_SET_CTAD_HPP__
#define __CDS_EX_LINKED_HASH_SET_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#if __CDS_cpplang_CTAD_available

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __ElementType,                                                             /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher = cds :: WrapperHasher < __ElementType, Hash < __ElementType > >  /* NOLINT(bugprone-reserved-identifier) */
        > LinkedHashSet (
                std :: initializer_list < __ElementType >
        ) -> LinkedHashSet < __ElementType, __Hasher >;

        template <
                typename __ElementType,                                                             /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher = cds :: WrapperHasher < __ElementType, Hash < __ElementType > >  /* NOLINT(bugprone-reserved-identifier) */
        > LinkedHashSet (
                __Hasher,
                std :: initializer_list < __ElementType >
        ) -> LinkedHashSet < __ElementType, __Hasher >;

    }
}

#endif

#endif /* __CDS_EX_LINKED_HASH_SET_CTAD_HPP__ */

/*
 * Created by loghin on 17/07/22.
 */

#ifndef __CDS_EX_LINKED_LIST_CTAD_HPP__
#define __CDS_EX_LINKED_LIST_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#if __CDS_cpplang_CTAD_available

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        LinkedList (
                std :: initializer_list < __ElementType >
        ) -> LinkedList < __ElementType >;

    }
}

#endif

#endif /* __CDS_EX_LINKED_LIST_CTAD_HPP__ */

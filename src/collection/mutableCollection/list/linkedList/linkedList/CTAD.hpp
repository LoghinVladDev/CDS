//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_LINKED_LIST_CTAD_HPP__
#define __CDS_LINKED_LIST_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    LinkedList (
            std :: initializer_list < __ElementType >
    ) -> LinkedList < __ElementType >;

}

#endif

#endif // __CDS_LINKED_LIST_CTAD_HPP__

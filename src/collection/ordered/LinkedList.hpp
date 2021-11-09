//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_LINKEDLIST_HPP
#define CDS_LINKEDLIST_HPP

namespace cds {

    template < typename T >
    class DoubleLinkedList;

    template < typename T >
    class SingleLinkedList;

}

#ifndef LLIST_FORCE_SLIST

namespace cds {

    template < typename T >
    using LinkedList = DoubleLinkedList < T >;

}

#else

namespace cds {

    template < typename T >
    using LinkedList = SingleLinkedList < T >;

}

#endif

#if !defined (CDS_LINKEDLIST_DOUBLEGUARD)
#define CDS_LINKEDLIST_DOUBLEGUARD

#include <CDS/SingleLinkedList>
#include <CDS/DoubleLinkedList>

#endif

#endif //CDS_LINKEDLIST_HPP

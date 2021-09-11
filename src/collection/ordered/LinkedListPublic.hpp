//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_LINKEDLISTPUBLIC_HPP
#define CDS_LINKEDLISTPUBLIC_HPP

#include "../../std-types.h"

template < typename T >
class DoubleLinkedList;

template < typename T >
class SingleLinkedList;

#ifndef LLIST_FORCE_SLIST
template < typename T >
using LinkedList = DoubleLinkedList < T >;
#else
template < typename T >
using LinkedList = SingleLinkedList < T >;
#endif


#endif //CDS_LINKEDLISTPUBLIC_HPP

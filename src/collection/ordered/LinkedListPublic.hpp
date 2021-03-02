//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_LINKEDLISTPUBLIC_HPP
#define CDS_LINKEDLISTPUBLIC_HPP

#include "../../std-types.h"

template <class T>
class DoubleLinkedList;

#ifndef LLIST_FORCE_SLIST
template <class T>
using LinkedList = DoubleLinkedList<T>;
#else

#endif


#endif //CDS_LINKEDLISTPUBLIC_HPP

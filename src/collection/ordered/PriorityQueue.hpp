//
// Created by loghin on 19.07.2021.
//

#ifndef CDS_PRIORITYQUEUE_HPP
#define CDS_PRIORITYQUEUE_HPP

#include <CDS/List>

template < typename T, typename PriorityFunction = std::less<> >
class PriorityQueue final : public List < T > {

};

#endif //CDS_PRIORITYQUEUE_HPP

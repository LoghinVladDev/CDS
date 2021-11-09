//
// Created by loghin on 08.11.2021.
//

#ifndef CDS_HASHSET_HPP
#define CDS_HASHSET_HPP

#include <CDS/Set>

namespace cds {

    template < typename T > __CDS_Requires( UniqueIdentifiable < T > )
    class HashSet : public Collection < T > {

    public:
        using ElementType               = typename Collection < T > :: ElementType;

    private:
        using ElementRef                = typename Collection < T > :: ElementRef;
        using ElementCRef               = typename Collection < T > :: ElementCRef;
        using ElementMRef               = typename Collection < T > :: ElementMRef;
        using ElementPtr                = typename Collection < T > :: ElementPtr;
        using ElementPtrRef             = typename Collection < T > :: ElementPtrRef;
        using ElementCPtr               = typename Collection < T > :: ElementCPtr;
        using InitializerList           = typename Collection < T > :: InitializerList;

    public:
        using Iterator                  = typename Collection < T > :: Iterator;
        using ConstIterator             = typename Collection < T > :: ConstIterator;

        using ReverseIterator           = typename Collection < T > :: ReverseIterator;
        using ConstReverseIterator      = typename Collection < T > :: ConstReverseIterator;

    private:
        using DelegateIterator          = typename Collection < T > :: DelegateIterator;
        using DelegateConstIterator     = typename Collection < T > :: DelegateConstIterator;




    public:

    };

}

#endif //CDS_HASHSET_HPP

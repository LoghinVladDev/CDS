//
// Created by stefan on 28.08.2022.
//

#ifndef __CDS_EX_TREE_SET_HPP__
#define __CDS_EX_TREE_SET_HPP__

#include <CDS/experimental/Set>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>

#include "../../shared/Node.hpp"

#include "shared/iterator/RedBlackTreeIterator.hpp"
#include "../../shared/impl/generalPredicates.hpp"
#include "shared/collectionInternalCommunication/server/TreeSetServerDispatcher.hpp"

#include "shared/collectionInternalCommunication/server/SetServer.hpp"

#include "shared/redBlackTree/RedBlackTree.hpp"

#include "treeSet/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType >                                                 // NOLINT(bugprone-reserved-identifier)
        class TreeSet :
                public Set < __ElementType >,
                protected __hidden :: __impl :: __TreeSetServer < __ElementType >,
                public __hidden :: __impl :: __TreeSetImplementation < __ElementType >,
                public __hidden :: __impl :: __TreeSetDispatcher < __ElementType > {

        protected:  using Implementation                = __hidden :: __impl :: __TreeSetImplementation < __ElementType >;

        public:
            TreeSet() noexcept;

        public:
            TreeSet (
                    TreeSet const & set
            ) noexcept;

        public:
            auto clear () noexcept -> void override;

        public:
            auto remove ( __ElementType const & element ) noexcept -> bool override;
        };

    }
}

#include "shared/redBlackTree/impl/RedBlackTree.hpp"

#include "shared/iterator/impl/RedBlackTreeIterator.hpp"

#include "shared/collectionInternalCommunication/server/impl/TreeSetServerDispatcher.hpp"

#include "treeSet/impl/TreeSet.hpp"

#endif //__CDS_EX_TREE_SET_HPP__

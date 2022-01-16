//
// Created by stefan on 16.01.2022.
//

#ifndef CDS_GRAPH_HPP
#define CDS_GRAPH_HPP

#include <CDS/Object>
#include <CDS/List>
#include <CDS/Pointer>


namespace cds{

    enum EdgeType {
        DEFAULT_EDGE,
        DIRECTED_EDGE,
        MULTIGRAPH
    };


    template < typename V,  EdgeType E >
    class Graph : public Object{
    private:

        /*
         *  add data structures for nodes, vertices and adjacency list
         */

    public:

        using VertexType = V;

        /// Those methods are just a prototype. Further improvements and changes will occur

        auto addEdge ( VertexType const & sourceVertex, VertexType const & destVertex )                 noexcept ( false ) -> UniquePointer < Graph >;

        auto getEdge ( VertexType const & sourceVertex, VertexType const & destVertex )                 const noexcept ( false ) -> EdgeType;

        auto containsEdge ( VertexType const & sourceVertex, VertexType const & destVertex )            const noexcept ( false ) -> bool;

        template < EdgeType T = E , EnableIf < T != MULTIGRAPH > = 0 >
        auto getAllEdgesBetween ( VertexType const & sourceVertex, VertexType const & destVertex  )     const noexcept ( false )-> UnorderedSet < EdgeType >;

        template< EdgeType T = E, EnableIf < T == MULTIGRAPH > >
        auto getAllEdgesBetween ( VertexType const & sourceVertex, VertexType const & destVertex )      const noexcept ( false ) -> List < EdgeType >;

        template < EdgeType T = E , EnableIf < T != MULTIGRAPH > = 0 >
        auto getEdgeSet ( VertexType const & sourceVertex, VertexType const & destVertex  )             const noexcept ( false )-> UnorderedSet < EdgeType >;

        template< EdgeType T = E, EnableIf < T == MULTIGRAPH > >
        auto getEdgeSet ( VertexType const & sourceVertex, VertexType const & destVertex )              const noexcept ( false ) -> List < EdgeType >;


        auto addVertex ( VertexType const & vertex )                                                    noexcept ( false ) -> UniquePointer < Graph >;

        auto getVertex ( VertexType const & vertex )                                                    noexcept ( false ) -> UniquePointer< VertexType >;

        auto containsVertex ( VertexType const & vertex )                                               const noexcept ( false ) -> bool;

        auto degreeOf (VertexType const & vertex )                                                      const noexcept ( false ) -> int;

        auto inDegreeOf (VertexType const & vertex )                                                    const noexcept ( false ) -> int;

        auto outDegreeOf (VertexType const & vertex )                                                   const noexcept ( false ) -> int;

        auto getVertexSet ( )                                                                           const noexcept ( false ) -> UnorderedSet < VertexType >;

    };

}



#endif //CDS_GRAPH_HPP

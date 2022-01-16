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

        /** returning an uniquePointer implies that a new graph is created. Perhaps returning Graph & was intended */
        auto addEdge ( VertexType const & sourceVertex, VertexType const & destVertex )                 noexcept ( false ) -> UniquePointer < Graph >;

        auto getEdge ( VertexType const & sourceVertex, VertexType const & destVertex )                 const noexcept ( false ) -> EdgeType;

        /* consider 'contains' as the base prototype, and overloading it with contains ( vertex, vertex ) and contains ( edge ) */
        auto containsEdge ( VertexType const & sourceVertex, VertexType const & destVertex )            const noexcept ( false ) -> bool;

        /** library standard uses 'allEdgesBetween' instead of 'getAllEdgesBetween', like in 'degreeOf'. Also if no other case than ALL Edges exists, consider naming 'edgesBetween' */
        template < EdgeType T = E , EnableIf < T != MULTIGRAPH > = 0 >
        auto getAllEdgesBetween ( VertexType const & sourceVertex, VertexType const & destVertex  )     const noexcept ( false )-> UnorderedSet < EdgeType >;

        template< EdgeType T = E, EnableIf < T == MULTIGRAPH > >
        auto getAllEdgesBetween ( VertexType const & sourceVertex, VertexType const & destVertex )      const noexcept ( false ) -> List < EdgeType >;

        /* if 'getEdgeSet' has the same functionality as 'getAllEdgesBetween', consider removing prototype */
        template < EdgeType T = E , EnableIf < T != MULTIGRAPH > = 0 >
        auto getEdgeSet ( VertexType const & sourceVertex, VertexType const & destVertex  )             const noexcept ( false )-> UnorderedSet < EdgeType >;

        template< EdgeType T = E, EnableIf < T == MULTIGRAPH > >
        auto getEdgeSet ( VertexType const & sourceVertex, VertexType const & destVertex )              const noexcept ( false ) -> List < EdgeType >;


        /** returning an uniquePointer implies that a new graph is created. Perhaps returning Graph & was intended */
        auto addVertex ( VertexType const & vertex )                                                    noexcept ( false ) -> UniquePointer < Graph >;

        /** returning an uniquePointer implies that a new vertex is created. Perhaps returning VertexType & was intended ( library standard ), or maybe ForeignPointer < VertexType > ( implies no new vertex is created ).
         * Also, if parameter is vertex, why get it in the first place ? */
        auto getVertex ( VertexType const & vertex )                                                    noexcept ( false ) -> UniquePointer< VertexType >;

        auto containsVertex ( VertexType const & vertex )                                               const noexcept ( false ) -> bool;

        auto degreeOf (VertexType const & vertex )                                                      const noexcept ( false ) -> int;

        auto inDegreeOf (VertexType const & vertex )                                                    const noexcept ( false ) -> int;

        auto outDegreeOf (VertexType const & vertex )                                                   const noexcept ( false ) -> int;

        /* if returned value contains all vertices of object, consider UnorderedSet < VertexType > const & */
        auto getVertexSet ( )                                                                           const noexcept ( false ) -> UnorderedSet < VertexType >;

    };

}



#endif //CDS_GRAPH_HPP

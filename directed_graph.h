//
// Created by Bogdan Iordache on 3/6/2018.
//

#ifndef DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_H
#define DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_H

#include <iostream>
#include "util_stack.h"
#include "util_vector.h"

namespace dgraph {
    class Node {
      public:
        Node(int id = -1);
        Node(const Node& rhs);
        Node& operator = (const Node& rhs);
        virtual ~Node() = default;

        int id();

        void add_direct_successor(const Node& node);
        void add_direct_predecessor(const Node& node);

        int get_in_degree() const;
        int get_out_degree() const;
      private:
        int id_;
        util::Vector< const Node& > direct_successors_;
        util::Vector< const Node& > direct_predecessors_;
    };

    class Edge {
      public:
        Edge();
        Edge(const Node& from_node, const Node& to_node);
        Edge(const Edge& rhs);
        Edge& operator = (const Edge& rhs);
        virtual ~Edge() = default;

        const Node& from_node();
        const Node& to_node();

        bool operator == (const Edge& rhs);
        bool operator != (const Edge& rhs);
        bool operator < (const Edge& rhs);
      private:
        Node from_node_, to_node_;
    };

    class DirectedGraph {
      public:
        DirectedGraph();
        DirectedGraph(const DirectedGraph& rhs);
        DirectedGraph& operator = (const DirectedGraph& rhs);
        virtual ~Edge() = default;

        //Methods for reading and writing the data of the graph from and to a stream
        //The input and output must respect the same format:
        // -the first line contains the number of nodes (N) and the number of edges (M) in the graph
        // -each of the following M lines contains two integers between 0 and N-1 describing an edge
        //          the first number representing the source of the edge, and the second one, the destination.
        //          no two edges can be identical and there must be no self-loops.
        friend std::istream& operator >> (std::istream& in, DirectedGraph& graph);
        friend std::ostream& operator << (std::ostream& out, DirectedGraph& graph);

        int node_count();
        int edge_count();

        //returns a Vector containing the nodes in the order that they were accessed during the bfs
        util::Vector< Node > breadth_first_search(int source_id = 0);
        //outputs the above Vector
        void output_breadth_first_search(std::ostream& out, int source_id = 0);

        //returns a Vector containing the nodes in the order that they were accessed during the dfs
        util::Vector< Node > depth_first_search(int source_id = 0);
        //outputs the above Vector
        void output_depth_first_search(std::ostream& out, int source_id = 0);

        //returns a matrix where (i, j) is true iff there is a path from i to j
        util::Vector< util::Vector< bool > > get_path_matrix();
        //outputs the above matrix
        void output_path_matrix(std::ostream& out);

        //returns the list of scc as lists of Nodes
        util::Vector< util::Vector< Node > > get_strongly_connected_components();
        //outputs the above list
        void output_strongly_connected_components(std::ostream& out);


      private:
        int node_count_, edge_count_;
        util::Vector< Node > nodes_;
    };
}

#endif //DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_H

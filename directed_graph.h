//
// Created by Bogdan Iordache on 3/6/2018.
//

#ifndef DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_H
#define DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_H

#include <iostream>
#include <algorithm>
#include "util_stack.h"
#include "util_vector.h"
#include "directed_graph_exceptions.h"

namespace dgraph {
    class Node {
      public:
        explicit Node(int id = -1);
        Node(const Node& rhs);
        Node& operator = (const Node& rhs);
        virtual ~Node();

        int get_id() const;
        void set_id(int id);

        void add_direct_successor(Node* node);
        void add_direct_predecessor(Node* node);

        const util::Vector< Node* >& get_direct_successors() const;
        const util::Vector< Node* >& get_direct_predecessors() const;

        int get_in_degree() const;
        int get_out_degree() const;

        bool operator == (const Node& rhs);
        bool operator != (const Node& rhs);
        bool operator < (const Node& rhs);
      private:
        int id_;
        util::Vector< Node* > direct_successors_;
        util::Vector< Node* > direct_predecessors_;
    };

    class Edge {
      public:
        explicit Edge(int from_node_id = -1, int to_node_id = -1);
        Edge(const Edge& rhs);
        Edge& operator = (const Edge& rhs);
        virtual ~Edge();

        int from_node_id() const;
        int to_node_id() const;

        bool operator == (const Edge& rhs);
        bool operator != (const Edge& rhs);
        bool operator < (const Edge& rhs);
      private:
        int from_node_id_, to_node_id_;
    };

    class DirectedGraph {
      public:
        DirectedGraph();
        DirectedGraph(const DirectedGraph& rhs);
        DirectedGraph& operator = (const DirectedGraph& rhs);
        virtual ~DirectedGraph();

        //Methods for reading and writing the data of the graph from and to a stream
        //The input and output must respect the same format:
        // -the first line contains the number of nodes (N) and the number of edges (M) in the graph
        // -each of the following M lines contains two integers between 0 and N-1 describing an edge
        //          the first number representing the source of the edge, and the second one, the destination.
        //          no two edges can be identical and there must be no self-loops.
        friend std::istream& operator >> (std::istream& in, DirectedGraph& graph);
        friend std::ostream& operator << (std::ostream& out, DirectedGraph& graph);

        int node_count() const;
        int edge_count() const;

        //returns a Vector containing the nodes in the order that they were accessed during the bfs
        util::Vector< Node > breadth_first_search(int source_id = 0) const;
        //outputs the above Vector
        void output_breadth_first_search(std::ostream& out, int source_id = 0) const;

        //returns a Vector containing the nodes in the order that they were accessed during the dfs
        util::Vector< Node > depth_first_search(int source_id = 0) const;
        //outputs the above Vector
        void output_depth_first_search(std::ostream& out, int source_id = 0) const;

        //returns a matrix where (i, j) is true iff there is a path from i to j
        util::Vector< util::Vector< bool > > get_path_matrix() const;
        //outputs the above matrix
        void output_path_matrix(std::ostream& out) const;

        //returns the list of scc as lists of Nodes
        util::Vector< util::Vector< Node > > get_strongly_connected_components() const;
        //outputs the above list
        void output_strongly_connected_components(std::ostream& out) const;

        //method that returns true if the graph is strongly connected
        bool is_strongly_connected() const;

        //method that returns true if the graph has no cycles
        bool is_acyclic() const;

        //method that returns a Vector containing the nodes in topological order
        util::Vector< Node > topological_sort() const;
        //outputs the above Vector
        void output_topological_sort(std::ostream& out) const;

      private:
        int node_count_, edge_count_;
        util::Vector< Node > nodes_;

        void add_edge(int from, int to);
    };
}

#endif //DIRECTEDGRAPHHANDLER_DIRECTED_GRAPH_H

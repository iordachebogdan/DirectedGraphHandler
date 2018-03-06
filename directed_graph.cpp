//
// Created by Bogdan Iordache on 3/6/2018.
//

#include "directed_graph.h"

namespace dgraph {

    //implementation of Node's methods
    Node::Node(int id) : id_(id) {};
    Node::Node(const Node &rhs) {
        id_ = rhs.id_;
        direct_predecessors_ = rhs.direct_predecessors_;
        direct_successors_ = rhs.direct_successors_;
    }
    Node& Node::operator=(const Node &rhs) {
        id_ = rhs.id_;
        direct_predecessors_ = rhs.direct_predecessors_;
        direct_successors_ = rhs.direct_successors_;
        return (*this);
    }
    Node::~Node() {}

    int Node::get_id() const { return id_; }
    void Node::set_id(int id) { id_ = id; }

    void Node::add_direct_successor(Node* node) {
        direct_successors_.push_back(node);
    }
    void Node::add_direct_predecessor(Node* node) {
        direct_predecessors_.push_back(node);
    }

    const util::Vector< Node* >& Node::get_direct_predecessors() const {
        return direct_predecessors_;
    }
    const util::Vector< Node* >& Node::get_direct_successors() const {
        return direct_successors_;
    }

    int Node::get_in_degree() const {
        return (int)direct_predecessors_.size();
    }
    int Node::get_out_degree() const {
        return (int)direct_successors_.size();
    }

    bool Node::operator == (const Node &rhs) { return id_ == rhs.id_; };
    bool Node::operator != (const Node &rhs) { return id_ != rhs.id_; };
    bool Node::operator < (const Node &rhs) { return id_ < rhs.id_; };

    //implementation of Edge's methods
    Edge::Edge(int from_node_id, int to_node_id) :
            from_node_id_(from_node_id), to_node_id_(to_node_id) {}
    Edge::Edge(const Edge &rhs) {
        from_node_id_ = rhs.from_node_id_;
        to_node_id_ = rhs.to_node_id_;
    }
    Edge& Edge::operator=(const Edge &rhs) {
        from_node_id_ = rhs.from_node_id_;
        to_node_id_ = rhs.to_node_id_;
        return (*this);
    }
    Edge::~Edge() {}

    int Edge::from_node_id() const {
        return from_node_id_;
    }
    int Edge::to_node_id() const {
        return to_node_id_;
    }

    bool Edge::operator == (const Edge &rhs) {
        return (to_node_id_ == rhs.to_node_id_ && from_node_id_ == rhs.from_node_id_);
    }
    bool Edge::operator != (const Edge &rhs) {
        return (to_node_id_ != rhs.to_node_id_ || from_node_id_ != rhs.from_node_id_);
    }
    bool Edge::operator < (const Edge &rhs) {
        return (from_node_id_  < rhs.from_node_id_ ||
                (from_node_id_ == rhs.from_node_id_ && to_node_id_ < rhs.to_node_id_) );
    }

    //implementation of DirectedGraph's methods
    DirectedGraph::DirectedGraph() : node_count_(0), edge_count_(0), nodes_(0) {}
    DirectedGraph::DirectedGraph(const DirectedGraph &rhs) {
        (*this) = rhs;
    }
    DirectedGraph& DirectedGraph::operator=(const DirectedGraph &rhs) {
        node_count_ = rhs.node_count_;
        edge_count_ = rhs.edge_count_;
        util::Vector<Edge> edges; //get all edges from rhs
        for (int i = 0; i < node_count_; ++i) {
            util::Vector<Node*> current_successors = rhs.nodes_[i].get_direct_successors();
            for (util::Vector<Node*>::iterator it = current_successors.begin();
                 it != current_successors.end(); ++it)
                edges.push_back(Edge(rhs.nodes_[i].get_id(), (*it)->get_id()));
        }
        nodes_ = util::Vector<Node>(node_count_);
        for (int i = 0; i < node_count_; ++i)
            nodes_[i].set_id(i);
        for (int i = 0; i < (int)edges.size(); ++i)
            add_edge(edges[i].from_node_id(), edges[i].to_node_id());
        return (*this);
    }

    DirectedGraph::~DirectedGraph() {};

    std::istream& operator >> (std::istream &in, DirectedGraph &graph) {
        if (!(in >> graph.node_count_)) throw bad_dgraph_config();
        if (!(in >> graph.edge_count_)) throw bad_dgraph_config();
        if (graph.node_count_ < 0 || graph.edge_count_ < 0) throw bad_dgraph_config();

        graph.nodes_ = util::Vector<Node>(graph.node_count_);
        for (int i = 0; i < graph.node_count_; ++i)
            graph.nodes_[i].set_id(i);

        util::Vector< Edge > edges;
        for (int i = 0; i < graph.edge_count_; ++i) {
            int from, to;
            //test configuration
            if (!(in >> from)) throw bad_dgraph_config();
            if (!(in >> to)) throw bad_dgraph_config();
            if (0 > from || from >= graph.node_count_ ||
                    0 > to || to >= graph.node_count_)
                throw bad_dgraph_config();
            //test for self-loops
            if (from == to)
                throw bad_dgraph_config();
            edges.push_back(Edge(from, to));
        }

        //test if there are any edge duplicates
        std::sort(edges.begin(), edges.end());
        for (int i = 0; i < (int)edges.size() - 1; ++i)
            if (edges[i] == edges[i + 1])
                throw bad_dgraph_config();

        for (int i = 0; i < (int)edges.size(); ++i)
            graph.add_edge(edges[i].from_node_id(), edges[i].to_node_id());

        return in;
    }

    std::ostream& operator << (std::ostream& out, DirectedGraph& graph) {
        out << graph.node_count_ << " " << graph.edge_count_ << "\n";
        for (int i = 0; i < graph.node_count_; ++i) {
            util::Vector<Node*> current_node_successors =
                    graph.nodes_[i].get_direct_successors();
            for (util::Vector<Node*>::iterator it = current_node_successors.begin();
                    it != current_node_successors.end(); ++it)
                out << i << " " << (*it)->get_id();
        }
    }

    int DirectedGraph::node_count() const { return node_count_; }
    int DirectedGraph::edge_count() const { return edge_count_; }

    const Node* DirectedGraph::get_node_by_id(int id) const {
        return &nodes_[id];
    }

    void DirectedGraph::add_edge(int from, int to) {
        nodes_[from].add_direct_successor(&nodes_[to]);
        nodes_[to].add_direct_predecessor(&nodes_[from]);
    }

    util::Vector< const Node* > DirectedGraph::breadth_first_search(int source_id) const {
        if (source_id < 0 || source_id >= node_count_)
            throw std::out_of_range("Invalid node id!");
        util::Vector< const Node* > res;
        bfs(source_id, res);
        return res;
    }

    void DirectedGraph::output_breadth_first_search(std::ostream &out, int source_id) const {
        util::Vector< const Node* > res = breadth_first_search(source_id);
        for (util::Vector< const Node* >::iterator it = res.begin(); it != res.end(); ++it)
            out << (*it)->get_id() << ' ';
        out << '\n';
    }

    void DirectedGraph::bfs(int source_id, util::Vector<const Node *> &res) const {
        //implementation of BFS as explained here:
        //https://en.wikipedia.org/wiki/Breadth-first_search
        util::Vector< bool > visited(node_count_, false); visited[source_id] = true;
        util::Queue< int > queue; queue.push(source_id);
        res.clear();

        while (!queue.empty()) {
            int current_id = queue.front();
            queue.pop();
            res.push_back(&nodes_[current_id]);

            util::Vector< Node* > current_successors = nodes_[current_id].get_direct_successors();
            for (util::Vector< Node* >::iterator it = current_successors.begin();
                    it != current_successors.end(); ++it)
                if (!visited[(*it)->get_id()]) {
                    visited[(*it)->get_id()] = true;
                    queue.push((*it)->get_id());
                }
        }
    }

    util::Vector< const Node* > DirectedGraph::depth_first_search(int source_id) const {
        util::Vector< const Node* > res;
        util::Vector< bool > visited(node_count_, false);
        dfs(source_id, res, visited);
        return res;
    }

    void DirectedGraph::output_depth_first_search(std::ostream &out, int source_id) const {
        util::Vector< const Node* > res = depth_first_search(source_id);
        for (util::Vector< const Node* >::iterator it = res.begin(); it != res.end(); ++it)
            out << (*it)->get_id() << ' ';
        out << '\n';
    }

    void DirectedGraph::dfs(int source_id, util::Vector<const Node *> &res,
                            util::Vector<bool> &visited) const {
        //implementation of BFS as explained here:
        //https://en.wikipedia.org/wiki/Depth-first_search
        visited[source_id] = true;
        res.push_back(&nodes_[source_id]);
        util::Vector< Node* > current_successors = nodes_[source_id].get_direct_successors();
        for (util::Vector< Node* >::iterator it = current_successors.begin();
                it != current_successors.end(); ++it)
            if (!visited[(*it)->get_id()])
                dfs((*it)->get_id(), res, visited);
    }

}

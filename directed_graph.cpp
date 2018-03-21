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
        clear_nodes();
        node_count_ = rhs.node_count_;
        edge_count_ = rhs.edge_count_;
        util::Vector<Edge> edges; //get all edges from rhs
        for (int i = 0; i < node_count_; ++i) {
            util::Vector<Node*> current_successors = rhs.nodes_[i]->get_direct_successors();
            for (util::Vector<Node*>::iterator it = current_successors.begin();
                 it != current_successors.end(); ++it)
                edges.push_back(Edge(rhs.nodes_[i]->get_id(), (*it)->get_id()));
        }
        nodes_ = util::Vector<Node*>(node_count_, NULL);
        for (int i = 0; i < node_count_; ++i)
            nodes_[i] = new Node(i);
        for (int i = 0; i < (int)edges.size(); ++i)
            add_edge(edges[i].from_node_id(), edges[i].to_node_id());
        return (*this);
    }

    DirectedGraph::~DirectedGraph() {
        clear_nodes();
    };

    std::istream& operator >> (std::istream &in, DirectedGraph &graph) {
        graph.clear_nodes();
        if (!(in >> graph.node_count_)) throw bad_dgraph_config();
        if (!(in >> graph.edge_count_)) throw bad_dgraph_config();
        if (graph.node_count_ < 0 || graph.edge_count_ < 0) throw bad_dgraph_config();

        graph.nodes_ = util::Vector<Node*>(graph.node_count_);
        for (int i = 0; i < graph.node_count_; ++i)
            graph.nodes_[i] = new Node(i);

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

    std::ostream& operator << (std::ostream& out, const DirectedGraph& graph) {
        out << graph.node_count_ << " " << graph.edge_count_ << "\n";
        for (int i = 0; i < graph.node_count_; ++i) {
            util::Vector<Node*> current_node_successors =
                    graph.nodes_[i]->get_direct_successors();
            for (util::Vector<Node*>::iterator it = current_node_successors.begin();
                    it != current_node_successors.end(); ++it)
                out << i << " " << (*it)->get_id() << '\n';
        }
        return out;
    }

    int DirectedGraph::node_count() const { return node_count_; }
    int DirectedGraph::edge_count() const { return edge_count_; }

    const Node* DirectedGraph::get_node_by_id(int id) const {
        return nodes_[id];
    }

    void DirectedGraph::add_edge(int from, int to) {
        nodes_[from]->add_direct_successor(nodes_[to]);
        nodes_[to]->add_direct_predecessor(nodes_[from]);
    }

    void DirectedGraph::clear_nodes() {
        for (int i = 0; i < node_count_; ++i)
            if (nodes_[i] != NULL)
                delete nodes_[i];
        nodes_.clear();
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
            res.push_back(nodes_[current_id]);

            util::Vector< Node* > current_successors = nodes_[current_id]->get_direct_successors();
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
        //implementation of DFS as explained here:
        //https://en.wikipedia.org/wiki/Depth-first_search
        visited[source_id] = true;
        res.push_back(nodes_[source_id]);
        util::Vector< Node* > current_successors = nodes_[source_id]->get_direct_successors();
        for (util::Vector< Node* >::iterator it = current_successors.begin();
                it != current_successors.end(); ++it)
            if (!visited[(*it)->get_id()])
                dfs((*it)->get_id(), res, visited);
    }

    util::Vector< util::Vector< bool > > DirectedGraph::get_path_matrix() const {
        //does a Roy-Floyd-like approach of finding the path matrix
        util::Vector< util::Vector< bool > > res(node_count_, util::Vector< bool >(node_count_, false));
        for (int i = 0; i < node_count_; ++i) {
            res[i][i] = true; //every node is accessible from itself
            util::Vector< Node* > current_successors = nodes_[i]->get_direct_successors();
            for (util::Vector< Node* >::iterator it = current_successors.begin();
                    it != current_successors.end(); ++it)
                res[i][(*it)->get_id()] = true; //for each edge mark the corresponding path

        }

        for (int interm = 0; interm < node_count_; ++interm)
            for (int first = 0; first < node_count_; ++first)
                if (first != interm)
                    for (int last = 0; last < node_count_; ++last)
                        if (last != first && last != interm)
                            res[first][last] |= (res[first][interm] && res[interm][last]);

        return res;
    }

    void DirectedGraph::output_path_matrix(std::ostream &out) const {
        util::Vector< util::Vector< bool > > res = get_path_matrix();
        for (int i = 0; i < node_count_; ++i, out << '\n')
            for (int j = 0; j < node_count_; ++j)
                out << res[i][j];
    }

    util::Vector< util::Vector< const Node* > > DirectedGraph::get_strongly_connected_components() const {
        util::Vector< util::Vector< const Node* > > scc;
        int curr_idx = 0;
        util::Vector<int> idx(node_count_, 0);
        util::Vector<int> lowlink(node_count_, 0);
        util::Stack<int> stack;
        util::Vector<bool> in_stack(node_count_, false);

        for (int i = 0; i < node_count_; ++i)
            if (idx[i] == 0)
                dfs_tarjan(i, curr_idx, idx, lowlink, stack, in_stack, scc);

        return scc;
    }

    void DirectedGraph::output_strongly_connected_components(std::ostream &out) const {
        util::Vector< util::Vector< const Node* > > scc = get_strongly_connected_components();
        out << scc.size() << '\n';
        for (int i = 0; i < (int)scc.size(); ++i, out << '\n')
            for (int j = 0; j < (int)scc[i].size(); ++j)
                out << scc[i][j]->get_id() << ' ';
    }

    void DirectedGraph::dfs_tarjan(int node_id, int &curr_idx, util::Vector<int> &idx, util::Vector<int> &lowlink,
                                   util::Stack<int> &stack, util::Vector<bool> &in_stack,
                                   util::Vector<util::Vector<const Node *> > &scc) const {
        //implementation for obtaining the strongly connected components of a graph
        //using Tarjan's algorithm:
        // https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
        curr_idx++;
        idx[node_id] = lowlink[node_id] = curr_idx;
        stack.push(node_id);
        in_stack[node_id] = true;

        util::Vector< Node* > curr_successors = nodes_[node_id]->get_direct_successors();
        for (util::Vector< Node* >::iterator it = curr_successors.begin();
                it != curr_successors.end(); ++it) {
            if (idx[(*it)->get_id()] == 0) {
                dfs_tarjan((*it)->get_id(), curr_idx, idx, lowlink, stack, in_stack, scc);
                lowlink[node_id] = std::min(lowlink[node_id], lowlink[(*it)->get_id()]);
            }
            else if (in_stack[(*it)->get_id()])
                lowlink[node_id] = std::min(lowlink[node_id], lowlink[(*it)->get_id()]);
        }

        if (idx[node_id] == lowlink[node_id]) {
            scc.push_back(util::Vector<const Node*>());
            int curr;
            do {
                curr = stack.top();
                scc.back().push_back(nodes_[curr]);
                stack.pop();
                in_stack[curr] = false;
            } while (curr != node_id);
        }
    }

    bool DirectedGraph::is_strongly_connected() const {
        util::Vector< util::Vector< const Node* > > scc = get_strongly_connected_components();
        //in a strongly connected graph there is only one strongly connected comp
        return ((int)scc.size() == 1);
    }

    bool DirectedGraph::is_acyclic() const {
        util::Vector< util::Vector< const Node* > > scc = get_strongly_connected_components();
        //in a acyclic graph the no of nodes is equal to the no of scc
        return ((int)scc.size() == node_count_);
    }

    util::Vector< const Node* > DirectedGraph::topological_sort() const {
        if (!is_acyclic())
            throw bad_top_sort();

        util::Vector< const Node* > res;
        util::Vector< bool > visited(node_count_, false);
        for (int i = 0; i < node_count_; ++i)
            if (!visited[i] && nodes_[i]->get_in_degree() == 0)
                dfs_sort_top(i, visited, res);
        std::reverse(res.begin(), res.end());
        return res;
    }

    void DirectedGraph::output_topological_sort(std::ostream &out) const {
        util::Vector< const Node* > res = topological_sort();
        for (util::Vector< const Node* >::iterator it = res.begin(); it != res.end(); ++it)
            out << (*it)->get_id() << ' ';
        out << '\n';
    }

    void DirectedGraph::dfs_sort_top(int node_id, util::Vector<bool> &visited,
                                     util::Vector<const Node *> &res) const {
        //with a simple dfs in this graph we can obtain the reversed topological sort
        //by adding each node at the end of its corresponding function call
        visited[node_id] = true;
        util::Vector< Node* > current_successors = nodes_[node_id]->get_direct_successors();
        for (util::Vector< Node* >::iterator it = current_successors.begin();
             it != current_successors.end(); ++it)
            if (!visited[(*it)->get_id()])
                dfs_sort_top((*it)->get_id(), visited, res);
        res.push_back(nodes_[node_id]);
    }

    DirectedGraph DirectedGraph::operator+(const DirectedGraph& rhs) const {
        if (rhs.node_count_ != node_count_)
            throw bad_dgraph_config();
        util::Vector< Edge > edges;

        for (int node = 0; node < node_count_; ++node) {
            util::Vector< Node* > current_successors;
            current_successors = nodes_[node]->get_direct_successors();
            for (util::Vector< Node* >::iterator it = current_successors.begin();
                 it != current_successors.end(); ++it)
                edges.push_back(Edge(node, (*it)->get_id()));

            current_successors = rhs.nodes_[node]->get_direct_successors();
            for (util::Vector< Node* >::iterator it = current_successors.begin();
                 it != current_successors.end(); ++it)
                edges.push_back(Edge(node, (*it)->get_id()));
        }

        DirectedGraph res;
        int res_edge_count = 0;
        res.node_count_ = node_count_;
        for (int i = 0; i < node_count_; ++i)
            res.nodes_.push_back(new Node(i));

        std::sort(edges.begin(), edges.end());
        for (int i = 0; i < (int)edges.size(); ++i)
            if (i == 0 || edges[i] != edges[i - 1]) {
                res.add_edge(edges[i].from_node_id(), edges[i].to_node_id());
                res_edge_count++;
            }
        res.edge_count_ = res_edge_count;

        return res;
    }

}

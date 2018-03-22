#include <iostream>
#include <fstream>
#include <string>
#include "directed_graph.h"

class Tester {
  public:
    Tester() {}
    Tester(Tester& rhs) {}
    Tester& operator = (const Tester& rhs) { return (*this); }
    virtual ~Tester() {}

    void load_test(std::string path = "") {
        if (path == "")
            std::cin >> directed_graph_ >> directed_graph_2_;
        else {
            std::ifstream fin(path.data());
            fin >> directed_graph_ >> directed_graph_2_;
            fin.close();
        }
    }

    void topological_sort(std::string path = "") {
        if (path == "")
            directed_graph_.output_topological_sort(std::cout);
        else {
            std::ofstream fout(path.data());
            directed_graph_.output_topological_sort(fout);
            fout << '\n';
            fout.close();
        }
    }

    void print_graph(std::string path = "") {
        if (path == "")
            std::cout << directed_graph_ << '\n';
        else {
            std::ofstream fout(path.data());
            fout << directed_graph_ << '\n';
            fout.close();
        }
    }

    void bfs(std::string path = "") {
        if (path == "")
            directed_graph_.output_breadth_first_search(std::cout);
        else {
            std::ofstream fout(path.data());
            directed_graph_.output_breadth_first_search(fout);
            fout << '\n';
            fout.close();
        }
    }

    void dfs(std::string path = "") {
        if (path == "")
            directed_graph_.output_depth_first_search(std::cout);
        else {
            std::ofstream fout(path.data());
            directed_graph_.output_depth_first_search(fout);
            fout << '\n';
            fout.close();
        }
    }

    void scc(std::string path = "") {
        if (path == "")
            directed_graph_.output_strongly_connected_components(std::cout);
        else {
            std::ofstream fout(path.data());
            directed_graph_.output_strongly_connected_components(fout);
            fout << '\n';
            fout.close();
        }
    }

    void path_matrix(std::string path = "") {
        if (path == "")
            directed_graph_.output_path_matrix(std::cout);
        else {
            std::ofstream fout(path.data());
            directed_graph_.output_path_matrix(fout);
            fout << '\n';
            fout.close();
        }
    }

    void graph_reunion(std::string path = "") {
        if (path == "")
            std::cout << directed_graph_ + directed_graph_2_ << '\n';
        else {
            std::ofstream fout(path.data());
            fout << directed_graph_ + directed_graph_2_ << '\n';
            fout.close();
        }
    }

    void add_new_node(std::string path) {
        if (path == "")
            directed_graph_.add_new_node(std::cin);
        else {
            std::ifstream fin(path.data());
            directed_graph_.add_new_node(fin);
            fin.close();
        }

    }

  private:
    dgraph::DirectedGraph directed_graph_, directed_graph_2_;
};

int main() {
    Tester tester;
    tester.load_test("data.in");
    //tester.topological_sort("topological_sort.out");
    tester.bfs("bfs.out");
    tester.dfs("dfs.out");
    tester.scc("scc.out");
    tester.path_matrix("path_matrix.out");
    tester.graph_reunion("graph_reunion.out");
    tester.add_new_node("");
    tester.print_graph("data.out");

    return 0;
}